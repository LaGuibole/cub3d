/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:14:38 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/20 11:35:35 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int 	hook_handler(int keycode, t_game *ctx)
{
	if (keycode == ESC)
		clean_and_exit(ctx);
	return (0);
}

int 	claim_hooks( t_game *ctx)
{
	mlx_hook(ctx->win, 17, 0, clean_and_exit, ctx);
	mlx_hook(ctx->win, 2, 1L << 0, hook_handler, ctx);
	return (0);
}
