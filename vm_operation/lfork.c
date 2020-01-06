/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:04:08 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/05 20:08:38 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline static void	log_lfork(t_car *carriage, int pos, short log_flag)
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
	fprint("%d | lfork %d (%d)\n", carriage->id, pos, \
			carriage->position + pos);
}

/*
**	OPERATION	LFORK (long fork)
**	OPCODE		ARGUMENT_1
**	15 (0x0F)	T_DIR
**
**	Дублирует каретку и размещает ее по адресу первого аргумента без ограничения
**	по IDX_MOD.
*/

void				operation_lfork(t_car *carriage, t_vm *vm)
{
	t_car	*tmp;
	int		pos;

	pos = get_bytes(vm->arena, (carriage->position + 1) % MEM_SIZE, 2, vm);
	tmp = carriage_duplicate(carriage, vm);
	tmp->position = tmp->position + pos;
	while (tmp->position < 0)
		tmp->position += MEM_SIZE;
	tmp->position = tmp->position % MEM_SIZE;
	tmp->command = -1;
	carriage->step = 3;
	log_lfork(carriage, pos, vm->flag & FLAG_LOG);
}
