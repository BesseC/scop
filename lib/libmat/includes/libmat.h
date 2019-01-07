/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmat.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 16:27:36 by cbesse            #+#    #+#             */
/*   Updated: 2018/12/21 16:27:41 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMAT_H
# define LIBMAT_H
# include <math.h>

typedef struct s_mat4
{
    float m[16];
}              t_mat4;

typedef struct s_vec4
{
    float v[4];
}              t_vec4;

typedef struct s_vec3
{
    float v[16];
}              t_vec3;

void set_mat4(t_mat4 *m, float f);
t_mat4  mat4_add(t_mat4 m1, t_mat4 m2);
t_mat4  mat4_sub(t_mat4 m1, t_mat4 m2);
t_mat4  mat4_mult(t_mat4 m1, t_mat4 m2);
#endif
