/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:26:18 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/27 15:50:56 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	op_or(t_car *carriage, t_vm *vm)
{
	int types;
	int arg1;
	int arg2;
	int reg;

	fprint("operation or\n");
	types = get_args_types(&vm->arena[carriage->position + 1]);
	carriage->step = 2;
	arg1 = get_arg(carriage, vm, types / 1000, 4);
	arg2 = get_arg(carriage, vm, (types / 100) % 10, 4);
	get_bytes(&reg, vm->arena, \
		(carriage->position + carriage->step) % MEM_SIZE, REG_SIZE);
	carriage->reg[reg] = arg1 | arg2;
	carriage->carry = 0;
	if (carriage->reg[reg] == 0)
		carriage->carry = 1;
}
