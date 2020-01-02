/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:06:09 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/01 19:58:15 by bsabre-c         ###   ########.fr       */
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
	int		reg_nbr;
	char	symbol;

	if (!carriage || !vm)
		error_exit(vm, "operation aff - empty ptr found");
	// fprint("cycle %d\tposition %d  operation aff\t", (int)carriage->position, (int)vm->cw->cycle);
	
	carriage->step = 3;
	reg_nbr = (int)vm->arena[(carriage->position + 1) % MEM_SIZE];
	if (reg_nbr < 1 || reg_nbr > REG_NUMBER)
		return ;
	symbol = (char)carriage->reg[reg_nbr - 1];
	//fprint("r%d char '%c'\n", reg_nbr - 1, symbol);
}
