/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:14:38 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/23 18:46:46 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int 	hook_handler(int keycode, t_game *ctx)
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

int 	claim_hooks( t_game *ctx)
{
	mlx_hook(ctx->win, 17, 0, clean_and_exit, ctx);
	mlx_hook(ctx->win, 2, 1L << 0, hook_handler, ctx);
	return (0);
}
