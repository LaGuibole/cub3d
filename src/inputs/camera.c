/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:43:55 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/23 18:49:16 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	old_dir_x = game->player_dir.x;
	old_plane_x = game->player_plane.x;
	cos_rot = cos(ROT_SPEED);
	sin_rot = sin(ROT_SPEED);

	game->player_dir.x = game->player_dir.x * cos_rot - game->player_dir.y * sin_rot;
	game->player_dir.y = old_dir_x * sin_rot + game->player_dir.y * cos_rot;

	game->player_plane.x = game->player_plane.x * cos_rot - game->player_plane.y * sin_rot;
	game->player_plane.y = old_plane_x * sin_rot + game->player_plane.y * cos_rot;
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	old_dir_x = game->player_dir.x;
	old_plane_x = game->player_plane.x;
	cos_rot = cos(-ROT_SPEED);
	sin_rot = sin(-ROT_SPEED);

	game->player_dir.x = game->player_dir.x * cos_rot - game->player_dir.y * sin_rot;
	game->player_dir.y = old_dir_x * sin_rot + game->player_dir.y * cos_rot;

	game->player_plane.x = game->player_plane.x * cos_rot - game->player_plane.y * sin_rot;
	game->player_plane.y = old_plane_x * sin_rot + game->player_plane.y * cos_rot;
}

// void	rotate_left(t_game *game)
// {
// 	double	old_dir_x = game->player_dir.x;
// 	double	old_plane_x = game->player_plane.x;

// 	game->player_dir.x = game->player_dir.x * cos(-ROT_SPEED) - game->player_dir.y * sin(-ROT_SPEED);
// 	game->player_dir.y = old_dir_x * sin(-ROT_SPEED) + game->player_dir.y * cos(-ROT_SPEED);
// 	game->player_plane.x = game->player_plane.x * cos(-ROT_SPEED) - game->player_plane.y * sin(-ROT_SPEED);
// 	game->player_plane.y = old_plane_x * sin(-ROT_SPEED) + game->player_plane.y * cos(-ROT_SPEED);
// }

// void	rotate_right(t_game *game)
// {
// 	double	old_dir_x = game->player_dir.x;
// 	double	old_plane_x = game->player_plane.x;

// 	game->player_dir.x = game->player_dir.x * cos(ROT_SPEED) - game->player_dir.y * sin(ROT_SPEED);
// 	game->player_dir.y = old_dir_x * sin(ROT_SPEED) + game->player_dir.y * cos(ROT_SPEED);
// 	game->player_plane.x = game->player_plane.x * cos(ROT_SPEED) - game->player_plane.y * sin(ROT_SPEED);
// 	game->player_plane.y = old_plane_x * sin(ROT_SPEED) + game->player_plane.y * cos(ROT_SPEED);
// }
