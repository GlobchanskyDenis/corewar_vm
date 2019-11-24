/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:19:40 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/24 19:06:28 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_live(t_car *carriage, t_vm *vm)
{
	int player;

	carriage->last_live_cycle = vm->cycle;
	vm->lives_for_cycle++;
	get_bytes(&player, vm->arena, carriage->position + 1, 4);
	if (player == (-1) * carriage->reg[0])
	{
		vm->player[player].last_live_cycle = vm->cycle;
		vm->last_alive = player;
	}
	carriage->step = DIR_SIZE;
}
