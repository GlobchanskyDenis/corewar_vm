/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_getters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:12:03 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/28 17:51:14 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	input parameter byte - consists information about variables, that current
**	operation uses. Every 2 bits in this byte tells about 1 argument.
**	senior bits responsible for first argument. So we put this byte and
**	number of argument that we needed. Function returns only bits that matches
**	this argument.
*/

short	get_info(unsigned char byte, short arg_nbr)
{
	short	dst;

	if (byte == 0 || arg_nbr < 1 || arg_nbr > 4)
		return (0);
	dst = (short)byte;
	if (arg_nbr == 1)
		return (dst >> 6);
	if (arg_nbr == 2)
		return ((dst >> 4) & 3);
	if (arg_nbr == 3)
		return ((dst >> 2) & 3);
	return (dst & 3);
}

/*
**	Function returns how many bytes we must read in this argument
*/

short	get_arg_size(unsigned char byte, short operation_nbr)
{
	if (byte == REG_CODE)
		return (1);
	if (byte == DIR_CODE)
	{
		if ((operation_nbr >= OP_LIVE && operation_nbr <= OP_XOR) || \
				operation_nbr == OP_LLD || operation_nbr == OP_AFF)
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

short	get_execution_length(unsigned char command)
{
	if (command == OP_LIVE || command == OP_ADD || command == OP_SUB || \
			command == OP_LLD)
		return (10);
	if (command == OP_LD || command == OP_ST)
		return (5);
	if (command == OP_AND || command == OP_OR || command == OP_XOR)
		return (6);
	if (command == OP_ZJMP)
		return (20);
	if (command == OP_LDI || command == OP_STI)
		return (25);
	if (command == OP_FORK)
		return (800);
	if (command == OP_LLDI)
		return (50);
	if (command == OP_LFORK)
		return (1000);
	if (command == OP_AFF)
		return (2);
	return (1);
}

/*
**	function returns selected bytes from the arena in unsigned int variable
*/

unsigned int	get_bytes(unsigned char *arena, short start, short len, \
		t_vm *vm)
{
	short			i;
	short			position;
	unsigned int	dst;

	if (!arena || !vm || len < 1 || len > 4)
		error_exit(vm, "get bytes - empty ptr found");
	dst = 0;
	i = -1;
	while (++i < len)
	{
		if (i + start < MEM_SIZE)
			position = i + start;
		else
			position = i + start - MEM_SIZE;
		dst = dst << 8;
		dst += (unsigned int)arena[position];
	}
	return (dst);
}
