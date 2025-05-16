/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:10:06 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/16 12:04:18 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"
# include <unistd.h>
void setambient(t_scene scene, char  **line_split)
{
    int     i;
    char    **array_tmp;
    
    i = 1;
}

void parse(t_scene scene, char *file)
{
    char    *line;
    int     fd;
    char    **line_split;
    int     *error;
    
	error= 0;
    fd = open (file,0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_split = ft_split(line, " ");
        if (!ft_strncmp (line_split[0],"A",1))
            setambient(scene, line_split);
        else  if (!ft_strnmp (line_split[0],"C",1))
            setcamera(scene, line_split);
        else  if (!ft_strnmp (line_split[0],"L", 1))
            setlight(scene, line_split);
        else  if (!ft_strncmp (line_split[0],"pl",2))
            setplane(scene, line_split);
        else  if (!ft_strncmp (line_split[0],"sp",2))
            setsphere(scene, line_split);
        else  if (!ft_strncmp (line_split[0],"cy",2))
            setcylinder(scene, line_split);
        else
           *error= 1;
        free(line);
		if (error == 1)
        {
            destroy_all();
        }
        
          
		line = get_next_line(fd);
	}
}

int main (int argc, char **argv)
{
    t_scene escena;
    
    parse(escena, argv[1]);
}
