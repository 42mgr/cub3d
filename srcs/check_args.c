/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:29:37 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/20 22:32:22 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_putstr(char *string, char *arg)
{
	ft_putstr_fd(string, 1);
	ft_putstr_fd(arg, 1);
	ft_putstr_fd("\n", 1);
}

int	check_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr(path, ": ");
		if (errno == ENOENT)
			ft_putstr("\tFile path is invalid or does not exist.", NULL);
		else
			ft_putstr("\tError opening the the file: ", strerror(errno));
		close(fd);
		return (1);
	}
	else
	{
		if (read(fd, NULL, 0) == -1)
		{
			ft_putstr(path, ": ");
			ft_putstr("\tFile is valid, but no read permissions.", NULL);
			close(fd);
			return (1);
		}
	}
	close(fd);
	return (0);
}

int	check_args(int ac, char **av)
{
	int	len;

	if (ac == 1 || ac != 2)
	{
		ft_putstr("Wrong number of arguments. Only one .cub file.", NULL);
		return (1);
	}
	len = ft_strlen(av[1]);
	if (len < 5)
	{
		ft_putstr("Invalid name for .cub file.", NULL);
		return (1);
	}
	if (ft_strncmp(av[1] + len - 4, ".cub", 4))
	{
		ft_putstr("Invalid type. Please use .cub extension.", NULL);
		return (1);
	}
	return (check_file(av[1]));
}
