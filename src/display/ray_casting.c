/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:08:34 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/23 19:33:01 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	calculate_pixel_to_fill(t_ray_casting *ray_cast, t_game *game, int x)
{
	int	y;

	ray_cast->lineHeight = (int)(WIN_HEIGHT / ray_cast->perpWallDist);
	ray_cast->drawStart = -ray_cast->lineHeight / 2 + WIN_HEIGHT / 2;
	if (ray_cast->drawStart < 0)
		ray_cast->drawStart = 0;
	ray_cast->drawEnd = ray_cast->lineHeight / 2 + WIN_HEIGHT / 2;
	if (ray_cast->drawEnd >= WIN_HEIGHT)
		ray_cast->drawEnd = WIN_HEIGHT - 1;
	y = ray_cast->drawStart;
	while (y <= ray_cast->drawEnd)
	{
		put_pixel(game->img, x, y, 0xFFFFFF);
		y++;
	}
	return (0);
}

int	perform_dda(t_ray_casting *ray_cast, t_game *ctx)
{
	while (ray_cast->hit == 0)
	{
		if (ray_cast->sideDistX < ray_cast->sideDistY)
		{
			ray_cast->sideDistX += ray_cast->deltaDistX;
			ray_cast->mapX += ray_cast->stepX;
			ray_cast->side = 0;
		}
		else
		{
			ray_cast->sideDistY += ray_cast->deltaDistY;
			ray_cast->mapY += ray_cast->stepY;
			ray_cast->side = 1;
		}
		if (ray_cast->mapY < 0
			|| ray_cast->mapX < 0
			|| !ctx->map[ray_cast->mapY]
			|| !ctx->map[ray_cast->mapY][ray_cast->mapX])
			ray_cast->hit = 0;
		if (ctx->map[ray_cast->mapY][ray_cast->mapX] == '1')
			ray_cast->hit = 1;
	}
	return (0);
}

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
		pick_texture_and_texx(&ray_cast, ctx);
		draw_textured_column(&ray_cast, ctx, x);
		x++;
	}
	draw_minimap(ctx);
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img.img_ptr, 0, 0);
	return (0);
}
