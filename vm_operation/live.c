/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:19:40 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/05 21:07:15 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

inline static void	log_live(size_t carriage_id, int player_nbr, short log_flag)
{
	if (!log_flag)
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

void				operation_live(t_car *carriage, t_vm *vm)
{
	int			player_nbr;

	carriage->last_live_cycle = vm->cw->cycle;
	if (vm->cw->lives_for_cycle > 30000)
		vm->cw->lives_for_cycle = 30000;
	vm->cw->lives_for_cycle++;
	player_nbr = get_bytes(vm->arena, carriage->position + 1, 4, vm);
	carriage->step = 5;
	log_live(carriage->id, player_nbr, vm->flag & FLAG_LOG);
	if (-player_nbr <= (int)vm->max_pl && -player_nbr > 0)
	{
		vm->player[-player_nbr - 1].last_live_cycle = vm->cw->cycle;
		vm->cw->last_alive = -player_nbr;
		if (vm->flag & FLAG_LOG)
			fprint("Player %d (%s) is said to be alive\n", \
					-player_nbr, vm->player[-player_nbr - 1].name);
	}
}
