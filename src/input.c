/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 15:24:07 by cbesse            #+#    #+#             */
/*   Updated: 2019/08/12 16:15:17 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_mat4	mouvement(GLFWwindow *window, t_mat4 view)
{
	int key;

	key = glfwGetKey(window, 333);
	if (key == 1)
		view = mat4_translate(view, 0, 0, -0.25);
	key = glfwGetKey(window, 334);
	if (key == 1)
		view = mat4_translate(view, 0, 0, 0.25);
	key = glfwGetKey(window, 263);
	if (key == 1)
		view = mat4_translate(view, 0.25, 0, 0);
	key = glfwGetKey(window, 262);
	if (key == 1)
		view = mat4_translate(view, -0.25, 0, 0);
	key = glfwGetKey(window, 265);
	if (key == 1)
		view = mat4_translate(view, 0, 0.25, 0);
	key = glfwGetKey(window, 264);
	if (key == 1)
		view = mat4_translate(view, 0, -0.25, 0);
	return (view);
}

t_mat4	key_callback(GLFWwindow *window, t_mat4 view, t_option *op)
{
	op->key_cooldown > 1 ? op->key_cooldown -= 1 : 0;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS
				&& op->key_cooldown <= 1)
	{
		op->stop_rot = !op->stop_rot;
		op->key_cooldown = COOLDOWN;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && op->key_cooldown <= 1)
	{
		op->flat_color = !op->flat_color;
		op->key_cooldown = COOLDOWN;
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && op->key_cooldown <= 1)
	{
		op->gray_color = !op->gray_color;
		op->key_cooldown = COOLDOWN;
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && op->key_cooldown <= 1)
	{
		op->text_mode = !op->text_mode;
		op->key_cooldown = COOLDOWN;
	}
	view = mouvement(window, view);
	return (view);
}
