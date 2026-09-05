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

static t_fdf	init_fdf(void)
{
	t_fdf	fdf;

	fdf.mlx = NULL;
	fdf.img = NULL;
	fdf.map.points = NULL;
	fdf.map.width = 0;
	fdf.map.height = 0;
	fdf.map.z_min = 0;
	fdf.map.z_max = 0;
	fdf.map_rows = NULL;
	fdf.map_tokens = NULL;
	fdf.cam.zoom = 1.0;
	fdf.cam.x_offset = 0;
	fdf.cam.y_offset = 0;
	return (fdf);
}

static void	check_args(t_fdf *fdf, int argc, char **argv)
{
	char	*dot;

	if (argc != 2)
		ft_error(fdf, "Usage: ./fdf <map.fdf>\n", ERR_USER);
	dot = ft_strrchr(argv[1], '.');
	if (!dot || ft_strcmp(dot, ".fdf") != 0)
		ft_error(fdf, "fdf: map file must end in .fdf\n", ERR_USER);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	fdf = init_fdf();
	check_args(&fdf, argc, argv);
	parse_map(&fdf, argv[1]);
	init_mlx(&fdf);
	render(&fdf);
	mlx_loop(fdf.mlx);
	free_fdf(&fdf);
	return (EXIT_SUCCESS);
}
