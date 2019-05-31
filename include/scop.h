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
# define BUFFER_SIZE 128
# define FPS 60

typedef struct s_text
{
    unsigned char *img;
    int width;
    int height;
    int size;
    int opp;
    int line_size;
}           t_text;

int load_obj(GLuint **indices, GLfloat **points, char *filename, int *nbv);
void    load_bmp(t_text *text, char *filename);
#endif
