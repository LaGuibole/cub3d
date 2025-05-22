/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:36:11 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/20 08:10:51 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>

// TO SORT DEFINES
#define RED_PIXEL 0xFF0000

// WINDOWS DEFINES

# define	WIN_WIDTH 1920
# define	WIN_HEIGHT 960

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

// IMG STRUCT
typedef struct s_img
{
	void	*img_ptr;
	char	*img_addr;
	int		bit_per_pixel;
	int		line_len;
	int		endian;
	int		color;
} t_img;

// RAY-CASTING STRUCT
typedef struct s_ray_casting
{
	int		w;
	int 	h;

	double	pPosX;
	double	pPosY;

	int		stepX;
	int		stepY;

	int		mapX;
	int		mapY;
	int		lineHeight;

	double	dirPosX;
	double	dirPosY;

	double	planeX;
	double	planeY;

	double	perpWallDist;
	int		hit;
	int		side;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;

	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	dirX;
	double	dirY;

	int		drawStart;
	int 	drawEnd;

} t_ray_casting;

// GAME STRUCT
typedef	struct s_game
{
	void	*mlx;
	void	*win;
	t_img	img;
} t_game;

int		has_valid_extension(t_config *filename);
char	**read_file_lines(char *filepath);
int		parse_texture_line(char *line, t_config *cfg);
void	init_config(t_config *cfg, char **argv);
void	clean_config(t_config *cfg);
void	init_flags(t_flags *flags);
int		clean_context(t_game *ctx);
int		clean_and_exit(t_game *ctx);
int 	close_window(t_game *ctx);
int 	claim_hooks(t_game *ctx);
int		update_game_display(t_game *ctx);
void	put_pixel(t_img img, int x, int y, int color);
int		print_background(t_game ctx);

#endif
