/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheld <fheld@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:29:04 by fheld             #+#    #+#             */
/*   Updated: 2023/09/20 16:34:11 by fheld            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <unistd.h>

char	**map_00(void);

void	ft_dot(void * param)
{
	mlx_image_t*	image;

	image = param;
	mlx_put_pixel(image, 20, 20, 0xFFFFFFFF);
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	put_minimap(mlx_t **mlx)
{
	mlx_image_t*	image;
	
	//tmp
	char	**arr;
	arr = map_00();
	ft_putstr_fd(arr[0], 1);
	//endtmp

	if(!(*mlx = mlx_init(1000, 500, "cub3d mg fh 1", true)))
		ft_putstr_fd("err1", 1);
	
	if(!(image = mlx_new_image(*mlx, 128, 128)))
		ft_putstr_fd("err2", 1);
	
    if(-1 == mlx_image_to_window(*mlx, image, 10, 10))
		ft_putstr_fd("err3", 1);


	mlx_loop_hook(*mlx, ft_dot, image);
	mlx_loop_hook(*mlx, ft_hook, *mlx);
	mlx_loop(*mlx);

	mlx_terminate(*mlx);

	return ;
}