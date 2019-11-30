/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_war.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:13:25 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/30 17:48:17 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	dump(t_vm *vm)
{
	print_all(vm);
	free_exit(vm, "DUMP !!");
}

static void	exe_carriages(t_vm *vm)
{
	t_car *carriage;

	//fprint("exe cariages\n");
	carriage = vm->car;
	while (carriage)
	{
		carriage->cycles_to_exe--;
		if (carriage->cycles_to_exe < 1)
		{
			vm->operation[carriage->command](carriage, vm);
			carriage_make_step(carriage, vm);
			carriage_read_command(carriage, vm);
		}
		carriage = carriage->next;
	}
}

static t_corewar	initialize_variables(t_vm *vm)
{
	t_corewar	cw;

	if (!vm)
		error_exit(vm, "initialize variables - empty ptr found");
	ft_bzero(&cw, sizeof(t_corewar));
	cw.cycles_to_die = CYCLE_TO_DIE;
	cw.next_check = CYCLE_TO_DIE;
	cw.last_alive = vm->max_pl;
	return (cw);
}

/*
**	vm->cw = &cw; <= this is need to all operations (ld, sti...) can have access
**	to all variables
*/

void		corewar(t_vm *vm)
{
	t_corewar	cw;

	if (!vm)
		error_exit(vm, "corewar - empty ptr found");
	cw = initialize_variables(vm);
	vm->cw = &cw;
	print_all(vm);
	while (cw.cycles_to_die > 0 && ++cw.cycle)
	{
		if (vm->flag & FLAG_DUMP && vm->dump <= cw.cycle)
			dump(vm);
		if (cw.cycle == cw.next_check)
		{
			//check(vm);
			if (cw.cycles_to_die >= CYCLE_DELTA)
				cw.cycles_to_die -= CYCLE_DELTA;
			else
				cw.cycles_to_die = 0;
			
			cw.next_check += cw.cycles_to_die;
		}
		exe_carriages(vm);
		//fprint("cycle %d\tcycle to die %d\n", (int)cw.cycle, (int)cw.cycles_to_die);
	}
	fprint("Last player alive: %d\n", cw.last_alive);
	//print_all(vm);
	fprint("last cycle = %d\n", (int)cw.cycle);
}