#include "../../include/corewar.h"

void	in_sub(t_vm *vm, t_process *process)
{
	t_mem	*ptr;
	int		reg1;
	int		reg2;
	int		reg3;
	int		res;

	UNUSED(vm);
	ptr = process->pc->next;
	reg1 = ptr->data;
	ptr = ptr->next;
	reg2 = ptr->data;
	reg3 = ptr->next->data;
	;
	if (BADREG(reg1) || BADREG(reg2) || BADREG(reg3))
		return ;
	res = process->registers[reg1] - process->registers[reg2];
	process->registers[reg3] = res;
	process->carry = (res == 0);
}
