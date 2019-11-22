/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_initialize_game.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:25:51 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/22 18:25:53 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Function copy players code to the Arena, creates carriages for them
**	and fills them
*/

void		initialize_game(unsigned char *arena, t_vm *vm)
{
	short	step;
	short	i;
	t_car	*carriage;

	if (!arena || !vm)
		error_exit(vm, "initialize game - empty ptr found");
	step = MEM_SIZE / vm->max_pl;
	i = -1;
	while (++i < vm->max_pl)
	{
		ft_memcpy(&(arena[i * step]), vm->player[i].code, \
				vm->player[i].codesize);
		carriage = add_new_carriage_in_stack(vm);
		carriage->position = i * step;
		carriage->reg[0] = -vm->player[i].id;
	}
}
