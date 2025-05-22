/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_map_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:17:49 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/22 19:55:29 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_lines_after_map(char **lines, int y);

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
			fd_printf(STDERR_FILENO,
				"Error: unexpected content after map at line %d\n", y + 1);
			return (RET_ERR);
		}
		y++;
	}
	return (RET_OK);
}
