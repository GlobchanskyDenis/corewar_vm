/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:33:08 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/03 16:57:34 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline static short	is_invalid_parameters(unsigned char types, int arg2, \
		int arg3, short reg_num)
{
	if (reg_num > REG_NUMBER || reg_num < 1)
		return (1);
	if ((types >> 6 != REG_CODE) || ((types >> 4 & 3) == 0) || \
			((types >> 2 & 3) != REG_CODE && (types >> 2 & 3) != DIR_CODE))
		return (1);
	if ((types >> 4 & 3) == REG_CODE && (arg2 > REG_NUMBER || arg2 < 1))
		return (1);
	if ((types >> 2 & 3) == REG_CODE && (arg3 > REG_NUMBER || arg3 < 1))
		return (1);
	return (0);
}

inline static void	log_sti(t_car *carriage, short reg_num, int arg2, int arg3)
{
	if (!(g_flags & FLAG_LOG))
		return ;
	fprint("P ");
	if (carriage->id < 1000)
		ft_putchar(' ');
	if (carriage->id < 100)
		ft_putchar(' ');
	if (carriage->id < 10)
		ft_putchar(' ');
	fprint("%d | sti r%d %d %d\n", carriage->id, reg_num, arg2, arg3);
	fprint("       | -> store to %d + %d = %d (with pc and mod %d)\n", \
			arg2, arg3, arg2 + arg3, \
			carriage->position + ((arg2 + arg3) % IDX_MOD));
}

/*
**	OPERATION	STI (store index)
**	OPCODE		ARGUMENT_1		ARGUMENT_2			ARGUMENT_3
**	11 (0x0B)	T_REG			T_REG/T_DIR/T_IND	T_REG/T_DIR
**
**	Эта операция записывает значение регистра, переданного в качестве первого
**	параметра, по адресу — текущая позиция +
**	(<ЗНАЧЕНИЕ_ВТОРОГО_АРГУМЕНТА> + <ЗНАЧЕНИЕ_ТРЕТЕГО_АРГУМЕНТА>) % IDX_MOD
*/

void				operation_sti(t_car *carriage, t_vm *vm)
{
	unsigned char	types;
	short			reg_num;
	int				arg2;
	int				arg3;
	int				address;

	types = vm->arena[(carriage->position + 1) % MEM_SIZE];
	carriage->step = 2 + get_arg_size(types >> 6, 11) + get_arg_size((types \
			>> 4) & 3, 11) + get_arg_size((types >> 2) & 3, 11);
	reg_num = vm->arena[(carriage->position + 2) % MEM_SIZE];
	arg2 = get_bytes(vm->arena, (carriage->position + 3) % MEM_SIZE, \
			get_arg_size((types >> 4) & 3, 11), vm);
	arg3 = get_bytes(vm->arena, (carriage->position + 3 + \
			get_arg_size((types >> 4) & 3, 11)) % MEM_SIZE, \
			get_arg_size((types >> 2) & 3, 11), vm);
	if (is_invalid_parameters(types, arg2, arg3, reg_num))
		return ;
	address = calc_ind_address(carriage->position, \
			get_argument(arg2, (types >> 4) & 3, carriage, vm) + \
			get_argument(arg3, (types >> 2) & 3, carriage, vm), vm);
	set_bytes(&carriage->reg[reg_num - 1], vm->arena, address, 4);
	set_owner(carriage->owner_id, vm->arena_owner, address, 4);
	log_sti(carriage, reg_num, \
			get_argument(arg2, (types >> 4) & 3, carriage, vm), \
			get_argument(arg3, (types >> 2) & 3, carriage, vm));
}
