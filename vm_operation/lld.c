/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:05:37 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/05 20:21:42 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline static short	is_invalid_parameters(short types, short reg_num)
{
	if (reg_num > REG_NUMBER || reg_num < 1)
		return (1);
	if (types >> 6 == REG_CODE || types >> 6 == 0 || \
		(types >> 4 & 3) != REG_CODE)
		return (1);
	return (0);
}

inline static void	log_lld(size_t carriage_id, t_arg val, short log_flag)
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
	fprint("%d | lld %d r%d\n", carriage_id, val.arg1, val.reg_nbr);
}

/*
**	OPERATION	LLD (long load)
**	OPCODE		ARGUMENT_1		ARGUMENT_2
**	13 (0x0D)	T_DIR/T_IND		T_REG
**
**	Загружает значение из аргумента 1 в регистр из аргумента 2 без ограничения
**	по дальности IDX_MOD. Меняет carry.
*/

void				operation_lld(t_car *carriage, t_vm *vm)
{
	short	types;
	short	arg1_size;
	t_arg	val;

	types = (short)vm->arena[(carriage->position + 1) % MEM_SIZE];
	arg1_size = get_arg_size(types >> 6, 2);
	carriage->step = 2 + arg1_size + get_arg_size((types >> 4) & 3, 2);
	val.arg1 = get_bytes(vm->arena, (carriage->position + 2) % MEM_SIZE, \
			arg1_size, vm);
	val.reg_nbr = vm->arena[(carriage->position + 2 + arg1_size) % MEM_SIZE];
	if (is_invalid_parameters(types, val.reg_nbr))
		return ;
	if (types >> 6 == DIR_CODE)
	{
		carriage->reg[val.reg_nbr - 1] = val.arg1;
		carriage->carry = (carriage->reg[val.reg_nbr - 1]) ? 0 : 1;
	}
	else if (types >> 6 == IND_CODE)
		carriage->reg[val.reg_nbr - 1] = get_bytes(vm->arena, \
				calc_long_ind_address(carriage->position, val.arg1, vm), 4, vm);
	log_lld(carriage->id, val, vm->flag & FLAG_LOG);
}
