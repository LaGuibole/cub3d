/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_context.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:28:31 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/20 11:06:58 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	clean_context(t_game *ctx)
{
	(void)ctx;
	return (0);
}

int close_window(t_game *ctx)
{
	if (ctx->win)
		mlx_destroy_window(ctx->mlx,ctx->win);
	if (ctx->mlx)
	{
		mlx_destroy_display(ctx->mlx);
		free(ctx->mlx);
	}
	return (1);
}

int	clean_and_exit(t_game *ctx)
{
	close_window(ctx);
	exit(0);
}
