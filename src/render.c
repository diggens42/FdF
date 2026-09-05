/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 18:41:27 by fwahl             #+#    #+#             */
/*   Updated: 2026/09/05 18:41:27 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	fit_view(t_fdf *fdf)
{
	double	span_x;
	double	span_y;

	span_x = (fdf->map.width + fdf->map.height) * cos(M_PI / 6);
	span_y = (fdf->map.width + fdf->map.height) * sin(M_PI / 6)
		+ (fdf->map.z_max - fdf->map.z_min);
	if (span_x < 0.001)
		span_x = 0.001;
	if (span_y < 0.001)
		span_y = 0.001;
	fdf->cam.zoom = FIT_MARGIN * WIN_WIDTH / span_x;
	if (WIN_HEIGHT / span_y < WIN_WIDTH / span_x)
		fdf->cam.zoom = FIT_MARGIN * WIN_HEIGHT / span_y;
	fdf->cam.x_offset = WIN_WIDTH / 2;
	fdf->cam.y_offset = WIN_HEIGHT / 2
		+ (int)((fdf->map.z_min + fdf->map.z_max) / 2.0 * fdf->cam.zoom);
}

static void	clear_image(mlx_image_t *img)
{
	ft_memset(img->pixels, 0, (size_t)img->width * img->height * 4);
}

void	render(t_fdf *fdf)
{
	int	x;
	int	y;

	clear_image(fdf->img);
	y = -1;
	while (++y < fdf->map.height)
	{
		x = -1;
		while (++x < fdf->map.width)
		{
			if (x + 1 < fdf->map.width)
				draw_line(fdf->img, project_point(fdf, x, y),
					project_point(fdf, x + 1, y));
			if (y + 1 < fdf->map.height)
				draw_line(fdf->img, project_point(fdf, x, y),
					project_point(fdf, x, y + 1));
		}
	}
}
