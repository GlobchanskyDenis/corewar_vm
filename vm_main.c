/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:16:17 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/27 20:41:27 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_vm	*create_vm_struct(short *tab)
{
	t_vm	*vm;

	if (!tab)
		error_exit(NULL, "create_vm_struct - empty ptr found");
	if (!(vm = (t_vm *)ft_memalloc(sizeof(t_vm))))
		error_exit(NULL, "create_vm_struct - malloc (vm) returned null");
	if (!(vm->player = (t_pl *)ft_memalloc(sizeof(t_pl) * tab[0])))
		error_exit(vm, "create_vm_struct - malloc (player arr) returned null");
	if (!(vm->arena = (unsigned char *)ft_memalloc(sizeof(unsigned char) * \
			MEM_SIZE)))
		error_exit(vm, "create_vm_struct - malloc (arena) returned null");
	if (!(vm->command_tab = (t_command *)ft_memalloc(sizeof(t_command) * \
			COMMAND_AMOUNT)))
		error_exit(vm, "create_vm_struct - malloc (command) returned null");
	vm->tab = tab;
	vm->max_pl = tab[0];
	return (vm);
}

void		exe_carriages(t_vm *vm)
{
	t_car *carriage;

	carriage = vm->car;
	while (carriage)
	{
		if (carriage->cycles_to_exe > 0)
			carriage->cycles_to_exe--;
		else
		{
			vm->operation[carriage->command](carriage, vm);
			carriage_make_step(carriage, vm);
			carriage_read_command(carriage, vm);
		}
		carriage = carriage->next;
	}
}

/*
**	if (get_info(vm->arena[MEM_SIZE - 4], 1) == REG_CODE)
**		fprint("This byte is register\n");
**	else if (get_info(vm->arena[MEM_SIZE - 4], 1) == DIR_CODE)
**		fprint("This byte is dir address\n");
**	else if (get_info(vm->arena[MEM_SIZE - 4], 1) == IND_CODE)
**		fprint("This byte is ind address\n");
**	else
**		fprint("Empty\n");
**	if (get_info(vm->arena[MEM_SIZE - 4], 2) == REG_CODE)
**		fprint("This byte is register\n");
**	else if (get_info(vm->arena[MEM_SIZE - 4], 2) == DIR_CODE)
**		fprint("This byte is dir address\n");
**	else if (get_info(vm->arena[MEM_SIZE - 4], 2) == IND_CODE)
**		fprint("This byte is ind address\n");
**	else
**		fprint("Empty\n");
**	if (get_info(vm->arena[MEM_SIZE - 4], 3) == REG_CODE)
**		fprint("This byte is register\n");
**	else if (get_info(vm->arena[MEM_SIZE - 4], 3) == DIR_CODE)
**		fprint("This byte is dir address\n");
**	else if (get_info(vm->arena[MEM_SIZE - 4], 3) == IND_CODE)
**		fprint("This byte is ind address\n");
**	else
**		fprint("Empty\n");
**	if (get_info(vm->arena[MEM_SIZE - 4], 4) == REG_CODE)
**		fprint("This byte is register\n");
**	else if (get_info(vm->arena[MEM_SIZE - 4], 4) == DIR_CODE)
**		fprint("This byte is dir address\n");
**	else if (get_info(vm->arena[MEM_SIZE - 4], 4) == IND_CODE)
**		fprint("This byte is ind address\n");
**	else
**		fprint("Empty\n");
*/

int			main(int ac, char **av)
{
	t_vm	*vm;
	size_t	cur_cycle;
	size_t	next_check;

	if (ac < 2 || (ac < 3 && av[1][0] == '-') || ac > MAX_ARGS_NUMBER + 10)
	{
		fprint("Wrong number of parameters. ");
		fprint("Flags: [-grafix] [-dump nbr_cycles]\n");
		free_exit(NULL, "Use: ./corewar [-flags] [[-n number]champion] ...");
	}
	if (!(vm = create_vm_struct(preliminary_parse_flags(ac, av))))
		error_exit(vm, "main - null ptr returned");
	initialize_all(ac, av, vm);
	print_all(vm);
	cur_cycle = 0;
	next_check = vm->cycles_to_die;
	while (vm->cycles_to_die > 0)
	{
		if (vm->flag & FLAG_DUMP && vm->dump <= cur_cycle)
		{
			print_all(vm);
			free_exit(vm, "DUMP !!");
		}
		if (cur_cycle == next_check)
		{
			check(vm);
			if (vm->cycles_to_die >= CYCLE_DELTA)
				vm->cycles_to_die -= CYCLE_DELTA;
			else
				vm->cycles_to_die = 0;
			next_check += vm->cycles_to_die;
		}
		exe_carriages(vm);
		cur_cycle++;
	}
	fprint("Last player alive: %d\n", vm->last_alive);
	//print_all(vm);
	fprint("last cycle = %d\n", (int)cur_cycle);
	free_exit(vm, "its ok!");
	return (0);
}
