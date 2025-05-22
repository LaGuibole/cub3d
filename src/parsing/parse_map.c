/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:00:53 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/22 16:29:34 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief Cleans up the map lines by removing newline characters and
///			Replace spaces with tab
/// @param lines An array of strings representing lines from the .cub file
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

/// @brief Finds the index of the first line that marks the beginning of map
/// @param lines An array of strings representing lines from the .cub file
/// @return Index of the first map line, or RET_NEG_ERR if not found
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

/// @brief Extracts the map lines from the .cub file starting at a given index
/// @param lines Array of all lines from the .cub file
/// @param start Index of the first line of the map
/// @return A newly allocated array of strings containig only the map
/// lines, or NULL on failure
// char	**extract_map(char **lines, int start)
// {
// 	int		i;
// 	int		count;
// 	char	**map;

// 	i = start;
// 	count = 0;
// 	while (lines[i] && lines[start][0] != '\0')
// 	{
// 		count++;
// 		i++;
// 	}
// 	map = malloc(sizeof(char *) * (count + 1));
// 	if (!map)
// 		return (NULL);
// 	i = 0;
// 	while (lines[start] && lines[start][0] != '\0')
// 		map[i++] = ft_strdup(lines[start++]);
// 	map[i] = NULL;
// 	return (map);
// }

// char	**extract_map(char **lines, int start, int height)
// {
// 	char	**map;
// 	int		i;
// 	int		y;

// 	map = malloc(sizeof(char *) * (height + 1));
// 	if (!map)
// 		return (NULL);
// 	i = 0;
// 	y = start;
// 	while (lines[y] && i < height)
// 	{
// 		if (is_map_line(lines[y]))
// 			map[i++] = ft_strdup(lines[y]);
// 		y++;
// 	}
// 	map[i] = NULL;
// 	return (map);
// }

char	**extract_map(char **lines, int start, int height)
{
	char	**map;
	int		i;
	int		y;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	i = 0;
	y = start;
	while (lines[y] && i < height)
	{
		if (is_map_line(lines[y]))
			map[i++] = ft_strdup(lines[y]);
		y++;
	}
	map[i] = NULL;
	return (map);
}



/// @brief Parses the map section from the .cub file, populates dimensions and
/// validates structure
/// @param cfg Pointer to the configuration structure to fill
/// @param lines Array of all lines from the .cub file
/// @return RET_OK on success, RET_ERR on failure
// int	parse_map(t_config *cfg, char **lines)
// {
// 	int		start;
// 	char	**map;

// 	start = find_map_start_index(lines);
// 	get_map_dimensions(lines, start, &cfg->map_ctx.width, &cfg->map_ctx.height);
// 	sanitize_map(lines);
// 	if (start == RET_NEG_ERR)
// 		return (fd_printf(STDERR_FILENO, "No Valid map was found\n"), RET_ERR);
// 	map = extract_map(lines, start);
// 	if (!map)
// 		return (fd_printf(STDERR_FILENO, "Map allocation failed\n"), RET_ERR);
// 	cfg->map_ctx.map = map;
// 	check_map_char(map);
// 	if (!check_map_closed(cfg))
// 		return (RET_ERR);
// 	return (RET_OK);
// }

// int	parse_map(t_config *cfg, char **lines)
// {
// 	int		start;
// 	char	**map;

// 	start = find_map_start_index(lines);
// 	if (start == RET_NEG_ERR)
// 		return (fd_printf(STDERR_FILENO, "No Valid map was found\n"), RET_ERR);

// 	if (!get_map_dimensions(lines, start, &cfg->map_ctx.width, &cfg->map_ctx.height))
// 		return (RET_ERR);

// 	map = extract_map(lines, start, cfg->map_ctx.height);
// 	if (!map)
// 		return (fd_printf(STDERR_FILENO, "Map allocation failed\n"), RET_ERR);

// 	sanitize_map(map);
// 	cfg->map_ctx.map = map;

// 	if (!check_map_char(map))
// 		return (RET_ERR);
// 	if (!check_map_closed(cfg))
// 		return (RET_ERR);
// 	return (RET_OK);
// }

int	parse_map(t_config *cfg, char **lines)
{
	int		start;
	char	**map;

	start = find_map_start_index(lines);
	if (start == RET_NEG_ERR)
		return (fd_printf(STDERR_FILENO, "No Valid map was found\n"), RET_ERR);
	if (validate_map_block(lines, start, &cfg->map_ctx.width, &cfg->map_ctx.height) == RET_ERR)
		return (RET_ERR);
	map = extract_map(lines, start, cfg->map_ctx.height);
	if (!map)
		return (fd_printf(STDERR_FILENO, "Map allocation failed\n"), RET_ERR);
	sanitize_map(map);
	cfg->map_ctx.map = map;
	if (!check_map_char(map))
		return (RET_ERR);
	if (!check_map_closed(cfg))
		return (RET_ERR);
	return (RET_OK);
}


