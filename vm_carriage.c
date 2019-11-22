/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_carriage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 13:55:50 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/17 14:15:34 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_car		*add_new_carriage_in_stack(t_vm *vm)
{
	t_car		*carriage;

	if (!vm)
		error_exit(vm, "add new carriage in stack - empty ptr found");
	if (!(carriage = (t_car *)ft_memalloc(sizeof(t_car))))
		error_exit(vm, "add new carriage in stack - malloc returned null");
	if (!(carriage->reg = (unsigned int *)ft_memalloc(sizeof(unsigned int) * \
			REG_NUMBER)))
		error_exit(vm, "add new carriage in stack - malloc returned null");
	carriage->next = vm->car;
	vm->car = carriage;
	return (carriage);
}

t_car		*carriage_duplicate(t_car *carriage, t_vm *vm)
{
	t_car		*dst;

	if (!vm || !carriage)
		error_exit(vm, "carriage duplicate - empty ptr found");
	if (!(dst = (t_car *)ft_memalloc(sizeof(t_car))))
		error_exit(vm, "carriage duplicate - malloc returned null");
	ft_memcpy(dst, carriage, sizeof(t_car));
	if (!(carriage->reg = (unsigned int *)ft_memalloc(sizeof(unsigned int) * \
			REG_NUMBER)))
		error_exit(vm, "carriage duplicate - malloc returned null");
	ft_memcpy(dst->reg, carriage->reg, sizeof(unsigned int) * REG_NUMBER);
	dst->next = vm->car;
	vm->car = dst;
	return (dst);
}

/*
**	if (carriage->command >= COMMAND_AMOUNT)
**		free_exit(vm, "Warning: unknown command detected!");
*/

void		carriage_read_command(t_car *carriage, t_vm *vm)
{
	t_command	command;

	if (!vm || !carriage || !vm->arena || !vm->command_tab)
		error_exit(vm, "carriage read command - empty ptr found");
	carriage->command = vm->arena[carriage->position % MEM_SIZE];
	command = vm->command_tab[(short)carriage->command];
	carriage->cycles_to_exe = command.cycles_to_exe;
	if (command.carry)
		carriage->carry = command.carry;
	carriage->step = command.step;
}

/*
**	Carriage makes step to end of command in arena. If new cell is not
**	a command or an empty cell, it goes forward while new command or an
**	empty cell will not found
*/

void		carriage_make_step(t_car *carriage, t_vm *vm)
{
	if (!vm || !carriage || !vm->arena)
		error_exit(vm, "carriage jump - empty ptr found");
	carriage->position = (carriage->position + carriage->step) % MEM_SIZE;
	while (vm->arena[carriage->position] > COMMAND_AMOUNT)
		carriage->position = (carriage->position + 1) % MEM_SIZE;
}

void		delete_shown_carriage(t_car *carriage, t_vm *vm)
{
	t_car		*tmp;
	t_car		*prev;

	if (!vm || !carriage)
		error_exit(vm, "delete shown carriage - empty ptr found");
	tmp = vm->car;
	prev = NULL;
	while (tmp && tmp != carriage)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		error_exit(vm, "delete shown carriage - can't find carriage");
	if (prev)
	{
		prev->next = tmp->next;
		free(tmp);
	}
	else
	{
		vm->car = vm->car->next;
		free(tmp);
	}
}