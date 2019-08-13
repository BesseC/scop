/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 18:30:01 by cbesse            #+#    #+#             */
/*   Updated: 2019/08/13 16:27:58 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	draw(t_env *env)
{
	glUniformMatrix4fv(env->shader.model_location, 1, GL_FALSE, env->model.m);
	glUniformMatrix4fv(env->shader.view_location, 1, GL_FALSE, env->view.m);
	glUniformMatrix4fv(env->shader.projection_location, 1
			, GL_FALSE, env->projection.m);
	glUniform1i(env->shader.flat, env->option.flat_color);
	glUniform1i(env->shader.gray, env->option.gray_color);
	glUniform1i(env->shader.text_mode, env->option.text_mode);
	glBindTexture(GL_TEXTURE_2D, env->buffer.texture);
	glBindVertexArray(env->buffer.vao);
	glDrawElements(GL_TRIANGLES, env->buffer.idlen, GL_UNSIGNED_INT, 0);
	glfwPollEvents();
	glfwSwapBuffers(env->window);
}

int		main(int ac, char **av)
{
	double	lasttime;
	t_env	env;

	if (ac != 2)
		return (1);
	init(&env, av[1]);
	lasttime = glfwGetTime();
	while (!glfwWindowShouldClose(env.window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(env.shader.shader_programme);
		env.view = key_callback(env.window, env.view, &env.option);
		if (env.option.stop_rot == 0)
		{
			env.model = mat4_rot_axis(env.model, AXIS_X, 0.5);
			env.model = mat4_rot_axis(env.model, AXIS_Y, 1);
		}
		draw(&env);
		while (glfwGetTime() < lasttime + 1.0 / FPS)
			;
		lasttime += 1.0 / FPS;
	}
	glfwTerminate();
	return (0);
}
