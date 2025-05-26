/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:36:11 by guphilip          #+#    #+#             */
/*   Updated: 2025/05/24 13:07:39 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>

// TO SORT DEFINES
# define RED_PIXEL 0xFF0000

// WINDOWS DEFINES

# define WIN_WIDTH 1920
# define WIN_HEIGHT 960

// MAP ASSETS

# define WALL	'1'
# define VOID	' '
# define FLOOR	'0'
# define PLAYER	'P'
# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_EAST 2
# define TEX_WEST 3
# define TEX_COUNT 4

// FILE EXTENSION

# define EXT_XPM ".xpm"
# define EXT_CUB ".cub"

// RETURN DEFINES

# define RET_OK	0
# define RET_ERR 1
# define RET_NEG_ERR -1

// HOOKS DEFINES

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define UP 65362
# define LEFT 65361
# define RIGHT 65363
# define DOWN 65364

# define ROT_SPEED 0.03
# define PLAYER_SPEED 0.05

// MINIMAP

# define MINI_TILE_SIZE 5
# define MINI_MAP_RADIUS 10

// PARSING
typedef struct s_flags
{
	int	so;
	int	no;
	int	we;
	int	ea;
	int	f;
	int	c;
}	t_flags;

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_map_ctx
{
	char	**map;
	char	**copy;
	int		width;
	int		height;
	t_vec2	player_pos;
	char	player_dir;
}	t_map_ctx;

typedef struct s_config
{
	char		*map_name;
	char		**map;
	int			map_width;
	int			map_height;
	char		*north_tex;
	char		*south_tex;
	char		*west_tex;
	char		*east_tex;
	char		*floor_tex;
	char		*ceiling_tex;
	int			ceiling_rgb[3];
	int			floor_rgb[3];
	int			player_spawn;
	long		floor_color;
	long		ceiling_color;
	int			no_fd;
	int			so_fd;
	int			we_fd;
	int			ea_fd;
	t_flags		flags;
	t_map_ctx	map_ctx;
}	t_config;

// IMG STRUCT
typedef struct s_img
{
	void	*img_ptr;
	char	*img_addr;
	int		bit_per_pixel;
	int		line_len;
	int		endian;
	int		color;
}	t_img;

// RAY-CASTING STRUCT
typedef struct s_ray_casting
{
	int		w;
	int		h;

	double	pPosX;
	double	pPosY;

	int		stepX;
	int		stepY;

	int		mapX;
	int		mapY;
	int		lineHeight;

	double	perpWallDist;
	int		hit;
	int		side;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;

	double	cameraX;
	double	dirX;
	double	dirY;

	int		drawStart;
	int		drawEnd;
	int		texNum;
	int		texX;
}	t_ray_casting;

// GAME STRUCT
typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_vec2	player_pos;
	long	floor_color;
	long	ceiling_color;
	t_img	*textures[TEX_COUNT];
	int		wall_height;
	int		wall_width;
	t_vec2	player_plane;
	t_vec2	player_dir;
	char	dir_char;
	t_img	img;
	char	**map;
	int		map_height;
	int		map_width;
}	t_game;

//CLEAN
	//CLEAN_CONFIG.C
void	clean_config(t_config *cfg);
int		free_config_and_lines(t_config *cfg, char **lines, int ret);
	//CLEAN_CONTEXT.C
int		clean_context(t_game *ctx);
int		close_window(t_game *ctx);
int		clean_and_exit(t_game *ctx);
	//CLEAN_EXIT_GAME.C
void	exit_game(t_game *game);

//DISPLAY
	//DISPLAY.C
void	put_pixel(t_img img, int x, int y, int color);
int		print_background(t_game *ctx);
	//INIT_DISPLAY.C
int		init_dda(t_ray_casting *ray_cast, t_game *ctx);
int		init_ray_struct(t_ray_casting *ray_cast, t_game *ctx, int x);
	//PLAYER_ANGLE.C
void	player_angle(t_game *ctx);
	//RAY_CASTING.C
int		calculate_pixel_to_fill(t_ray_casting *ray_cast, t_game *game, int x);
int		perform_dda(t_ray_casting *ray_cast, t_game *ctx);
int		ray_casting(t_game *ctx);
	//WALL.C
void	calc_wall_dist(t_ray_casting *ray_cast, t_game *ctx);
void	draw_textured_column(t_ray_casting *r, t_game *g, int x);
void	pick_texture_and_texx(t_ray_casting *r, t_game *g);

// INIT
	//INIT_GAME.C
void	init_game_parser(t_game *game);
void	init_game_from_config(t_game *game, t_config *cfg);
	//INIT_MAP_TEXTURES.C
void	init_textures_fds(t_config *cfg);
void	set_floor_ceiling_colors(t_game *game, t_config *cfg);
int		check_textures_accessibility(t_config *cfg);
	//INIT_PARSING.C
void	init_config(t_config *cfg, char **argv);

//INPUTS
	//CAMERA.C
void	rotate_right(t_game *game);
void	rotate_left(t_game *game);
	//HANDLE_INPUTS.C
int		hook_handler(int keycode, t_game *ctx);
int		claim_hooks( t_game *ctx);
	//MOVE.C
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);

//LOAD
	//LOAD_WALLS.C
void	load_walls(t_game *g, t_config *cfg);

//MINIMAP
	//DRAW_MINIMAP.C
void	draw_minimap(t_game *game);
	//MINIMAP_UTILS.C
void	draw_square(t_game *game, int px, int py, int color);
void	draw_player_dot(t_game *game);
void	draw_direction_ray(t_game *game);
int		get_tile_color(t_game *game, t_vec2 map);
void	draw_minimap_tiles(t_game *game, t_vec2 c);

//PARSING
	//CONFIG_PARSE_UTILS.C
bool	is_config_line(char *line);
bool	is_color_config_line(char *line);
int		is_valid_texture_path(char *path);
void	sanitize_path(char *path);
int		is_texture_missing(t_flags *flags);
	//COPY_MAP.C
char	**copy_map(char **src);
	//GAME_PARSER_UTILS.C
bool	is_map_line(char *line);
int		is_player_spawn(char c);
void	find_player_pos(t_map_ctx *map);
	//GLOBAL_PARSER.C
int		parse_cub_file(t_config *cfg, char *filepath);
	//PARSE_COLOR.C
int		parse_rgb_values(char *line, int *dest);
int		get_rgba(int r, int g, int b);
	//PARSE_CONFIG.C
int		has_valid_extension(t_config *filename);
int		mark_seen(t_flags *f, char *id);
int		parse_texture_line(char *line, t_config *cfg);
	//PARSE_MAP.C
int		find_map_start_index(char **lines);
char	**extract_map(char **lines, int start, int height);
int		parse_map(t_config *cfg, char **lines);
	//PREPARE_FLOOD_FILL.C
char	**rectangularize_map(char **map, int height, int width);
char	**prepare_map_for_flood(char **map, int height, int width);
	//PREPARE_MAP_CHECKS.C
int		validate_map_block(char **lines, int start, int *width, int *height);
	//READ_MAP.C
char	**read_file_lines(char *filepath);
	//VALIDATE_MAP_CHAR.C
int		check_map_char(char **map);
int		check_player_spawn_count(char **map);
	//VALIDATE_MAP_FLOOD.C
int		check_map_closed(t_config *cfg);
bool	flood_fill(t_map_ctx *map_ctx, int x, int y);

#endif
