/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:09:45 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/23 20:36:12 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_arg(t_car *carriage, t_vm *vm, short type)
{
	int		arg;
	int		res;

	if (type == REG_CODE)
	{
		get_bytes(&arg, vm->arena, carriage->position, REG_SIZE);
		carriage->position += REG_SIZE;
	}
	else if (type == DIR_CODE)
	{
		get_bytes(&arg, vm->arena, carriage->position, DIR_SIZE);
		carriage->position += DIR_SIZE;
	}
	else if (type == IND_CODE)
	{
		get_bytes(&res, vm->arena, carriage->position, IND_SIZE);
		get_bytes(&arg, vm->arena, (carriage->position - 2 + res % IDX_MOD) % MEM_SIZE, 4);
		carriage->position += IND_SIZE;
	}
	return (arg);
}

void	op_ldi(t_car *carriage, t_vm *vm)
{
	int		arg1;
	int		arg2;
	int		reg;
	int		val;
	short	type1;
	short	type2;

	//get types
	carriage->position += 2;
	arg1 = get_arg1(carriage, vm, type1);
	get_bytes(&reg, vm->arena, carriage->position % MEM_SIZE, REG_SIZE);
	get_bytes(&val, vm->arena, ((arg1 + arg2) % IDX_MOD) % MEM_SIZE, 4);
	carriage->reg[reg] = val;
	carriage->step = REG_SIZE;
}