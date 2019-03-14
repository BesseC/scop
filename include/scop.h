/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 14:21:28 by cbesse            #+#    #+#             */
/*   Updated: 2019/01/10 14:21:29 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H
#include <GL/glew.h>	/* include GLEW and new version of GL on Windows */
#include <GLFW/glfw3.h> /* GLFW helper library */
#include <stdio.h>
#include "libft.h"
#include "libmat.h"
#include "time.h"
# define BUFFER_SIZE 128
# define FPS 120

int	load_obj(GLuint **indices, GLfloat **points, char *filename, int *nbv);
#endif
