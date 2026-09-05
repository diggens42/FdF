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
