/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:12:04 by edelplan          #+#    #+#             */
/*   Updated: 2025/02/18 17:44:11 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TILE_SIZE 64
# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define ROTATION_SPEED 0.05
# define PLAYER_SPEED 0.05
# define FOV 66
# define FPS 70
# define NUM_RAYS WIN_WIDTH
# define MINIMAP_SCALE 0.1
# define PLAYER_SIZE 32
# define DEBUG 1
# define SUCCESS 0
# define FAILURE 1
# define CONTINUE 2
# define CHECK_NEXT_ELEMENT 3

# define DATA_INIT_FAIL "Error\nFailed to init game data.\n"
# define WRONG_FOV "Error\nFOV needs to be between 50 and 120\n"
# define INVALID_MAP "Error\nInvalid map format\n"
# define NOT_ENOUGH_DATA "Error\nNot enough data\n"
# define WRONG_RESOLUTION "Error\nResolution is unsupported\n"
# define NO_MAP_FOUND "Error\nNo map found\n"
# define INVALID_MAP_SYMBOLS "Error\nInvalid map symbols\n"
# define EMPTY_LINE_IN_MAP "Error\nEmpty line in map\n"
# define INVALID_START_POS_AMOUNT "Error\nInvalid start position amount\n"
# define INVALID_FLOOR_COLOR "Error\nInvalid floor color format\n"
# define INVALID_CEILING_COLOR "Error\nInvalid ceiling color format\n"
# define INVALID_FILE_EXTENSION "Error\nInvalid file extension.\n"
# define CANNOT_FIND_OPEN_FILE "Error\nCannot find or open file.\n"
# define MAP_NOT_CLOSED "Error\nMap has spaces or is not closed\n"
# define EMPTY_FILE "Error\nEmpty file\n"
# define TEXTURES_ERROR "Error\nError on textures\n"
# define INVALID_DATA "Error\nInvalid data\n"
# define INVALID_TEXTURE "Error\nInvalid texture data\n"
# define MAPDATA_IS_NULL "Error\nMapdata is NULL\n"
# define NULL_TEXTURE_PATH "Error\nTexture path is NULL\n"
# define FAILED_LOADING_TEXTURES "Error\nFailed to load textures.\n"
# define INVALID_FILE "Error\nInvalid file name\n"
# define CANNOT_OPEN_FILE "Error\nCannot find or open file.\n"
# define MLX_INIT_FAIL "Error\nFailed to initialize MLX\n"
# define RETURN_MAP_FAIL "Error\nFailed to return map\n"
# define NO_START_POSITION "Error\nNo start position for player\n"
# define WIN_CREATE_FAIL "Failed to create window\n"
# define EMPTY_LINE_IN_MAP "Error\nEmpty line in map\n"

# define NO "NO "
# define SO "SO "
# define WE "WE "
# define EA "EA "
# define F "F "
# define C "C "

# ifndef M_PI
#  define M_PI 3.14159265358979323846 /* pi */
# endif

# include <X11/X.h>
# include <X11/keysym.h>
# include <libft.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>

typedef enum e_cardinal_dir
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3
}				t_cardinal_dir;

typedef struct s_mapdata
{
	char		*no_txt_path;
	char		*so_txt_path;
	char		*we_txt_path;
	char		*ea_txt_path;
	int			f_rgb[3];
	int			c_rgb[3];
	char		**map;
	int			width;
	int			height;
	int			start_map;
}				t_mapdata;

typedef struct s_player
{
	double		x_pos;
	double		y_pos;
	char		start_direction;
	double		rot_angle;
}				t_player;

typedef struct s_input
{
	int			w_pressed;
	int			a_pressed;
	int			s_pressed;
	int			d_pressed;
	int			left_pressed;
	int			right_pressed;
	int			mouse_x;
	int			mouse_y;
}				t_input;

typedef struct s_wall_dir
{
	bool		north;
	bool		south;
	bool		east;
	bool		west;
}				t_wall_dir;

typedef struct s_ray
{
	double		angle;
	double		distance;
	double		wall_hit_x;
	double		wall_hit_y;
	double		ray_dir_x;
	double		ray_dir_y;
	bool		hit_vertical;
	t_wall_dir	wall_dir;
}				t_ray;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_camera
{
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_camera;

typedef struct s_point
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;
}				t_point;

typedef struct s_dda
{
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
}				t_dda;

typedef struct s_wall
{
	int			start;
	int			end;
	int			height;
	int			tex_x;
	double		wall_x;
}				t_wall;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	void		*textures[4];
	double		last_update;
	t_mapdata	*mapdata;
	t_input		*input;
	t_player	*player;
	t_ray		*rays;
	t_camera	*camera;
	t_img		*player_layer;
	t_img		*map_layer;
	t_img		*ray_layer;
	t_img		*wall_layer;
	t_img		*global_layer;
	t_img		*textures_buffer[4];
}				t_data;

typedef struct s_parse
{
	bool		textures_found[6];
	int			data_counter;
	int			count;
	char		*tmp;
}				t_parse;

int				init_layers(t_data *data);

// PARSING
// check_empty_lines.c

bool			check_virgules(char *values);

int				check_empty_lines(char *map);

// check_map_integrity.c

int				check_map_integrity(char *map, t_mapdata *mapdata);

// check_textures_presence_utils.c

void			skip_spaces(t_parse *parse);
int				check_empty_line(t_parse *parse, int *i);
int				handle_prefixes_part1(t_parse *parse, char *line);
int				handle_prefixes_part2(t_parse *parse, char *line);
int				handle_prefixes_part3(t_parse *parse, char *line);

// check_textures_presence.c

int				check_lines(t_parse *parse, char **texture_data, int *i);
int				check_textures_presence(char **texture_data,
					t_mapdata *mapdata);

// cub3d_utils.c

void			free_array(char **map);
int				convert_to_hex(int *rgb_value);
bool			set_texture_path(t_mapdata *mapdata, char *line,
					const char *identifier);

// destroy_handler_utils.c

void			free_texture_paths(t_mapdata *mapdata);
void			free_rays(t_data *data);
void			free_single_layer(void *mlx, t_img *layer);
void			free_layers(t_data *data);
void			free_textures_buffer(t_data *data);

// destroy_handler.c

int				on_destroy(t_data *data);

// flood_fill_helper.c

bool			is_valid_coord(char **map, int x, int y);
bool			is_valid_pos(char **map_array, int x, int y);

// flood_fill.c

char			**create_map_array(char *map, t_mapdata *mapdata);
bool			flood_fill(char **map, int x, int y);
bool			check_zero_neighbors(char **map_array, int x, int y);
bool			flood_fill_map(char **map_array);
int				check_if_closed(char *map, t_mapdata *mapdata);

// get_map.c
int				check_file_format(char *str, char *format);
int				check_fd_format(char *str, char *format, int fd);
int				check_fd_error(char *str, char *format, int fd);
char			*reading_map(char *read_map, char *tmp, char *oneline_file,
					int fd);

// parse_map.c
char			**get_texture_data(char *map, t_mapdata *mapdata);
char			*get_oneline_file(char *str);
int				check_map_validity(char **av, t_mapdata *mapdata);
char			**return_map(char **av, t_mapdata *mapdata);

// parse_textures.c
char			*get_texture_path(char *line, const char *identifier);
int				check_textures_data(t_mapdata *mapdata, char **texture_data);

// EXEC
int				on_destroy(t_data *data);
// game_init.c

int				init_player_pos(t_data *data, t_mapdata *mapdata,
					t_player *player);
int				game_init(t_data *data, char **av);

// game_loop.c

int				mlx_main_loop(t_data *data);

// player_movement_helper.c
int				find_start_pos(t_data *data, t_mapdata *mapdata);
int				find_start_rot_pos(t_data *data);
int				check_collision(t_data *data, double next_x, double next_y);
void			update_rotation(t_data *data, double turn_direction);
void			update_camera_plane(t_data *data, double turn_direction);

// player_movement.c

void			movement_handler(t_data *data);
int				handle_keypress(int keysym, t_data *data);
int				handle_keyrelease(int keysym, t_data *data);

// RENDER
// texture_handler.c

int				check_fd_error(char *str, char *format, int fd);
int				load_textures(t_data *data, t_mapdata *mapdata);

// render_init.c
int				ft_tablen(char **tab);

// rendering_tools.c

void			clear_layer(t_img *layer, int layer_size);

// raycast.c

void			cast_single_ray(t_data *data, t_ray *ray, int ray_id);
void			cast_rays(t_data *data);
void			project_walls(t_data *data);
void			put_pixel_to_layer(t_img *layer, int x, int y, int color);
// rendering.c

void			create_comp(t_data *data);

// raycast_tools.c

int				wall_hit(t_data *data, double x, double y);
double			normalize_angle(double angle);

// project_walls.c

int				get_texture_color(void *tex_data, int x, int y);
void			project_ceiling_floor(t_data *data);
void			calculate_wall_bounds(t_ray ray, int *start, int *end,
					int *height);
int				get_texture_number(t_ray ray);
double			calculate_wall_x(t_data *data, t_ray ray);

#endif
