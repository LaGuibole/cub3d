/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:33:37 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/27 17:19:09 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_config(t_config *cfg, char *filepath)
{
	if (has_valid_extension(cfg) != RET_OK)
		return (fd_printf(STDERR_FILENO,
				"Error: Invalid file extension\n"), RET_ERR);
	if (parse_cub_file(cfg, filepath) != RET_OK)
		return (RET_ERR);
	if (check_textures_accessibility(cfg) != RET_OK)
		return (RET_OK);
	return (RET_OK);
}

static int	init_mlx(t_game *ctx)
{
	ctx->mlx = mlx_init();
	if (!ctx->mlx)
		return (fd_printf(STDERR_FILENO, "Error: mlx_init_failed\n"), RET_ERR);
	ctx->win = mlx_new_window(ctx->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!ctx->win)
		return (fd_printf(STDERR_FILENO, "Error: window creation failed\n"),
			RET_ERR);
	ctx->img.img_ptr = mlx_new_image(ctx->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!ctx->img.img_ptr)
		return (fd_printf(STDERR_FILENO,
				"Error: image creation failed\n"), RET_ERR);
	ctx->img.img_addr = mlx_get_data_addr(ctx->img.img_ptr,
			&ctx->img.bit_per_pixel,
			&ctx->img.line_len,
			&ctx->img.endian);
	if (!ctx->img.img_addr)
		return (fd_printf(STDERR_FILENO,
				"Error: get_data_addr failed\n"), RET_ERR);
	return (RET_OK);
}

int	main(int argc, char **argv)
{
	t_game		ctx;
	t_config	cfg;

	if (argc != 2)
		return (fd_printf(STDERR_FILENO,
				"Usage: ./cub3d <map.cub>\n"), RET_ERR);
	ctx = (t_game){0};
	init_config(&cfg, argv);
	init_game_parser(&ctx);
	cfg.map_name = argv[1];
	if (validate_config(&cfg, argv[1]) != RET_OK)
		return (RET_ERR);
	init_game_from_config(&ctx, &cfg);
	player_angle(&ctx);
	if (init_mlx(&ctx) != RET_OK)
		return (RET_ERR);
	load_walls(&ctx, &cfg);
	claim_hooks(&ctx);
	mlx_loop_hook(ctx.mlx, ray_casting, &ctx);
	clean_config(&cfg);
	mlx_loop(ctx.mlx);
	return (RET_OK);
}
