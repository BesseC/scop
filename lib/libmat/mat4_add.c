/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 16:47:43 by cbesse            #+#    #+#             */
/*   Updated: 2018/12/21 16:47:44 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libmat.h"

t_mat4  mat4_add(t_mat4 m1, t_mat4 m2)
{
  t_mat4 m3;
  int i;

  i = -1;
  while(++i < 16)
    m3.m[i] = m1.m[i] + m2.m[i];
  return(m3);
}