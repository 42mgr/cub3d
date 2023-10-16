/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:29:37 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/16 16:22:51 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Writes string to fd 2 (stderr)
*/
static void	ft_putstr(char *string, char *arg)
{
	ft_putstr_fd(string, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\n", 2);
}

/**
 * Checks if the file exists and is readable
*/
int	check_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		if (errno == ENOENT)
			ft_putstr("\e[1;41mError\e[0m\n", "\tFile path is invalid.");
		else
			ft_putstr("\e[1;41mError\e[0m\n opening file:\t", strerror(errno));
		close(fd);
		ft_putstr("\t", path);
		return (1);
	}
	else
	{
		if (read(fd, NULL, 0) == -1)
		{
			ft_putstr("\e[1;41mError\e[0m\n\t", path);
			ft_putstr("\tFile is valid, but no read permissions.", NULL);
			close(fd);
			return (1);
		}
	}
	close(fd);
	return (0);
}

/**
 * Checks if the file extension is .cub
*/
int	check_args(int ac, char **av)
{
	int	len;

	if (ac == 1 || ac != 2)
	{
		ft_putstr("Error\n\tWrong number of arguments.", NULL);
		return (1);
	}
	len = ft_strlen(av[1]);
	if (len < 5)
	{
		ft_putstr("\e[1;41mError\e[0m\n\tInvalid name for .cub file.", NULL);
		return (1);
	}
	if (ft_strncmp(av[1] + len - 4, ".cub", 4))
	{
		ft_putstr("\e[1;41mError\e[0m\n\tInvalid type. Please use .cub extension.", NULL);
		return (1);
	}
	return (0);
}
