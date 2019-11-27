/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:33:08 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/27 21:00:36 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	op_sti(t_car *carriage, t_vm *vm)
{
	int		arg2;
	int		arg3;
	int		reg;
	int		adr;
	int		types;

	fprint("operation sti\n");
	types = get_args_types(&vm->arena[carriage->position + 1]);
	carriage->step = 2;
	fprint("types %d\n", types);
	reg = get_arg(carriage, vm, types / 1000, 2);
	arg2 = get_arg(carriage, vm, (types / 100) % 10, 2);
	arg3 = get_arg(carriage, vm, (types / 10) % 10, 2);
	adr = (carriage->position + (arg2 + arg3) % IDX_MOD) % MEM_SIZE;
	ft_memcpy(&vm->arena[adr], &reg, REG_SIZE);//// PIZDETS NAXYI YA PISAL FYNKTSIYU SET_BYTE ?????
}
