/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfuncswchar2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:15:22 by aderby            #+#    #+#             */
/*   Updated: 2017/08/14 16:36:17 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

wchar_t	*ft_wstrnew(size_t len)
{
	wchar_t	*str;

	if (!(str = (wchar_t *)malloc(sizeof(wchar_t) * len + 1)))
		return (NULL);
	ft_memset(str, L'\0', len + 1);
	return (str);
}

void	ft_putwstr(wchar_t *ws)
{
	int i;

	i = 0;
	while (ws[i])
		ft_putwchar(ws[i++]);
}
