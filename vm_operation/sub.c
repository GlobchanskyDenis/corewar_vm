/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:51:44 by jmaynard          #+#    #+#             */
/*   Updated: 2019/12/22 20:01:57 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static short	is_invalid_parameters(unsigned char types, int reg1, int reg2, \
		int reg3)
{	
	if ((REG_CODE << 6) & (REG_CODE << 4) & (REG_CODE << 2) != types)
	{
		fprint("wrong argument type, skip the command\n");
		fprint("types = %d\tshould be %d\n", types, \
				(REG_CODE << 6) & (REG_CODE << 4) & (REG_CODE << 2));
		return (1);
	}
	if (reg1 > REG_NUMBER || reg1 < 1 || reg2 > REG_NUMBER || reg2 < 1 || \
			reg3 > REG_NUMBER || reg3 < 1)
	{
		fprint("wrong reg number, skip the command\n");
		fprint("reg1 %d\treg2 %d\treg3 %d\n", reg1, reg2, reg3);
		return (1);
	}
	return (0);
}

void	operation_sub(t_car *carriage, t_vm *vm)
{
	int		types;
	int		reg1;
	int		reg2;
	int		reg3;

	if (!vm || !carriage)
		error_exit(vm, "operation sub - empty ptr found");
	fprint("operation sub\tcycle %d\tposition %d\n", (int)vm->cw->cycle, (int)carriage->position);
	types = vm->arena[(carriage->position + 1) % MEM_SIZE];
	
	carriage->step = 2 + get_arg_size(types >> 6, 5) + \
			get_arg_size(types >> 4 & 3, 5) + \
			get_arg_size(types >> 2 & 3, 5);

	reg1 = (int)vm->arena[(carriage->position + 2) % MEM_SIZE];
	reg2 = (int)vm->arena[(carriage->position + 3) % MEM_SIZE];
	reg3 = (int)vm->arena[(carriage->position + 4) % MEM_SIZE];
	
	if (is_invalid_parameters(types, reg1, reg2, reg3))
		return ;
	
	carriage->reg[reg3 - 1] = carriage->reg[reg1 - 1] - \
			carriage->reg[reg2 - 1];
	
	carriage->carry = (carriage->reg[reg3 - 1]) ? 0 : 1;
}
