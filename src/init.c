/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 14:05:14 by cbesse            #+#    #+#             */
/*   Updated: 2019/08/13 16:10:30 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_buffers(t_buffer *buffer, char *av)
{
	int nbv;

	buffer->idlen = load_obj(&buffer->indices, &buffer->points, av, &nbv);
	glGenVertexArrays(1, &buffer->vao);
	glGenBuffers(1, &buffer->vbo);
	glGenBuffers(1, &buffer->ebo);
	glBindVertexArray(buffer->vao);
	glBindBuffer(GL_ARRAY_BUFFER, buffer->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof( GLfloat )
			* nbv, buffer->points, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof( GLuint )
			* buffer->idlen, buffer->indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);
	bind_texture(buffer);
}

void	init_shader(t_shader *shader)
{
	shader->vertex_shader = get_shader_source(VERTEX_SHADER);
	shader->fragment_shader = get_shader_source(FRAGMENT_SHADER);
	shader->vert_shader = glCreateShader(GL_VERTEX_SHADER);
	shader->frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader->vert_shader, 1, &shader->vertex_shader, NULL);
	glCompileShader(shader->vert_shader);
	glShaderSource(shader->frag_shader, 1, &shader->fragment_shader, NULL);
	glCompileShader(shader->frag_shader);
	shader->shader_programme = glCreateProgram();
	glAttachShader(shader->shader_programme, shader->frag_shader);
	glAttachShader(shader->shader_programme, shader->vert_shader);
	glBindAttribLocation(shader->shader_programme, 0, "vertex_position");
	glLinkProgram(shader->shader_programme);
	shader->model_location = glGetUniformLocation(shader->shader_programme
			, "model");
	shader->view_location = glGetUniformLocation(shader->shader_programme
			, "view");
	shader->projection_location = glGetUniformLocation(shader->shader_programme
			, "projection");
	shader->flat = glGetUniformLocation(shader->shader_programme, "flatmode");
	shader->gray = glGetUniformLocation(shader->shader_programme, "graymode");
	shader->text_mode = glGetUniformLocation(shader->shader_programme
			, "textmode");
	shader->text_location = glGetUniformLocation(shader->shader_programme
			, "texture");
}

void	init_window(t_env *env)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_VERSION);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	env->window = glfwCreateWindow(WIDHT, HEIGHT, "Scop", NULL, NULL);
	if (!env->window)
	{
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(env->window);
}

void	init_mvp(t_env *env)
{
	mat4_id(&env->view);
	mat4_id(&env->model);
	set_projection(&env->projection, 90);
	env->view = mat4_translate(env->view, 0, 0, -5);
}

void	init(t_env *env, char *av)
{
	env->option.stop_rot = 0;
	env->option.flat_color = 0;
	env->option.gray_color = 0;
	env->option.text_mode = 1;
	env->option.key_cooldown = 0;
	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(1);
	}
	init_window(env);
	glewExperimental = GL_TRUE;
	glewInit();
	env->renderer = glGetString(GL_RENDERER);
	env->version = glGetString(GL_VERSION);
	printf("Renderer: %s\n", env->renderer);
	printf("OpenGL version supported %s\n", env->version);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	init_buffers(&env->buffer, av);
	init_shader(&env->shader);
	init_mvp(env);
}
