/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:33:37 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/19 18:47:30 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_config(t_config *cfg)
{
	ft_printf("North: %s\n", cfg->north_tex);
	ft_printf("South: %s\n", cfg->south_tex);
	ft_printf("West: %s\n", cfg->west_tex);
	ft_printf("East: %s\n", cfg->east_tex);
	ft_printf("Floor: %s\n", cfg->floor_tex);
	ft_printf("Ceiling: %s\n", cfg->ceiling_tex);
}

int	main(int argc, char **argv)
{
	char		**lines;
	t_config	 config;
	int			i;

	config.map_name = argv[1];
	if (argc != 2)
		return (ft_printf("no good\n"), 1);
	if (has_valid_extension(&config) != 0)
		return (ft_printf("no good extension\n"), 1);
	lines = read_file_lines(argv[1]);
	if (!lines)
		return (ft_printf("error reading file\n"), 1);
	init_config(&config, argv);
	i = 0;
	while (lines[i])
	{
		if (!parse_texture_line(lines[i], &config))
			break ;
		i++;
	}
	print_config(&config);
	free_double_tab(lines);
	clean_config(&config);
	return (0);
}
