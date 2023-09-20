/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:09:28 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/20 21:56:15 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		ret;

	// temp necessary for wall werror wextra
	(void)ac;
	(void)av;
	(void)env;
	(void)data;

	ret = 1;
 	ret = check_args(ac, av);
/*	if (ret == 0)
		ret = setup_file(data, av);
	if (ret == 0)
		ret = raytracker(data);
	if (ret == 0)
		ret = draw_game(data); */
	return (ret);
}