/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parse_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:00:19 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/22 19:57:14 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief Checks if a line corresponds to a configuration directive
/// (texture or color)
/// @param line The line to check from the .cub file
/// @return true if the line is a configuration line (NO, SO, WE, EA, F, or C),
/// false otherwise
bool	is_config_line(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0);
}

/// @brief
/// @param line
/// @return
bool	is_color_config_line(char *line)
{
	return (ft_strncmp(line, "C", 1) == 0
		|| ft_strncmp(line, "F", 1) == 0);
}

/// @brief
/// @param path
/// @return
int	is_valid_texture_path(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		return (fd_printf(STDERR_FILENO,
				"Error: invalid texture path: %s\n", path), RET_ERR);
	if (ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (fd_printf(STDERR_FILENO,
				"Error: texture must be a .xpm file: %s\n", path), RET_ERR);
	if (len == 4 || path[len - 5] == '/')
		return (fd_printf(STDERR_FILENO,
				"Error: filename is missing before .xpm: %s\n", path), RET_ERR);
	return (RET_OK);
}

/// @brief
/// @param path
void	sanitize_path(char *path)
{
	char	*tmp;

	if (!path)
		return ;
	tmp = ft_strchr(path, '\n');
	if (tmp)
		*tmp = '\0';
}

/// @brief
/// @param flags
/// @return
int	is_texture_missing(t_flags *flags)
{
	if (flags->f == 0)
		return (fd_printf(STDERR_FILENO,
				"Error: Floor textures is missing\n"), RET_ERR);
	if (flags->c == 0)
		return (fd_printf(STDERR_FILENO,
				"Error: Ceiling textures is missing\n"), RET_ERR);
	if (flags->no == 0)
		return (fd_printf(STDERR_FILENO,
				"Error: North textures is missing\n"), RET_ERR);
	if (flags->so == 0)
		return (fd_printf(STDERR_FILENO,
				"Error: South textures is missing\n"), RET_ERR);
	if (flags->ea == 0)
		return (fd_printf(STDERR_FILENO,
				"Error: East textures is missing\n"), RET_ERR);
	if (flags->we == 0)
		return (fd_printf(STDERR_FILENO,
				"Error: West textures is missing\n"), RET_ERR);
	return (RET_OK);
}
