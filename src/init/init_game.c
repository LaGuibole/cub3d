/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:50:21 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/23 14:50:49 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief
/// @param game
void	init_game_parser(t_game *game)
{
	game->floor_color = 0;
	game->ceiling_color = 0;
}

/// @brief
/// @param game
/// @param cfg
void	init_game_from_config(t_game *game, t_config *cfg)
{
	game->player_pos = cfg->map_ctx.player_pos;
	game->player_dir = cfg->map_ctx.player_dir;
	game->map = copy_map(cfg->map_ctx.map);
	set_floor_ceiling_colors(game, cfg);
}
