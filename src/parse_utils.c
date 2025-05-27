/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:10:06 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/27 11:14:22 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"
# include <unistd.h>
# include "get_next_line.h"
# include "libft.h"

void set_pos(t_Vector3 *pos, char **pos_a)
{
    pos->x = ft_atof(pos_a[0]);
    pos->y = ft_atof(pos_a[1]);
    pos->z = ft_atof(pos_a[2]);
}

void set_rot(t_Vector3 *pos, char **pos_a)
{
    pos->x = ft_atof(pos_a[0]);
    pos->y = ft_atof(pos_a[1]);
    pos->z = ft_atof(pos_a[2]);
    *pos = vector_normalize(*pos);
}
