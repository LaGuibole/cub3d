/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 11:36:39 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/27 12:29:28 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief Frees all wall textures allocated in the game context
/// @param game Pointer to the game context containing the textures data
static void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (game->textures[i])
		{
			if (game->textures[i])
			{
				if (game->textures[i]->img_ptr)
					mlx_destroy_image(game->mlx, game->textures[i]->img_ptr);
				free(game->textures[i]);
				game->textures[i] = NULL;
			}
			i++;
		}
	}
}

/// @brief Frees all dynamically allocated game resources (map and texs)
/// @param game Pointer to the game context to be cleaned up
void	exit_game(t_game *game)
{
	if (game->map)
		free_double_tab(game->map);
	free_textures(game);
	if (game->img.img_ptr)
		mlx_destroy_image(game->mlx, game->img.img_ptr);
}
