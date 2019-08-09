/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:34:35 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/01 21:21:23 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	put_int_min_fd(int fd)
{
	write(fd, "-2147483648", 11);
}

void		ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	digit;

	if (fd < 0)
		return ;
	if (n == -2147483648)
		return (put_int_min_fd(fd));
	if (n < 0)
	{
		write(fd, "-", 1);
		return (ft_putnbr_fd(0 - n, fd));
	}
	i = 1;
	while (n / 10 >= i)
		i *= 10;
	while (i != 0)
	{
		digit = '0' + (n / i) % 10;
		write(fd, &digit, 1);
		i /= 10;
	}
}
