/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:23:59 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/22 19:52:47 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clean_textures(t_config *cfg);
static void	clean_floor_ceiling(t_config *cfg);

/// @brief Frees all dynamically allocated memory inside the config struct
/// @param cfg Pointer to the configuration structure to clean
void	clean_config(t_config *cfg)
{
	clean_textures(cfg);
	clean_floor_ceiling(cfg);
	if (cfg->map_ctx.map)
		free_double_tab(cfg->map_ctx.map);
}

static void	clean_textures(t_config *cfg)
{
	if (cfg->north_tex)
	{
		free(cfg->north_tex);
		cfg->north_tex = NULL;
	}
	if (cfg->south_tex)
	{
		free(cfg->south_tex);
		cfg->south_tex = NULL;
	}
	if (cfg->west_tex)
	{
		free(cfg->west_tex);
		cfg->west_tex = NULL;
	}
	if (cfg->east_tex)
	{
		free(cfg->east_tex);
		cfg->east_tex = NULL;
	}
}

static void	clean_floor_ceiling(t_config *cfg)
{
	if (cfg->ceiling_tex)
	{
		free(cfg->ceiling_tex);
		cfg->ceiling_tex = NULL;
	}
	if (cfg->floor_tex)
	{
		free(cfg->floor_tex);
		cfg->floor_tex = NULL;
	}
}

int	free_config_and_lines(t_config *cfg, char **lines, int ret)
{
	if (lines)
		free_double_tab(lines);
	if (cfg)
		clean_config(cfg);
	return (ret);
}
