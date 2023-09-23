/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:29:37 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/22 22:11:15 by mgraf            ###   ########.fr       */
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
			ft_putstr("-> Error:\n", "\tFile path is invalid or does not exist.");
		else
			ft_putstr("-> Error opening the the file:\t", strerror(errno));
		close(fd);
		ft_putstr("\t", path);
		return (1);
	}
	else
	{
		if (read(fd, NULL, 0) == -1)
		{
			ft_putstr("-> Error:\n\t", path);
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
