/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <imugica-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:18:17 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/19 11:36:15 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_RGB rgba_to_rgb(unsigned int color)
{
	t_RGB rgb;
	rgb.r = (color >> 24) & 0xFF;
	rgb.g = (color >> 16) & 0xFF;
	rgb.b = (color >> 8) & 0xFF;
	return rgb;
}

unsigned int	rgb_to_rgba(t_RGB rgb)
{
	return (((rgb.r & 0xFF) << 24) | ((rgb.g & 0xFF) << 16) | ((rgb.b & 0xFF) << 8) | 0xFF);
}