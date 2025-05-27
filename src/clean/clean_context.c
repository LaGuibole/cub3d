/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_context.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:28:31 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/27 12:28:14 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief Placeholder function to clean the game context. Does nothing lol
/// @param ctx Pointer to the game context
/// @return Always return 0 (WTF)
int	clean_context(t_game *ctx)
{
	(void)ctx;
	return (0);
}

/// @brief Closes the game window and frees the MLX display resources
/// @param ctx Pointer to the game context containing MLX references
/// @return Returns 1 after cleanup
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

/// @brief Cleans up the game state and closes the window before exiting
/// @param ctx Pointer to the game context to be cleaned
/// @return This function does not return, it exits the program with 0
int	clean_and_exit(t_game *ctx)
{
	exit_game(ctx);
	close_window(ctx);
	exit(0);
}
