/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:02:30 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/27 15:51:47 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void		op_zjmp(t_car *carriage, t_vm *vm)
{
	int		pos;

	fprint("operation zjmp\n");
	carriage->step = 2;
	if (carriage->carry == 0)
		return ;
	get_bytes(&pos, vm->arena, carriage->position + 1, 2);
	carriage->step = (pos % IDX_MOD) % MEM_SIZE;
}
