/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:02:30 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/05 21:02:33 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline static void	log_zjmp(t_car *carriage, int arg1, short log_flag)
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
	fprint("%d | zjmp %d %s\n", carriage->id, arg1, \
			(carriage->carry) ? "OK" : "FAILED");
}

/*
**	OPERATION	ZJMP (zero jump)
**	OPCODE		ARGUMENT_1
**	9			T_DIR
**
**	Если флаг carry был установлен в единицу (операция записала ноль), каретка
**	прыгает на расстояние указанное аргументом 1.
*/

void				operation_zjmp(t_car *carriage, t_vm *vm)
{
	int		arg1;

	arg1 = get_bytes(vm->arena, (carriage->position + 1) % MEM_SIZE, \
			get_arg_size(DIR_CODE, 9), vm);
	if (carriage->carry != 0)
		carriage->step = arg1 % IDX_MOD;
	else
		carriage->step = 3;
	log_zjmp(carriage, arg1, vm->flag & FLAG_LOG);
}
