/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:09:00 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/21 17:47:48 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_config_line(t_config *cfg, char **lines, int limit);
static int	validate_map(t_config *cfg);


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
		return (free_double_tab(lines),
			fd_printf(STDERR_FILENO, "Error : no map found\n"), RET_ERR);
	if (!parse_config_line(cfg, lines, map_start))
		return (free_double_tab(lines), RET_ERR);
	if (parse_map(cfg, lines))
		return (free_double_tab(lines), RET_ERR);
	free_double_tab(lines);
	if (!validate_map(cfg))
		return (clean_config(cfg), RET_ERR);
	return (RET_OK);
}

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

