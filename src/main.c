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

#include "../includes/cub3d.h"

void	print_map(t_config *cfg)
{
	int	i;

	i = 0;
	ft_printf("Map Loaded: \n");
	while (cfg->map_ctx.map[i])
	{
		ft_printf("%s\n", cfg->map_ctx.map[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_game		ctx;
	t_config	config;
	ctx = (t_game){0};
	ctx.mlx = mlx_init();

	ctx.win = mlx_new_window(ctx.mlx, WIN_WIDTH, WIN_HEIGHT, "cube3d");

	ctx.img.img_ptr = mlx_new_image(ctx.mlx, WIN_WIDTH, WIN_HEIGHT);
	ctx.img.img_addr = mlx_get_data_addr(ctx.img.img_ptr, &ctx.img.bit_per_pixel, &ctx.img.line_len, &ctx.img.endian);
	claim_hooks(&ctx);

	if (argc != 2)
		return (fd_printf(STDERR_FILENO, "Usage: ./cub3d <map.cub>\n"),
			RET_ERR);
	init_config(&config, argv);
	config.map_name = argv[1];
	if (has_valid_extension(&config) != 0)
		return (fd_printf(STDERR_FILENO,
				"Error : Invalid file extension\n"), RET_ERR);
	if (parse_cub_file(&config, argv[1]) != RET_OK)
		return (RET_ERR);
	init_game_from_config(&ctx, &config);
	print_map(&config);
	ray_casting(&ctx);
	clean_config(&config);
	mlx_loop(ctx.mlx);
	return (0);
}
