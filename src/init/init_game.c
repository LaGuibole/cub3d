/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:50:21 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/23 17:09:36 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief
/// @param game
void	init_game_parser(t_game *game)
{
	game->floor_color = 0;
	game->ceiling_color = 0;
	game->north_wall = NULL;
	game->south_wall = NULL;
	game->east_wall = NULL;
	game->west_wall = NULL;
	game->wall_height = 64;
	game->wall_width = 64;
}

void	init_game_from_config(t_game *game, t_config *cfg)
{
	game->player_pos = cfg->map_ctx.player_pos;
	game->dir_char = cfg->map_ctx.player_dir;
	game->map = copy_map(cfg->map_ctx.map);
	game->map_height = cfg->map_height;
	set_floor_ceiling_colors(game, cfg);
}
