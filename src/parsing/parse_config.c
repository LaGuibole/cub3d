/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:49:17 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/19 19:46:51 by guphilip         ###   ########.fr       */
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

/// @brief Marks a configuration identifier as seen, and checks for duplicata
/// @param f Pointer to the flags structure tracking seen identifiers
/// @param id Configuration identifer (e.g "NO" "F", "C")
/// @return -1 if the id has already been seen, 0 otherwise
int	mark_seen(t_flags *f, char *id)
{
	if (ft_strcmp(id, "NO") == 0 && ++f->no > 1)
		return (-1);
	if (ft_strcmp(id, "SO") == 0 && ++f->so > 1)
		return (-1);
	if (ft_strcmp(id, "WE") == 0 && ++f->we > 1)
		return (-1);
	if (ft_strcmp(id, "EA") == 0 && ++f->ea > 1)
		return (-1);
	if (ft_strcmp(id, "F") == 0 && ++f->f > 1)
		return (-1);
	if (ft_strcmp(id, "C") == 0 && ++f->c > 1)
		return (-1);
	return (0);
}

/// @brief Parses a configuration line and stores its value in the config
/// @param line Line from the .cub file to parse (e.g "NO ./path")
/// @param cfg Pointer to the configuration structure to populate
/// @return 1 if successfully parsed, 0 if the line is unrelated, -1 if duplica
int	parse_texture_line(char *line, t_config *cfg)
{
	char	**split;
	int		status;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
		return (free_double_tab(split), 0);
	status = mark_seen(&cfg->flags, split[0]);
	if (status == -1)
		return (free_double_tab(split), -1);
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
		return(free_double_tab(split), 0);
	free_double_tab(split);
	return (1);
}

