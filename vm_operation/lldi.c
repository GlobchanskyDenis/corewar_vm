/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:39:05 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/03 16:57:16 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline static short	is_invalid_parameters(unsigned char types, int arg1, \
		int arg2, int reg_num)
{
	if (reg_num > REG_NUMBER || reg_num < 1)
		return (1);
	if ((types & 3) != 0 || (types >> 2 & 3) != REG_CODE || \
			(types >> 4 & 3) == 0 || (types >> 4 & 3) == IND_CODE || \
			types >> 6 == 0)
		return (1);
	if ((types >> 6) == REG_CODE && (arg1 > REG_NUMBER || arg1 < 1))
		return (1);
	if ((types >> 4 & 3) == REG_CODE && (arg2 > REG_NUMBER || arg2 < 1))
		return (1);
	return (0);
}

inline static void	log_lldi(t_car *carriage, int arg1, int arg2, short reg_num)
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
	fprint("%d | lldi %d %d r%d\n", carriage->id, arg1, arg2, reg_num);
	fprint("       | -> load from %d + %d = %d (with pc %d)\n", arg1, arg2, \
			arg1 + arg2, carriage->position + (arg1 + arg2));
}

/*
**	OPERATION	LLDI (long load index)
**	OPCODE		ARGUMENT_1			ARGUMENT_2		ARGUMENT_3
**	14 (0x0E)	T_REG/T_DIR/T_IND	T_REG/T_DIR		T_REG
**
**	Загружает значение в регистр из аргумента 3. Значением являются 4 байта
**	считанные по адресу суммы значений аргументов 1 и 2. Без ограничения
**	по IDX_MOD.
*/

void				operation_lldi(t_car *carriage, t_vm *vm)
{
	unsigned char	types;
	short			reg_num;
	int				arg1;
	int				arg2;
	int				ind;

	types = vm->arena[(carriage->position + 1) % MEM_SIZE];
	carriage->step = 2 + get_arg_size(types >> 6, 10) + \
			get_arg_size(types >> 4 & 3, 10) + get_arg_size(types >> 2 & 3, 10);
	reg_num = vm->arena[(carriage->position + 2 + get_arg_size(types >> 6, 10) \
			+ get_arg_size(types >> 4 & 3, 10)) % MEM_SIZE];
	arg1 = get_bytes(vm->arena, (carriage->position + 2) % MEM_SIZE, \
			get_arg_size(types >> 6, 10), vm);
	arg2 = get_bytes(vm->arena, (carriage->position + 2 + \
		get_arg_size(types >> 6, 10)) % MEM_SIZE, \
		get_arg_size(types >> 4 & 3, 10), vm);
	if (is_invalid_parameters(types, arg1, arg2, reg_num))
		return ;
	ind = get_argument(arg1, types >> 6, carriage, vm) + \
			get_argument(arg2, types >> 4 & 3, carriage, vm);
	carriage->reg[reg_num - 1] = get_bytes(vm->arena, \
				calc_long_ind_address(carriage->position, ind, vm), 4, vm);
	carriage->carry = (carriage->reg[reg_num - 1]) ? 0 : 1;
	log_lldi(carriage, arg1, arg2, reg_num);
}
