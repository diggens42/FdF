/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 17:01:19 by fwahl             #+#    #+#             */
/*   Updated: 2026/08/29 17:01:19 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "MLX42/MLX42.h"
# include "libft.h"

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

# define ERR_USER 0
# define ERR_SYS 1

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

typedef struct s_line
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line;

typedef struct s_cam
{
	double	zoom;
	int		x_offset;
	int		y_offset;
} t_cam;

typedef struct s_map
{
	int		*points;
	int		width;
	int		height;
	int		z_min;
	int		z_max;
} t_map;

typedef struct s_fdf
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		map;
	t_cam		cam;
	t_list		*map_rows;
	char		**map_tokens;
} t_fdf;

//utils.c
void	ft_error(t_fdf *fdf, char *err_msg, int err_code);
void	free_fdf(t_fdf *fdf);

//map.c
void	allocate_map(t_fdf *fdf, int width, int height);
void	set_map_bounds(t_map *map);
void	free_map(t_map *map);

//parse.c
void	parse_map(t_fdf *fdf, char *map_path);

//project.c
t_point	project_point(t_fdf *fdf, t_point point);

//draw.c
void	draw_line(mlx_image_t *img, t_point a, t_point b);

#endif
