/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:14:38 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/27 17:11:01 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief Handle key press events and maps them to game actions
/// @param keycode The code of the key that was pressed
/// @param ctx Pointer to the game context to apply the action to
/// @return Always returns 0
int	hook_handler(int keycode, t_game *ctx)
{
	if (keycode == ESC)
		clean_and_exit(ctx);
	if (keycode == W)
		move_forward(ctx);
	if (keycode == S)
		move_backward(ctx);
	if (keycode == A)
		move_left(ctx);
	if (keycode == D)
		move_right(ctx);
	if (keycode == LEFT)
		rotate_left(ctx);
	if (keycode == RIGHT)
		rotate_right(ctx);
	return (0);
}

/// @brief Register event hooks for the game window, including key press
/// @param ctx Pointer to the game context containing the MLX window ref
/// @return Always returns 0
int	claim_hooks( t_game *ctx)
{
	mlx_hook(ctx->win, 17, 0, clean_and_exit, ctx);
	mlx_hook(ctx->win, 2, 1L << 0, hook_handler, ctx);
	return (0);
}
