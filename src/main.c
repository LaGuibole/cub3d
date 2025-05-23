/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:33:37 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/23 12:30:40 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_config(t_config *cfg)
{
	ft_printf("North: %s\n", cfg->north_tex);
	ft_printf("South: %s\n", cfg->south_tex);
	ft_printf("West: %s\n", cfg->west_tex);
	ft_printf("East: %s\n", cfg->east_tex);
	ft_printf("Floor Red: %d\n", cfg->floor_rgb[0]);
	ft_printf("Floor Green: %d\n", cfg->floor_rgb[1]);
	ft_printf("Floor Blue: %d\n\n", cfg->floor_rgb[2]);
	ft_printf("Ceiling Red: %d\n", cfg->ceiling_rgb[0]);
	ft_printf("Ceiling Green: %d\n", cfg->ceiling_rgb[1]);
	ft_printf("Ceiling Blue: %d\n\n", cfg->ceiling_rgb[2]);
	ft_printf("Map width = [%d], Map height = [%d]\n",
		cfg->map_ctx.width, cfg->map_ctx.height);
	printf("Player Pos x = [%.2f], y = [%.2f]\n", cfg->map_ctx.player_pos.x, cfg->map_ctx.player_pos.y);
	ft_printf("Player Dir = [%c]\n", cfg->map_ctx.player_dir);
}

// void	print_map(t_config *cfg)
// {
// 	int	i;

// 	i = 0;
// 	ft_printf("Map Loaded: \n");
// 	while (cfg->map_ctx.map[i])
// 	{
// 		ft_printf("%s\n", cfg->map_ctx.map[i]);
// 		i++;
// 	}
// }

void	print_map(char **map)
{
	int	i;

	i = 0;
	ft_printf("Map Loaded: \n");
	while (map[i])
	{
		ft_printf("%s\n", map[i]);
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
	init_game_parser(&game);
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
	if (game.map)
		free_double_tab(game.map);
	mlx_loop(ctx.mlx);
	return (0);
}
