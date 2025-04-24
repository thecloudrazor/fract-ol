/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:05:02 by emgenc            #+#    #+#             */
/*   Updated: 2025/04/14 16:53:23 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	graceful_exit(t_info *data)
{
	if (data->shutdown_lock_active)
		return (0);
	data->shutdown_lock_active = 1;
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
}

void	error(void)
{
	ft_putstr_fd("\nError! You have supplied bad/wrong arguments. \n \n", 2);
	ft_putstr_fd("[USAGE]: \n./fractol julia [VALUE 1] [VALUE 2]\n", 2);
	ft_putstr_fd("./fractol mandelbrot\n\n\n\n", 2);
	exit(2);
}
