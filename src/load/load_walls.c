/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:55:46 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/26 17:43:55 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_north(t_game *g, t_config *cfg)
{
	int	w;
	int	h;

	g->textures[TEX_NORTH] = malloc(sizeof(t_img));
	if (!g->textures[TEX_NORTH])
		return ;
	g->textures[TEX_NORTH]->img_ptr = mlx_xpm_file_to_image(
			g->mlx, cfg->north_tex, &w, &h);
	if (!g->textures[TEX_NORTH]->img_ptr)
		return ;
	g->wall_width = w;
	g->wall_height = h;
	g->textures[TEX_NORTH]->img_addr = mlx_get_data_addr(
			g->textures[TEX_NORTH]->img_ptr,
			&g->textures[TEX_NORTH]->bit_per_pixel,
			&g->textures[TEX_NORTH]->line_len,
			&g->textures[TEX_NORTH]->endian);
}

static void	load_south(t_game *g, t_config *cfg)
{
	int	w;
	int	h;

	g->textures[TEX_SOUTH] = malloc(sizeof(t_img));
	if (!g->textures[TEX_SOUTH])
		return ;
	g->textures[TEX_SOUTH]->img_ptr = mlx_xpm_file_to_image(
			g->mlx, cfg->south_tex, &w, &h);
	if (!g->textures[TEX_SOUTH]->img_ptr)
		return ;
	g->textures[TEX_SOUTH]->img_addr = mlx_get_data_addr(
			g->textures[TEX_SOUTH]->img_ptr,
			&g->textures[TEX_SOUTH]->bit_per_pixel,
			&g->textures[TEX_SOUTH]->line_len,
			&g->textures[TEX_SOUTH]->endian);
}

static void	load_east(t_game *g, t_config *cfg)
{
	int	w;
	int	h;

	g->textures[TEX_EAST] = malloc(sizeof(t_img));
	if (!g->textures[TEX_EAST])
		return ;
	g->textures[TEX_EAST]->img_ptr = mlx_xpm_file_to_image(
			g->mlx, cfg->east_tex, &w, &h);
	if (!g->textures[TEX_EAST]->img_ptr)
		return ;
	g->textures[TEX_EAST]->img_addr = mlx_get_data_addr(
			g->textures[TEX_EAST]->img_ptr,
			&g->textures[TEX_EAST]->bit_per_pixel,
			&g->textures[TEX_EAST]->line_len,
			&g->textures[TEX_EAST]->endian);
}

static void	load_west(t_game *g, t_config *cfg)
{
	int	w;
	int	h;

	g->textures[TEX_WEST] = malloc(sizeof(t_img));
	if (!g->textures[TEX_WEST])
		return ;
	g->textures[TEX_WEST]->img_ptr = mlx_xpm_file_to_image(
			g->mlx, cfg->west_tex, &w, &h);
	if (!g->textures[TEX_WEST]->img_ptr)
		return ;
	g->textures[TEX_WEST]->img_addr = mlx_get_data_addr(
			g->textures[TEX_WEST]->img_ptr,
			&g->textures[TEX_WEST]->bit_per_pixel,
			&g->textures[TEX_WEST]->line_len,
			&g->textures[TEX_WEST]->endian);
}

void	load_walls(t_game *g, t_config *cfg)
{
	load_north(g, cfg);
	load_south(g, cfg);
	load_east(g, cfg);
	load_west(g, cfg);
}
