/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:02:30 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/23 20:05:09 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_zjmp(t_car *carriage, t_vm *vm)
{
	int		pos;

	carriage->step = 2;
	if (carriage->carry == 0)
		return ;
	get_bytes(&pos, vm->arena, carriage->position + 1, 2);
	carriage->step = (pos % IDX_MOD) % MEM_SIZE;
}