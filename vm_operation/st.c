/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:28:25 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/24 16:59:22 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_st(t_car *carriage, t_vm *vm)
{
	int		types;
	int		arg;
	int		reg;
	int		val;

	types = get_args_types(vm->arena[carriage->position + 1]);
	get_bytes(&reg, vm->arena, (carriage->position + 2) % MEM_SIZE, REG_SIZE);
	arg = get_arg(carriage, vm, (types / 100) % 10, 4);
	if (arg == REG_CODE)
	{
		get_bytes(&val, vm->arena, \
			(carriage->position + 2 + REG_SIZE) % MEM_SIZE, REG_SIZE);
		carriage->reg[val] = carriage->reg[reg];
		carriage->step = 2 + REG_SIZE + REG_SIZE;
	}
	else if (arg == IND_CODE)
	{
		get_bytes(&val, vm->arena, \
			(carriage->position + 2 + REG_SIZE) % MEM_SIZE, IND_SIZE);
		ft_memcpy(vm->arena[(carriage->position + arg % IDX_MOD) % MEM_SIZE], \
			carriage->reg[reg], REG_SIZE);
		carriage->step = 2 + IND_SIZE + REG_SIZE;
	}
}