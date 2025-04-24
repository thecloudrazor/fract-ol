/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:41:55 by emgenc            #+#    #+#             */
/*   Updated: 2025/04/14 18:01:53 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx/mlx.h"
# include "libft-emgenc/libft.h"
# include <stdlib.h>

# define SIZE 800
# define CURRENT 30
# define MW_ZOOMOUT 4
# define MW_ZOOMIN 5

typedef struct s_complex
{
	double	imaginary;
	double	real;
}			t_complex;

typedef struct s_info
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		iteration_modifier;
	int		max_count;
	int		fractal_type;
	int		redraw_switch;
	int		shutdown_lock_active;
	double	c_real;
	double	c_img;
	double	zoom_amount;
	double	offset_x;
	double	offset_y;
}			t_info;

void	mandelbrot(t_info *data);
void	julia(t_info *data, double c_real, double c_img);
double	ft_atod(char *str);
int		redraw(t_info *data);
int		new_color(int count, int max_count);
int		keyboard_hooks(int pressed_key, t_info *data);
int		mouse_hooks(int button, int x, int y, t_info *data);
void	error(void);
int		graceful_exit(t_info *data);
void	my_mlx_pixel_put(t_info *data, int x, int y, int color);

#endif
