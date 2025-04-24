/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trailing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:18:42 by emgenc            #+#    #+#             */
/*   Updated: 2025/04/14 17:53:26 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_trailing(char *s1, char const *set)
{
	size_t	end;

	if (!s1)
		return ;
	end = ft_strlen(s1) - 1;
	while (s1[end] && ft_strchr(set, s1[end]))
		end--;
	s1[end + 1] = '\0';
}
