/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:09:45 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/24 16:57:58 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_ldi(t_car *carriage, t_vm *vm)
{
	int		arg1;
	int		arg2;
	int		reg;
	int		val;
	int		types;

	types = get_args_types(vm->arena[carriage->position + 1]);
	carriage->step = 2;
	arg1 = get_arg(carriage, vm, types / 1000, 2);
	arg2 = get_arg(carriage, vm, (types / 100) % 10, 2);
	get_bytes(&reg, vm->arena, \
		(carriage->position + carriage->step) % MEM_SIZE, REG_SIZE);
	get_bytes(&val, vm->arena, \
		(carriage->position + (arg1 + arg2) % IDX_MOD) % MEM_SIZE, 4);
	carriage->reg[reg] = val;
	carriage->step += REG_SIZE;
}