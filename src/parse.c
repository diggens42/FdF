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

static void	parse_row_content(t_fdf *fdf, char *line, int y)
{
	char	**split;
	int		x;

	split = ft_split(line, ' ');
	if (!split)
		ft_error(fdf, "malloc failed in fill_row", ERR_SYS);
	if (ft_strarray_len(split) != fdf->map.width)
		ft_error(fdf, "fdf: map rows have different widths\n", ERR_USER);
	x = -1;
	while (++x < fdf->map.width)
		// parse the token and store it in the map
	ft_free_strarray(split);
	split = NULL;
}


static void read_them_lines(t_fdf *fdf, t_list *rows, int fd)
{
	char	*line;
	char	*trimmed;
	t_list	*node;

	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \t\n\r\v\f");
		free(line);
		if (!trimmed)
			ft_error(fdf, "malloc failed in read_lines", ERR_SYS);
		if (!trimmed[0])
			free(trimmed);
		else
		{
			node = ft_lstnew(trimmed);
			if (!node)
				ft_error(fdf, "malloc failed in read_lines", ERR_SYS);
			ft_lstadd_back(&fdf->rows, node);
		}
		line = get_next_line(fd);
	}
}

void	parse_map(t_fdf *fdf, char *map_path)
{
	t_list	*cur;
	int		fd;
	int		y;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		ft_error(fdf, map_path, ERR_SYS);
	read_lines(fdf, fd);
	close(fd);
	if (!fdf->rows)
		ft_error(fdf, "fdf: map is empty\n", ERR_USER);
	cur = fdf->rows;
	y = 0;
	while (cur)
	{
		store_row(fdf, cur->content, y++);
		cur = cur->next;
	}
	ft_lstclear(&fdf->rows, free);
	//map shit
}