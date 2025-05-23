/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:41:20 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/23 14:52:50 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief
/// @param cfg
void	init_textures_fds(t_config *cfg)
{
	cfg->no_fd = -1;
	cfg->so_fd = -1;
	cfg->we_fd = -1;
	cfg->ea_fd = -1;
}

/// @brief
/// @param game
/// @param cfg
void	set_floor_ceiling_colors(t_game *game, t_config *cfg)
{
	if (cfg->ceiling_rgb)
		game->ceiling_color = get_rgba(cfg->ceiling_rgb[0],
				cfg->ceiling_rgb[1], cfg->ceiling_rgb[2]);
	if (cfg->floor_rgb)
		game->floor_color = get_rgba(cfg->floor_rgb[0],
				cfg->floor_rgb[1], cfg->floor_rgb[2]);
}

/// @brief
/// @param cfg
/// @return
int	check_textures_accessibility(t_config *cfg)
{
	if (!cfg->north_tex)
		return (fd_printf(STDERR_FILENO, "NO texture path = NULL\n"), RET_ERR);
	cfg->no_fd = open(cfg->north_tex, O_RDONLY);
	if (cfg->no_fd == -1)
		return (fd_printf(STDERR_FILENO, "Can't open NO textures\n"), RET_ERR);
	close(cfg->no_fd);
	if (!cfg->south_tex)
		return (fd_printf(STDERR_FILENO, "SO texture path = NULL\n"), RET_ERR);
	cfg->so_fd = open(cfg->south_tex, O_RDONLY);
	if (cfg->so_fd == -1)
		return (fd_printf(STDERR_FILENO, "Can't open SO textures\n"), RET_ERR);
	close(cfg->so_fd);
	if (!cfg->west_tex)
		return (fd_printf(STDERR_FILENO, "WE texture path = NULL\n"), RET_ERR);
	cfg->we_fd = open(cfg->west_tex, O_RDONLY);
	if (cfg->we_fd == -1)
		return (fd_printf(STDERR_FILENO, "Can't open WE textures\n"), RET_ERR);
	close(cfg->we_fd);
	if (!cfg->east_tex)
		return (fd_printf(STDERR_FILENO, "EA texture path = NULL\n"), RET_ERR);
	cfg->ea_fd = open(cfg->east_tex, O_RDONLY);
	if (cfg->ea_fd == -1)
		return (fd_printf(STDERR_FILENO, "Can't open EA textures\n"), RET_ERR);
	close(cfg->ea_fd);
	return (RET_OK);
}
