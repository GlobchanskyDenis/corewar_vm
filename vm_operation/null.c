/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 13:44:27 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/12/22 14:11:13 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
**	This case will be executed when comman is null (empty space)
*/

void	operation_null(t_car *carriage, t_vm *vm)
{
	if (!vm || !carriage)
		error_exit(vm, "operation null - empty ptr found");
	fprint("operation null\tcycle %d\tposition %d\n", (int)vm->cw->cycle, (int)carriage->position);
	carriage->step = 1;
}