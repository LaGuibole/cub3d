/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_chars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:42:55 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/22 13:17:44 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_char(char c);
static int	count_player_spawn(char c);

/// @brief
/// @param map
/// @return
int	check_map_char(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!is_valid_char(map[y][x]))
			{
				fd_printf(STDERR_FILENO,
					"Error : invalid char : '%c' at y: %d, x: %d\n",
					map[y][x], y + 1, x + 1);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

/// @brief
/// @param c
/// @return
static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == ' ');
}

/// @brief
/// @param c
/// @return
static int	count_player_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/// @brief
/// @param map
/// @return
int	check_player_spawn_count(char **map)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (count_player_spawn(map[y][x]))
				count++;
			x++;
		}
		y++;
	}
	if (count != 1)
	{
		fd_printf(STDERR_FILENO,
			"Error : invalid number of player spawns: %d \
			(should be exactly 1)\n", count);
		return (0);
	}
	return (1);
}
