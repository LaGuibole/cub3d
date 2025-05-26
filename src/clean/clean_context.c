/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_context.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:28:31 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/26 17:20:29 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	clean_context(t_game *ctx)
{
	(void)ctx;
	return (0);
}

int	close_window(t_game *ctx)
{
	if (ctx->win)
		mlx_destroy_window(ctx->mlx, ctx->win);
	if (ctx->mlx)
	{
		mlx_destroy_display(ctx->mlx);
		free(ctx->mlx);
	}
	return (1);
}

int	clean_and_exit(t_game *ctx)
{
	exit_game(ctx);
	close_window(ctx);
	exit(0);
}
