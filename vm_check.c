/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:22:32 by jmaynard          #+#    #+#             */
/*   Updated: 2019/12/21 13:29:52 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check(t_vm *vm)
{
	t_car *tmp;

	tmp = vm->car;
	vm->checks++;
	while (tmp)
	{
		if (tmp->last_live_cycle + vm->cw->cycles_to_die < vm->cw->cycle)
		{
			find_n_del_carriage(tmp, vm);
			fprint("%s\n", "del");
		}
		tmp = tmp->next;
	}
	if (vm->cw->lives_for_cycle >= NBR_LIVE)
	{
		vm->cw->cycles_to_die -= CYCLE_DELTA;
		vm->checks = 0;
	}
	else if (vm->checks == MAX_CHECKS)
	{
		vm->cw->cycles_to_die -= CYCLE_DELTA;
		vm->checks = 0;
	}
	if (vm->car == NULL || vm->cw->lives_for_cycle == 0)
		return (1);
	vm->cw->lives_for_cycle = 0;
	return (0);
}
