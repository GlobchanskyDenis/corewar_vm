/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 21:22:32 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/24 19:09:48 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_check(t_vm *vm)
{
	t_car *tmp;

	tmp = vm->car;
	vm->checks++;
	while (tmp)
	{
		if (tmp->last_live_cycle + vm->cycles_to_die < vm->cycle)
			find_n_del_carriage(vm, tmp);
		tmp = tmp->next;
	}
	if (vm->lives_for_cycle >= NBR_LIVE)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->checks = 0;
	}
	else if (vm->checks == MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->checks = 0;
	}
	vm->lives_for_cycle = 0;
}