/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:36:11 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/19 19:35:36 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>

// WINDOWS DEFINES

# define	WIN_WIDTH 1920
# define	WIN_HEIGHT 1080

// MAP ASSETS

# define	WALL	'1'
# define	VOID	' '
# define	FLOOR	'0'
# define	PLAYER	'P'

// FILE EXTENSION

# define	EXT_XPM ".xpm"
# define	EXT_CUB ".cub"

// RETURN DEFINES

# define	RET_OK	0
# define	RET_ERR	1
# define	RET_NEG_ERR -1

// HOOKS DEFINES

# define	ESC 65307
# define	W 119
# define	A 97
# define	S 115
# define	D 100
# define	UP 65362
# define	LEFT 65361
# define	RIGHT 65363
# define	DOWN 65364

// PARSING
typedef struct s_flags
{
	int	no;
	int so;
	int we;
	int ea;
	int	f;
	int	c;
} t_flags;


typedef	struct s_config
{
	char	*map_name;
	char	*north_tex;
	char	*south_tex;
	char	*west_tex;
	char	*east_tex;
	char	*floor_tex;
	char	*ceiling_tex;
	t_flags	flags;
} t_config;

// GAME STRUCT

typedef	struct s_game
{
	void	*mlx;
	void	*win;
} t_game;

int	has_valid_extension(t_config *filename);
char	**read_file_lines(char *filepath);
int	parse_texture_line(char *line, t_config *cfg);
void	init_config(t_config *cfg, char **argv);
void	clean_config(t_config *cfg);
void	init_flags(t_flags *flags);


#endif
