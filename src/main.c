/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:16:36 by imugica-          #+#    #+#             */
/*   Updated: 2025/05/26 11:46:32 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	key_hook(struct mlx_key_data keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(mlx);
	}
}
int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_scene		*escena;

    escena = (t_scene *) malloc (sizeof (t_scene));
	ft_memset (escena, 0 , sizeof(t_scene));
    parse(escena, argv[1]);
	(void)argc;
	if (!(mlx = mlx_init(1920, 1080, "tXuperRT", true)))
		return (perror(mlx_strerror(mlx_errno)), 1);
	if (!(image = mlx_new_image(mlx, 1920, 1080)))
		return (mlx_close_window(mlx),perror(mlx_strerror(mlx_errno)), 1);
	calculate_image(image, escena);
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
		return (mlx_close_window(mlx),perror(mlx_strerror(mlx_errno)), 1);
	mlx_key_hook(mlx, key_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_escena(&escena);
	return (0);
}
