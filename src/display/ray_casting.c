/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:08:34 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/23 19:33:01 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	player_angle1(t_game *ctx)
{
	if (ctx->dir_char == 'E')
	{
		ctx->player_dir.x = 1;
		ctx->player_dir.y = 0;
		ctx->player_plane.x = 0;
		ctx->player_plane.y = 0.66;
	}
	else if (ctx->dir_char == 'W')
	{
		ctx->player_dir.x = -1;
		ctx->player_dir.y = 0;
		ctx->player_plane.x = 0;
		ctx->player_plane.y = -0.66;
	}
}

void	player_angle(t_game *ctx)
{
	if (ctx->dir_char == 'N')
	{
		ctx->player_dir.x = 0;
		ctx->player_dir.y = -1;
		ctx->player_plane.x = 0.66;
		ctx->player_plane.y = 0;
	}
	else if (ctx->dir_char == 'S')
	{
		ctx->player_dir.x = 0;
		ctx->player_dir.y = 1;
		ctx->player_plane.x = -0.66;
		ctx->player_plane.y = 0;
	}
	player_angle1(ctx);
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

int calculate_pixel_to_fill(t_ray_casting *ray_cast, t_game *game, int x)
{
	int	y;

	ray_cast->lineHeight = (int)(WIN_HEIGHT / ray_cast->perpWallDist);
	ray_cast->drawStart = -ray_cast->lineHeight / 2 + WIN_HEIGHT / 2;
	if (ray_cast->drawStart < 0)
		ray_cast->drawStart = 0;
	ray_cast->drawEnd = ray_cast->lineHeight / 2 + WIN_HEIGHT / 2;
	if (ray_cast->drawEnd >= WIN_HEIGHT)
		ray_cast->drawEnd = WIN_HEIGHT - 1;
	y = ray_cast->drawStart;
	while (y <= ray_cast->drawEnd)
	{
		put_pixel(game->img, x, y, 0xFFFFFF);
		y++;
	}
	return (0);
}

int perform_dda(t_ray_casting *ray_cast, t_game *ctx)
{
	while (ray_cast->hit == 0)
	{
		if (ray_cast->sideDistX < ray_cast->sideDistY)
		{
			ray_cast->sideDistX += ray_cast->deltaDistX;
			ray_cast->mapX += ray_cast->stepX;
			ray_cast->side = 0;
		}
		else
		{
			ray_cast->sideDistY += ray_cast->deltaDistY;
			ray_cast->mapY += ray_cast->stepY;
			ray_cast->side = 1;
		}
		if (ray_cast->mapY < 0
			|| ray_cast->mapX < 0
			|| !ctx->map[ray_cast->mapY]
			|| !ctx->map[ray_cast->mapY][ray_cast->mapX])
			ray_cast->hit = 0;
		if (ctx->map[ray_cast->mapY][ray_cast->mapX] == '1')
			ray_cast->hit = 1;
	}
	return (0);
}

int init_dda(t_ray_casting *ray_cast, t_game *ctx)
{
	if (ray_cast->dirX < 0)
	{
		ray_cast->stepX = -1;
		ray_cast->sideDistX = (ctx->player_pos.x - ray_cast->mapX)
				* ray_cast->deltaDistX;
	}
	else
	{
		ray_cast->stepX = 1;
		ray_cast->sideDistX = (ray_cast->mapX + 1 - ctx->player_pos.x)
				* ray_cast->deltaDistX;
	}
	if (ray_cast->dirY < 0)
	{
		ray_cast->stepY = -1;
		ray_cast->sideDistY = (ctx->player_pos.y - ray_cast->mapY)
								* ray_cast->deltaDistY;
	}
	else
	{
		ray_cast->stepY = 1;
		ray_cast->sideDistY = (ray_cast->mapY + 1 - ctx->player_pos.y)
								* ray_cast->deltaDistY;
	}
	return (0);
}

int	init_ray_struct(t_ray_casting *ray_cast, t_game *ctx, int x)
{
	ray_cast->cameraX = 2 * x / (double)WIN_WIDTH - 1;
	ray_cast->dirX = ctx->player_dir.x + ctx->player_plane.x
			* ray_cast->cameraX;
	ray_cast->dirY = ctx->player_dir.y + ctx->player_plane.y
			* ray_cast->cameraX;
	ray_cast->mapX = (int)ctx->player_pos.x;
	ray_cast->mapY = (int)ctx->player_pos.y;
	if (ray_cast->dirX == 0)
		ray_cast->deltaDistX = 1e30;
	else
		ray_cast->deltaDistX = fabs(1 / ray_cast->dirX);
	if (ray_cast->dirY == 0)
		ray_cast->deltaDistY = 1e30;
	else
		ray_cast->deltaDistY = fabs(1 / ray_cast->dirY);
	ray_cast->hit = 0;
	return (0);
}

static int clamp(int v, int min, int max)
{
	if (v < min)
		return (min);
	if (v > max)
		return (max);
	return (v);
}

static int get_tex_color(t_img *tex, int tx, int ty)
{
	char	*p;

	p = tex->img_addr
		+ ty * tex->line_len
		+ tx * (tex->bit_per_pixel / 8);
	return (*(int *)p);
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
	while (y <= clamp(lh / 2 + WIN_HEIGHT / 2,
					  0, WIN_HEIGHT - 1))
	{
		ty = clamp(((y * 256 - WIN_HEIGHT * 128
					 + lh * 128)
					* g->wall_height / lh) / 256,
				   0, g->wall_height - 1);
		put_pixel(g->img, x, y++,
				  get_tex_color(tex, r->texX, ty));
	}
}


static void pick_texture_and_texx(t_ray_casting *r, t_game *g)
{
	double wallX;

	if (r->side == 0 && r->dirX > 0)
		r->texNum = TEX_WEST;
	if (r->side == 0 && r->dirX <= 0)
		r->texNum = TEX_EAST;
	if (r->side == 1 && r->dirY > 0)
		r->texNum = TEX_NORTH;
	if (r->side == 1 && r->dirY <= 0)
		r->texNum = TEX_SOUTH;
	if (r->side == 0)
		wallX = g->player_pos.y + r->perpWallDist * r->dirY;
	else
		wallX = g->player_pos.x + r->perpWallDist * r->dirX;
	wallX = wallX - floor(wallX);
	r->texX = (int)(wallX * g->wall_width);
	if (r->side == 0 && r->dirX < 0)
		r->texX = g->wall_width - r->texX - 1;
	if (r->side == 1 && r->dirY > 0)
		r->texX = g->wall_width - r->texX - 1;
}

int ray_casting(t_game *ctx)
{
	int				x;
	t_ray_casting	ray_cast;

	x = 0;
	ray_cast = (t_ray_casting){0};
	print_background(ctx);
	while (x < WIN_WIDTH)
	{
		init_ray_struct(&ray_cast, ctx, x);
		init_dda(&ray_cast, ctx);
		perform_dda(&ray_cast, ctx);
		calc_wall_dist(&ray_cast, ctx);
		pick_texture_and_texx(&ray_cast, ctx);
		draw_textured_column(&ray_cast, ctx, x);
		x++;
	}
	draw_minimap(ctx);
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img.img_ptr, 0, 0);
	return (0);
}
