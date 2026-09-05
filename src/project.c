/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 16:42:43 by fwahl             #+#    #+#             */
/*   Updated: 2026/09/05 19:55:40 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/**
 * turns grid coordinates into isometric screen coordinates,
 * centered on the map and scaled by zoom and offset
 */
t_point	project_point(t_fdf *fdf, int x, int y)
{
	t_cam	*cam;
	t_point	pt;
	double	wx;
	double	wy;
	double	wz;

	cam = &fdf->cam;
	wx = x - (fdf->map.width - 1) / 2.0;
	wy = y - (fdf->map.height - 1) / 2.0;
	wz = fdf->map.points[y * fdf->map.width + x];
	pt.x = (int)((wx - wy) * cos(M_PI / 6) * cam->zoom) + cam->x_offset;
	pt.y = (int)(((wx + wy) * sin(M_PI / 6) - wz) * cam->zoom) + cam->y_offset;
	return (pt);
}
