/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:35:13 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/23 20:07:51 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_fork(t_car *carriage, t_vm *vm)
{
	t_car	*tmp;
	int		pos;

	tmp = carriage_duplicate(carriage, vm);
	get_bytes(&pos, vm->arena, carriage->position + 1, 2);
	tmp->position = (pos % IDX_MOD) % MEM_SIZE;
	carriage->step = 2;
}