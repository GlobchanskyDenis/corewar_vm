/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:01:24 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/05 15:54:43 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline static short	is_invalid_parameters(unsigned char types, short reg_num)
{
	if (reg_num > REG_NUMBER || reg_num < 1)
		return (1);
	if ((types >> 6 != DIR_CODE && types >> 6 != IND_CODE) || \
			(types >> 4 & 3) != REG_CODE)
		return (1);
	return (0);
}

inline static void	log_ld(size_t carriage_id, int arg1, short reg_num)
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
	fprint("%d | ld %d r%d\n", carriage_id, arg1, reg_num);
}

/*
**	OPERATION	LD (load)
**	OPCODE		ARGUMENT_1		ARGUMENT_2
**	2			T_DIR/T_IND		T_REG
**
**	Загружает значение из аргумента 1 в регистр из аргумента 2. Меняет carry.
*/

void				operation_ld(t_car *carriage, t_vm *vm)
{
	unsigned char	types;
	short			reg_num;
	short			arg1_size;
	int				arg1;

	types = vm->arena[(carriage->position + 1) % MEM_SIZE];
	arg1_size = get_arg_size(types >> 6, 2);
	carriage->step = 2 + arg1_size + get_arg_size((types >> 4) & 3, 2);
	arg1 = get_bytes(vm->arena, (carriage->position + 2) % MEM_SIZE, \
			arg1_size, vm);
	reg_num = vm->arena[(carriage->position + 2 + arg1_size) % MEM_SIZE];
	if (is_invalid_parameters(types, reg_num))
		return ;
	if (types >> 6 == DIR_CODE)
	{
		carriage->reg[reg_num - 1] = arg1;
		carriage->carry = (carriage->reg[reg_num - 1]) ? 0 : 1;
	}
	else if (types >> 6 == IND_CODE)
		carriage->reg[reg_num - 1] = get_bytes(vm->arena, \
				calc_ind_address(carriage->position, arg1, vm), 4, vm);
	carriage->carry = (carriage->reg[reg_num - 1]) ? 0 : 1;
	log_ld(carriage->id, carriage->reg[reg_num - 1], reg_num);
}
