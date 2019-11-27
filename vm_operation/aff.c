/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:06:09 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/27 15:49:02 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void		op_aff(t_car *carriage, t_vm *vm)
{
	int		reg;

	fprint("operation aff\n");
	get_bytes(&reg, vm->arena, carriage->position + 1, REG_SIZE);
	fprint("player %d: %c\n", -(carriage->reg[0]), (char)reg);
	carriage->step = REG_SIZE;
}
