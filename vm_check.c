/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:22:32 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/02 15:04:54 by bsabre-c         ###   ########.fr       */
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
		if (tmp->last_live_cycle + (size_t)vm->cw->cycles_to_die < vm->cw->cycle)
			find_n_del_carriage(tmp, vm);
		tmp = tmp->next;
	}
	if (vm->cw->lives_for_cycle >= NBR_LIVE)
	{
		vm->cw->cycles_to_die -= CYCLE_DELTA;
		vm->checks = 0;
		if (DEBUG_LOG)
			fprint("Cycle to die is now %d\n", vm->cw->cycles_to_die);
	}
	else if (vm->checks == MAX_CHECKS)
	{
		vm->cw->cycles_to_die -= CYCLE_DELTA;
		vm->checks = 0;
		if (DEBUG_LOG)
			fprint("Cycle to die is now %d\n", vm->cw->cycles_to_die);
	}
	if (vm->car == NULL || vm->cw->lives_for_cycle == 0)
		return (1);
	vm->cw->lives_for_cycle = 0;
	return (0);
}
