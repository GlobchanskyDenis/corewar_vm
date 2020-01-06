/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:33:08 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/05 21:08:39 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline static short	is_invalid_parameters(short types, int arg2, int arg3, \
		short reg_num)
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

inline static void	log_sti(t_car *carriage, t_arg val, short log_flag)
{
	if (!log_flag)
		return ;
	fprint("P ");
	if (carriage->id < 1000)
		ft_putchar(' ');
	if (carriage->id < 100)
		ft_putchar(' ');
	if (carriage->id < 10)
		ft_putchar(' ');
	fprint("%d | sti r%d %d %d\n", carriage->id, val.reg_nbr, val.arg2, \
			val.arg3);
	fprint("       | -> store to %d + %d = %d (with pc and mod %d)\n", \
			val.arg2, val.arg3, val.arg2 + val.arg3, \
			carriage->position + ((val.arg2 + val.arg3) % IDX_MOD));
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
	short	types;
	int		address;
	t_arg	val;

	types = (short)vm->arena[(carriage->position + 1) % MEM_SIZE];
	carriage->step = 2 + get_arg_size(types >> 6, 11) + get_arg_size((types \
			>> 4) & 3, 11) + get_arg_size((types >> 2) & 3, 11);
	val.reg_nbr = vm->arena[(carriage->position + 2) % MEM_SIZE];
	val.arg2 = get_bytes(vm->arena, (carriage->position + 3) % MEM_SIZE, \
			get_arg_size((types >> 4) & 3, 11), vm);
	val.arg3 = get_bytes(vm->arena, (carriage->position + 3 + \
			get_arg_size((types >> 4) & 3, 11)) % MEM_SIZE, \
			get_arg_size((types >> 2) & 3, 11), vm);
	if (is_invalid_parameters(types, val.arg2, val.arg3, val.reg_nbr))
		return ;
	val.arg2 = get_argument(val.arg2, (types >> 4) & 3, carriage, vm);
	val.arg3 = get_argument(val.arg3, (types >> 2) & 3, carriage, vm);
	address = calc_ind_address(carriage->position, val.arg2 + val.arg3, vm);
	set_bytes(&carriage->reg[val.reg_nbr - 1], vm->arena, address, 4);
	set_owner(carriage->owner_id, vm->arena_owner, address, 4);
	log_sti(carriage, val, vm->flag & FLAG_LOG);
}
