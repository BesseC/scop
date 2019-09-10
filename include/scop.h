/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 14:21:28 by cbesse            #+#    #+#             */
/*   Updated: 2019/09/10 14:21:05 by cbesse           ###   ########.fr       */
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
# define VERTEX_SHADER "shaders/vertex.glsl"
# define FRAGMENT_SHADER "shaders/fragment.glsl"
# define TEXTURE_PATH "./chaton.bmp"
# define MAJOR_VERSION 4
# define MINOR_VERSION 1

typedef unsigned int	t_boolean;

typedef struct			s_text
{
	unsigned char	*img;
	int				width;
	int				height;
	int				size;
	int				opp;
	int				line_size;
}						t_text;

typedef struct			s_option
{
	t_boolean	stop_rot;
	t_boolean	flat_color;
	t_boolean	gray_color;
	t_boolean	text_mode;
	int			key_cooldown;
}						t_option;

typedef struct			s_shader
{
	GLint			model_location;
	GLint			view_location;
	GLint			flat;
	GLint			gray;
	GLint			text_mode;
	GLint			projection_location;
	GLint			text_location;
	GLuint			vert_shader;
	GLuint			frag_shader;
	GLuint			shader_programme;
	const GLchar	*vertex_shader;
	const GLchar	*fragment_shader;
}						t_shader;

typedef struct			s_buffer
{
	GLuint	vao;
	GLuint	vbo;
	GLuint	ebo;
	GLuint	*indices;
	GLfloat	*points;
	GLuint	texture;
	int		idlen;
}						t_buffer;

typedef struct			s_env
{
	t_option		option;
	t_shader		shader;
	t_buffer		buffer;
	GLFWwindow		*window;
	t_mat4			view;
	t_mat4			model;
	t_mat4			projection;
	const GLubyte	*renderer;
	const GLubyte	*version;
}						t_env;

int						load_obj(GLuint **indices, GLfloat **points
		, char *filename, int *nbv);
void					load_bmp(t_text *text, char *filename);
GLuint					*gluint_array_copy(GLuint *array, int length, int m);
GLchar					*get_shader_source(char *filename);
t_mat4					key_callback(GLFWwindow *window
		, t_mat4 view, t_option *op);
void					init(t_env *env, char *av);
void					bind_texture(t_buffer *buffer);
void					set_projection(t_mat4 *m, float fov);
void					print_to_exit(char *msg);
#endif
