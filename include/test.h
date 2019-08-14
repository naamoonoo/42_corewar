/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 14:41:24 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/12 14:41:45 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# define WRITE_TO_MEM(MEM, VALUES, SIZE) \
	do \
	{ \
		t_mem *PTR = MEM; \
		for (int i = 0; i < SIZE; i++) \
		{ \
			PTR->data = VALUES[i]; \
			PTR = PTR->next; \
		} \
	} while (0)

#endif
