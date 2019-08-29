/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widestuff2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 17:06:34 by aderby            #+#    #+#             */
/*   Updated: 2017/08/14 03:37:52 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int		pf_widechar(t_printf *print1)
{
	int fw;

	fw = 0;
	if (print1->pid->f_ladj != -1)
	{
		ft_putwchar(print1->pid->fmt->wc);
		while (++fw < print1->pid->fw)
			ft_putchar(' ');
	}
	else
	{
		while (++fw < print1->pid->fw)
			ft_putchar(' ');
		ft_putwchar(print1->pid->fmt->wc);
	}
	return (fw);
}
