/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <hnam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 03:08:47 by hnam              #+#    #+#             */
/*   Updated: 2019/09/24 17:24:19 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/visualizer.h"

int			get_small(int a, int b)
{
	return (a > b ? b : a);
}

int			ft_numlen(uint64_t n, uint64_t base)
{
	if (n < base)
		return (1);
	else
		return (ft_numlen(n % base, base)
			+ ft_numlen(n / base, base));
}

uint64_t	ft_pow_u(uint64_t base, int times)
{
	if (times == 0)
		return (1);
	else if (times == 1)
		return (base);
	else
		return (ft_pow_u(base, times - 1) * base);
}

char		*make_base_set(char *base, int str_base)
{
	int		i;
	char	*base_set;

	i = -1;
	base_set = "0123456789abcdef";
	if (!(base = (char *)malloc(sizeof(char) * (str_base + 1))))
		return (NULL);
	while (++i < str_base)
		base[i] = base_set[i];
	base[i] = '\0';
	return (base);
}

char		*base_itoa(uint64_t n, int str_base, int len)
{
	char		*res;
	char		*base_set;
	int			i;
	uint64_t	dv;
	int			num_len;

	i = 0;
	num_len = ft_numlen(n, (uint64_t)str_base);
	dv = ft_pow_u(str_base, num_len - 1);
	base_set = NULL;
	if (!(res = (char *)malloc((num_len + len + 1) * sizeof(char))))
		return (NULL);
	base_set = make_base_set(base_set, str_base);
	if (len > num_len)
		while (i < len - num_len)
			res[i++] = '0';
	while (num_len-- > 0)
	{
		res[i++] = base_set[n / dv];
		n -= (n / dv) * dv;
		dv /= str_base;
	}
	res[i] = '\0';
	ft_strdel(&base_set);
	return (res);
}
