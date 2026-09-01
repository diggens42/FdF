/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 22:55:59 by fwahl             #+#    #+#             */
/*   Updated: 2026/09/01 22:55:59 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	add_row(t_fdf *fdf, char *line)
{
	t_list	*node;

	node = ft_lstnew(line);
	if (!node)
	{
		free(line);
		ft_error(fdf, "malloc failed in add_row", ERR_SYS);
	}
	ft_lstadd_back(&fdf->rows, node);
}

void	parse_map(t_fdf *fdf, char *map_path)
{
	int		fd;
	char	*line;
	char	*trimmed;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		ft_error(fdf, map_path, ERR_SYS);
	line = get_next_line(fd);
	close(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \t\n\r\v\f");
		free(line);
		if (!trimmed)
			ft_error(fdf, "malloc failed in read_lines", ERR_SYS);
		if (trimmed[0])
			add_row(fdf, trimmed);
		else
			free(trimmed);
		line = get_next_line(fd);
	}
	close(fd);
}