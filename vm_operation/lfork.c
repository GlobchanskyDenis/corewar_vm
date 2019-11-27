/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:04:08 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/27 15:50:00 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void		op_lfork(t_car *carriage, t_vm *vm)
{
	t_car	*tmp;
	int		pos;

	fprint("operation lfork\n");
	tmp = carriage_duplicate(carriage, vm);
	get_bytes(&pos, vm->arena, carriage->position + 1, 2);
	tmp->position += pos % MEM_SIZE;
	carriage->step = 2;
}
