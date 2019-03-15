/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 15:20:44 by cbesse            #+#    #+#             */
/*   Updated: 2017/12/05 16:18:16 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/get_next_line.h"

int					get_next_line(int const fd, char **line)
{
	static t_list	*list;
	t_gnl			gnl;

	if (fd < 0 || !line)
		return (-1);
	gnl.content = ft_content_init(&list, fd);
	gnl.tmp = ft_strnew(0);
	while (gnl.content->ret > 0)
	{
		if ((gnl.out_rd = ft_lst_read(gnl.content, &list, &gnl.tmp, line)) != 0)
			return (gnl.out_rd);
		while (gnl.content->i < gnl.content->ret)
		{
			gnl.new_str = ft_lst_concat(gnl.content);
			gnl.tmp_bis = ft_strjoin(gnl.tmp, gnl.new_str);
			free(gnl.new_str);
			free(gnl.tmp);
			gnl.tmp = gnl.tmp_bis;
			if (gnl.content->new_line == 1)
				*line = gnl.tmp;
			if (gnl.content->new_line == 1)
				return (1);
		}
	}
	return (ft_lst_remove(&list, fd, &gnl.tmp));
}

t_content			*ft_content_init(t_list **list, int fd)
{
	t_content       *content;
	t_list			*tmp;

	tmp = *list;
	while (tmp)
	{
		content = (t_content *)(tmp->content);
		if (content->fd == fd)
			return (content);
		tmp = tmp->next;
	}
	content = (t_content *)ft_memalloc(sizeof(t_content));
	content->buffer = ft_strnew(BUFF_SIZE);
	content->ret = BUFF_SIZE;
	content->i = BUFF_SIZE;
	content->fd = fd;
	content->new_line = 1;
	tmp = ft_lstnew(content, sizeof(t_content));
	ft_memdel((void **)&content);
	ft_lstadd(list, tmp);
	return ((t_content *)(tmp->content));
}

int					ft_lst_read(t_content *content, t_list **list,
char **tmp, char **line)
{
	if (content->i == content->ret)
	{
		content->ret = read(content->fd, content->buffer, BUFF_SIZE);
		if (content->ret == -1)
		{
			ft_lst_remove(list, content->fd, tmp);
			return (-1);
		}
		content->i = 0;
		if (content->ret == 0)
		{
			if (content->new_line == 0)
			{
				*line = *tmp;
				return (1);
			}
		}
	}
	return (0);
}

char				*ft_lst_concat(t_content *content)
{
	int				i;

	i = 0;
	content->new_line = 0;
	while (content->i + i < content->ret)
	{
		if (content->buffer[content->i + i] == '\n')
		{
			content->new_line = 1;
			i++;
			break ;
		}
		i++;
	}
	content->i += i;
	return (ft_strsub(content->buffer, content->i - i, i - content->new_line));
}

int					ft_lst_remove(t_list **list, int fd, char **str)
{
	t_content		*tmp_content;
	t_list			**tmp_list;
	t_list			*next_list;

	tmp_list = list;
	while (*tmp_list)
	{
		tmp_content = (t_content *)((*tmp_list)->content);
		if (tmp_content->fd == fd)
			break ;
		*tmp_list = ((*tmp_list)->next);
	}
	if (*tmp_list)
	{
		next_list = (*tmp_list)->next;
		ft_strdel(&(tmp_content->buffer));
		ft_memdel((void **)&tmp_content);
		ft_memdel((void **)tmp_list);
		*tmp_list = next_list;
	}
	ft_strdel(str);
	return (0);
}
