/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 18:18:52 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/13 19:15:58 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_visualizer
{
	void		*data;
	t_mem		*mem_start;
	void		(*init)(void *gv_data);
	void		(*instruction_read)(void *gv_data, int index);
	void		(*instruction_fired)(void *gv_data, int index);
	void		(*process_lived)(void *gv_data, t_process *process);
	void		(*memory_read)(void *gv_data, t_mem *address, int value);
	void		(*memory_written)(void *gv_data, t_mem *address, int value);
	void		(*update_misc)(void *gv_data, t_vm *vm);
}				t_visualizer;
