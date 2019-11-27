/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:35:13 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/27 15:49:27 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	op_fork(t_car *carriage, t_vm *vm)
{
	t_car	*tmp;
	int		pos;

	fprint("operation fork\n");
	tmp = carriage_duplicate(carriage, vm);
	get_bytes(&pos, vm->arena, carriage->position + 1, 2);
	tmp->position = (pos % IDX_MOD) % MEM_SIZE;
	carriage->step = 2;
}
