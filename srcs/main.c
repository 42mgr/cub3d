/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:09:28 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/26 19:03:51 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		ret = draw_game(&data);
	free_data(&data)	*/

	/*
	my free_strs is not working, so everything here manually
	 */
	if (data.maze)
	{
		int i = 0;
		while (data.maze[i])
		{
			free(data.maze[i++]);
		}
		free(data.maze);
	}
	free(data.textures.n_path);
	free(data.textures.e_path);
	free(data.textures.s_path);
	free(data.textures.w_path);
	return (0);
}
