/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:40:51 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/23 17:31:04 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player_pos.x + game->player_dir.x * PLAYER_SPEED;
	new_y = game->player_pos.y + game->player_dir.y * PLAYER_SPEED;
	if (game->map[(int)new_y][(int)game->player_pos.x] != '1')
		game->player_pos.y = new_y;
	if (game->map[(int)game->player_pos.y][(int)new_x] != '1')
		game->player_pos.x = new_x;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player_pos.x - game->player_dir.x * PLAYER_SPEED;
	new_y = game->player_pos.y - game->player_dir.y * PLAYER_SPEED;

	// Vérification des collisions avec les murs
	if (game->map[(int)new_y][(int)game->player_pos.x] != '1')
		game->player_pos.y = new_y;
	if (game->map[(int)game->player_pos.y][(int)new_x] != '1')
		game->player_pos.x = new_x;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player_pos.x + game->player_dir.y * PLAYER_SPEED;
	new_y = game->player_pos.y - game->player_dir.x * PLAYER_SPEED;
	if (game->map[(int)new_y][(int)game->player_pos.x] != '1')
		game->player_pos.y = new_y;
	if (game->map[(int)game->player_pos.y][(int)new_x] != '1')
		game->player_pos.x = new_x;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player_pos.x - game->player_dir.y * PLAYER_SPEED;
	new_y = game->player_pos.y + game->player_dir.x * PLAYER_SPEED;

	// Vérification des collisions avec les murs
	if (game->map[(int)new_y][(int)game->player_pos.x] != '1')
		game->player_pos.y = new_y;
	if (game->map[(int)game->player_pos.y][(int)new_x] != '1')
		game->player_pos.x = new_x;
}
