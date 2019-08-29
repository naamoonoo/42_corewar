/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 10:53:26 by aderby            #+#    #+#             */
/*   Updated: 2017/06/08 13:30:49 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalnum(int c)
{
	int alphacheck;
	int numcheck;

	alphacheck = ft_isalpha(c);
	numcheck = ft_isdigit(c);
	if (alphacheck == 1 || numcheck == 1)
		return (1);
	return (0);
}
