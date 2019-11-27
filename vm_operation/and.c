/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:52:31 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/27 15:49:15 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	op_and(t_car *carriage, t_vm *vm)
{
	int types;
	int arg1;
	int arg2;
	int reg;

	fprint("operation and\n");
	types = get_args_types(&vm->arena[carriage->position + 1]);
	carriage->step = 2;
	arg1 = get_arg(carriage, vm, types / 1000, 4);
	arg2 = get_arg(carriage, vm, (types / 100) % 10, 4);
	get_bytes(&reg, vm->arena, \
		(carriage->position + carriage->step) % MEM_SIZE, REG_SIZE);
	carriage->reg[reg] = arg1 & arg2;
	carriage->carry = 0;
	if (carriage->reg[reg] == 0)
		carriage->carry = 1;
}
