/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_getters_setters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:38:44 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/30 20:11:21 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Function extracts argument (can be register / direct data / indirect data)
*/

int		get_argument(int value, short type, t_car *carriage, t_vm *vm)
{
	if (!vm || !vm->arena || !carriage)
		error_exit(vm, "get argument - empty ptr found");
	if (type == REG_CODE && value >= 1 && value <= REG_NUMBER)
		return (carriage->reg[value - 1]);
	if (type == DIR_CODE)
		return (value);
	if (type == IND_CODE)
		return (get_ind_data(carriage->position, value, vm));
	return (0);
}

/*
**	set bytes from unsigned integer variable (maximum 4 bytes) to the arena
*/

void	set_bytes(void *src, unsigned char *arena, short start, short len)
{
	short			i;
	short			position;
	unsigned int	*ptr;

	if (!arena || !src || len < 1 || len > 4)
		return ;
	ptr = src;
	i = -1;
	while (++i < len)
	{
		if (i + start < MEM_SIZE)
			position = i + start;
		else
			position = i + start - MEM_SIZE;
		arena[position] = (unsigned char)*ptr;
		*ptr = *ptr >> 8;
	}
}