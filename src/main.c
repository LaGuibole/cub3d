/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:33:37 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/19 19:35:01 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int game_loop(t_game *ctx)
{
	(void)ctx;
	return (0);
}

int main(void)
{
	t_game	ctx;

	ctx = (t_game){0};
	ctx.mlx = mlx_init();

	ctx.win = mlx_new_window(ctx.mlx, WIN_WIDTH, WIN_HEIGHT, "cube3d");

	ctx.img.img_ptr = mlx_new_image(ctx.mlx, WIN_WIDTH, WIN_HEIGHT);
	ctx.img.img_addr = mlx_get_data_addr(ctx.img.img_ptr, &ctx.img.bit_per_pixel, &ctx.img.line_len, &ctx.img.endian);

	update_game_display(&ctx);
	claim_hooks(&ctx);
	mlx_loop(ctx.mlx);
}
