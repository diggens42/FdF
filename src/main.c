/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 17:01:35 by fwahl             #+#    #+#             */
/*   Updated: 2026/08/29 17:01:35 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	init_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "fdf", true);
	if (!fdf->mlx)
		ft_error(fdf, "fdf: mlx_init failed\n");
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img || mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) < 0)
		ft_error(fdf, "fdf: could not create image\n");
}

t_fdf	init_fdf(void)
{
	t_fdf	fdf;

	fdf.mlx = NULL;
	fdf.img = NULL;
	return (fdf);
}

int main(int argc, char **argv)
{
	t_fdf	fdf;
	fdf = init_fdf();
	init_mlx(&fdf);
	return (EXIT_SUCCESS);
}