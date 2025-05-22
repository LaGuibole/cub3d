/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_flood_fill.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:37:50 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/22 13:55:38 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**alloc_rectangular_map(int height, int width);
static void	fill_line_with_padding(char *dest, char *src, int width);

/// @brief Creates a new rectangular version of the map with padding spaces
///	if needed
/// @param map Original map as a NULL-terminated array of strings
/// @param height Number of lines in the map
/// @param width Maximum width of the map (used for padding)
/// @return A newly allocated rectangular map, or NULL on failure
char	**rectangularize_map(char **map, int height, int width)
{
	char	**new_map;
	int		y;

	new_map = alloc_rectangular_map(height, width);
	if (!new_map)
		return (NULL);
	y = 0;
	while (y < height)
	{
		fill_line_with_padding(new_map[y], map[y], width);
		y++;
	}
	return (new_map);
}

/// @brief Prepares a padded copy of the map for flood fill by replacing
//  spaces with walls ('1')
/// @param map Original map to copy
/// @param height Height of the map
/// @param width Width of the map (used for padding)
/// @return A padded and normalized copy of the map ready for flood fill,
/// or NULL on failure
char	**prepare_map_for_flood(char **map, int height, int width)
{
	char	**copy;
	int		y;
	int		x;

	copy = rectangularize_map(map, height, width);
	if (!copy)
		return (NULL);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (copy[y][x] == ' ')
				copy[y][x] = '1';
			x++;
		}
		y++;
	}
	return (copy);
}

/// @brief Allocates memory for a rectangular map of given dimensions
/// @param height Number of rows in the map
/// @param width Number of columns (characters) per row
/// @return A newly allocated 2D array of characters, or NULL on alloc fail
static char	**alloc_rectangular_map(int height, int width)
{
	char	**map;
	int		y;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	y = 0;
	while (y < height)
	{
		map[y] = malloc(sizeof(char) * (width + 1));
		if (!map[y])
			return (free_double_tab(map), NULL);
		y++;
	}
	map[y] = NULL;
	return (map);
}

/// @brief Fills a line with the content of another,
/// add spaces as padding if needed
/// @param dest Destination string to fill
/// @param src Source string to copy
/// @param width Desired width of the destination string (with padding)
static void	fill_line_with_padding(char *dest, char *src, int width)
{
	int	x;
	int	len;

	if (src)
		len = ft_strlen(src);
	else
		len = 0;
	x = 0;
	while (x < width)
	{
		if (src && x < len)
			dest[x] = src[x];
		else
			dest[x] = ' ';
		x++;
	}
	dest[x] = '\0';
}
