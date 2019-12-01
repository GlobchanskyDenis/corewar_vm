/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_getters_setters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:38:44 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/12/01 15:05:50 by bsabre-c         ###   ########.fr       */
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
**	Function returns indirect address for all operations. This function
**	was made for safelly getting address (varification for IDX_MOD, MEM_SIZE
**	and negative values)
*/

int		get_ind_after_idx(short position, int ind, t_vm *vm)
{
	if (!vm || !vm->arena)
		error_exit(vm, "get indirect address - empty ptr found");
	if (ind >= 0 && ind >= (int)position && ind - (int)position < IDX_MOD)
		return(ind % MEM_SIZE);
	if (ind >= 0 && ind >= (int)position && ind - (int)position >= IDX_MOD)
		return(((int)position + (ind - (int)position) % IDX_MOD) % MEM_SIZE);
	if (ind >= 0 && ind < (int)position && (int)position - ind < IDX_MOD)
		return(ind);
	if (ind >= 0 && ind < (int)position && (int)position - ind >= IDX_MOD)
		return(((int)position - ((int)position - ind) % IDX_MOD));
	if (ind < 0 && (int)position - (-ind) % IDX_MOD >= 0)
		return((int)position - (-ind) % IDX_MOD);
	if (ind < 0 && (int)position - (-ind) % IDX_MOD < 0)
		return(MEM_SIZE - ((int)position - (-ind) % IDX_MOD));
	fprint("function get_ind_addr - terrible error!!\n");
	return (-1);
}

/*
**	set bytes from unsigned integer variable (maximum 4 bytes) to the arena
*/

void	set_bytes(void *src, unsigned char *arena, short start, short len)
{
	short			i;
	short			position;
	unsigned char	*ptr;

	if (!arena || !src || len < 1 || len > 4)
		return ;
	ptr = src;
	ptr += len - 1;
	i = -1;
	while (++i < len)
	{
		if (i + start < MEM_SIZE)
			position = i + start;
		else
			position = i + start - MEM_SIZE;
		arena[position] = *ptr;
		ptr--;
	}
}