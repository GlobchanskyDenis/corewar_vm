/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:04:08 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/23 19:18:31 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_lfork(t_car *carriage, t_vm *vm)
{
	t_car	*tmp;
	int		pos;

	tmp = carriage_duplicate(carriage, vm);
	get_bytes(&pos, vm->arena, carriage->position + 1, 2);
	tmp->position += pos % MEM_SIZE;
	carriage->step = 2;
}