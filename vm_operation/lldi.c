/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:39:05 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/27 15:50:36 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	op_lldi(t_car *carriage, t_vm *vm)
{
	int		arg1;
	int		arg2;
	int		reg;
	int		val;
	int		types;

	if (!vm)
		error_exit(vm, "operation lldi - empty ptr found");
	fprint("operation lldi\n");
	types = get_args_types(&vm->arena[carriage->position + 1]);
	carriage->step = 2;
	arg1 = get_arg(carriage, vm, types / 1000, 2);
	arg2 = get_arg(carriage, vm, (types / 100) % 10, 2);
	get_bytes(&reg, vm->arena, \
		(carriage->position + carriage->step) % MEM_SIZE, REG_SIZE);
	get_bytes(&val, vm->arena, \
		(carriage->position + (arg1 + arg2)) % MEM_SIZE, 4);
	carriage->reg[reg] = val;
	carriage->carry = 0;
	if (val == 0)
		carriage->carry = 1;
	carriage->step += REG_SIZE;
}
