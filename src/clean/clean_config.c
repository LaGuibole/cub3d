/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:23:59 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/20 18:10:17 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief Frees all dynamically allocated memory inside the config struct
/// @param cfg Pointer to the configuration structure to clean
void	clean_config(t_config *cfg)
{
	free(cfg->east_tex);
	free(cfg->north_tex);
	free(cfg->south_tex);
	free(cfg->west_tex);
	free(cfg->ceiling_tex);
	free(cfg->floor_tex);
	if (cfg->map)
		free_double_tab(cfg->map);
}
