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

/**
 * allocates the point grid and saves the map dimensions
 */
void	allocate_map(t_fdf *fdf, int width, int height)
{
	if (width <= 0 || height <= 0)
		ft_error(fdf, "fdf: map has no points\n", ERR_USER);
	fdf->map.points = ft_calloc((size_t)width * height, sizeof(int));
	if (!fdf->map.points)
		ft_error(fdf, "malloc failed in allocate_map\n", ERR_SYS);
	fdf->map.width = width;
	fdf->map.height = height;
}

/**
 * finds the lowest and highest altitude in the map
 */
void	set_map_bounds(t_map *map)
{
	int	i;
	int	total;

	total = map->width * map->height;
	map->z_min = map->points[0];
	map->z_max = map->points[0];
	i = 0;
	while (++i < total)
	{
		if (map->points[i] < map->z_min)
			map->z_min = map->points[i];
		if (map->points[i] > map->z_max)
			map->z_max = map->points[i];
	}
}

/**
 * frees the point grid and resets the map values
 */
void	free_map(t_map *map)
{
	if (map->points)
		free(map->points);
	map->points = NULL;
	map->width = 0;
	map->height = 0;
	map->z_min = 0;
	map->z_max = 0;
}
