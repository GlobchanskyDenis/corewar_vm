/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_get_set_bytes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:38:44 by bsabre-c          #+#    #+#             */
/*   Updated: 2020/01/05 15:58:10 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	get_4_bytes(unsigned char *arena, short start, t_vm *vm)
{
	short			i;
	short			position;
	int				dst;

	if (!arena || !vm)
		error_exit(vm, "get bytes - empty ptr found");
	if (start < 0 || start > MEM_SIZE)
		error_exit(vm, "get bytes - wrong start value");
	dst = 0;
	i = -1;
	while (++i < 4)
	{
		if (i + start < MEM_SIZE)
			position = i + start;
		else
			position = i + start - MEM_SIZE;
		dst = dst << 8;
		dst += (int)arena[position];
	}
	return (dst);
}

static int	get_2_bytes(unsigned char *arena, short start, t_vm *vm)
{
	short			i;
	short			position;
	short			dst;

	if (!arena || !vm)
		error_exit(vm, "get bytes - empty ptr found");
	if (start < 0 || start > MEM_SIZE)
		error_exit(vm, "get bytes - wrong start value");
	dst = 0;
	i = -1;
	while (++i < 2)
	{
		if (i + start < MEM_SIZE)
			position = i + start;
		else
			position = i + start - MEM_SIZE;
		dst = dst << 8;
		dst += (short)arena[position];
	}
	return ((int)dst);
}

/*
**	function returns selected bytes from the arena in integer variable
**
**	WARNING!! For security, in this function there is no check for len == 0,
**	because in this case carriage must skip current command and move forward.
**	In case of len == 0 you must check for it in further functions to skip
**	the command.
*/

int			get_bytes(unsigned char *arena, short start, short len, \
		t_vm *vm)
{
	if (!arena || !vm)
		error_exit(vm, "get bytes - empty ptr found");
	if (len < 0 || len > 4)
		error_exit(vm, "get bytes - wrong len value");
	while (start < 0)
		start += MEM_SIZE;
	start = start % MEM_SIZE;
	if (len == 4)
		return (get_4_bytes(arena, start, vm));
	if (len == 2)
		return (get_2_bytes(arena, start, vm));
	if (len == 1)
		return ((int)arena[start]);
	return (0);
}

/*
**	set bytes from unsigned integer variable (maximum 4 bytes) to the arena
*/

void		set_bytes(void *src, unsigned char *arena, short start, short len)
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

void		set_owner(short owner_id, short *arena_owner, short start, \
		short len)
{
	short			i;
	short			position;

	if (!arena_owner || start < 0 || start >= MEM_SIZE || len > CHAMP_MAX_SIZE)
		return ;
	i = -1;
	while (++i < len)
	{
		position = (i + start < MEM_SIZE) ? i + start : i + start - MEM_SIZE;
		arena_owner[position] = owner_id;
	}
}
