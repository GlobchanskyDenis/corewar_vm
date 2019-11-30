/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_carriage_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 13:55:50 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/30 14:46:31 by bsabre-c         ###   ########.fr       */
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
	if (!(carriage->reg = (int *)ft_memalloc(sizeof(int) * REG_NUMBER)))
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
	if (!(dst->reg = (int *)ft_memalloc(sizeof(int) * REG_NUMBER)))
		error_exit(vm, "carriage duplicate - malloc returned null");
	ft_memcpy(dst->reg, carriage->reg, sizeof(unsigned int) * REG_NUMBER);
	dst->next = vm->car;
	vm->car = dst;
	return (dst);
}

/*
**	Function reads command from byte, where is carriage situated on
**	and gets the cycles_to_exe for this command
*/

void		carriage_read_command(t_car *carriage, t_vm *vm)
{
	if (!vm || !carriage || !vm->arena)
		error_exit(vm, "carriage read command - empty ptr found");
	carriage->command = vm->arena[carriage->position % MEM_SIZE];
	if (carriage->command >= COMMAND_AMOUNT)
	{
		carriage->command = 0;
		fprint("something wrong with command\n");
	}
	carriage->cycles_to_exe = get_execution_length(carriage->command);
}

/*
**	Carriage makes step to end of command in arena. If new cell is not
**	a command or an empty cell, it goes forward while new command or an
**	empty cell will not found
*/

void		carriage_make_step(t_car *carriage, t_vm *vm)
{
	if (!vm || !carriage || !vm->arena)
		error_exit(vm, "carriage make step - empty ptr found");
	carriage->position = (carriage->position + carriage->step) % MEM_SIZE;
	while (vm->arena[carriage->position] > COMMAND_AMOUNT)
		carriage->position = (carriage->position + 1) % MEM_SIZE;
	carriage->step = 0;
}
