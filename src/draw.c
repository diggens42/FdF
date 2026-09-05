/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 17:29:30 by fwahl             #+#    #+#             */
/*   Updated: 2026/09/05 18:51:10 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/**
 * sets up the bresenham values: deltas, step direction and error
 */
static void	init_line(t_line *line, t_point a, t_point b)
{
	line->dx = ft_abs(b.x - a.x);
	line->dy = -ft_abs(b.y - a.y);
	line->sx = -1;
	if (a.x < b.x)
		line->sx = 1;
	line->sy = -1;
	if (a.y < b.y)
		line->sy = 1;
	line->err = line->dx + line->dy;
}

/**
 * true if the whole line lies outside the window
 */
static bool	check_off_screen(mlx_image_t *img, t_point a, t_point b)
{
	if (a.x < 0 && b.x < 0)
		return (true);
	if (a.y < 0 && b.y < 0)
		return (true);
	if (a.x >= (int)img->width && b.x >= (int)img->width)
		return (true);
	if (a.y >= (int)img->height && b.y >= (int)img->height)
		return (true);
	return (false);
}

/**
 * puts one pixel, skips it if it lies outside the image
 */
static void	put_pixel(mlx_image_t *img, t_point p)
{
	if (p.x < 0 || p.y < 0)
		return ;
	if (p.x >= (int)img->width || p.y >= (int)img->height)
		return ;
	mlx_put_pixel(img, (uint32_t)p.x, (uint32_t)p.y, COLOR_LINE);
}

/**
 * moves the point one step closer to the end of the line
 */
static void	line_step(t_line *line, t_point *p)
{
	int	err_2;

	err_2 = 2 * line->err;
	if (err_2 >= line->dy)
	{
		line->err += line->dy;
		p->x += line->sx;
	}
	if (err_2 <= line->dx)
	{
		line->err += line->dx;
		p->y += line->sy;
	}
}

/**
 * draws a line between two points with bresenham
 */
void	draw_line(mlx_image_t *img, t_point a, t_point b)
{
	t_line	line;
	t_point	pt;

	if (check_off_screen(img, a, b))
		return ;
	init_line(&line, a, b);
	pt = a;
	while (true)
	{
		put_pixel(img, pt);
		if (pt.x == b.x && pt.y == b.y)
			break ;
		line_step(&line, &pt);
	}
}
