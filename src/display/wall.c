/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:49:03 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/24 12:49:06 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		ray_cast->perpWallDist = (ray_cast->mapX - ctx->player_pos.x
				+ (1 - ray_cast->stepX) / 2) / ray_cast->dirX;
	else
		ray_cast->perpWallDist = (ray_cast->mapY - ctx->player_pos.y
				+ (1 - ray_cast->stepY) / 2) / ray_cast->dirY;
}

void	draw_textured_column(t_ray_casting *r, t_game *g, int x)
{
	t_img	*tex;
	int		lh;
	int		ds;
	int		y;
	int		ty;

	if (r->texNum < 0 || r->texNum >= TEX_COUNT)
		return ;
	tex = g->textures[r->texNum];
	lh = (int)(WIN_HEIGHT / r->perpWallDist);
	ds = clamp(-lh / 2 + WIN_HEIGHT / 2,
			0, WIN_HEIGHT - 1);
	r->texX = clamp(r->texX,
			0, g->wall_width - 1);
	y = ds;
	while (y <= clamp(lh / 2 + WIN_HEIGHT / 2, 0, WIN_HEIGHT - 1))
	{
		ty = clamp(((y * 256 - WIN_HEIGHT * 128 + lh * 128)
					* g->wall_height / lh) / 256,
				0, g->wall_height - 1);
		put_pixel(g->img, x, y++, get_tex_color(tex, r->texX, ty));
	}
}

void	pick_texture_and_texx(t_ray_casting *r, t_game *g)
{
	double	wallx;

	if (r->side == 0 && r->dirX > 0)
		r->texNum = TEX_WEST;
	if (r->side == 0 && r->dirX <= 0)
		r->texNum = TEX_EAST;
	if (r->side == 1 && r->dirY > 0)
		r->texNum = TEX_NORTH;
	if (r->side == 1 && r->dirY <= 0)
		r->texNum = TEX_SOUTH;
	if (r->side == 0)
		wallx = g->player_pos.y + r->perpWallDist * r->dirY;
	else
		wallx = g->player_pos.x + r->perpWallDist * r->dirX;
	wallx = wallx - floor(wallx);
	r->texX = (int)(wallx * g->wall_width);
	if (r->side == 0 && r->dirX < 0)
		r->texX = g->wall_width - r->texX - 1;
	if (r->side == 1 && r->dirY > 0)
		r->texX = g->wall_width - r->texX - 1;
}
