/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:28:25 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/05 20:41:30 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline static short	is_invalid_parameters(short types, short reg_num, \
		short arg2)
{
	if (reg_num > REG_NUMBER || reg_num < 1)
		return (1);
	if ((types >> 6 != REG_CODE) || ((types >> 4 & 3) != REG_CODE && \
			(types >> 4 & 3) != IND_CODE))
		return (1);
	if ((types >> 4 & 3) == REG_CODE && (arg2 > REG_NUMBER || arg2 < 1))
		return (1);
	return (0);
}

inline static void	log_st(size_t carriage_id, t_arg val, short log_flag)
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
	fprint("%d | st r%d %d\n", carriage_id, val.reg_nbr, val.arg2);
}

/*
**	OPERATION	ST (store)
**	OPCODE		ARGUMENT_1		ARGUMENT_2
**	3			T_REG			T_REG/T_IND
**
**	Записывает значение из регистра заданного первым аргументом по адресу
**	заданному вторым аргументом либо в регистр заданный аргументом 2.
*/

void				operation_st(t_car *carriage, t_vm *vm)
{
	short	types;
	t_arg	val;

	types = (short)vm->arena[(carriage->position + 1) % MEM_SIZE];
	carriage->step = 2 + get_arg_size(types >> 6, 3) + \
			get_arg_size((types >> 4) & 3, 3);
	val.reg_nbr = vm->arena[(carriage->position + 2) % MEM_SIZE];
	val.arg2 = get_bytes(vm->arena, (carriage->position + 3) % MEM_SIZE, \
			get_arg_size((types >> 4) & 3, 3), vm);
	if (is_invalid_parameters(types, val.reg_nbr, val.arg2))
		return ;
	log_st(carriage->id, val, vm->flag & FLAG_LOG);
	val.arg2 = val.arg2 % IDX_MOD;
	if ((types >> 4 & 3) == REG_CODE && (val.arg2 > REG_NUMBER || val.arg2 < 1))
		return ;
	if ((types >> 4 & 3) == IND_CODE)
	{
		set_bytes(&carriage->reg[val.reg_nbr - 1], vm->arena, \
			calc_ind_address(carriage->position, val.arg2, vm), 4);
		set_owner(carriage->owner_id, vm->arena_owner, \
			calc_ind_address(carriage->position, val.arg2, vm), 4);
	}
	else
		carriage->reg[val.arg2 - 1] = carriage->reg[val.reg_nbr - 1];
}
