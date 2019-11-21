/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_comm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 14:59:12 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/16 16:27:09 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	//vm->lives_for_cycle++;
**	//car->last_live_cycle = vm->curr_cycle;
**
**	//vm->last_pl_alive = (-1) * arg;
*/

void	ft_live(t_car *car, t_vm *vm)
{
	int		arg;

	arg = (int)((car->position) & 1111);
	if (arg >= -1 && arg <= vm->max_pl)
	{
		car->position = car->position + car->step;
	}
	else
	{
		car->position = car->position + 1;
	}
}
