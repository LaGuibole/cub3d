/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:33:37 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/21 17:48:40 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	ft_printf("Map width = [%d], Map height = [%d]\n", cfg->map_ctx.width, cfg->map_ctx.height);
}

void	print_map(t_config *cfg)
{
	int	i = 0;
	ft_printf("Map Loaded: \n");
	while (cfg->map_ctx.map[i])
	{
		ft_printf("%s\n", cfg->map_ctx.map[i]);
		i++;
	}
}

// int	main(int argc, char **argv)
// {
// 	char		**lines;
// 	t_config	 config;
// 	int			i;
// 	int			status;
// 	int			map_start;

// 	config.map_name = argv[1];
// 	if (argc != 2)
// 		return (ft_printf("no good\n"), 1);
// 	if (has_valid_extension(&config) != 0)
// 		return (ft_printf("no good extension\n"), 1);
// 	init_config(&config, argv);
// 	lines = read_file_lines(argv[1]);
// 	if (!lines)
// 		return (ft_printf("error reading file\n"), 1);
// 	i = 0;
// 	map_start = find_map_start_index(lines);
// 	while (lines[i] && i < map_start)
// 	{
// 		status = parse_texture_line(lines[i], &config);
// 		if (status == -1)
// 		{
// 			ft_printf("Error : config error at line %d\n", i + 1);
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (parse_map(&config, lines) != RET_OK)
// 	{
// 		ft_printf("Map parsing failed\n");
// 		return (1);
// 	}
// 	print_config(&config);
// 	print_map(&config);
// 	free_double_tab(lines);
// 	clean_config(&config);
// 	return (0);
// }

int main (int argc, char **argv)
{
	t_config	config;

	if (argc != 2)
		return (fd_printf(STDERR_FILENO, "Usage: ./cub3d <map.cub>\n"), RET_ERR);
	init_config(&config, argv);
	config.map_name = argv[1];
	if (has_valid_extension(&config) != 0)
		return (fd_printf(STDERR_FILENO, "Error : Invalid file extension\n"), RET_ERR);
	if (parse_cub_file(&config, argv[1]) != RET_OK)
		return (clean_config(&config), RET_ERR);
	print_config(&config);
	print_map(&config);
	clean_config(&config);
	return (0);
}
