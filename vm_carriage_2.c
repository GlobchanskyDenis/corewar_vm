/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_carriage_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:16:10 by bsabre-c          #+#    #+#             */
/*   Updated: 2020/01/02 15:40:01 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// static void	delete_shown_carriage(t_car *carriage, t_vm *vm)
// {
// 	if (!vm || !carriage)
// 		error_exit(vm, "delete shown carriage - empty ptr found");
// 	// if (carriage->reg)
// 	// 	free(carriage->reg);
// 	free(carriage);
// }

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
		// delete_shown_carriage(tmp, vm);
		// if (tmp->reg)
		// 	free(tmp->reg);
		free(tmp);
	}
	else
	{
		vm->car = vm->car->next;
		// delete_shown_carriage(tmp, vm);
		// if (tmp->reg)
		// 	free(tmp->reg);
		free(tmp);
	}
}
