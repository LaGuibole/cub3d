/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_angle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:42:41 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/26 17:44:31 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	player_angle1(t_game *ctx)
{
	if (ctx->dir_char == 'E')
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

void	player_angle(t_game *ctx)
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
	player_angle1(ctx);
}
