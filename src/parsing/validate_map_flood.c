/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_flood.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:13:02 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/22 18:42:50 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_map_copy_for_flood(t_config *cfg);
static int	should_flood_from(char c);
static int	handle_open_map(t_map_ctx *ctx);

/// @brief Performs a recursive flood algo tocheck if the map is fully enclosed
/// @param map_ctx Pointer to the map context containing the copy of the map
/// @param x Current x-coordinate in the map
/// @param y Current y-coordinate in the map
/// @return true if the area is enclosed, false if an open space is found
bool	flood_fill(t_map_ctx *map_ctx, int x, int y)
{
	if (y < 0 || y >= map_ctx->height || x < 0 || x >= map_ctx->width)
		return (false);
	if (map_ctx->copy[y][x] == '1' || map_ctx->copy[y][x] == 'V')
		return (true);
	if (map_ctx->copy[y][x] == ' ')
		return (false);
	map_ctx->copy[y][x] = 'V';
	return (
		flood_fill(map_ctx, x + 1, y)
		&& flood_fill(map_ctx, x - 1, y)
		&& flood_fill(map_ctx, x, y + 1)
		&& flood_fill(map_ctx, x, y - 1)
	);
}

/// @brief Verifies that the map is properly enclosed by walls using
/// flood fill from valid points
/// @param cfg Pointer to the configuration structure containing the map context
/// @return 1 if the map is closed, 0 if an open area is detected
int	check_map_closed(t_config *cfg)
{
	int		y;
	int		x;

	if (!init_map_copy_for_flood(cfg))
		return (0);
	y = 0;
	while (y < cfg->map_ctx.height)
	{
		x = 0;
		while (x < cfg->map_ctx.width)
		{
			if (should_flood_from(cfg->map_ctx.copy[y][x]))
			{
				if (!flood_fill(&cfg->map_ctx, x, y))
					return (handle_open_map(&cfg->map_ctx));
			}
			x++;
		}
		y++;
	}
	free_double_tab(cfg->map_ctx.copy);
	return (1);
}

/// @brief Initializes the map copy used for flood fill checking.
/// @param cfg Pointer to the configuration structure containing the map ctx
/// @return 1 on successful initialization, 0 on failure (with error message)
static int	init_map_copy_for_flood(t_config *cfg)
{
	cfg->map_ctx.copy = prepare_map_for_flood(
			cfg->map_ctx.map, cfg->map_ctx.height, cfg->map_ctx.width);
	if (!cfg->map_ctx.copy)
	{
		fd_printf(STDERR_FILENO, "Error: map copy failed\n");
		return (0);
	}
	return (1);
}

/// @brief Determines whether a character is a valid start point for flood fill
/// @param c The character to test
/// @return 1 if the char is a floor tile ('0') or a player spawn, 0 otherwise
static int	should_flood_from(char c)
{
	return ((c == '0' || is_player_spawn(c)) && c != 'V');
}

static int	handle_open_map(t_map_ctx *ctx)
{
	free_double_tab(ctx->copy);
	fd_printf(STDERR_FILENO, "Error : map is not closed\n");
	return (0);
}
