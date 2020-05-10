/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uspec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerolamo <jerolamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:00:46 by kdeloise          #+#    #+#             */
/*   Updated: 2020/05/10 17:03:17 by jerolamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_uspec(t_args *ag, t_fls *fl)
{
	fl->unsign = 1;
	if (!fl->lnh)
		return (ft_itoa_base(fl, va_arg(ag->args, unsigned int),
		4, "0123456789"));
	else if (fl->lnh == 2)
		return (ft_itoa_base(fl, va_arg(ag->args, unsigned long long int),
		8, "0123456789"));
	else if (fl->lnh == 1)
		return (ft_itoa_base(fl, va_arg(ag->args, unsigned long int),
		8, "0123456789"));
	else if (fl->lnh == 4)
		return (ft_itoa_base(fl, (unsigned char)va_arg(ag->args, unsigned int),
		1, "0123456789"));
	else if (fl->lnh == 3)
	{
		return (ft_itoa_base(fl, (unsigned short)va_arg(ag->args, unsigned int),
		2, "0123456789"));
	}
	return (0);
}

char	*ft_pspec(t_args *ag, t_fls *fl)
{
	fl->isptr = 1;
	return (ft_itoa_base(fl, va_arg(ag->args, long long int),
	8, "0123456789abcdef"));
}
