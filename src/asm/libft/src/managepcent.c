/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managepcent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 18:43:03 by aderby            #+#    #+#             */
/*   Updated: 2017/08/15 21:23:34 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static void	continue_readjusting_percentid(t_printf **print1)
{
	if (PFT == DD_TYPE || PFT == OO_TYPE || PFT == UU_TYPE)
	{
		PFT = (PFT == DD_TYPE) ? L_TYPE : PFT;
		PFT = (PFT == OO_TYPE) ? UL_TYPE : PFT;
		PFT = (PFT == UU_TYPE) ? UL_TYPE : PFT;
		(*print1)->pid->len = L_L;
	}
	if ((*print1)->pid->len == L_L)
	{
		PFT = (PFT == S_TYPE) ? WS_TYPE : PFT;
		PFT = (PFT == C_TYPE) ? WC_TYPE : PFT;
	}
	(*print1)->pid->base = (PFT == P_TYPE) ? 16 : (*print1)->pid->base;
	(*print1)->pid->f_alt = (PFT == P_TYPE) ? 16 : (*print1)->pid->f_alt;
}

void		readjust_percentid(t_printf **print1, char *s, int a)
{
	if (ft_isnumericconversionchar(s[a - 1]))
	{
		(*print1)->pid->f_zero = (((*print1)->pid->prec != -1 ||
					(*print1)->pid->f_ladj != -1)
				? -1 : (*print1)->pid->f_zero);
		(*print1)->pid->f_space = ((*print1)->pid->f_sign != -1
				? -1 : (*print1)->pid->f_space);
	}
	PFT = (IS_DI(PFT)) && ((*print1)->pid->len == L_HH) ? SC_TYPE : PFT;
	PFT = (IS_OUX(PFT)) && ((*print1)->pid->len == L_HH) ? UC_TYPE : PFT;
	PFT = (IS_DI(PFT)) && ((*print1)->pid->len == L_H) ? SH_TYPE : PFT;
	PFT = (IS_OUX(PFT)) && ((*print1)->pid->len == L_H) ? USH_TYPE : PFT;
	PFT = (IS_DI(PFT)) && ((*print1)->pid->len == L_L) ? L_TYPE : PFT;
	PFT = (IS_DI(PFT)) && ((*print1)->pid->len == L_LL) ? LL_TYPE : PFT;
	PFT = (IS_OUX(PFT)) && ((*print1)->pid->len == L_L) ? UL_TYPE : PFT;
	PFT = (IS_OUX(PFT)) && ((*print1)->pid->len == L_LL) ? ULL_TYPE : PFT;
	PFT = (IS_DI(PFT)) && ((*print1)->pid->len == L_J) ? IM_TYPE : PFT;
	PFT = (IS_OUX(PFT)) && ((*print1)->pid->len == L_J) ? UIM_TYPE : PFT;
	PFT = (IS_DI(PFT)) && ((*print1)->pid->len == L_Z) ? ST_TYPE : PFT;
	PFT = (IS_OUX(PFT)) && ((*print1)->pid->len == L_Z) ? ST_TYPE : PFT;
	continue_readjusting_percentid(print1);
}

void		initialize_function(t_function *function)
{
	function[0].f = &set_flags;
	function[1].f = &set_fieldwidth;
	function[2].f = &set_precision;
	function[3].f = &set_length;
	function[4].f = &set_type;
}

t_pid		*new_percentid(void)
{
	t_pid *new;

	if (!(new = (t_pid *)ft_memalloc(sizeof(t_pid))))
		return (NULL);
	new->fw = -1;
	new->prec = -1;
	new->len = -1;
	new->f_alt = -1;
	new->f_zero = -1;
	new->f_ladj = -1;
	new->f_space = -1;
	new->f_sign = -1;
	new->base = 10;
	new->xbase = -1;
	new->fmt = NULL;
	return (new);
}

int			store_formatmods(t_printf **p, char *s, va_list *a, int r)
{
	int			i;
	int			b;
	t_function	function[5];

	i = 0;
	b = 0;
	initialize_function(function);
	(*p)->next = ((*p)->type != -1) ? newlist() : NULL;
	*p = ((*p)->type != -1) ? (*p)->next : *p;
	if (s[++i])
	{
		if (!((*p)->pid = new_percentid()))
			return (-1);
		while (i != -1 && b < 5)
			i = function[b++].f(p, s, i);
		if (i != -1)
		{
			readjust_percentid(p, s, i);
			if (!(store_datafmt(p, a)))
				return (-1);
			return (i + r);
		}
	}
	return (-1);
}
