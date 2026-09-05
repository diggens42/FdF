/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 17:29:30 by fwahl             #+#    #+#             */
/*   Updated: 2026/09/05 17:29:30 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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

void	draw_line(mlx_image_t *img, t_point a, t_point b)
{
		t_line  line;


		if (check_off_screen(img, a, b))
			return ;
		init_line(&line, a, b);
}