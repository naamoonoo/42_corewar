/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizers.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 11:33:05 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/12 14:55:25 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIZERS_H
# define SIZERS_H

# include "argsize.h"

ARGSIZE	size_char(char modifier);
ARGSIZE	size_int(char modifier);
ARGSIZE	size_double(char modifier);
ARGSIZE	size_ptr(char modifier);

#endif
