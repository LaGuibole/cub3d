/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 11:36:39 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/26 17:23:50 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	exit_game(t_game *game)
{
	if (game->map)
		free_double_tab(game->map);
	free_textures(game);
	if (game->img.img_ptr)
		mlx_destroy_image(game->mlx, game->img.img_ptr);
}
