/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:59:30 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/20 15:35:06 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_rgb_char(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_isdigit(line[i]) && line[i] != ',')
			return (fd_printf(STDERR_FILENO, "rgb contains letters\n"), RET_ERR);
		i++;
	}
	return (RET_OK);
}

static int	*get_rgb_tab(char *line)
{
	char		**split;
	int			*color;

	if (validate_rgb_char(line) != RET_OK)
		return (NULL);
	split = ft_split(line, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (free_double_tab(split), fd_printf(STDERR_FILENO, "Wrong RGB format\n"), NULL);
	color = malloc(sizeof(int) * 3);
	if (!color)
		return(free_double_tab(split), fd_printf(STDERR_FILENO, "Malloc failed\n"), NULL);
	color[0] = ft_atoi(split[0]);
	color[1] = ft_atoi(split[1]);
	color[2] = ft_atoi(split[2]);
	free_double_tab(split);
	return (color);
}

static int	validate_rgb_int(int *color)
{
	if (!color)
		return (RET_ERR);
	if ((color[0] < 0 || color[0] > 255)
		|| (color[1] < 0 || color[1] > 255)
		|| (color[2] < 0 || color[2] > 255))
		return (fd_printf(STDERR_FILENO, "not a valid rgb value\n"), RET_ERR);
	return (RET_OK);
}

int	parse_rgb_values(char *line, int *dest)
{
	int *rgb;

	rgb = get_rgb_tab(line);
	if (!rgb)
		return (fd_printf(STDERR_FILENO, "RGB parsing failed\n"), RET_ERR);
	if (validate_rgb_int(rgb) != RET_OK)
		return (free(rgb), RET_ERR);
	dest[0] = rgb[0];
	dest[1] = rgb[1];
	dest[2] = rgb[2];
	free(rgb);
	return (RET_OK);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
