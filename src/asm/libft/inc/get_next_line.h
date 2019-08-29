/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 15:01:08 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/30 19:20:06 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# include "libft.h"

# define BUFF_SIZE 1024

/*
** WARNING! Avoid buffer size of larger than 65536
*/

int				get_next_line(const int fd, char **line);

typedef struct	s_fragment
{
	char		*data;
	int			size;
}				t_fragment;

#endif
