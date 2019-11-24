/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:45:08 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/24 17:13:22 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_args_types(unsigned char *byte)
{
	int res;
	int i;

	res = 0;
	res = get_info(byte, 1);
	res *= 10;
	res += get_info(byte, 2);
	res *= 10;
	res += get_info(byte, 3);
	res *= 10;
	res += get_info(byte, 4);
	return (res);
}

int		get_arg(t_car *c, t_vm *vm, short type, int dir_size)
{
	int		arg;
	int		res;

	if (type == REG_CODE)
	{
		get_bytes(&res, vm->arena, (c->position + c->step) % MEM_SIZE, REG_SIZE);
		c->step += REG_SIZE;
		arg = c->reg[res];
	}
	else if (type == DIR_CODE)
	{
		get_bytes(&arg, vm->arena, (c->position + c->step) % MEM_SIZE, dir_size);
		c->step += DIR_SIZE;
	}
	else if (type == IND_CODE)
	{
		get_bytes(&res, vm->arena, (c->position + c->step) % MEM_SIZE, IND_SIZE);
		get_bytes(&arg, vm->arena, \
			((c->position + c->step) + res % IDX_MOD) % MEM_SIZE, 4);
		c->step += IND_SIZE;
	}
	return (arg);
}