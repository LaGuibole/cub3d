/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_map_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:17:49 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/22 18:38:31 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_lines_after_map(char **lines, int y);

/// @brief Calculates the dimensions (width and height) of the map starting
/// from a given line
/// @param lines Array of strings representing all lines from the .cub file
/// @param start Index of the first line of the map
/// @param width Pointer to store the maximum width (longest line) of the map
/// @param height Pointer to store the total number of map lines
/// @return Always returns 1 (success)
// int	get_map_dimensions(char **lines, int start, int *width, int *height)
// {
// 	int	y;
// 	int	len;
// 	int	max_len;

// 	y = start;
// 	max_len = 0;
// 	while (lines[y] && lines[y][0] != '\0')
// 	{
// 		len = ft_strlen(lines[y]);
// 		if (len > max_len)
// 			max_len = len;
// 		y++;
// 	}
// 	*width = max_len;
// 	*height = y - start;
// 	return (1);
// }

// int	get_map_dimensions(char **lines, int start, int *width, int *height)
// {
// 	int	y = start;
// 	int	len;
// 	int	max_len = 0;
// 	int	valid_line_found = 0;

// 	while (lines[y])
// 	{
// 		if (is_map_line(lines[y]))
// 		{
// 			len = ft_strlen(lines[y]);
// 			if (len > max_len)
// 				max_len = len;
// 			(*height)++;
// 			valid_line_found = 1;
// 		}
// 		else if (valid_line_found && lines[y][0] != '\0')
// 		{
// 			break;
// 		}
// 		y++;
// 	}
// 	*width = max_len;
// 	return (1);
// }


// int	get_map_dimensions(char **lines, int start, int *width, int *height)
// {
// 	int	y = start;
// 	int	len;
// 	int	max_len = 0;

// 	*height = 0;
// 	while (lines[y])
// 	{
// 		if (is_map_line(lines[y]))
// 		{
// 			len = ft_strlen(lines[y]);
// 			if (len > max_len)
// 				max_len = len;
// 			(*height)++;
// 		}
// 		y++;
// 	}
// 	*width = max_len;
// 	return (1);
// }

int	validate_map_block(char **lines, int start, int *width, int *height)
{
	int	y;
	int	len;
	int	max_len;

	y = start;
	max_len = 0;
	*height = 0;
	while (lines[y] && is_map_line(lines[y]))
	{
		len = ft_strlen(lines[y]);
		if (len > max_len)
			max_len = len;
		(*height)++;
		y++;
	}
	*width = max_len - 1;
	return (check_lines_after_map(lines, y));
}

static int	check_lines_after_map(char **lines, int y)
{
	while (lines[y])
	{
		if (lines[y][0] != '\0')
		{
			fd_printf(STDERR_FILENO, "Error: unexpected content after map at line %d\n", y + 1);
			return (RET_ERR);
		}
		y++;
	}
	return (RET_OK);
}



