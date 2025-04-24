/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:04:52 by emgenc            #+#    #+#             */
/*   Updated: 2025/04/14 16:38:11 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	new_iteration(t_complex *z, t_complex *c, int max_count)
{
	int		count;
	double	r2;
	double	i2;
	double	swap;

	count = -1;
	r2 = (z->real * z->real);
	i2 = (z->imaginary * z->imaginary);
	while ((r2 + i2) < 4 && ++count < max_count)
	{
		swap = r2 - i2 + c->real;
		z->imaginary = 2.0 * z->real * z->imaginary + c->imaginary;
		z->real = swap;
		r2 = (z->real * z->real);
		i2 = (z->imaginary * z->imaginary);
	}
	return (count);
}

void	mandelbrot(t_info *data)
{
	int			x;
	int			y;
	t_complex	z;
	t_complex	c;
	int			count;

	x = -1;
	while (++x < SIZE)
	{
		y = -1;
		while (++y < SIZE)
		{
			z.real = 0;
			z.imaginary = 0;
			c.real = (4 * ((double)x / SIZE) - 2.0) * data->zoom_amount
				+ data->offset_x;
			c.imaginary = (-4 * ((double)y / SIZE) + 2.0) * data->zoom_amount
				+ data->offset_y;
			count = new_iteration(&z, &c, data->max_count);
			my_mlx_pixel_put(data, x, y, new_color(count, data->max_count));
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	julia(t_info *data, double c_real, double c_img)
{
	int			x;
	int			y;
	t_complex	z;
	t_complex	c;
	int			count;

	x = -1;
	c.real = c_real;
	c.imaginary = c_img;
	while (++x < SIZE)
	{
		y = -1;
		while (++y < SIZE)
		{
			z.real = (4 * ((double)x / SIZE) - 2.0) * data->zoom_amount
				+ data->offset_x;
			z.imaginary = (-4 * ((double)y / SIZE) + 2.0) * data->zoom_amount
				+ data->offset_y;
			count = new_iteration(&z, &c, data->max_count);
			my_mlx_pixel_put(data, x, y, new_color(count, data->max_count));
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

static void	assign(t_info *data, char *fractal_name)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, SIZE, SIZE, fractal_name);
	data->img = mlx_new_image(data->mlx, SIZE, SIZE);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len,
			&data->endian);
	data->max_count = CURRENT;
	data->iteration_modifier = 0;
	data->zoom_amount = 1.0;
	data->offset_x = 0.0;
	data->offset_y = 0.0;
	data->redraw_switch = 1;
	data->shutdown_lock_active = 0;
	mlx_mouse_hook(data->win, mouse_hooks, data);
	mlx_key_hook(data->win, keyboard_hooks, data);
	mlx_loop_hook(data->mlx, redraw, data);
	mlx_hook(data->win, 17, 0, *graceful_exit, data);
	mlx_loop(data->mlx);
}

int	main(int argc, char *argv[])
{
	t_info	data;

	if (argc == 2 && ft_strncmp(argv[1], "mandelbrot", 11) == 0)
	{
		data.fractal_type = 1;
		assign(&data, "Mandelbrot");
		mandelbrot(&data);
	}
	else if (argc == 4 && ft_strncmp(argv[1], "julia", 6) == 0)
	{
		if (!(argv[2]) && !(argv[3]) && (argv[2][0] == '\0')
			&& (argv[3][0] == '\0'))
			error();
		data.c_real = ft_atod(argv[2]);
		data.c_img = ft_atod(argv[3]);
		data.fractal_type = 2;
		assign(&data, "Julia");
		julia(&data, data.c_real, data.c_img);
	}
	else
		error();
	return (0);
}
