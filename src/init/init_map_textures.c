/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:41:20 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/23 11:13:39 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_floor_ceiling_colors(t_game *game, t_config *cfg)
{
	if (cfg->ceiling_rgb)
		game->ceiling_color = get_rgba(cfg->ceiling_rgb[0], cfg->ceiling_rgb[1], cfg->ceiling_rgb[2]);
	if (cfg->floor_rgb)
		game->floor_color = get_rgba(cfg->floor_rgb[0], cfg->floor_rgb[1], cfg->floor_rgb[2]);
}

// int	check_textures_accessibility(t_map_ctx *ctx)
// {

// }


