/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:00:53 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/20 18:06:04 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_map_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '0' && *line != '1'
			&& *line != 'N' && *line != 'S'
			&& *line != 'E' && *line != 'W')
			return (false);
		line++;
	}
	return (true);
}

static void	sanitize_map(char **lines)
{
	char	*tmp;
	int		i;

	i = 0;
	while (lines[i])
	{
		tmp = ft_strchr(lines[i], '\n');
		if (tmp)
			*tmp = '\0';
		++i;
	}
}

int	find_map_start_index(char **lines)
{
	int		i;

	i = 0;
	while (lines[i])
	{
		if (lines[i][0] != '\0' && is_map_line(lines[i]))
			return (i);
		i++;
	}
	return (RET_NEG_ERR);
}

char	**extract_map(char **lines, int start)
{
	int		i;
	int		count;
	char 	**map;


	i = start;
	count = 0;
	while (lines[i] && is_map_line(lines[i]))
	{
		count++;
		i++;
	}
	map = malloc(sizeof(char *) * (count + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (lines[start] && is_map_line(lines[start]))
		map[i++] = ft_strdup(lines[start++]);
	map[i] = NULL;
	return (map);
}

int	parse_map(t_config *cfg, char **lines)
{
	int		start;
	char	**map;

	sanitize_map(lines);
	start = find_map_start_index(lines);
	if (start == RET_NEG_ERR)
		return (fd_printf(STDERR_FILENO, "No Valid map was found\n"), RET_ERR);
	map = extract_map(lines, start);
	if (!map)
		return (fd_printf(STDERR_FILENO, "Map allocation failed\n"), RET_ERR);
	cfg->map = map;
	//free map
	return (RET_OK);
}
