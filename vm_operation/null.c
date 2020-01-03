/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 13:44:27 by bsabre-c          #+#    #+#             */
/*   Updated: 2020/01/02 21:55:25 by bsabre-c         ###   ########.fr       */
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
	carriage->step = 1;
}
