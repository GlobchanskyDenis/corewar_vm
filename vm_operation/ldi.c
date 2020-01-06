/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:09:45 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/05 21:16:00 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline static short	is_invalid_parameters(short types, int arg1, \
		int arg2, int reg_num)
{
	if (reg_num > REG_NUMBER || reg_num < 1)
		return (1);
	if ((types >> 2 & 3) != REG_CODE || \
			(types >> 4 & 3) == 0 || (types >> 4 & 3) == IND_CODE || \
			types >> 6 == 0)
		return (1);
	if ((types >> 6) == REG_CODE && (arg1 > REG_NUMBER || arg1 < 1))
		return (1);
	if ((types >> 4 & 3) == REG_CODE && (arg2 > REG_NUMBER || arg2 < 1))
		return (1);
	return (0);
}

inline static void	log_ldi(t_car *carriage, t_arg val, short log_flag)
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
	fprint("%d | ldi %d %d r%d\n", carriage->id, val.arg1, val.arg2, \
			val.reg_nbr);
	fprint("       | -> load from %d + %d = %d (with pc and mod %d)\n", \
			val.arg1, val.arg2, val.arg1 + val.arg2, carriage->position + \
			(val.arg1 + val.arg2) % IDX_MOD);
}

/*
**	OPERATION	LDI (load index)
**	OPCODE		ARGUMENT_1			ARGUMENT_2		ARGUMENT_3
**	10 (0x0A)	T_REG/T_DIR/T_IND	T_REG/T_DIR		T_REG
**
**	Загружает значение в регистр из аргумента 3. Значением являются 4 байта
**	считанные по адресу суммы значений аргументов 1 и 2.
*/

void				operation_ldi(t_car *carriage, t_vm *vm)
{
	short	types;
	int		ind;
	t_arg	val;

	types = (short)vm->arena[(carriage->position + 1) % MEM_SIZE];
	carriage->step = 2 + get_arg_size(types >> 6, 10) + \
			get_arg_size(types >> 4 & 3, 10) + get_arg_size(types >> 2 & 3, 10);
	val.reg_nbr = vm->arena[(carriage->position + 2 + \
			get_arg_size(types >> 6, 10) + get_arg_size(types >> 4 & 3, 10)) \
			% MEM_SIZE];
	val.arg1 = get_bytes(vm->arena, (carriage->position + 2) % MEM_SIZE, \
			get_arg_size(types >> 6, 10), vm);
	val.arg2 = get_bytes(vm->arena, (carriage->position + 2 + \
		get_arg_size(types >> 6, 10)) % MEM_SIZE, \
		get_arg_size(types >> 4 & 3, 10), vm);
	if (is_invalid_parameters(types, val.arg1, val.arg2, val.reg_nbr))
		return ;
	val.arg1 = get_argument(val.arg1, types >> 6, carriage, vm);
	val.arg2 = get_argument(val.arg2, types >> 4 & 3, carriage, vm);
	ind = val.arg1 + val.arg2;
	carriage->reg[val.reg_nbr - 1] = get_bytes(vm->arena, \
				calc_ind_address(carriage->position, ind, vm), 4, vm);
	log_ldi(carriage, val, vm->flag & FLAG_LOG);
}
