/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 14:21:28 by cbesse            #+#    #+#             */
/*   Updated: 2019/08/12 14:41:17 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <stdio.h>
# include "libft.h"
# include "libmat.h"
# define BUFFER_SIZE 128
# define FPS 60
# define WIDHT 1024
# define HEIGHT 800
# define COOLDOWN 20

typedef unsigned int boolean;

typedef struct	s_text
{
	unsigned char	*img;
	int				width;
	int				height;
	int				size;
	int				opp;
	int				line_size;
}				t_text;

typedef struct s_option
{
    boolean stop_rot;
    boolean flat_color;
    boolean gray_color;
    boolean text_mode;
    int key_cooldown; 
} t_option;

typedef struct s_shader {
	GLint model_location;
	GLint view_location;
	GLint flat;
	GLint gray;
	GLint text_mode;
	GLint projection_location;
	GLint text_location;
}				t_shader;

int				load_obj(GLuint **indices, GLfloat **points
						, char *filename, int *nbv);
void			load_bmp(t_text *text, char *filename);
GLuint			*gluint_array_copy(GLuint *array, int length, int m);
GLchar	*get_shader_source(char *filename);
t_mat4	key_callback(GLFWwindow* window, t_mat4 view, t_option *op);

#endif
