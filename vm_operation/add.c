/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:47:08 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/27 15:48:52 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	op_add(t_car *carriage, t_vm *vm)
{
	int reg1;
	int reg2;
	int reg3;

	fprint("operation add\n");
	get_bytes(&reg1, vm->arena, (carriage->position + 2) % MEM_SIZE, REG_SIZE);
	get_bytes(&reg2, vm->arena, \
		(carriage->position + 2 + REG_SIZE) % MEM_SIZE, REG_SIZE);
	get_bytes(&reg3, vm->arena, \
		(carriage->position + 2 + 2 * REG_SIZE) % MEM_SIZE, REG_SIZE);
	carriage->step = 2 + 3 * REG_SIZE;
	carriage->reg[reg3] = carriage->reg[reg1] + carriage->reg[reg2];
	carriage->carry = 0;
	if (carriage->reg[reg3] == 0)
		carriage->carry = 1;
}
