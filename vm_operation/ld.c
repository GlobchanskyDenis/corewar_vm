/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:01:24 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/23 20:07:54 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_ld(t_car *carriage, t_vm *vm)
{
	short	arg;
	int		reg;
	int		val;

	// get arg
	if (arg == DIR_CODE)
	{
		get_bytes(&val, vm->arena, (carriage->position + 2) % MEM_SIZE, DIR_SIZE);
		get_bytes(&reg, vm->arena, \
			(carriage->position + 2 + DIR_SIZE) % MEM_SIZE, REG_SIZE);
		carriage->step = 2 + DIR_SIZE + REG_SIZE;
	}
	else if (arg == IND_CODE)
	{
		get_bytes(&arg, vm->arena, (carriage->position + 2) % MEM_SIZE, IND_SIZE);
		get_bytes(&val, vm->arena, \
			(carriage->position + arg % IDX_MOD) % MEM_SIZE, REG_SIZE);
		get_bytes(&reg, vm->arena, \
			(carriage->position + 2 + IND_SIZE) % MEM_SIZE, REG_SIZE);
		carriage->step = 2 + IND_SIZE + REG_SIZE;
	}
	carriage->reg[reg] = val;
	carriage->carry = 0;
	if (reg == 0)
		carriage->carry = 1;
}