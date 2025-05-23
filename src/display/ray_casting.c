/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:08:34 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/23 09:21:22 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void    player_angle(t_game *ctx)
{
	if (ctx->dir_char == 'N')
	{
		ctx->player_dir.x = 0;
		ctx->player_dir.y = -1;
		ctx->player_plane.x = 0.66;
		ctx->player_plane.y = 0;
	}
	else if (ctx->dir_char == 'S')
	{
		ctx->player_dir.x = 0;
		ctx->player_dir.y = 1;
		ctx->player_plane.x = -0.66;
		ctx->player_plane.y = 0;
	}
	else if (ctx->dir_char == 'E')
	{
		ctx->player_dir.x = 1;
		ctx->player_dir.y = 0;
		ctx->player_plane.x = 0;
		ctx->player_plane.y = 0.66;
	}
	else if (ctx->dir_char == 'W')
	{
		ctx->player_dir.x = -1;
		ctx->player_dir.y = 0;
		ctx->player_plane.x = 0;
		ctx->player_plane.y = -0.66;
	}
}

void    calc_wall_dist(t_ray_casting *ray_cast, t_game *ctx)
{
	if (ray_cast->side == 0)
		ray_cast->perpWallDist = (ray_cast->mapX - ctx->player_pos.x + (1 - ray_cast->stepX) / 2) /
							ray_cast->dirX;
	else
		ray_cast->perpWallDist = (ray_cast->mapY - ctx->player_pos.y + (1 - ray_cast->stepY) / 2) /
							ray_cast->dirY;
}

int calculate_pixel_to_fill(t_ray_casting *ray_cast, t_game *game, int x)
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

int perform_dda(t_ray_casting *ray_cast, t_game *ctx)
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

int init_dda(t_ray_casting *ray_cast, t_game *ctx)
{
	if (ray_cast->dirX < 0)
	{
		ray_cast->stepX = -1;
		ray_cast->sideDistX = (ctx->player_pos.x - ray_cast->mapX)
				* ray_cast->deltaDistX;
	}
	else
	{
		ray_cast->stepX = 1;
		ray_cast->sideDistX = (ray_cast->mapX + 1 - ctx->player_pos.x)
				* ray_cast->deltaDistX;
	}
	if (ray_cast->dirY < 0)
	{
		ray_cast->stepY = -1;
		ray_cast->sideDistY = (ctx->player_pos.y - ray_cast->mapY)
								* ray_cast->deltaDistY;
	}
	else
	{
		ray_cast->stepY = 1;
		ray_cast->sideDistY = (ray_cast->mapY + 1 - ctx->player_pos.y)
								* ray_cast->deltaDistY;
	}
	return (0);
}

int	init_ray_struct(t_ray_casting *ray_cast, t_game *ctx, int x)
{
	ray_cast->cameraX = 2 * x / (double)WIN_WIDTH - 1;
	ray_cast->dirX = ctx->player_dir.x + ctx->player_plane.x
			* ray_cast->cameraX;
	ray_cast->dirY = ctx->player_dir.y + ctx->player_plane.y
			* ray_cast->cameraX;
	ray_cast->mapX = (int)ctx->player_pos.x;
	ray_cast->mapY = (int)ctx->player_pos.y;
	if (ray_cast->dirX == 0)
		ray_cast->deltaDistX = 1e30;
	else
		ray_cast->deltaDistX = fabs(1 / ray_cast->dirX);
	if (ray_cast->dirY == 0)
		ray_cast->deltaDistY = 1e30;
	else
		ray_cast->deltaDistY = fabs(1 / ray_cast->dirY);
	ray_cast->hit = 0;
	return (0);
}

//recuperer la pPos, acceder a la map.
int ray_casting(t_game *ctx)
{
	int				x;
	t_ray_casting	ray_cast;

	x = 0;
	ray_cast = (t_ray_casting){0};
	print_background(ctx);
	while (x < WIN_WIDTH)
	{
		player_angle(ctx);
		init_ray_struct(&ray_cast, ctx, x);
		init_dda(&ray_cast, ctx);
		perform_dda(&ray_cast, ctx);
		calc_wall_dist(&ray_cast, ctx);
		calculate_pixel_to_fill(&ray_cast, ctx, x);
		x++;
	}
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img.img_ptr, 0, 0);
	return (0);
}
