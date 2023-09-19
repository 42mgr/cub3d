#include <sys/types.h>
#include <stddef.h>

//typedef int mlx_t;
//typedef int bool;

void	ft_putstr_fd(char *s, int fd);
//static bool mlx_init_render(mlx_t* mlx);

int main()
{
	ft_putstr_fd("hello", 1);
//	mlx_init_render(NULL);
	return (0);
}