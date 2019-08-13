/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 14:11:23 by cbesse            #+#    #+#             */
/*   Updated: 2019/08/12 14:11:35 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLuint	*gluint_array_copy(GLuint *array, int length, int m)
{
	int		i;
	GLuint	*new;

	i = -1;
	new = (GLuint*)ft_memalloc(sizeof(GLuint) * length);
	while (++i < length - m)
		new[i] = array[i];
	free(array);
	array = new;
	return (new);
}

GLchar	*get_shader_source(char *filename)
{
	int		fd;
	int		ret;
	char	buffer[BUFFER_SIZE];
	char	*source;
	char	*del;

	source = ft_strnew(BUFFER_SIZE);
	fd = open(filename, O_RDONLY);
	while ((ret = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[ret] = '\0';
		del = source;
		source = ft_strjoin(source, buffer);
		ft_strdel(&del);
	}
	close(fd);
	return (source);
}

void	set_projection(t_mat4 *m, float fov)
{
	float	s;
	float	far;
	float	near;

	far = 100.0;
	near = 0.1;
	s = 1 / (tan(fov * 0.5 * M_PI / 180.0));
	set_mat4(m, 0);
	m->m[0] = s / ((float)(WIDHT / HEIGHT));
	m->m[5] = s;
	m->m[10] = -(far + near) / (far - near);
	m->m[11] = -1;
	m->m[14] = -2 * far * near / (far - near);
}
