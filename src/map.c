/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 23:56:56 by fwahl             #+#    #+#             */
/*   Updated: 2026/09/01 23:56:56 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	allocate_map(t_fdf *fdf, int width, int height)
{
	if (width <= 0 || height <= 0)
		ft_error(fdf, "fdf: map has no points\n", ERR_USER);
	fdf->map.pts = ft_calloc((size_t)width * height, sizeof(t_point));
	if (!fdf->map.pts)
		ft_error(fdf, "malloc failed in map_alloc", ERR_SYS);
	fdf->map.width = width;
	fdf->map.height = height;
}