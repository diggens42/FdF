/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 21:51:56 by fwahl             #+#    #+#             */
/*   Updated: 2026/09/01 21:51:56 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	free_fdf(t_fdf *fdf)
{
	if (fdf->map_rows)
		ft_lstclear(&fdf->map_rows, free);
	if (fdf->map_tokens)
		ft_free_strarray(fdf->map_tokens);
	fdf->map_tokens = NULL;
	free_map(&fdf->map);
	if (fdf->img)
		mlx_delete_image(fdf->mlx, fdf->img);
	fdf->img = NULL;
	if (fdf->mlx)
		mlx_terminate(fdf->mlx);
	fdf->mlx = NULL;
}

void	ft_error(t_fdf *fdf, char *err_msg, int err_code)
{
	if (err_code == ERR_SYS)
		perror(err_msg);
	else
		ft_putstr_fd(err_msg, STDERR_FILENO);
	free_fdf(fdf);
	exit(EXIT_FAILURE);
}
