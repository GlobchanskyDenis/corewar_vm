/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:51:44 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/03 16:57:39 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline static short	is_invalid_parameters(unsigned char types, int reg1, \
		int reg2, int reg3)
{
	if ((REG_CODE << 6) | (REG_CODE << 4) | (REG_CODE << 2) != types)
		return (1);
	if (reg1 > REG_NUMBER || reg1 < 1 || reg2 > REG_NUMBER || reg2 < 1 || \
			reg3 > REG_NUMBER || reg3 < 1)
		return (1);
	return (0);
}

inline static void	log_sub(short carriage_id, int reg1, int reg2, int reg3)
{
	if (!(g_flags & FLAG_LOG))
		return ;
	fprint("P ");
	if (carriage_id < 1000)
		ft_putchar(' ');
	if (carriage_id < 100)
		ft_putchar(' ');
	if (carriage_id < 10)
		ft_putchar(' ');
	fprint("%d | sub r%d r%d r%d\n", carriage_id, reg1, reg2, reg3);
}

/*
**	OPERATION	SUB (subtraction)
**	OPCODE		ARGUMENT_1		ARGUMENT_2		ARGUMENT_3
**	5			T_REG			T_REG			T_REG
**
**	Записывает в регистр заданный аргументом 3 разницу значений регистров
**	полученных из аргументов 1 и 2. Меняет carry.
*/

void				operation_sub(t_car *carriage, t_vm *vm)
{
	int		types;
	int		reg1;
	int		reg2;
	int		reg3;

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
	log_sub(carriage->id, reg1, reg2, reg3);
}
