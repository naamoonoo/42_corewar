void	process_prepare_instruction(t_process *process)
{
	char		op_code;
	const t_op	*op;

	op_code = process->pc->data;
	if (op_code < 1 || op_code > MAX_OPS)
	{
		process->instruction = NULL;
		process->cycles_to_wait = 1;
	}
	op = &g_op_tab[op_code - 1];
	process->instruction = op->instruction;
	process->cycles_to_wait = op->cycles;
}
