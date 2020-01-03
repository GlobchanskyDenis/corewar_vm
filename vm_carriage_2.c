/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_carriage_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:16:10 by bsabre-c          #+#    #+#             */
/*   Updated: 2020/01/03 17:29:44 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		find_n_del_carriage(t_car *carriage, t_vm *vm)
{
	t_car		*tmp;
	t_car		*prev;

	if (!vm || !carriage)
		error_exit(vm, "delete shown carriage - empty ptr found");
	tmp = vm->car;
	prev = NULL;
	while (tmp && tmp != carriage)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		error_exit(vm, "delete shown carriage - can't find carriage");
	if (prev)
	{
		prev->next = tmp->next;
		free(tmp);
	}
	else
	{
		vm->car = vm->car->next;
		free(tmp);
	}
}
