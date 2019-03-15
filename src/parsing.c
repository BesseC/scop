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

t_vec3	compute_center_axis(GLfloat *vertices, int num_vertices)
{
	int		i;
	t_vec3	max;
	t_vec3	min;
	t_vec3	center;

	i = 0;
	max = vec3_set(-10000, -10000, -10000);
	min = vec3_set(10000, 10000, 10000);
	while (i < num_vertices - 6)
	{
		vertices[i] > max.x ? max.x = vertices[i] : 0;
		vertices[i] < min.x ? min.x = vertices[i] : 0;
		vertices[i + 1] > max.y ? max.y = vertices[i + 1] : 0;
		vertices[i + 1] < min.y ? min.y = vertices[i + 1] : 0;
		vertices[i + 2] > max.z ? max.z = vertices[i + 2] : 0;
		vertices[i + 2] < min.z ? min.z = vertices[i + 2] : 0;
		i += 6;
	}
	printf("\n----  %f, %f  ---\n", min.y, max.y);
	center = vec3_mult(vec3_add(max, min), 0.5);
	return (center);
}

GLfloat	*center_vertices(GLfloat *vertices, t_vec3 center, int length)
{
	int		i;
	//float	tx;
	//float	theta;

	i = 0;
	//theta = 90 * (M_PI / 180);
	while (i < length)
	{
		vertices[i] -= center.x;
		vertices[i + 1] -= center.y;
		vertices[i + 2] -= center.z;
		/*tx = vertices[i] * cos(theta) - vertices[i + 2] * sin(theta);
		vertices[i + 2] = vertices[i] * sin(theta) + vertices[i + 2] * cos(theta);
		vertices[i] = tx;*/
		i += 6;
	}
	return(vertices);
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
t_vec3 center;

//int i = 1;

v = 0;
f = 0;
*points = (GLfloat*)malloc(sizeof(GLfloat) * 3);
*indices = (GLuint*)malloc(sizeof(GLuint) * 3);
fd = open(filename, O_RDWR);
while (get_next_line(fd, &line) > 0)
{
//	printf("%d eme ligne \n",i );
  if (line[0] == 'v' && line[1] == ' ')
    *points = append_vertices(*points, line, &v);
  else if (line[0] == 'f' && line[1] == ' ')
    *indices = append_indices(*indices, line, &f);
  ft_strdel(&line);
	//i++;
}
center = compute_center_axis(*points, v);
printf("\n%f %f %f\n",center.x, center.y, center.z);
*points = center_vertices(*points, center, v);
ft_strdel(&line);
*nbv = v;
return(f);
}
