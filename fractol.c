/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:44:28 by emgenc            #+#    #+#             */
/*   Updated: 2025/02/14 11:26:27 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <X11/keysym.h>
#include <math.h>

int	key_hook(int keycode, t_data *d)
{
	if (keycode == XK_Escape)
		graceful_exit(d);
	return (0);
}

void	my_mlx_pixel_put(t_data *d, int x, int y, int color)
{
	char	*dst;

	dst = d->addr + (y * d->len + x * (d->bpp / 8));
	*(unsigned int *)dst = color;
}

int	main(void)
{
	t_data	d;

	d.mlx = mlx_init();
	d.win = mlx_new_window(d.mlx, 1920, 1080, "fractol");
	d.img = mlx_new_image(d.mlx, 1920, 1080);
	d.addr = mlx_get_data_addr(d.img, &d.bpp, &d.len, &d.endian);
	mlx_put_image_to_window(d.mlx, d.win, d.img, 0, 0);
	mlx_key_hook(d.win, key_hook, &d);
	mlx_hook(d.win, 17, 0, *graceful_exit, &d);
	mlx_loop(d.mlx);
}
