/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:10:06 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/26 12:20:04 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"
# include <unistd.h>
# include "get_next_line.h"
# include "libft.h"

float   ft_atof(char *n)
{
    int     i;
    int     j;
    float   nb;
    int     m;
    i = 0;
    nb = 0;
    m = 1;
    j = 1;
    if (n[i] == '-')
    {
        m = -m;
        i++;
    }
    while (n[i] && n[i] != '\n')
    {
        if (j > 1 && n[i - 1] != '.')
            j *= 10;
        if (n[i] == '.')
            j *= 10;
        else
            nb = nb * 10 + (n[i] - 48);
        i++;
    }
    return (m * nb / j);
}

int array_len(char **array)
{
    int c;

    c = 0;
    while (array[c])
        c++;
    return (c);
}

void set_color(t_RGB *color,char **col_num)
{
    color->r = (ft_atoi (col_num[0]));
    color->g = (ft_atoi (col_num[1]));
    color->b = (ft_atoi (col_num[2]));
}

int is_float_array(char  *str)
{
   int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            if (str[i]!= '.' && str[i]!= '-')
                return (1);
        i++;
    }
    return (0);
}

int valid_iii(char **str)
{
    int tmp;
    int c;
    
    tmp = 0;
    c = 0;
    if( array_len(str) != 3 )
        return(1);
    while (c < 3)
    {
        tmp = ft_atoi(str[c++]);
        if (tmp < 0 || tmp > 255)
            return (1);
    }
    return (0);
}

int valid_fff(char **str)
{
    int     c;
    
    c = 0;
    if( array_len(str) != 3 )
        return(1);
    while (c < 3)
    {
        if (is_float_array (str[c]))
            return(1);
        c++;  
    }
    return (0);
}

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
}
