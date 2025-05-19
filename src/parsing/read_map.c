/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:06:56 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/19 18:25:38 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**add_line(char **lines, char *new_line, int count);

char	**read_file_lines(char *filepath)
{
	int		fd;
	char	*line;
	char	**lines;
	int		count;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lines = NULL;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines = add_line(lines, line, count);
		if (!lines)
			break ;
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

static char	**add_line(char **lines, char *new_line, int count)
{
	char	**new_tab;
	int		i;

	new_tab = malloc(sizeof(char *) * (count + 2));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_tab[i] = lines[i];
		i++;
	}
	new_tab[i++] = new_line;
	new_tab[i] = NULL;
	free(lines);
	return (new_tab);
}
