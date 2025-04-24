/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:55:22 by emgenc            #+#    #+#             */
/*   Updated: 2025/04/14 17:55:56 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <float.h>

static void	plus_minus_handler(int *sign, char **p)
{
	if (**p == '+' || **p == '-')
	{
		if (**p == '-')
			*sign = -1;
		(*p)++;
		if (**p == '\0')
			error();
	}
}

static void	digit_handler(int *d, double *div, double *result, const char *p)
{
	*d = 1;
	if (*div == 0.0)
	{
		if (*result > ((DBL_MAX - (*p - '0')) / 10.0))
			error();
		*result = (*result) * 10.0 + (*p - '0');
	}
	else
	{
		*result = *result + (((*p) - '0') / (*div));
		*div = (*div) * 10.0;
	}
}

static void	dot_handler(double *divider)
{
	if (*divider != 0.0)
		error();
	*divider = 10.0;
}

static void	initializer(double *r, double *d, int *s, int *dig)
{
	*r = 0.0;
	*d = 0.0;
	*dig = 0;
	*s = 1;
}

double	ft_atod(char *str)
{
	int			sign;
	double		result;
	double		divider;
	int			digitfound;

	if (*str == '\0')
		error();
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	ft_trailing(str, " \t\n\v\f\r");
	initializer(&result, &divider, &sign, &digitfound);
	plus_minus_handler(&sign, &str);
	while (*str != '\0')
	{
		if (*str == '.')
			dot_handler(&divider);
		else if (*str >= '0' && *str <= '9')
			digit_handler(&digitfound, &divider, &result, str);
		else
			error();
		str++;
	}
	if (digitfound == 0)
		error();
	return (sign * result);
}
