/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_carriage_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 13:55:50 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/05 12:36:23 by bsabre-c         ###   ########.fr       */
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
	carriage->id = vm->max_car_id + 1;
	vm->max_car_id = carriage->id;
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
	ft_memcpy(dst->reg, carriage->reg, sizeof(int) * REG_NUMBER);
	dst->id = vm->max_car_id + 1;
	vm->max_car_id = dst->id;
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
	if (carriage->command >= COMMAND_AMOUNT || carriage->command < 0)
		carriage->command = 0;
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
	carriage->position = carriage->position + carriage->step;
	while (carriage->position < 0)
		carriage->position += MEM_SIZE;
	carriage->position = carriage->position % MEM_SIZE;
	carriage->step = 0;
	carriage->command = -1;
}
