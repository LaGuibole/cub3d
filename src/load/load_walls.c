/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:55:46 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/23 16:02:37 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_walls(t_config *cfg, t_game *game)
{
	if (cfg->north_tex)
		game->north_wall = mlx_xpm_file_to_image(game->mlx, cfg->north_tex, &game->wall_width, &game->wall_height);
	if (cfg->south_tex)
		game->south_wall = mlx_xpm_file_to_image(game->mlx, cfg->south_tex, &game->wall_width, &game->wall_height);
	if (cfg->east_tex)
		game->east_wall = mlx_xpm_file_to_image(game->mlx, cfg->east_tex, &game->wall_width, &game->wall_height);
	if (cfg->west_tex)
		game->west_wall = mlx_xpm_file_to_image(game->mlx, cfg->west_tex, &game->wall_width, &game->wall_height);
}
