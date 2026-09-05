/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 19:05:51 by fwahl             #+#    #+#             */
/*   Updated: 2026/09/05 19:05:51 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	key_hook(mlx_key_data_t key_data, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (key_data.action != MLX_PRESS)
		return ;
	if (key_data.key == MLX_KEY_ESCAPE)
		mlx_close_window(fdf->mlx);
}

void	init_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "fdf", true);
	if (!fdf->mlx)
		ft_error(fdf, "fdf: mlx_init failed\n", ERR_SYS);
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img || mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) < 0)
		ft_error(fdf, "fdf: could not create image\n", ERR_SYS);
}