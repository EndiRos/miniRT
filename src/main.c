/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <imugica-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:16:36 by imugica-          #+#    #+#             */
/*   Updated: 2025/05/14 11:49:06 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int c, char **args)
{
	t_Vector3 ray_origin = {0, 0, 0};
	t_Vector3 ray_dir = vector_normalize((t_Vector3){0, 0, 1});

	t_cyl_prop cyl;
	cyl.pos = (t_Vector3){0, 0, 5};
	cyl.rot = vector_normalize((t_Vector3){1, 1, 1}); // diagonal cylinder
	cyl.radius = 1.0f;
	cyl.height = 4.0f;

	float t;
	if (ray_cylinder_intersect(ray_origin, ray_dir, cyl, &t)) {
		printf("Intersection at t = %f\n", t);
	} else {
		printf("No intersection\n");
	}
	return 0;
}
