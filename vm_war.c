/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_war.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:13:25 by bsabre-c          #+#    #+#             */
/*   Updated: 2020/01/05 16:02:35 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			exe_carriages(t_vm *vm)
{
	t_car *carriage;

	carriage = vm->car;
	while (carriage)
	{
		carriage->cycles_to_exe--;
		if (carriage->command == -1)
		{
			carriage_read_command(carriage, vm);
			carriage->cycles_to_exe--;
		}
		if (carriage->cycles_to_exe < 1)
		{
			vm->operation[carriage->command](carriage, vm);
			carriage_make_step(carriage, vm);
		}
		carriage = carriage->next;
	}
}

static t_corewar	initialize_variables(t_vm *vm)
{
	t_corewar	cw;

	ft_bzero(&cw, sizeof(t_corewar));
	cw.cycle = 0;
	cw.cycles_to_die = CYCLE_TO_DIE;
	cw.next_check = CYCLE_TO_DIE;
	cw.last_alive = vm->max_pl;
	return (cw);
}

static void			cycles_to_die_check(t_vm *vm)
{
	t_car *tmp;
	t_car *carriage;

	carriage = vm->car;
	vm->checks++;
	while (carriage)
	{
		tmp = carriage->next;
		if (carriage->last_live_cycle + vm->cw->cycles_to_die <= vm->cw->cycle)
			find_n_del_carriage(carriage, vm);
		carriage = tmp;
	}
	if (vm->cw->lives_for_cycle >= NBR_LIVE || vm->checks >= MAX_CHECKS)
	{
		vm->cw->cycles_to_die -= CYCLE_DELTA;
		vm->checks = 0;
		if ((g_flags & FLAG_LOG))
			fprint("Cycle to die is now %d\n", vm->cw->cycles_to_die);
	}
	vm->cw->lives_for_cycle = 0;
	vm->cw->next_check += vm->cw->cycles_to_die;
}

void				corewar(t_vm *vm)
{
	t_corewar	cw;

	cw = initialize_variables(vm);
	vm->cw = &cw;
	while (vm->car)
	{
		if (vm->flag & FLAG_DUMP && vm->dump <= cw.cycle)
			dump(vm);
		cw.cycle++;
		if (vm->flag & FLAG_LOG)
			fprint("It is now cycle %d\n", (int)cw.cycle);
		exe_carriages(vm);
		if (cw.cycle == cw.next_check || cw.cycles_to_die <= 0)
			cycles_to_die_check(vm);
	}
	fprint("Contestant %d, \"%s\", has won !\n", cw.last_alive, \
			vm->player[cw.last_alive - 1].name);
}
