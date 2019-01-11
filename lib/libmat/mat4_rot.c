/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_rot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 14:05:42 by cbesse            #+#    #+#             */
/*   Updated: 2019/01/10 16:00:32 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libmat.h"

static void	get_x_rot(t_mat4 *m, float theta)
{
	m->m[5] = cos(theta);
	m->m[6] = -sin(theta);
	m->m[9] = sin(theta);
	m->m[10] = cos(theta);
}

static void	get_y_rot(t_mat4 *m, float theta)
{
	m->m[0] = cos(theta);
	m->m[2] = sin(theta);
	m->m[8] = -sin(theta);
	m->m[10] = cos(theta);
}

static void	get_z_rot(t_mat4 *m, float theta)
{
	m->m[0] = cos(theta);
	m->m[1] = -sin(theta);
	m->m[4] = sin(theta);
	m->m[5] = cos(theta);
}

t_mat4		mat4_rot_axis(t_mat4 m, int axis, float angle)
{
	t_mat4	m1;
	float	theta;

	mat4_id(&m1);
	theta = angle * (M_PI / 180);
	if (axis == AXIS_X)
	{
		get_x_rot(&m1, theta);
		m = mat4_mult(m, m1);
	}
	if (axis == AXIS_Y)
	{
		get_y_rot(&m1, theta);
		m = mat4_mult(m, m1);
	}
	if (axis == AXIS_Z)
	{
		get_z_rot(&m1, theta);
		m = mat4_mult(m, m1);
	}
	return (m);
}
