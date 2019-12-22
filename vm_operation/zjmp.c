/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:02:30 by jmaynard          #+#    #+#             */
/*   Updated: 2019/12/22 20:03:09 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void		operation_zjmp(t_car *carriage, t_vm *vm)
{
	if (!vm || !carriage)
		error_exit(vm, "operation zjmp - empty ptr found");
	fprint("operation zjmp\tcycle %d\tposition %d\n", (int)vm->cw->cycle, (int)carriage->position);
	carriage->step = 3;
	if (carriage->carry == 0)
		return ;
	carriage->step = get_bytes(vm->arena, (carriage->position + 1) % MEM_SIZE, \
			get_arg_size(DIR_CODE, 9), vm) % IDX_MOD;
	//fprint("JUMP!! %d\n", carriage->step);
}
