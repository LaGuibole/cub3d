/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:23:59 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/19 18:53:45 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_config(t_config *cfg)
{
	free(cfg->east_tex);
	free(cfg->north_tex);
	free(cfg->south_tex);
	free(cfg->west_tex);
	free(cfg->ceiling_tex);
	free(cfg->floor_tex);
}
