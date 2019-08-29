#include "../../include/corewar.h"
#include "../../include/visualizer.h"

t_sdl	*sdl_init(void);

void	visualizer_sdl_process_lived(void *data, t_process *process)
{
	UNUSED(data);
	return ;
	ft_printf("process %d lived\n", process->pid);
}

void	visualizer_sdl_memory_read(void *data, t_mem *address, int value, t_process *process)
{
	UNUSED(data);
	return ;
	ft_printf("%s #%d (color %.8X) read %d from %p\n", process->owner->name, process->pid, process->owner->color, value, address);
}

void	visualizer_sdl_memory_written(void *data, t_mem *address, int value, t_process *process)
{
	t_sdl	*sdl;

	sdl = (t_sdl *)data;
	address->owner = process->owner->filename;
	address->next->owner = process->owner->filename;
	address->next->next->owner= process->owner->filename;
	address->next->next->next->owner = process->owner->filename;
	address->is_instruction = 1;
	return ;
	ft_printf("%s #%d (color %.8X) wrote value %d to %p\n", process->owner->name, process->pid, process->owner->color, value, address);
}

void	get_pc(t_sdl *sdl, t_vm *vm)
{
	static int	call_time = 0;
	t_process	*process;
	int			i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		vm->memory->is_pc = 0;
		if (call_time == 0)
			vm->memory->rect = (SDL_Rect){MAP_P_X + (i % 64) * BOX_W + 1,
			MAP_P_Y + (i  / 64) * BOX_H + 1, BOX_W - 2, BOX_H - 2};
		vm->memory = vm->memory->next;
	}
	sdl->mem_start = vm->memory;
	process = vm->p_list;
	while(process)
	{
		process->pc->is_pc = 1;
		process = process->next;
	}
}

void	visualizer_sdl_render(void *data, t_vm *vm)
{
	t_sdl	*sdl;

	sdl = (t_sdl *)data;
	get_pc(sdl, vm);
	while (SDL_PollEvent(&(sdl->e)))
		event_handler(sdl);
	SDL_RenderClear(sdl->ren);
	render_play_page(sdl);
	// SDL_SetRenderDrawBlendMode(sdl->ren, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(sdl->ren, 0xda, 0xdd, 0xdf, 0);
	SDL_RenderPresent(sdl->ren);
	SDL_Delay(1000 / 60);
	return ;
	ft_printf("Cycle %d\n", vm->total_cycles);
}

void	visualizer_sdl_init(void *data, int argc, char **argv)
{

	t_sdl	*sdl;

	sdl = (t_sdl *)data;
	// SDL_RenderClear(sdl->ren);
	// UNUSED(data);
	// SDL_RenderPresent(sdl->ren);
	UNUSED(argc);
	UNUSED(argv);
}

void	visualizer_sdl_instruction_read(void *data, t_mem *address)
{
	UNUSED(data);
	return ;
	ft_printf("instruction %d read at address %p\n", address->data, address);
}

void	visualizer_sdl_instruction_fired(void *data, t_mem *address)
{
	UNUSED(data);
	return ;
	ft_printf("instruction fired at address %p\n", address);
}

int		visualizer_sdl_program_active(void *data)
{
	t_sdl	*sdl;

	sdl = (t_sdl *)data;
	// SDL_SetRenderDrawColor(sdl->ren, 0xda, 0xdd, 0xdf, 0);
	// SDL_RenderClear(sdl->ren);
	return (sdl->is_running);
}

void	visualizer_sdl_game_over(void *data, t_vm *vm)
{
	int		winner_id;
	char	*winner_name;
	t_sdl	*sdl;

	sdl = (t_sdl *)data;
	winner_id = vm->last_alive;
	winner_name = vm_get_champ_name(vm, winner_id);
	render_finish(sdl, winner_id, winner_name);
	return ;
	ft_printf("Player %d (%s) won\n", winner_id, winner_name);
}

void	visualizer_sdl_cleanup(void *data)
{
	t_sdl	*sdl;

	sdl = (t_sdl *)data;
	while (!sdl->is_quit)
	{
		while (SDL_PollEvent(&(sdl->e)))
			if (sdl->e.type == SDL_QUIT || sdl->e.key.keysym.sym == 27)
				sdl->is_quit = 1;
		SDL_Delay(1000 / 60);
	}
	end_process(sdl);
}

static t_arrlst	*champs_from_file_array(t_set selected_cmp[MAX_PLAYERS], int n)
{
	int			champ_number;
	t_arrlst	*champions;
	t_champion	*champ;
	int			i;

	champions = ft_arrlst_new(sizeof(t_champion *));
	if (champions == NULL)
		return (NULL);
	champ_number = 1;
	i = 0;
	while (i < n)
	{
		champ = read_champion_from_file(selected_cmp[i].text);
		if (champ == NULL)
			return (NULL);
		champ->number = champ_number;
		// TODO better color assignment
		champ->color = rand();
		if (ft_arrlst_add(champions, &champ) == NULL)
		{
			ft_printf("Failed to add champion.\n");
//			free_champions(champions);
		}
		champ_number++;
		i++;
	}
	return (champions);
}

t_arrlst	*visualizer_sdl_select_champs(void *data)
{
	t_sdl	*sdl;

	sdl = (t_sdl *)data;
	sdl->ready = FALSE;
	while (!sdl->ready)
	{
		sdl = (t_sdl *)data;
		while (SDL_PollEvent(&(sdl->e)))
			event_handler(sdl);
		SDL_RenderClear(sdl->ren);
		render_start_page(sdl);
		SDL_SetRenderDrawColor(sdl->ren, 0xda, 0xdd, 0xdf, 0);
		SDL_RenderPresent(sdl->ren);
		SDL_Delay(1000 / 60);
	}
	// delete start
	destroy_start_page(sdl);
	return (champs_from_file_array(sdl->selected_cmp, sdl->nb_of_p));
}

t_visualizer	*visualizer_sdl_new(void)
{
	t_visualizer *gv;
	t_sdl	*sdl;

	gv = (t_visualizer *)malloc(sizeof(t_visualizer));
	if (gv == NULL)
		return (NULL);
	sdl = sdl_init();
	if (sdl == NULL)
	{
		free(gv);
		return (NULL);
	}
	gv->data = sdl;
	gv->init = &visualizer_sdl_init;
	gv->instruction_read = &visualizer_sdl_instruction_read;
	gv->instruction_fired = &visualizer_sdl_instruction_fired;
	gv->process_lived = &visualizer_sdl_process_lived;
	gv->memory_read = &visualizer_sdl_memory_read;
	gv->memory_written = &visualizer_sdl_memory_written;
	gv->render = &visualizer_sdl_render;
	gv->program_active = &visualizer_sdl_program_active;
	gv->game_over = &visualizer_sdl_game_over;
	gv->cleanup = &visualizer_sdl_cleanup;
	gv->select_champs = &visualizer_sdl_select_champs;
	sdl->mem_start = gv->mem_start;
	return (gv);
}
