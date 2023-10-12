/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheld <fheld@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:09:28 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/11 12:39:25 by fheld            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	final_free(t_data *data)
{
	free_2d_array(data->maze);
	free_2d_array(data->maze_cpy);
	free(data->textures.n_path);
	free(data->textures.e_path);
	free(data->textures.s_path);
	free(data->textures.w_path);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		ret;

	ret = 1;
	ret = check_args(ac, av);
	if (ret == 0)
		ret = check_file(av[1]);
	if (ret != 0)
		return (1);
	if (ret == 0)
		ret = setup_file(&data, av);
	if (ret == 0)
		ft_putstr_fd("-> SUCCESS:\n\tFile successfully parsed and valid.\n", 2);
	else
		ft_putstr_fd("-> ERROR:\n\tParsing aborted.\n", 2);
/*	if (ret == 0)
		ret = raytracker(&data);
	if (ret == 0)
		ret = draw_game(&data); */
 	if (ret == 0)
		ret = render_map(&data);
	final_free(&data);
	return (0);
}
