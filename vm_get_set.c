/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_get_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:12:03 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/23 18:12:04 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

short	get_info(unsigned char byte, short arg_nbr)
{
	short	dst;

	if (byte == 0 || arg_nbr < 1 || arg_nbr > 4)
		return (0);
	dst = (short)byte;
	if (arg_nbr == 1)
		return (dst >> 6);
	if (arg_nbr == 2)
		return ((dst >> 4) & 3);
	if (arg_nbr == 3)
		return ((dst >> 2) & 3);
	return (dst & 3);
}

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

unsigned int	get_bytes(unsigned char *arena, short start, short len, t_vm *vm)
{
	short			i;
	short			position;
	unsigned int	dst;

	if (!arena || !vm || len < 0 || len > 4)
		error_exit(vm, "get bytes - empty ptr found");
	dst = 0;
	i = -1;
	while (++i < len)
	{
		if (i + start < MEM_SIZE)
			position = i + start;
		else
			position = i + start - MEM_SIZE;
		dst = dst << 8;
		dst += (unsigned int)arena[position];
	}
	return (dst);
}
