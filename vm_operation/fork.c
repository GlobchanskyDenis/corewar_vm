/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:35:13 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/05 19:30:49 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline static void	log_fork(t_car *carriage, int pos, short log_flag)
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
	fprint("%d | fork %d (%d)\n", carriage->id, pos, \
			carriage->position + pos % IDX_MOD);
}

/*
**	OPERATION	FORK (fork)
**	OPCODE		ARGUMENT_1
**	12 (0x0C)	T_DIR
**
**	Дублирует каретку и размещает ее по адресу первого аргумента
*/

void				operation_fork(t_car *carriage, t_vm *vm)
{
	t_car	*tmp;
	int		pos;

	pos = get_bytes(vm->arena, (carriage->position + 1) % MEM_SIZE, 2, vm);
	tmp = carriage_duplicate(carriage, vm);
	tmp->position = tmp->position + pos % IDX_MOD;
	if (tmp->position < 0)
		tmp->position = tmp->position + MEM_SIZE;
	tmp->position = tmp->position % MEM_SIZE;
	tmp->command = -1;
	carriage->step = 3;
	log_fork(carriage, pos, vm->flag & FLAG_LOG);
}
