/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:10:06 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/27 14:25:02 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_pos(t_Vector3 *pos, char **pos_a)
{
	pos->x = ft_atof(pos_a[0]);
	pos->y = ft_atof(pos_a[1]);
	pos->z = ft_atof(pos_a[2]);
}

void	set_rot(t_Vector3 *pos, char **pos_a)
{
	pos->x = ft_atof(pos_a[0]);
	pos->y = ft_atof(pos_a[1]);
	pos->z = ft_atof(pos_a[2]);
	*pos = vector_normalize(*pos);
}

int	valid_fff(char **str)
{
	int	c;

	c = 0;
	if (array_len(str) != 3)
		return (1);
	while (c < 3)
	{
		if (is_float_array (str[c]))
			return (1);
		c++;
	}
	return (0);
}
