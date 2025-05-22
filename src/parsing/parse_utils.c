/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:00:19 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/22 13:54:11 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief Checks if a line corresponds to a configuration directive
/// (texture or color)
/// @param line The line to check from the .cub file
/// @return true if the line is a configuration line (NO, SO, WE, EA, F, or C),
/// false otherwise
bool	is_config_line(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0);
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

/// @brief Checks whether a character represents a player spawn point
/// @param c The character to check
/// @return 1 if the character is 'N', 'S', 'E', or 'W', 0 otherwise
int	is_player_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
