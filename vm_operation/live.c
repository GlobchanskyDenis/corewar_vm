/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:19:40 by jmaynard          #+#    #+#             */
/*   Updated: 2019/12/18 02:31:36 by bsabre-c         ###   ########.fr       */
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

/*
**	Comment from Nastya:
**	For each valid execution of the live instruction, 
**	the machine must display: 
**	“A process shows that player X (champion_name) is alive”.
*/


void	operation_live(t_car *carriage, t_vm *vm)
{
	int			player_nbr;

	if (!carriage || !vm)
		error_exit(vm, "operation live - empty ptr found");
	fprint("operation live\tcycle %d\tposition %d\n", (int)vm->cw->cycle, (int)carriage->position);
	carriage->last_live_cycle = vm->cw->cycle;
	vm->cw->lives_for_cycle++;
	player_nbr = get_bytes(vm->arena, carriage->position + 1, 4, vm);
	if (player_nbr == -carriage->reg[0] && player_nbr <= \
			(int)vm->max_pl)
	{
		if (vm->cw->cycle - vm->player[player_nbr - 1].last_live_cycle < \
				(size_t)vm->cw->cycles_to_die)
		{
			vm->player[player_nbr - 1].last_live_cycle = vm->cw->cycle;
			vm->cw->last_alive = player_nbr;
			if (LIVE_PRINT_FLAG)
			{
				fprint("A process shows that player %d (%s) is alive\n", \
						player_nbr, vm->player[player_nbr - 1].name);
			}
		}
	}
	carriage->step = 5;
}
