/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_angle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:42:41 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/27 12:38:48 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief Set's the player's direction and camera plane vectors based on
/// East / West orientation. Called internally by player_angle to handle
/// 'E' and 'W' cases.
/// @param ctx Pointer to the game context containing the direction char
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

/// @brief Init the player's facing direction and camera plane
/// based on the spawn orientation ('N', 'S', 'E', 'W')
/// @param ctx Pointer to the game context containing the dir char
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
