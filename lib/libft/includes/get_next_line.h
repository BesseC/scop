/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:57:05 by cbesse            #+#    #+#             */
/*   Updated: 2018/04/10 12:00:39 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "libft.h"

# define BUFF_SIZE 4096

typedef struct		s_content
{
	int				fd;
	char			*buffer;
	int				ret;
	int				i;
	int				new_line;
}					t_content;

typedef struct		s_gnl
{
	t_content		*content;
	int				out_rd;
	char			*tmp;
	char			*new_str;
	char			*tmp_bis;
}					t_gnl;

int					ft_lst_remove(t_list **list, int fd, char **str);
t_content			*ft_content_init(t_list **lst, int fd);
int					ft_lst_read(t_content *content, t_list **list,
char **tmp, char **line);
char				*ft_lst_concat(t_content *content);
int					get_next_line(const int fd, char **line);
#endif
