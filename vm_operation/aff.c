/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:06:09 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/05 19:10:59 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
**	OPERATION	AFF (aff)
**	OPCODE		ARGUMENT_1
**	16 (0x10)	T_REG
**
**	Эта операция выводит на экран значение из регистра как ASCII символ.
*/

void	operation_aff(t_car *carriage, t_vm *vm)
{
	short	types;
	short	reg_nbr;
	char	symbol;

	types = (short)vm->arena[(carriage->position + 1) % MEM_SIZE];
	carriage->step = 2 + get_arg_size(types >> 6, 16);
	if (types >> 6 != REG_CODE)
		return ;
	reg_nbr = (short)vm->arena[(carriage->position + 2) % MEM_SIZE];
	if (reg_nbr < 1 || reg_nbr > REG_NUMBER)
		return ;
	symbol = (char)carriage->reg[reg_nbr - 1];
	if (vm->flag & FLAG_AFF)
		fprint("Aff: %c\n", symbol);
}
