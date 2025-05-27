/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:43:55 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/27 17:09:22 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief Rotates the player's direction and camera plane to the right
/// by a fixed angle (ROT_SPEED), updating direction and plane vectors
/// @param game Pointer to the game context containing player direction
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
	game->player_dir.x = game->player_dir.x
		* cos_rot - game->player_dir.y * sin_rot;
	game->player_dir.y = old_dir_x * sin_rot
		+ game->player_dir.y * cos_rot;
	game->player_plane.x = game->player_plane.x
		* cos_rot - game->player_plane.y * sin_rot;
	game->player_plane.y = old_plane_x * sin_rot
		+ game->player_plane.y * cos_rot;
}

/// @brief Rotates the player's direction and camera plane to the left
/// by a fixed angle (ROT_SPEED), updating direction and plane vectors
/// @param game Pointer to the game context containing player direction
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
	game->player_dir.x = game->player_dir.x
		* cos_rot - game->player_dir.y * sin_rot;
	game->player_dir.y = old_dir_x * sin_rot
		+ game->player_dir.y * cos_rot;
	game->player_plane.x = game->player_plane.x
		* cos_rot - game->player_plane.y * sin_rot;
	game->player_plane.y = old_plane_x * sin_rot
		+ game->player_plane.y * cos_rot;
}
