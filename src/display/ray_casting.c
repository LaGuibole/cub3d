/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:08:34 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/27 12:45:40 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief Calculates the vertical slice to draw for a wall hit and fills it
/// with color. Determines the line height and draw start / end positions based
/// on wall distance. Then fills the vertical line of pixels at column 'x'
/// @param ray_cast Pointer to the raycasting structure with hit info
/// @param game Pointer to the game context containing the image buffer
/// @param x Current screen to column where the wall slice should be drawn
/// @return Always returns 0
int	calculate_pixel_to_fill(t_ray_casting *ray_cast, t_game *game, int x)
{
	int	y;

	ray_cast->line_height = (int)(WIN_HEIGHT / ray_cast->perp_wall_dist);
	ray_cast->draw_start = -ray_cast->line_height / 2 + WIN_HEIGHT / 2;
	if (ray_cast->draw_start < 0)
		ray_cast->draw_start = 0;
	ray_cast->draw_end = ray_cast->line_height / 2 + WIN_HEIGHT / 2;
	if (ray_cast->draw_end >= WIN_HEIGHT)
		ray_cast->draw_end = WIN_HEIGHT - 1;
	y = ray_cast->draw_start;
	while (y <= ray_cast->draw_end)
	{
		put_pixel(game->img, x, y, 0xFFFFFF);
		y++;
	}
	return (0);
}

/// @brief Executes the DDA algorithm to detect the first wall hit along a ray.
/// Steps through the map grid until a wall cell ('1') is hit or boundaries are
/// exceeded.
/// Updates side and hit information in the raycasting structure.
/// @param ray_cast Pointer to the raycasting structure being updated.
/// @param ctx Pointer to the game context containing the map data.
/// @return Always returns 0.
int	perform_dda(t_ray_casting *ray_cast, t_game *ctx)
{
	while (ray_cast->hit == 0)
	{
		if (ray_cast->side_dist_x < ray_cast->side_dist_y)
		{
			ray_cast->side_dist_x += ray_cast->delta_dist_x;
			ray_cast->map_x += ray_cast->step_x;
			ray_cast->side = 0;
		}
		else
		{
			ray_cast->side_dist_y += ray_cast->delta_dist_y;
			ray_cast->map_y += ray_cast->step_y;
			ray_cast->side = 1;
		}
		if (ray_cast->map_y < 0
			|| ray_cast->map_x < 0
			|| !ctx->map[ray_cast->map_y]
			|| !ctx->map[ray_cast->map_y][ray_cast->map_x])
			ray_cast->hit = 0;
		if (ctx->map[ray_cast->map_y][ray_cast->map_x] == '1')
			ray_cast->hit = 1;
	}
	return (0);
}

/// @brief Main rendering function using raycasting to draw the 3D scenes
/// Iterate over each vertical column on screen, casts a ray, calculate its hit
/// info, selects a texture, and draws the corresponding wall slice + minimap
/// @param ctx Pointer to the game context containing player state and render
/// @return Always returns 0
int	ray_casting(t_game *ctx)
{
	int				x;
	t_ray_casting	ray_cast;

	x = 0;
	ray_cast = (t_ray_casting){0};
	print_background(ctx);
	while (x < WIN_WIDTH)
	{
		init_ray_struct(&ray_cast, ctx, x);
		init_dda(&ray_cast, ctx);
		perform_dda(&ray_cast, ctx);
		calc_wall_dist(&ray_cast, ctx);
		pick_texture_and_tex_x(&ray_cast, ctx);
		draw_textured_column(&ray_cast, ctx, x);
		x++;
	}
	draw_minimap(ctx);
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img.img_ptr, 0, 0);
	return (0);
}
