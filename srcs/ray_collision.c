/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheld <fheld@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:08:37 by fheld             #+#    #+#             */
/*   Updated: 2023/10/03 19:15:06 by fheld            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// no access protection yet and only checking 10 fields deep
t_int_p2	hrc_up(t_data *data)
{
	t_int_p2	end;
	int 		i;

	i = 0;
	while (1 && i < 10)
	{
		end.y = ((data->start.y / SPRITE_SIZE) - i) * SPRITE_SIZE;
		end.x = data->start.x - tan(data->start.dir / 180.0 * M_PI) * (data->start.y - end.y);
		if (end.y / SPRITE_SIZE - 1 < 0 || end.y / SPRITE_SIZE - 1 >= data->dim.dim_y)
			break ;
		if (end.x / SPRITE_SIZE < 0 || end.x / SPRITE_SIZE >= data->dim.dim_x)
			break ;
		if (data->maze_cpy[end.y / SPRITE_SIZE - 1][(end.x / SPRITE_SIZE)] == '1')
			break ;
		i++;
	}
	return (end);
}

t_int_p2	hrc_down(t_data *data)
{
	t_int_p2	end;
	int 		i;

	i = 0;
	while (1 && i < 10)
	{
		end.y = ((data->start.y / SPRITE_SIZE) + 1 + i) * SPRITE_SIZE;
		end.x = data->start.x - tan((data->start.dir - 180) / 180.0 * M_PI) * (data->start.y - end.y);
		if (end.y / SPRITE_SIZE < 0 || end.y / SPRITE_SIZE >= data->dim.dim_y)
			break ;
		if (end.x / SPRITE_SIZE < 0 || end.x / SPRITE_SIZE >= data->dim.dim_x)
			break ;
		if (data->maze_cpy[(end.y / SPRITE_SIZE)][(end.x / SPRITE_SIZE)] == '1')
			break ;
		i++;
	}
	return (end);
}

	// {
	// 	end.y = (data->start.y / SPRITE_SIZE) * SPRITE_SIZE;
	// 	end.x = data->start.x - tan(data->start.dir / 180.0 * M_PI) * (data->start.y - end.y); 
	// }
	// {
	// 	end.y = ((data->start.y / SPRITE_SIZE) + 1) * SPRITE_SIZE;
	// 	end.x = data->start.x - tan((data->start.dir - 180) / 180.0 * M_PI) * (data->start.y - end.y); 		
	// }
// order of calculation is important
t_int_p2	horizontal_ray_collision(t_data *data)
{
	t_int_p2	end;

	if (data->start.dir > 270 || data->start.dir < 90)
		end = hrc_up(data);
	else if (data->start.dir < 270 && data->start.dir > 90)
		end = hrc_down(data);
	else if (data->start.dir == 90)
	{
		end.x = 0;
		end.y = data->start.y; 
	}
	else if(data->start.dir == 270)
	{
		end.x = (data->start.x - data->dim.min_x);
		end.y = data->start.y; 
	}
	else
		end = (t_int_p2){1,1};
	return (end);
}

// note: we are not checking for out of boundness of the array
// array access function?
// t_int_p2	vrc_left(t_data *data)
// {
// 	t_int_p2	end;
// 	int			i;

// 	i = 0;
// 	while (1)
// 	{
// 		end.x = ((data->start.x / SPRITE_SIZE) - i) * SPRITE_SIZE;
// 		end.y = data->start.y - tan((90 - data->start.dir) / 180.0 * M_PI) * (data->start.x - end.x - (i * SPRITE_SIZE)); 
// 		if (data->maze_cpy[(end.y/SPRITE_SIZE - 1)][(end.x/SPRITE_SIZE)] == '1')
// 			break ;
// 		i++;
// 	}
// 	return (end);
// }


t_int_p2	vrc_left(t_data *data)
{
	t_int_p2	end;
	int 		i;

	i = 0;
	while (1 && i < 10)
	{
		end.x = (data->start.x / SPRITE_SIZE - i) * SPRITE_SIZE;
		end.y = data->start.y - tan((90 - data->start.dir) / 180.0 * M_PI) * (data->start.x - end.x); 
		if (end.y / SPRITE_SIZE < 0 || end.y / SPRITE_SIZE >= data->dim.dim_y)
			break ;
		if (end.x / SPRITE_SIZE - 1 < 0 || end.x / SPRITE_SIZE - 1 >= data->dim.dim_x)
			break ;
		// mlx_put_pixel(data->mlx42.mm_player_img, end.x, end.y, 0x00FF00FF);
		if (data->maze_cpy[(end.y / SPRITE_SIZE)][(end.x / SPRITE_SIZE) -1 ] == '1')
			break ;
		i++;
	}
	return (end);
}

t_int_p2	vrc_right(t_data *data)
{
	t_int_p2	end;
	int 		i;

	i = 0;
	while (1 && i < 10)
	{
        end.x = (data->start.x / SPRITE_SIZE + 1 + i) * SPRITE_SIZE;
		end.y = data->start.y - tan((data->start.dir - 270) / 180.0 * M_PI) * (end.x - data->start.x); 
		if (end.y / SPRITE_SIZE < 0 || end.y / SPRITE_SIZE >= data->dim.dim_y)
			break ;
		if (end.x / SPRITE_SIZE < 0 || end.x / SPRITE_SIZE >= data->dim.dim_x)
			break ;
		if (data->maze_cpy[end.y / SPRITE_SIZE][end.x / SPRITE_SIZE] == '1')
			break ;
		i++;
	}
	return (end);
}

t_int_p2	vertical_ray_collision(t_data *data)
{
	t_int_p2	end;

	if (data->start.dir > 0 && data->start.dir < 180)
		end = vrc_left(data);
	else if (data->start.dir > 180 && data->start.dir < 360)
		end = vrc_right(data);
	else if (data->start.dir == 0)
	{
		end.x = data->start.x; 
		end.y = 0;
	}
	else if(data->start.dir == 180)
	{
		end.x = data->start.x; 
		end.y = (data->start.y - data->dim.min_y);
	}
	else
		end = (t_int_p2){1,1};
	return (end);
}
