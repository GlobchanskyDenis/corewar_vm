/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:45:08 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/27 20:57:49 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int		get_args_types(unsigned char *byte)
{
	int res;
	//int i;

	res = 0;
	res = get_info(*byte, 1);
	res *= 10;
	res += get_info(*byte, 2);
	res *= 10;
	res += get_info(*byte, 3);
	res *= 10;
	res += get_info(*byte, 4);
	return (res);
}

int		get_arg(t_car *carriage, t_vm *vm, short type, int dir_size)
{
	int		arg;
	int		res;

	res = 0;
	arg = 0;
	fprint("GET_ARG FUNCION\n");
	fprint("type %d\n", (int)type);
	fprint("type\n", (int)type);
	//get_bytes(void *dst, unsigned char *arena, short start, short len);
	if (type == REG_CODE)
	{
		fprint("check1.1\n");
		get_bytes(&res, vm->arena, (carriage->position + carriage->step) % \
				MEM_SIZE, REG_SIZE);
		fprint("check1.2\n");
		carriage->step += REG_SIZE;
		fprint("check1.3\n");
		fprint("res %d\n", res);
		arg = carriage->reg[res];
		fprint("check1.4\n");
	}
	else if (type == DIR_CODE)
	{
		fprint("check2.1\n");
		get_bytes(&arg, vm->arena, (carriage->position + carriage->step) % \
				MEM_SIZE, dir_size);
		fprint("check2.2\n");
		carriage->step += DIR_SIZE;
		fprint("check2.3\n");
	}
	else if (type == IND_CODE)
	{
		fprint("check3.1\n");
		get_bytes(&res, vm->arena, (carriage->position + \
				carriage->step) % MEM_SIZE, IND_SIZE);
		fprint("check3.2\n");
		get_bytes(&arg, vm->arena, ((carriage->position + \
				carriage->step) + res % IDX_MOD) % MEM_SIZE, 4);
		fprint("check3.3\n");
		carriage->step += IND_SIZE;
		fprint("check3.4\n");
	}
	return (arg);
}
