/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:04:08 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/01 21:31:50 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static void	log_lfork(t_car *carriage, int pos)
{
	if (!DEBUG_LOG)
		return ;
	fprint("P ");
	if (carriage->id < 1000)
		ft_putchar(' ');
	if (carriage->id < 100)
		ft_putchar(' ');
	if (carriage->id < 10)
		ft_putchar(' ');
	fprint("%d | lfork %d (%d)\n", carriage->id, pos, \
			carriage->position + pos % IDX_MOD);
}

/*
**	OPERATION	LFORK (long fork)
**	OPCODE		ARGUMENT_1
**	15 (0x0F)	T_DIR
**
**	Дублирует каретку и размещает ее по адресу первого аргумента без ограничения
**	по IDX_MOD.
*/

void	operation_lfork(t_car *carriage, t_vm *vm)
{
	t_car	*tmp;
	int		pos;

	if (!vm || !carriage)
		error_exit(vm, "operation lfork - empty ptr found");
	// fprint("operation lfork\tcycle %d\tposition %d\n", (int)vm->cw->cycle, (int)carriage->position);

	pos = get_bytes(vm->arena, (carriage->position + 1) % MEM_SIZE, 2, vm);
	tmp = carriage_duplicate(carriage, vm);
	tmp->position = (tmp->position + pos) % MEM_SIZE;
	carriage_read_command(tmp, vm);
	carriage->step = 3;

	log_lfork(carriage, pos);
}
