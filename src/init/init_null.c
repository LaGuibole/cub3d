/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_null.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:16:06 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/19 18:47:58 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_config(t_config *cfg, char **argv)
{
	cfg->north_tex = NULL;
	cfg->south_tex = NULL;
	cfg->east_tex = NULL;
	cfg->west_tex = NULL;
	cfg->ceiling_tex = NULL;
	cfg->floor_tex = NULL;
	cfg->map_name = argv[1];
}
