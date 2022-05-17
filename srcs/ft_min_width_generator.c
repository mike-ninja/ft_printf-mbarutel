/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_width_generator.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:30:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/05/16 10:34:26 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

char	*ft_min_width_generator(t_flags *flags)
{
	int		i;
	char	*ret;

	if (flags->width > 0)
	{
		i = 0;
		ret = (char *)malloc(flags->width + 1);
		if (ret)
		{
			ret[flags->width] = '\0';
			while (i < flags->width)
			{
				if (flags->zero)
					ret[i++] = '0';
				else
					ret[i++] = ' ';
			}
			return (ret);
		}
	}
	return (NULL);
}
