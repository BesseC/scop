/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 16:29:35 by cbesse            #+#    #+#             */
/*   Updated: 2019/01/07 16:29:37 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libmat.h"

t_mat4  mat4_scale(t_mat4 m, float f)
{
  t_mat4 m3;
  int i;

  i = -1;
  while(++i < 16)
  {
    m3.m[i] = m.m[i] * f;
  }
  return(m3);
}
