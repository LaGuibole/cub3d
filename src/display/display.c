/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:47:36 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/27 12:31:50 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief Draws a single pixel to the image buffer without using mlxputpixel
/// @param img Reference to the img structure to modify
/// @param x Horizontal pixel position
/// @param y Vertical pixel position
/// @param color Pixel color in hexadeciaml format
void	put_pixel(t_img img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = img.img_addr + (y * img.line_len + x * (img.bit_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

/// @brief Renders the backgroumd by filling the top half with the ceiling
/// color and the bottom half with the floor color, then displays the image
/// @param ctx Pointer to the game context containing rendering data
/// @return Always returns 0
int	print_background(t_game *ctx)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			if (y > WIN_HEIGHT / 2)
				put_pixel(ctx->img, x, y, ctx->floor_color);
			else
				put_pixel(ctx->img, x, y, ctx->ceiling_color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img.img_ptr, 0, 0);
	return (0);
}
