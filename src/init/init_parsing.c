/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:16:06 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/19 19:44:00 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief Initializes all fields of the configuration structure to default
/// @param cfg Pointer to the configuration structure to init
/// @param argv Command-line argument, used to set the map name
void	init_config(t_config *cfg, char **argv)
{
	cfg->north_tex = NULL;
	cfg->south_tex = NULL;
	cfg->east_tex = NULL;
	cfg->west_tex = NULL;
	cfg->ceiling_tex = NULL;
	cfg->floor_tex = NULL;
	cfg->map_name = argv[1];
	init_flags(&cfg->flags);
}

/// @brief Initializes all parsing flags to zero
/// @param flags Pointer to the flags structure to init
void	init_flags(t_flags *flags)
{
	flags->no = 0;
	flags->so = 0;
	flags->we = 0;
	flags->ea = 0;
	flags->c = 0;
	flags->f = 0;
}
