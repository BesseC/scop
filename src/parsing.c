/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 12:07:45 by cbesse            #+#    #+#             */
/*   Updated: 2019/08/08 18:50:57 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vec3	compute_center_axis(GLfloat *vertices, int num_vertices)
{
	int		i;
	t_vec3	max;
	t_vec3	min;
	t_vec3	center;

	i = 0;
	max = vec3_set(-10000, -10000, -10000);
	min = vec3_set(10000, 10000, 10000);
	while (i < num_vertices)
	{
		vertices[i] > max.x ? max.x = vertices[i] : 0;
		vertices[i] < min.x ? min.x = vertices[i] : 0;
		vertices[i + 1] > max.y ? max.y = vertices[i + 1] : 0;
		vertices[i + 1] < min.y ? min.y = vertices[i + 1] : 0;
		vertices[i + 2] > max.z ? max.z = vertices[i + 2] : 0;
		vertices[i + 2] < min.z ? min.z = vertices[i + 2] : 0;
		i += 3;
	}
	printf("\n----  %f, %f  ---\n", min.y, max.y);
	center = vec3_mult(vec3_add(max, min), 0.5);
	return (center);
}

GLfloat	*center_vertices(GLfloat *vertices, t_vec3 center, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		vertices[i] -= center.x;
		vertices[i + 1] -= center.y;
		vertices[i + 2] -= center.z;
		i += 3;
	}
	return (vertices);
}

GLfloat	*append_vertices(GLfloat *array, char *line, int *length)
{
	int		i;
	int		j;
	char	**tab;
	GLfloat	*new;

	tab = ft_strsplit(&line[1], ' ');
	*length += 3;
	new = (GLfloat*)ft_memalloc(sizeof(GLfloat) * *length);
	i = -1;
	while (++i < *length - 3)
		new[i] = array[i];
	free(array);
	array = new;
	j = -1;
	while (tab[++j] != NULL)
	{
		array[*length - 3 + j] = (GLfloat)ft_atof(tab[j]);
		ft_strdel(&tab[j]);
	}
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
	m = ft_arraylen((void**)tab) == 4 ? 6 : 3;
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

int		load_obj(GLuint **indices, GLfloat **points, char *filename, int *nbv)
{
	int		fd;
	int		v;
	int		f;
	char	*line;
	t_vec3	center;

	v = 0;
	f = 0;
	*points = (GLfloat*)ft_memalloc(sizeof(GLfloat) * 3);
	*indices = (GLuint*)ft_memalloc(sizeof(GLuint) * 3);
	if ((fd = open(filename, O_RDWR)) == -1)
		exit(1);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'v' && line[1] == ' ')
			*points = append_vertices(*points, line, &v);
		else if (line[0] == 'f' && line[1] == ' ')
			*indices = append_indices(*indices, line, &f);
		ft_strdel(&line);
	}
	center = compute_center_axis(*points, v);
	*points = center_vertices(*points, center, v);
	ft_strdel(&line);
	*nbv = v;
	return (f);
}
