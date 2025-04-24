/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:04:04 by emgenc            #+#    #+#             */
/*   Updated: 2025/04/14 15:52:40 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <X11/keysym.h>

int	redraw(t_info *data)
{
	if (data->iteration_modifier != 0)
	{
		data->max_count += data->iteration_modifier;
		if (data->max_count > 25000)
			data->max_count = 25000;
		if (data->max_count < 3)
			data->max_count = 3;
		data->redraw_switch = 1;
	}
	if (data->redraw_switch)
	{
		if (data->fractal_type == 1)
			mandelbrot(data);
		else if (data->fractal_type == 2)
			julia(data, data->c_real, data->c_img);
		data->redraw_switch = 0;
	}
	return (0);
}

int	new_color(int count, int max_count)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = (double)count / max_count;
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	if (r < 0)
		r = 0;
	else if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	else if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	else if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

int	keyboard_hooks(int pressed_key, t_info *data)
{
	if (pressed_key == XK_Escape)
		graceful_exit(data);
	else if (pressed_key == XK_s)
		data->iteration_modifier = -1;
	else if (pressed_key == XK_w)
		data->iteration_modifier = 1;
	else if (pressed_key == XK_space)
		data->iteration_modifier = 0;
	else if (pressed_key == XK_BackSpace)
	{
		data->iteration_modifier = 0;
		data->max_count = CURRENT;
		data->redraw_switch = 1;
	}
	else if (pressed_key == XK_Up)
		data->offset_y += 0.1 * data->zoom_amount;
	else if (pressed_key == XK_Down)
		data->offset_y -= 0.1 * data->zoom_amount;
	else if (pressed_key == XK_Left)
		data->offset_x -= 0.1 * data->zoom_amount;
	else if (pressed_key == XK_Right)
		data->offset_x += 0.1 * data->zoom_amount;
	data->redraw_switch = 1;
	return (0);
}

int	mouse_hooks(int button, int x, int y, t_info *data)
{
	double	old_zoom;
	double	zoom_factor;

	old_zoom = data->zoom_amount;
	if (button == MW_ZOOMIN)
	{
		zoom_factor = 1.1;
		data->zoom_amount *= zoom_factor;
	}
	else if (button == MW_ZOOMOUT)
	{
		zoom_factor = 0.9;
		data->zoom_amount *= zoom_factor;
	}
	else
		return (0);
	data->offset_x += 4 * (((double)x / SIZE) - 0.5) * old_zoom
		* (1 - zoom_factor);
	data->offset_y -= 4 * (((double)y / SIZE) - 0.5) * old_zoom
		* (1 - zoom_factor);
	data->redraw_switch = 1;
	return (0);
}

void	my_mlx_pixel_put(t_info *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}
