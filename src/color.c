/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:18:17 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/26 11:42:01 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_RGB	rgba_to_rgb(unsigned int color)
{
	t_RGB	rgb;

	rgb.r = (color >> 24) & 0xFF;
	rgb.g = (color >> 16) & 0xFF;
	rgb.b = (color >> 8) & 0xFF;
	return (rgb);
}

unsigned int	rgb_to_rgba(t_RGB rgb)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;
	unsigned int	color;

	r = ((int)rgb.r & 0xFF) << 24;
	g = ((int)rgb.g & 0xFF) << 16;
	b = ((int)rgb.b & 0xFF) << 8;
	a = 0xFF;
	color = r | g | b | a;
	return (color);
}

unsigned int	color_merge(unsigned int min_color, t_RGB ambient)
{
	t_RGB	base_rgb;

	base_rgb = rgba_to_rgb(min_color);
	base_rgb.r = (base_rgb.r * ambient.r) / 255;
	base_rgb.g = (base_rgb.g * ambient.g) / 255;
	base_rgb.b = (base_rgb.b * ambient.b) / 255;
	return (rgb_to_rgba(base_rgb));
}

unsigned int	compute_color(t_scene *escena, t_shade shading,
	t_Intersection inter, int light)
{
t_RGB base_rgb; //
float diffuse;  //
float specular; //
shading.light_dir = vector_normalize(vector_sub(*escena->light->pos,
			shading.hit_point));
shading.view_dir = vector_normalize(vector_sub(*escena->cam->pos,
			shading.hit_point));
diffuse = fmaxf(0.0f, vector_dot(shading.normal, shading.light_dir))
	* escena->light->intensity;
shading.reflected = reflect(vector_scale(shading.light_dir, -1),
		shading.normal);
specular = powf(fmaxf(vector_dot(shading.reflected, shading.view_dir),
			0.0f), 32.0f);
specular *= escena->light->intensity * light;
base_rgb = rgba_to_rgb(inter.min_color);
base_rgb.r = fminf(base_rgb.r * diffuse + specular * 255.0f
		+ escena->seting->ambient_col->r, 255);
base_rgb.g = fminf(base_rgb.g * diffuse + specular * 255.0f
		+ escena->seting->ambient_col->g, 255);
base_rgb.b = fminf(base_rgb.b * diffuse + specular * 255.0f
		+ escena->seting->ambient_col->b, 255);
return (rgb_to_rgba(base_rgb));
}
