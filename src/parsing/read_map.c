/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:06:56 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/19 19:49:40 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**add_line(char **lines, char *new_line, int count);

/// @brief Reads all lines from the file and stores them in a null-term arr
/// @param filepath Path to the .cub file to read
/// @return A null-terminated arr of strings containing the file's lines or NUL
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

/// @brief Dynamically adds a new line to an existing arr of strings
/// @param lines The current array of strings (can be NULL)
/// @param new_line The new line to append to the array
/// @param count The current number of lines in the array
/// @return A new null-terminated array including the new line, or NULL fail
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
