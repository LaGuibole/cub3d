/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_map_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:17:49 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/22 13:53:35 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief Calculates the dimensions (width and height) of the map starting
/// from a given line
/// @param lines Array of strings representing all lines from the .cub file
/// @param start Index of the first line of the map
/// @param width Pointer to store the maximum width (longest line) of the map
/// @param height Pointer to store the total number of map lines
/// @return Always returns 1 (success)
int	get_map_dimensions(char **lines, int start, int *width, int *height)
{
	int	y;
	int	len;
	int	max_len;

	y = start;
	max_len = 0;
	while (lines[y] && lines[y][0] != '\0')
	{
		len = ft_strlen(lines[y]);
		if (len > max_len)
			max_len = len;
		y++;
	}
	*width = max_len;
	*height = y - start;
	return (1);
}
