#include "../../include/corewar.h"

void	in_and(t_vm *vm, t_process *process)
{
	t_mem	*ptr;
	int		reg1;
	int		reg2;
	int		reg3;

	UNUSED(vm);
	ptr = process->pc->next;
	reg1 = ptr->data;
	ptr = ptr->next;
	reg2 = ptr->data;
	reg3 = ptr->next->data;
	;
	if (BADREG(reg1) || BADREG(reg2) || BADREG(reg3))
		return ;
	reg3 = reg1 & reg2;
	process->carry = (reg3 == 0);
}
