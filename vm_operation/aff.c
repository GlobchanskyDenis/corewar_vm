/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:06:09 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/23 20:32:27 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_aff(t_car *carriage, t_vm *vm)
{
	int		reg;

	get_bytes(&reg, vm->arena, carriage->position + 1, REG_SIZE);
	fprint("player %d: %c\n", -(carriage->reg[0]), (char)reg);
	carriage->step = REG_SIZE;
}