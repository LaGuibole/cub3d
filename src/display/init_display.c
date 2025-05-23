/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:45:01 by jbastard          #+#    #+#             */
/*   Updated: 2025/05/20 11:45:03 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/// @brief Print pixel at img address without mlx_put_pixel (+ opti)
/// @param img Reference to the image struct for editing
/// @param color Color in hexadecimal
void put_pixel(t_img img, int x, int y, int color)
{
	char *dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = img.img_addr + (y * img.line_len + x * (img.bit_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

//Attention : color doit etre changee par get_rgba quand le parsing le mettra a disposition.
int	print_background(t_game *ctx)
{
	int x;
	int y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			if (y > WIN_HEIGHT / 2)
				put_pixel(ctx->img, x, y, 14443520);
			else
				put_pixel(ctx->img, x, y, 14443775);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img.img_ptr, 0, 0);
	return (0);
}

int	update_game_display(t_game *ctx)
{
	(void)ctx;
	return (0);
}
