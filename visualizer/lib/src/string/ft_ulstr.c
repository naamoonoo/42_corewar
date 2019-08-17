/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 00:01:20 by hnam              #+#    #+#             */
/*   Updated: 2019/03/01 00:01:21 by hnam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ulstr(char c)
{
	char	temp;

	if (c >= 'a' && c <= 'z')
		temp = c - 32;
	else if (c >= 'A' && c <= 'Z')
		temp = c + 32;
	else
		temp = c;
	write(1, &temp, 1);
}