/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:28:25 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/04 22:39:24 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline static short	is_invalid_parameters(unsigned char types, short reg_num, \
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

inline static void	log_st(size_t carriage_id, short reg_num, short arg2)
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
	fprint("%d | st r%d %d\n", carriage_id, reg_num, arg2);
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
	unsigned char	types;
	short			reg_num;
	short			arg2;

	types = vm->arena[(carriage->position + 1) % MEM_SIZE];
	carriage->step = 2 + get_arg_size(types >> 6, 3) + \
			get_arg_size((types >> 4) & 3, 3);
	reg_num = vm->arena[(carriage->position + 2) % MEM_SIZE];
	arg2 = get_bytes(vm->arena, (carriage->position + 3) % MEM_SIZE, \
			get_arg_size((types >> 4) & 3, 3), vm);
	if (is_invalid_parameters(types, reg_num, arg2))
		return ;
	log_st(carriage->id, reg_num, arg2);
	arg2 = arg2 % IDX_MOD;
	if ((types >> 4 & 3) == REG_CODE && (arg2 > REG_NUMBER || arg2 < 1))
		return ;
	if ((types >> 4 & 3) == IND_CODE)
	{
		set_bytes(&carriage->reg[reg_num - 1], vm->arena, \
			calc_ind_address(carriage->position, arg2, vm), 4);
		set_owner(carriage->owner_id, vm->arena_owner, \
			calc_ind_address(carriage->position, arg2, vm), 4);
	}
	else
		carriage->reg[arg2 - 1] = carriage->reg[reg_num - 1];
}
