/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 11:14:22 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/27 17:18:55 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief Draws a filled square on the image buffer, used to represent player
/// in the mini map
/// @param game Pointer to the game context containing the image buffer
/// @param px Position X og the top left corner of the square
/// @param py Poistion Y of the top left corner of the square
/// @param color Color to fill the square with
void	draw_square(t_game *game, int px, int py, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINI_TILE_SIZE)
	{
		x = 0;
		while (x < MINI_TILE_SIZE)
		{
			put_pixel(game->img, px + x, py + y, color);
			x++;
		}
		y++;
	}
}

/// @brief Draws a small green dot at the center of the minimap to reprensent
/// the current player's position
/// @param game Pointer to the game structure containing player statse
void	draw_player_dot(t_game *game)
{
	t_vec2	p;
	int		size;
	int		center_x;
	int		center_y;

	size = 2;
	center_x = 12 + MINI_MAP_RADIUS * MINI_TILE_SIZE;
	center_y = 12 + MINI_MAP_RADIUS * MINI_TILE_SIZE;
	p.y = -size;
	while (p.y <= size)
	{
		p.x = -size;
		while (p.x <= size)
		{
			put_pixel(game->img, center_x + p.x, center_y + p.y, 0x00FF00);
			p.x++;
		}
		p.y++;
	}
}

/// @brief Draws a red line extending from the player's position
/// @param game Pointer to the game structure containing player direction
void	draw_direction_ray(t_game *game)
{
	int			i;
	t_vec2		p;
	t_vec2		start;
	double		dir_x;
	double		dir_y;

	start.x = 12 + MINI_MAP_RADIUS * MINI_TILE_SIZE;
	start.y = 12 + MINI_MAP_RADIUS * MINI_TILE_SIZE;
	dir_x = game->player_dir.x;
	dir_y = game->player_dir.y;
	i = 0;
	while (i < 10)
	{
		p.x = start.x + (int)(dir_x * i);
		p.y = start.y + (int)(dir_y * i);
		put_pixel(game->img, p.x, p.y, 0xFF0000);
		i++;
	}
}

/// @brief Determines the color to use for a given tile in the mini-map
/// @param game Pointer to the game context containing the map and floor
/// @param map 2D vector representing the tile's map coordinates
/// @return Hexadecimal color to represent the tile
int	get_tile_color(t_game *game, t_vec2 map)
{
	char	tile;

	tile = game->map[(int)map.y][(int)map.x];
	if (tile == '1')
		return (0x5B676E);
	if (tile == '0' || tile == game->dir_char)
		return (game->floor_color);
	return (0);
}

/// @brief Renders all visible tiles around the player position in the
/// mini-map. Draws each tile using its corresponding color
/// @param game Pointer to the game context containing the map and rendering
/// infos
/// @param c 2D vector representing the center of the mini-map (player map pos)
void	draw_minimap_tiles(t_game *game, t_vec2 c)
{
	t_vec2	p;
	t_vec2	map;
	int		color;

	p.y = -MINI_MAP_RADIUS;
	while (p.y <= MINI_MAP_RADIUS)
	{
		p.x = -MINI_MAP_RADIUS;
		while (p.x <= MINI_MAP_RADIUS)
		{
			map.x = c.x + p.x;
			map.y = c.y + p.y;
			if (map.y >= 0 && map.y < game->map_height
				&& map.x >= 0 && map.x < game->map_width)
			{
				color = get_tile_color(game, map);
				if (color)
					draw_square(game,
						10 + (p.x + MINI_MAP_RADIUS) * MINI_TILE_SIZE,
						10 + (p.y + MINI_MAP_RADIUS) * MINI_TILE_SIZE, color);
			}
			p.x++;
		}
		p.y++;
	}
}
