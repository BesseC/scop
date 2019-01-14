/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 15:08:10 by cbesse            #+#    #+#             */
/*   Updated: 2018/03/30 12:03:58 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_vec3	vec3_mult(t_vec3 v1, double i)
{
	t_vec3	v2;

	v2.x = v1.x * i;
	v2.y = v1.y * i;
	v2.z = v1.z * i;
	return (v2);
}

t_vec3	vec3_negate(t_vec3 v1)
{
	t_vec3	v2;

	v2.x = -v1.x;
	v2.y = -v1.y;
	v2.z = -v1.z;
	return (v2);
}

t_vec3	vec3_div(t_vec3 v1, double i)
{
	t_vec3	v2;

	v2.x = v1.x / i;
	v2.y = v1.y / i;
	v2.z = v1.z / i;
	return (v2);
}

t_vec3	vec3_set(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3	vec3_normalize(t_vec3 v)
{
	t_vec3	vnorm;

	vnorm = vec3_div(v, vec3_norm(v));
	return (vnorm);
}


t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v3;

	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;
	return (v3);
}

t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v3;

	v3.x = v1.x - v2.x;
	v3.y = v1.y - v2.y;
	v3.z = v1.z - v2.z;
	return (v3);
}

t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v3;

	v3.x = ((v1.y * v2.z) - (v1.z * v2.y));
	v3.y = ((v1.z * v2.x) - (v1.x * v2.z));
	v3.z = ((v1.x * v2.y) - (v1.y * v2.x));
	return (v3);
}

double		vec3_dot(t_vec3 v1, t_vec3 v2)
{
	double	r;

	r = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (r);
}

double		vec3_norm(t_vec3 v)
{
	double	norm;

	norm = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (norm);
}
