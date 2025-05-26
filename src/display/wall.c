/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:49:03 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/26 17:44:21 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	clamp(int v, int min, int max)
{
	if (v < min)
		return (min);
	if (v > max)
		return (max);
	return (v);
}

static int	get_tex_color(t_img *tex, int tx, int ty)
{
	char	*p;

	p = tex->img_addr
		+ ty * tex->line_len
		+ tx * (tex->bit_per_pixel / 8);
	return (*(int *)p);
}

void	calc_wall_dist(t_ray_casting *ray_cast, t_game *ctx)
{
	if (ray_cast->side == 0)
		ray_cast->perp_wall_dist = (ray_cast->map_x - ctx->player_pos.x
				+ (1 - ray_cast->step_x) / 2) / ray_cast->dir_x;
	else
		ray_cast->perp_wall_dist = (ray_cast->map_y - ctx->player_pos.y
				+ (1 - ray_cast->step_y) / 2) / ray_cast->dir_y;
}

void	draw_textured_column(t_ray_casting *r, t_game *g, int x)
{
	t_img	*tex;
	int		lh;
	int		ds;
	int		y;
	int		ty;

	if (r->tex_num < 0 || r->tex_num >= TEX_COUNT)
		return ;
	tex = g->textures[r->tex_num];
	lh = (int)(WIN_HEIGHT / r->perp_wall_dist);
	ds = clamp(-lh / 2 + WIN_HEIGHT / 2,
			0, WIN_HEIGHT - 1);
	r->tex_x = clamp(r->tex_x,
			0, g->wall_width - 1);
	y = ds;
	while (y <= clamp(lh / 2 + WIN_HEIGHT / 2, 0, WIN_HEIGHT - 1))
	{
		ty = clamp(((y * 256 - WIN_HEIGHT * 128 + lh * 128)
					* g->wall_height / lh) / 256,
				0, g->wall_height - 1);
		put_pixel(g->img, x, y++, get_tex_color(tex, r->tex_x, ty));
	}
}

void	pick_texture_and_tex_x(t_ray_casting *r, t_game *g)
{
	double	wallx;

	if (r->side == 0 && r->dir_x > 0)
		r->tex_num = TEX_WEST;
	if (r->side == 0 && r->dir_x <= 0)
		r->tex_num = TEX_EAST;
	if (r->side == 1 && r->dir_y > 0)
		r->tex_num = TEX_NORTH;
	if (r->side == 1 && r->dir_y <= 0)
		r->tex_num = TEX_SOUTH;
	if (r->side == 0)
		wallx = g->player_pos.y + r->perp_wall_dist * r->dir_y;
	else
		wallx = g->player_pos.x + r->perp_wall_dist * r->dir_x;
	wallx = wallx - floor(wallx);
	r->tex_x = (int)(wallx * g->wall_width);
	if (r->side == 0 && r->dir_x < 0)
		r->tex_x = g->wall_width - r->tex_x - 1;
	if (r->side == 1 && r->dir_y > 0)
		r->tex_x = g->wall_width - r->tex_x - 1;
}
