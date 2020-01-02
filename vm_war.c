/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_war.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:13:25 by bsabre-c          #+#    #+#             */
/*   Updated: 2020/01/02 13:25:22 by bsabre-c         ###   ########.fr       */
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
			vm->operation[carriage->command](carriage, vm);
		carriage = carriage->next;
	}
	carriage = vm->car;
	while (carriage)
	{
		if (carriage->cycles_to_exe < 1)
		{
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
	cw.cycle = 0;
	cw.cycles_to_die = CYCLE_TO_DIE;
	cw.next_check = CYCLE_TO_DIE;
	cw.last_alive = vm->max_pl;
	return (cw);
}

void		introduce(short max_pl, t_vm *vm)
{
	short	nbr;
	t_pl	player;

	nbr = 0;
	ft_putstr("Introducing contestants...\n");

	while(nbr < max_pl)
	{
		player = vm->player[nbr];
		fprint("* Player %d, weighing %d bytes, ", nbr + 1, player.codesize);
		fprint("\"%s\" (\"%s\") !\n", player.name, player.comment);
		nbr++;
	}
}

void		winner_is(t_corewar cw, t_vm *vm)
{
	fprint("Contestant %d, \"%s\", has won !\n", cw.last_alive, vm->player[cw.last_alive - 1].name);
	fprint("cycle %d\n", (int)cw.cycle);
}

void		corewar(t_vm *vm)
{
	t_corewar	cw;

	if (!vm)
		error_exit(vm, "corewar - empty ptr found");
	cw = initialize_variables(vm);
	vm->cw = &cw;

	// introduction of contestants
	introduce(vm->max_pl, vm);

	while (cw.cycles_to_die > 0)
	{
		if (vm->flag & FLAG_DUMP && vm->dump <= cw.cycle)
			dump(vm);
		if (cw.cycle == cw.next_check)
		{
			check(vm);
			cw.next_check += cw.cycles_to_die;
		}
		++cw.cycle;
		if (DEBUG_LOG)
			fprint("It is now cycle %d\n", (int)cw.cycle);
		exe_carriages(vm);
	}
	winner_is(cw, vm);
}