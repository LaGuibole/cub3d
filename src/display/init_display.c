/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:45:01 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/27 12:35:59 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief Init DDA (Digital Differential Analysis) params for raycasting,
/// setting step directions and initial side distances based on ray direction
/// @param ray_cast Pointer to the raycasting sruct to init
/// @param ctx Pointer to the game context containing the player position
/// @return Always returns 0
int	init_dda(t_ray_casting *ray_cast, t_game *ctx)
{
	if (ray_cast->dir_x < 0)
	{
		ray_cast->step_x = -1;
		ray_cast->side_dist_x = (ctx->player_pos.x - ray_cast->map_x)
			* ray_cast->delta_dist_x;
	}
	else
	{
		ray_cast->step_x = 1;
		ray_cast->side_dist_x = (ray_cast->map_x + 1 - ctx->player_pos.x)
			* ray_cast->delta_dist_x;
	}
	if (ray_cast->dir_y < 0)
	{
		ray_cast->step_y = -1;
		ray_cast->side_dist_y = (ctx->player_pos.y - ray_cast->map_y)
			* ray_cast->delta_dist_y;
	}
	else
	{
		ray_cast->step_y = 1;
		ray_cast->side_dist_y = (ray_cast->map_y + 1 - ctx->player_pos.y)
			* ray_cast->delta_dist_y;
	}
	return (0);
}

/// @brief Init the raycasting struct for a specific vertical stripe of the
/// screen. Calculates ray direction, current map position, and delta distances
/// @param ray_cast Pointer to the raycasting structure to init
/// @param ctx Pointer to the game context containing player direction + plane
/// @param x Current sreen column(pixel) used to compute camera ray
/// @return Always returns 0
int	init_ray_struct(t_ray_casting *ray_cast, t_game *ctx, int x)
{
	ray_cast->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray_cast->dir_x = ctx->player_dir.x + ctx->player_plane.x
		* ray_cast->camera_x;
	ray_cast->dir_y = ctx->player_dir.y + ctx->player_plane.y
		* ray_cast->camera_x;
	ray_cast->map_x = (int)ctx->player_pos.x;
	ray_cast->map_y = (int)ctx->player_pos.y;
	if (ray_cast->dir_x == 0)
		ray_cast->delta_dist_x = 1e30;
	else
		ray_cast->delta_dist_x = fabs(1 / ray_cast->dir_x);
	if (ray_cast->dir_y == 0)
		ray_cast->delta_dist_y = 1e30;
	else
		ray_cast->delta_dist_y = fabs(1 / ray_cast->dir_y);
	ray_cast->hit = 0;
	return (0);
}
