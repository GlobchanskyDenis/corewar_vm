/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:47:08 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/05 19:01:25 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline static short	is_invalid_parameters(short types, int reg1, int reg2, \
		int reg3)
{
	if (types >> 6 != REG_CODE || (types >> 4 & 3) != REG_CODE || \
			(types >> 2 & 3) != REG_CODE)
		return (1);
	if (reg1 > REG_NUMBER || reg1 < 1 || reg2 > REG_NUMBER || reg2 < 1 || \
			reg3 > REG_NUMBER || reg3 < 1)
		return (1);
	return (0);
}

inline static void	log_add(size_t carriage_id, t_arg val, short log_flag)
{
	if (!log_flag)
		return ;
	fprint("P ");
	if (carriage_id < 1000)
		ft_putchar(' ');
	if (carriage_id < 100)
		ft_putchar(' ');
	if (carriage_id < 10)
		ft_putchar(' ');
	fprint("%d | add r%d r%d r%d\n", carriage_id, val.arg1, val.arg2, val.arg3);
}

/*
**	OPERATION	ADD (addition)
**	OPCODE		ARGUMENT_1		ARGUMENT_2		ARGUMENT_3
**	4			T_REG			T_REG			T_REG
**
**	Записывает в регистр заданный аргументом 3 сумму значений регистров
**	полученных из аргументов 1 и 2. Меняет carry.
*/

void				operation_add(t_car *carriage, t_vm *vm)
{
	short	types;
	t_arg	val;

	types = (short)vm->arena[(carriage->position + 1) % MEM_SIZE];
	carriage->step = 2 + get_arg_size(types >> 6, 4) + \
			get_arg_size(types >> 4 & 3, 4) + \
			get_arg_size(types >> 2 & 3, 4);
	val.arg1 = (int)vm->arena[(carriage->position + 2) % MEM_SIZE];
	val.arg2 = (int)vm->arena[(carriage->position + 3) % MEM_SIZE];
	val.arg3 = (int)vm->arena[(carriage->position + 4) % MEM_SIZE];
	if (is_invalid_parameters(types, val.arg1, val.arg2, val.arg3))
		return ;
	carriage->reg[val.arg3 - 1] = carriage->reg[val.arg1 - 1] + \
			carriage->reg[val.arg2 - 1];
	carriage->carry = (carriage->reg[val.arg3 - 1]) ? 0 : 1;
	log_add(carriage->id, val, vm->flag & FLAG_LOG);
}
