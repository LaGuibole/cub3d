/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:16:06 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/23 09:36:03 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_rgb(t_config *cfg);
static void	init_vec(t_vec2 *vec);
static void	init_flags(t_flags *flags);

/// @brief Initializes all fields of the configuration structure to default
/// @param cfg Pointer to the configuration structure to init
/// @param argv Command-line argument, used to set the map name
void	init_config(t_config *cfg, char **argv)
{
	cfg->north_tex = NULL;
	cfg->south_tex = NULL;
	cfg->east_tex = NULL;
	cfg->west_tex = NULL;
	cfg->ceiling_tex = NULL;
	cfg->floor_tex = NULL;
	cfg->map_ctx.map = NULL;
	cfg->map_ctx.copy = NULL;
	cfg->map_name = argv[1];
	cfg->player_spawn = 0;
	cfg->map_ctx.height = 0;
	cfg->map_ctx.width = 0;
	init_flags(&cfg->flags);
	init_rgb(cfg);
	init_vec(&cfg->map_ctx.player_pos);
}

/// @brief Initializes all parsing flags to zero
/// @param flags Pointer to the flags structure to init
static void	init_flags(t_flags *flags)
{
	flags->no = 0;
	flags->so = 0;
	flags->we = 0;
	flags->ea = 0;
	flags->c = 0;
	flags->f = 0;
}

/// @brief Initializes all rgb values to be parsed
/// @param cfg Pointer to the config structure to init
static void	init_rgb(t_config *cfg)
{
	cfg->floor_rgb[0] = -1;
	cfg->floor_rgb[1] = -1;
	cfg->floor_rgb[2] = -1;
	cfg->ceiling_rgb[0] = -1;
	cfg->ceiling_rgb[1] = -1;
	cfg->ceiling_rgb[2] = -1;
}

static void	init_vec(t_vec2 *vec)
{
	vec->x = 0;
	vec->y = 0;
}

void	init_game_from_config(t_game *game, t_config *cfg)
{
	game->player_pos = cfg->map_ctx.player_pos;
	game->player_dir = cfg->map_ctx.player_dir;
	game->map = cfg->map_ctx.map;
}
