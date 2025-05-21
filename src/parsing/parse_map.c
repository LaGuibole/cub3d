/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:00:53 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/21 17:45:27 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	sanitize_map(char **lines)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (lines[i])
	{
		tmp = ft_strchr(lines[i], '\n');
		if (tmp)
			*tmp = '\0';
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == '\t')
				lines[i][j] = ' ';
			j++;
		}
		++i;
	}
}

int	find_map_start_index(char **lines)
{
	int		i;

	i = 0;
	while (lines[i])
	{
		if (lines[i][0] != '\0' && !is_config_line(lines[i])
			&& is_map_line(lines[i]))
			return (i);
		i++;
	}
	return (RET_NEG_ERR);
}

char	**extract_map(char **lines, int start)
{
	int		i;
	int		count;
	char	**map;

	i = start;
	count = 0;
	while (lines[i] && lines[start][0] != '\0')
	{
		count++;
		i++;
	}
	map = malloc(sizeof(char *) * (count + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (lines[start] && lines[start][0] != '\0')
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
	get_map_dimensions(lines, start, &cfg->map_ctx.width, &cfg->map_ctx.height);
	if (start == RET_NEG_ERR)
		return (fd_printf(STDERR_FILENO, "No Valid map was found\n"), RET_ERR);
	map = extract_map(lines, start);
	if (!map)
		return (fd_printf(STDERR_FILENO, "Map allocation failed\n"), RET_ERR);
	cfg->map_ctx.map = map;
	check_map_char(map);
	if (!check_map_closed(cfg))
		return (RET_ERR);
	return (RET_OK);
}
