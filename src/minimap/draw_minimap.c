/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:04:45 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/24 11:17:11 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(t_game *game)
{
	t_vec2	c;

	c.x = (int)game->player_pos.x;
	c.y = (int)game->player_pos.y;
	draw_minimap_tiles(game, c);
	draw_player_dot(game);
	draw_direction_ray(game);
}
