/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 12:07:45 by cbesse            #+#    #+#             */
/*   Updated: 2019/01/10 12:07:47 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		array_len(void **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

GLuint	*gluint_array_copy(GLuint *array, int length, int m)
{
	int		i;
	GLuint	*new;

	i = -1;
	new = (GLuint*)malloc(sizeof(GLuint) * length);
	while (++i < length - m)
		new[i] = array[i];
	free(array);
	array = new;
	return (new);
}

GLfloat *set_color(GLfloat *array, int length)
{
  if(length/6%3 == 0)
  {
    array[length - 3] = 1.0f;
    array[length - 2] = 0.0f;
    array[length - 1] = 0.0f;
  }
  else if(length/6%3 == 1)
  {
    array[length - 3] = 0.0f;
    array[length - 2] = 1.0f;
    array[length - 1] = 0.0f;
  }
  else if(length/6%3 == 2)
  {
    array[length - 3] = 0.0f;
    array[length - 2] = 0.0f;
    array[length - 1] = 1.0f;
  }
  return (array);
}

GLfloat	*append_vertices(GLfloat *array, char *line, int *length)
{
	int		i;
	int		j;
	char	**tab;
	GLfloat	*new;

	tab = ft_strsplit(&line[1], ' ');
	*length += 6;
	new = (GLfloat*)malloc(sizeof(GLfloat) * *length);
	i = -1;
	while (++i < *length - 6)
		new[i] = array[i];
	free(array);
	array = new;
	j = -1;
	while (tab[++j] != NULL)
	{
		array[*length - 6 + j] = (GLfloat)ft_atof(tab[j]);
		ft_strdel(&tab[j]);
	}
  array = set_color(array, *length);
	ft_strdel(&tab[j]);
	free(tab);
	tab = NULL;
	return (array);
}

GLuint	*append_indices(GLuint *array, char *line, int *length)
{
	int		j;
	int		m;
	char	**tab;

	tab = ft_strsplit(&line[1], ' ');
	m = array_len((void**)tab) == 4 ? 6 : 3;
	*length += m;
	array = gluint_array_copy(array, *length, m);
	j = -1;
	while (++j < 3)
	{
		array[*length - m + j] = (GLuint)ft_atoi(tab[j]) - 1;
		if (m == 6)
			array[*length - m + 3 + j] =
			(GLuint)ft_atoi(tab[j > 0 ? j + 1 : 0]) - 1;
		ft_strdel(&tab[j]);
	}
	ft_strdel(&tab[j]);
	free(tab);
	tab = NULL;
	return (array);
}

int	load_obj(GLuint **indices, GLfloat **points, char *filename, int *nbv)
{
int		fd;
int		v;
int		f;
char	*line;

v = 0;
f = 0;
*points = (GLfloat*)malloc(sizeof(GLfloat) * 3);
*indices = (GLuint*)malloc(sizeof(GLuint) * 3);
fd = open(filename, O_RDWR);
while (get_next_line(fd, &line) > 0)
{
  if (line[0] == 'v' && line[1] == ' ')
    *points = append_vertices(*points, line, &v);
  else if (line[0] == 'f' && line[1] == ' ')
    *indices = append_indices(*indices, line, &f);
  ft_strdel(&line);
}
ft_strdel(&line);
*nbv = v;
return(f);
}
