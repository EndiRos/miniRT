/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <imugica-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:18:17 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/22 11:43:46 by imugica-         ###   ########.fr       */
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
