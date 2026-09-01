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

void	parse_row_content(t_fdf *fdf, char *line, int y)
{
	char	**split;
	int	x;

	split = ft_split(line, ' ');
	if (!split)
		ft_error(fdf, "malloc failed in fill_row", ERR_SYS);
	if (ft_strarray_len(split) != fdf->map.width)
		ft_error(fdf, "fdf: map rows have different widths\n", ERR_USER);
	x = -1;
	while (++x < fdf->map.width)
		// this is where shit gets parsed and put into the map
	ft_free_strarray(split);
	split = NULL;
}

static int	parse_row_width(t_fdf *fdf, char *line)
{
	char	**split;
	int		width;

	split = ft_split(line, ' ');
	if (!split)
		ft_error(fdf, "malloc failed in row_width", ERR_SYS);
	width = ft_strarray_len(split);
	ft_free_strarray(split);
	split = NULL;
	return (width);
}

static void	add_row(t_fdf *fdf, t_list *rows, char *line)
{
	t_list	*node;

	node = ft_lstnew(line);
	if (!node)
	{
		free(line);
		ft_error(fdf, "malloc failed in add_row", ERR_SYS);
	}
	ft_lstadd_back(&rows, node);
}

static void read_them_lines(t_fdf *fdf, t_list *rows, int fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \t\n\r\v\f");
		free(line);
		if (!trimmed)
			ft_error(fdf, "malloc failed in read_lines", ERR_SYS);
		if (trimmed[0])
			add_row(fdf, &rows, trimmed);
		else
			free(trimmed);
		line = get_next_line(fd);
	}
}

void	parse_map(t_fdf *fdf, char *map_path)
{
	t_list	*rows;
	t_list	*current;
	int		fd;
	int		y;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		ft_error(fdf, map_path, ERR_SYS);
	read_them_lines(fdf, &rows, fd);
	close(fd);
	if (!rows)
		ft_error(fdf, "fdf: map is empty\n", ERR_USER);
	allocate_map(fdf, parse_row_width(fdf, rows->content), ft_lstsize(rows));
	current = rows;
	y = 0;
	while (current)
	{
		parse_row_content(fdf, current->content, y++);
		current = current->next;
	}
	ft_lstclear(&rows, free);
}