/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:45:01 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/23 17:45:45 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_dda(t_ray_casting *ray_cast, t_game *ctx)
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
