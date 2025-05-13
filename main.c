/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <imugica-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:16:36 by imugica-          #+#    #+#             */
/*   Updated: 2025/05/13 13:27:05 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int c, char **args)
{
	float			t;

	t_Vector3 ray_origin = {0, 0, 0};
	t_Vector3 ray_dir = {0, 0, 1};
	t_sphere_prop sphere = {{0, 0, 5}, {0, 0, 0}, 1.0f, {255, 0, 0}};
	if (ray_sphere_intersect(ray_origin, ray_dir, sphere, &t))
	{
		printf("Intersection at t = %f\n", t);
	}
	else
	{
		printf("No intersection\n");
	}
	return (0);
}
