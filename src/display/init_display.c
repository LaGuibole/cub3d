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
