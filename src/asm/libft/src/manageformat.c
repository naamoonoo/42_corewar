/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manageformat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 02:39:17 by aderby            #+#    #+#             */
/*   Updated: 2017/08/14 23:59:47 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	store_datafmt(t_printf **print1, va_list *args)
{
	if (!((*print1)->pid->fmt = (t_format *)ft_memalloc(sizeof(t_format *))))
		return (0);
	if (!(set_uniondata(print1, (*print1)->type, args)))
		return (0);
	return (1);
}
