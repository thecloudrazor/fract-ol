/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:44:28 by emgenc            #+#    #+#             */
/*   Updated: 2025/02/12 22:21:33 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
# include <X11/keysym.h>
# include <math.h>
# include <stdlib.h>

int	key_hook(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		graceful_exit(data);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	main(void)
{
	t_data	data;

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, 1920, 1080, "fract-ol");
	data.img = mlx_new_image(data.mlx, 1920, 1080);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_len, &data.endian);
	mlx_put_image_to_window(data.mlx, data.window, data.img, 0, 0);
	mlx_key_hook(data.window, key_hook, &data);
	mlx_loop(data.mlx);
}
