/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:49:17 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/19 18:51:57 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief A function to check if the map has .cub extension
/// @param filename will be argv[1] so the map file
/// @return 0 if map has .cub, 1 otherwise
int	has_valid_extension(t_config *filename)
{
	char	*str_cpy;

	if (!filename->map_name || ft_strlen(filename->map_name) <= 4)
		return (1);
	str_cpy = filename->map_name + ft_strlen(filename->map_name) - 4;
	return (ft_strcmp(str_cpy, ".cub"));
}

int	parse_texture_line(char *line, t_config *cfg)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
		return (free_double_tab(split), 0);
	if (ft_strcmp(split[0], "NO") == 0)
		cfg->north_tex = ft_strdup(split[1]);
	else if (ft_strcmp(split[0], "SO") == 0)
		cfg->south_tex = ft_strdup(split[1]);
	else if (ft_strcmp(split[0], "WE") == 0)
		cfg->west_tex = ft_strdup(split[1]);
	else if (ft_strcmp(split[0], "EA") == 0)
		cfg->east_tex = ft_strdup(split[1]);
	else if (ft_strcmp(split[0], "F") == 0)
		cfg->floor_tex = ft_strdup(split[1]);
	else if (ft_strcmp(split[0], "C") == 0)
		cfg->ceiling_tex = ft_strdup(split[1]);
	else
	{
		free_double_tab(split);
		return (0);
	}
	free_double_tab(split);
	return (1);
}

