/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:59:30 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/22 13:55:06 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief Validates that teh RGB string only contains digits and commas
/// @param line The string to check (expected format "R,G,B")
/// @return RET_OK if valid, RET_ERR if the string contains invalid chars
static int	validate_rgb_char(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_isdigit(line[i]) && line[i] != ',')
			return (fd_printf(STDERR_FILENO,
					"rgb contains letters\n"), RET_ERR);
		i++;
	}
	return (RET_OK);
}

/// @brief Parses a comma-separated RGB string and returns an int arr[3]
/// @param line the RGB string to parse (e.g., "220,100,0")
/// @return Pointer to an int array containing the RGB values, or NULL om fail
static int	*get_rgb_tab(char *line)
{
	char		**split;
	int			*color;

	if (validate_rgb_char(line) != RET_OK)
		return (NULL);
	split = ft_split(line, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (free_double_tab(split),
			fd_printf(STDERR_FILENO, "Wrong RGB format\n"), NULL);
	color = malloc(sizeof(int) * 3);
	if (!color)
		return (free_double_tab(split),
			fd_printf(STDERR_FILENO, "Malloc failed\n"), NULL);
	color[0] = ft_atoi(split[0]);
	color[1] = ft_atoi(split[1]);
	color[2] = ft_atoi(split[2]);
	free_double_tab(split);
	return (color);
}

/// @brief Check if the given RGB values are within the valid range [0, 255]
/// @param color Pointer to an array of 3 integers representing RGB values
/// @return RET_OK if all values are valid, RET_ERR otherwise
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

/// @brief Parses and validates an RGB string, then stores the result in dst ar
/// @param line The string to parse (e.g., "220,100,0")
/// @param dest Pointer to an array of 3 integers where the RGB values will
/// be stored
/// @return RET_OK on success, RET_ERR on failure
int	parse_rgb_values(char *line, int *dest)
{
	int	*rgb;

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

/// @brief Combines red, green, blue and alpha values into an int
/// @param r Red component
/// @param g Green component
/// @param b Blue component
/// @param a Alpha component
/// @return A 32 bit int representing the RGBA color
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
