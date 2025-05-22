/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:09:00 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/22 13:56:00 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_config_line(t_config *cfg, char **lines, int limit);
static int	validate_map(t_config *cfg);

/// @brief Parses the entire .cub file, separating config and map sections
/// @param cfg Pointer to the main configuration structure to populate
/// @param filepath Path to the .cub configuration file
/// @return RET_OK on success, RET_ERR on failure
int	parse_cub_file(t_config *cfg, char *filepath)
{
	char	**lines;
	int		map_start;

	lines = read_file_lines(filepath);
	if (!lines)
		return (fd_printf(STDERR_FILENO, "Error: failed to read file\n"),
			RET_ERR);
	map_start = find_map_start_index(lines);
	if (map_start == RET_NEG_ERR)
		return (fd_printf(STDERR_FILENO, "Error : no map found\n"), RET_ERR);
	if (!parse_config_line(cfg, lines, map_start))
		return (RET_ERR);
	if (parse_map(cfg, lines))
		return (RET_ERR);
	free_double_tab(lines);
	if (!validate_map(cfg))
		return (RET_ERR);
	return (RET_OK);
}

/// @brief Parses the configuration lines (tex, colors) before the map section
/// @param cfg Pointer to the configuration structure to fill
/// @param lines Array of string representing all lines from the .cub file
/// @param limit Index up to which configlines should be parsed (m_start)
/// @return 1 on success, 0 on error
static int	parse_config_line(t_config *cfg, char **lines, int limit)
{
	int	i;
	int	status;

	i = 0;
	while (i < limit)
	{
		status = parse_texture_line(lines[i], cfg);
		if (status == -1)
		{
			fd_printf(STDERR_FILENO, "Error at config line %d\n", i + 1);
			return (0);
		}
		i++;
	}
	return (1);
}

/// @brief Validates the map section by checking chars, player spawn and close
/// @param cfg Pointer to the configuration structure containing the map_ctx
/// @return 1 if the map is valid, 0 on error
static int	validate_map(t_config *cfg)
{
	if (!check_map_char(cfg->map_ctx.map))
		return (0);
	if (!check_player_spawn_count(cfg->map_ctx.map))
		return (0);
	if (!check_map_closed(cfg))
		return (0);
	return (1);
}
