/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_getters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:12:03 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/12/22 21:49:23 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Function returns how many bytes we must read in this argument
*/

short	get_arg_size(unsigned char byte, short op_code)
{
	if (byte == REG_CODE)
		return (1);
	if (byte == DIR_CODE)
	{
		if ((op_code >= OP_LIVE && op_code <= OP_XOR) || op_code == OP_LLD || \
				op_code == OP_AFF)
			return (4);
		return (2);
	}	
	if (byte == IND_CODE)
		return (2);
	return (0);
}

/*
**	Function returns parameter for cycles_to_exe variable
*/

short	get_execution_length(unsigned char op_code)
{
	if (op_code == OP_LIVE || op_code == OP_ADD || op_code == OP_SUB || \
			op_code == OP_LLD)
		return (10);
	if (op_code == OP_LD || op_code == OP_ST)
		return (5);
	if (op_code == OP_AND || op_code == OP_OR || op_code == OP_XOR)
		return (6);
	if (op_code == OP_ZJMP)
		return (20);
	if (op_code == OP_LDI || op_code == OP_STI)
		return (25);
	if (op_code == OP_FORK)
		return (800);
	if (op_code == OP_LLDI)
		return (50);
	if (op_code == OP_LFORK)
		return (1000);
	if (op_code == OP_AFF)
		return (2);
	return (1);
}

/*
**	Function extracts argument (can be register / direct data / indirect data)
*/

int		get_argument(int value, short type, t_car *carriage, t_vm *vm)
{
	//fprint("\tget_argument value %d\n", value);
	if (!vm || !vm->arena || !carriage)
		error_exit(vm, "get argument - empty ptr found");
	if (type == REG_CODE && value >= 1 && value <= REG_NUMBER)
	{
		fprint("\tget_arg (REG case) %d\n", carriage->reg[value - 1]);
		return (carriage->reg[value - 1]);
	}
	if (type == DIR_CODE)
	{
		fprint("\tget_arg (DIR case) %d\n", value);
		return (value);
	}
	if (type == IND_CODE)
	{
		fprint("\tget_arg (IND case) get bytes returns %d\n", get_bytes(vm->arena, calc_ind_address(carriage->position, value, vm), 4, vm));
		return (get_bytes(vm->arena, calc_ind_address(carriage->position, value, vm), 4, vm));
	}
	return (0);
}


int		calc_ind_address(short position, int ind, t_vm *vm)
{
	int		dst;

	if (!vm || !vm->arena)
		error_exit(vm, "get indirect address - empty ptr found");
	fprint("\tget_ind_address\tposition %d ind %d\t", position, ind);
	ind = ind % IDX_MOD;
	dst = (position + ind) % MEM_SIZE;
	if (dst < 0)
		dst = dst + MEM_SIZE;
	fprint("new_addr %d\n", dst);
	return (dst);
}