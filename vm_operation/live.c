/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:19:40 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/29 16:43:34 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
**	Она засчитывает, что каретка, которая выполняет операцию live, жива. Если
**	указанный в качестве аргумента операции live номер совпадает с номером
**	игрока, то она засчитывает, что это игрок жив. Например, если значение
**	аргумента равно -2, значит игрок с номером 2 жив.
**	The instruction that allows a process to stay alive. It can also record
**	that the player whose number is the argument is indeed alive. No argument’s
**	coding byte, opcode 0x01. Oh and its only argument is on 4 bytes.
*/

void	operation_live(t_car *carriage, t_vm *vm)
{
	int			player_nbr;

	if (!carriage || !vm)
		error_exit(vm, "operation live - empty ptr found");
	fprint("operation live\n");
	carriage->last_live_cycle = vm->cw->cycle;
	vm->cw->lives_for_cycle++;
	player_nbr = get_bytes(vm->arena, carriage->position + 1, 4, vm);
	if (player_nbr == (-1) * (int)carriage->reg[0])
	{
		vm->player[player_nbr - 1].last_live_cycle = vm->cw->cycle;
		vm->cw->last_alive = player_nbr;
	}
	carriage->step = 5;
}
