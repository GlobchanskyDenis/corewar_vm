/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:19:40 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/02 13:25:24 by bsabre-c         ###   ########.fr       */
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

static void	log_live(short carriage_id, int player_nbr)
{
	if (!DEBUG_LOG)
		return ;
	fprint("P ");
	if (carriage_id < 1000)
		ft_putchar(' ');
	if (carriage_id < 100)
		ft_putchar(' ');
	if (carriage_id < 10)
		ft_putchar(' ');
	fprint("%d | live %d\n", carriage_id, player_nbr);
}

/*
**	OPERATION	LIVE (alive)
**	OPCODE		ARGUMENT_1
**	1			T_DIR
**
**	Засчитывает что каретка жива (переменная last_alive), если аргумент
**	совпадает с номером живого чемпиона, то этот чемпион также обновляет свою
**	переменную last_alive
*/

void	operation_live(t_car *carriage, t_vm *vm)
{
	int			player_nbr;

	if (!carriage || !vm)
		error_exit(vm, "operation live - empty ptr found");
	//fprint("operation live\tcycle %d\tposition %d\n", (int)vm->cw->cycle, (int)carriage->position);

	// засчитываем операцию live для каретки вне зависимости от аргумента операции
	carriage->last_live_cycle = vm->cw->cycle;
	vm->cw->lives_for_cycle++;

	// считываем байты аргумента операции
	player_nbr = get_bytes(vm->arena, carriage->position + 1, 4, vm);
	carriage->step = 5;

	log_live(carriage->id, player_nbr);

	if (-player_nbr <= (int)vm->max_pl && -player_nbr > 0)
	{
		//fprint("\tplayer last live cycle %d\n", vm->player[-player_nbr - 1].last_live_cycle);
		if (vm->cw->cycle - vm->player[-player_nbr - 1].last_live_cycle < \
				(size_t)vm->cw->cycles_to_die)
		{
			vm->player[-player_nbr - 1].last_live_cycle = vm->cw->cycle;
			vm->cw->last_alive = -player_nbr;
			if (DEBUG_LOG)
			{
				//fprint("A process shows that player %d (%s) is alive\n", \
				//		-player_nbr, vm->player[-player_nbr - 1].name);
				fprint("Player %d (%s) is said to be alive\n", -player_nbr, vm->player[-player_nbr - 1].name);
			}
		}
		// else 
		// 	fprint("it seems that this player already dead\n");
	}
	// else	{
	// 	fprint("cant do live operation at all\t player nbr %d  -r0 %d\n", -player_nbr, carriage->reg[0]);
		//print_all(vm);
		//free_exit(vm, "unexpected DUMP !!\n");
	// }
}
