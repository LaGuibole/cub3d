/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:50:21 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/27 17:03:57 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief Init basic rendering parameters of the game before parsing
/// Sets default values for floor and ceiling colors, and wall textures dim
/// @param game Pointer to the game structure to init
void	init_game_parser(t_game *game)
{
	game->floor_color = 0;
	game->ceiling_color = 0;
	game->wall_height = 64;
	game->wall_width = 64;
}

/// @brief Populates the game structure with data extracted from the parser
/// Sets player pos, direction, map size and generates a rect map
/// @param game Pointer to the game structure to fill
/// @param cfg Pointer to the config structure containing parsed map and data
void	init_game_from_config(t_game *game, t_config *cfg)
{
	game->player_pos = cfg->map_ctx.player_pos;
	game->dir_char = cfg->map_ctx.player_dir;
	game->map_height = cfg->map_ctx.height;
	game->map_width = cfg->map_ctx.width;
	game->map = rectangularize_map(cfg->map_ctx.map,
			cfg->map_ctx.height, cfg->map_ctx.width);
	set_floor_ceiling_colors(game, cfg);
}
