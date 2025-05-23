/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:04:45 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/23 19:29:45 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_square(t_game *game, int px, int py, int color)
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

static void	draw_player_dot(t_game *game)
{
	t_vec2	p;
	int		size;
	int		center_x;
	int		center_y;

	size = 2;
	center_x = 10 + MINI_MAP_RADIUS * MINI_TILE_SIZE;
	center_y = 10 + MINI_MAP_RADIUS * MINI_TILE_SIZE;
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

static void	draw_direction_ray(t_game *game)
{
	int		i;
	t_vec2		p;
	t_vec2		start;
	double	dir_x;
	double	dir_y;

	start.x = 10 + MINI_MAP_RADIUS * MINI_TILE_SIZE;
	start.y = 10 + MINI_MAP_RADIUS * MINI_TILE_SIZE;
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

void	draw_minimap(t_game *game)
{
	int	x;
	int	y;
	int	mapx;
	int	mapy;
	int	cx;
	int	cy;
	int	color;

	cx = (int)game->player_pos.x;
	cy = (int)game->player_pos.y;
	y = -MINI_MAP_RADIUS;
	while (y <= MINI_MAP_RADIUS)
	{
		x = -MINI_MAP_RADIUS;
		while (x <= MINI_MAP_RADIUS)
		{
			mapx = cx + x;
			mapy = cy + y;
			if (mapy >= 0 && mapx >= 0
				&& mapy < game->map_height
				&& mapx < (int)ft_strlen(game->map[mapy]))
			{
				color = 0x222222;
				if (game->map[mapy][mapx] == '1')
					color = 0xFFFFFF;
				else if (game->map[mapy][mapx] == '0')
					color = 0x666666;
				draw_square(game,
					10 + (x + MINI_MAP_RADIUS) * MINI_TILE_SIZE,
					10 + (y + MINI_MAP_RADIUS) * MINI_TILE_SIZE,
					color);
			}
			x++;
		}
		y++;
	}
	draw_player_dot(game);
	draw_direction_ray(game);
}
