/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:28:15 by jmaynard          #+#    #+#             */
/*   Updated: 2019/12/22 20:02:11 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static short	is_invalid_parameters(unsigned char types, int reg)
{	
	if ((types & 3) != 0 || (types >> 2 & 3) != REG_CODE || \
			(types >> 4 & 3) == 0 || (types >> 6) == 0)
	{
		fprint("wrong argument type, skip the command\n");
		//fprint("types = %d\tshould be %d\n", types, (REG_CODE << 6) | (REG_CODE << 4) | (REG_CODE << 2));
		return (1);
	}
	if (reg > REG_NUMBER || reg < 1)
	{
		fprint("wrong reg number, skip the command\n");
		fprint("reg1 %d\n", reg);
		return (1);
	}
	return (0);
}

void	operation_xor(t_car *carriage, t_vm *vm)
{
	int		types;
	int		arg1;
	int		arg2;
	int		reg;

	if (!vm || !carriage)
		error_exit(vm, "operation xor - empty ptr found");
	fprint("operation xor\tcycle %d\tposition %d\n", (int)vm->cw->cycle, (int)carriage->position);
	types = vm->arena[(carriage->position + 1) % MEM_SIZE];

	carriage->step = 2 + get_arg_size(types >> 6, 6) + \
			get_arg_size(types >> 4 & 3, 6) + \
			get_arg_size(types >> 2 & 3, 6);

	reg = vm->arena[(carriage->position + 2 + get_arg_size(types >> 6, 6) + \
			get_arg_size(types >> 4 & 3, 6)) % MEM_SIZE];

	if (is_invalid_parameters(types, reg))
		return ;

	arg1 = get_bytes(vm->arena, carriage->position + 2, \
			get_arg_size(types >> 6, 6), vm);
	arg2 = get_bytes(vm->arena, carriage->position + 2 + \
			get_arg_size(types >> 6, 6), get_arg_size(types >> 4 & 3, 6), vm);

	carriage->reg[reg - 1] = get_argument(arg1, types >> 6, carriage, vm) \
			^ get_argument(arg2, types >> 4 & 3, carriage, vm);

	carriage->carry = (carriage->reg[reg - 1]) ? 0 : 1;
}
