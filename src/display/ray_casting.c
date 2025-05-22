/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:08:34 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/22 10:57:40 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int calculate_pixel_to_fill(t_ray_casting *ray_cast)
{
	ray_cast->drawStart = -ray_cast->lineHeight / 2 + WIN_HEIGHT / 2;
	if (ray_cast->drawStart < 0)
		ray_cast->drawStart = 0;
	ray_cast->drawEnd = ray_cast->lineHeight / 2 + WIN_HEIGHT / 2;
	if (ray_cast->drawEnd >= WIN_HEIGHT)
		ray_cast->drawEnd = WIN_HEIGHT - 1;
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
		if (ctx->map[ray_cast->mapX][ray_cast->mapY] != 0)
			ray_cast->hit = 1;
	}
	return (0);
}

int calculate_step(t_ray_casting *ray_cast)
{
	if (ray_cast->rayDirX < 0)
	{
		ray_cast->stepX = -1;
		ray_cast->sideDistX = (ray_cast->pPosX - ray_cast->mapX)
				* ray_cast->deltaDistX;
	}
	else
	{
		ray_cast->stepX = 1;
		ray_cast->sideDistX = (ray_cast->mapX + 1 - ray_cast->pPosX)
				* ray_cast->deltaDistX;
	}
	if (ray_cast->rayDirY < 0)
	{
		ray_cast->stepY = -1;
		ray_cast->sideDistY = (ray_cast->pPosY - ray_cast->mapY)
								* ray_cast->deltaDistX;
	}
	else
	{
		ray_cast->stepX = 1;
		ray_cast->sideDistY = (ray_cast->mapY + 1 - ray_cast->pPosY)
								* ray_cast->deltaDistY;
	}
	return (0);
}

//recuperer la position du joueur
int	init_ray_struct(t_ray_casting *ray_cast, t_game *ctx, int x)
{
	ray_cast->pPosX = player_posX;
	ray_cast->pPosY = player_posY;


	ray_cast->cameraX = 2 * x / WIN_WIDTH - 1;
	//direction du rayon
	ray_cast->rayDirX = ray_cast->dirX + ray_cast->planeX * ray_cast->cameraX;
	ray_cast->rayDirY = ray_cast->dirY + ray_cast->planeY * ray_cast->cameraX;

	//position du joueur defini sur la map
	ray_cast->mapX = (int)ray_cast->pPosX;
	ray_cast->mapY = (int)ray_cast->pPosY;





	ray_cast->sideDistX = sqrt(1 + (ray_cast->rayDirY * ray_cast->rayDirY)
								  / (ray_cast->rayDirX * ray_cast->rayDirX));
	ray_cast->sideDistX = sqrt(1 + (ray_cast->rayDirX * ray_cast->rayDirX)
								  / (ray_cast->rayDirY * ray_cast->rayDirY));

	ray_cast->dirPosX = 10;
	ray_cast->dirPosY = 10;

	ray_cast->dirX = -1;
	ray_cast->dirY = 0;

	ray_cast->planeX = 0;
	ray_cast->planeX = 0.66;
	return (0);
}

//recuperer la pPos, acceder a la map.
int ray_casting(t_game *ctx)
{
	int x = 0;
	t_ray_casting ray_cast;

	ray_cast = (t_ray_casting){0};
	while (x < WIN_WIDTH)
	{
		init_ray_struct(&ray_cast, ctx, x);
		perform_dda(&ray_cast, ctx);
		calculate_step(&ray_cast);

		if (ray_cast.side == 0)
			ray_cast.perpWallDist = ray_cast.sideDistX - ray_cast.deltaDistX;
		else
			ray_cast.perpWallDist = ray_cast.sideDistY - ray_cast.deltaDistY;

		ray_cast.lineHeight = (int)(WIN_HEIGHT / ray_cast.perpWallDist);

		calculate_pixel_to_fill(&ray_cast);

		x++;
	}
	return (0);
}
