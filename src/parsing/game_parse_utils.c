/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_parse_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:53:38 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/23 14:49:52 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief 
/// @param map
void	find_player_pos(t_map_ctx *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (is_player_spawn(map->map[y][x]))
			{
				map->player_pos.x = x + 0.5;
				map->player_pos.y = y + 0.5;
				map->player_dir = map->map[y][x];
				return ;
			}
			x++;
		}
		y++;
	}
}

/// @brief Checks whether a character represents a player spawn point
/// @param c The character to check
/// @return 1 if the character is 'N', 'S', 'E', or 'W', 0 otherwise
int	is_player_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/// @brief Determines whether a line is part of the map section
/// (starts with map characters)
/// @param line The line to analyze
/// @return true if the line is considered part of the map
/// (starts with 1, 0, or spawn character), false otherwise
bool	is_map_line(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return (*line == '1' || *line == '0' || *line == 'N'
		|| *line == 'S' || *line == 'E' || *line == 'W');
}
