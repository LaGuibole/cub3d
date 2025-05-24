/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 11:36:39 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/24 12:16:41 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_game(t_game *game)
{
	if (game->map)
		free_double_tab(game->map);
	if (game->img.img_ptr)
		mlx_destroy_image(game->mlx, game->img.img_ptr);
}
