/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:01:24 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/29 20:34:08 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

unsigned int	get_ind_addr(short position, int ind, t_vm *vm)
{
	unsigned int	dst;
	short			new_ind;

	if (!vm || !vm->arena)
		error_exit(vm, "get indirect address - empty ptr found");
	new_ind = (short)ind;
	if (position <= new_ind)
	{
		if (new_ind - position > IDX_MOD)
			dst = (unsigned int)(position + (new_ind - position) % IDX_MOD);
		dst = (unsigned int)new_ind;
	}
	else
	{
		if (position + new_ind > IDX_MOD)
			dst = (unsigned int)(position + (new_ind - position) % IDX_MOD);
		dst = (unsigned int)new_ind;
	}
	return (dst);
}

/*
**	Задача этой операции состоит в загрузке значения в регистр. Но её поведение
**	отличается в зависимости от типа первого аргумента:
**	Аргумент #1 — T_DIR
**	Если тип первого аргумента это T_DIR, то число переданное в качестве
**	аргумента будет воспринято «как есть».
**	Задачи операции:
**	Записать полученное число в регистр, который был передан в качестве
**	второго аргумента.
**	Если в регистр записали число 0, то установить значение carry в 1. Если
**	было записано не нулевое значение, то установить carry в 0.
**	Аргумент #1 — T_IND
**	Если тип первого аргумента это T_IND, то в данном случае число
**	представляет собой адрес.
**	В случае получения аргумента такого типа он обрезается по модулю —
**	<ПЕРВЫЙ_АРГУМЕНТ> % IDX_MOD.
**
**	 Take a random argument and a registry. Load the value of the first
**	argument in the registry. Its opcode is 10 in binary and it will change
**	the carry
*/

void			operation_ld(t_car *carriage, t_vm *vm)
{
	unsigned char	types;
	short			reg_num;
	short			arg1_size;
	int				arg1;

	if (!vm || !carriage)
		error_exit(vm, "operation ld - empty ptr found");
	fprint("operation ld\n");
	/*
	**	types = get_args_types(&vm->arena[carriage->position + 1]);
	**	first of all we must get byte that tells us,
	**	what type of arguments do we have
	*/
	types = vm->arena[(carriage->position + 1) % MEM_SIZE];
	/*
	**	step = 1(command byte) + 2 params(1-st xx byte 2-nd 1 byte) + 1;
	**	to know, what size is 2-nd and 3-d parameter, we will
	**	use function get_arg_size()
	*/
	arg1_size = get_arg_size(types >> 6, 2);
	arg1 = get_bytes(vm->arena, (carriage->position + 2) % MEM_SIZE, \
			arg1_size, vm);
	reg_num = vm->arena[(carriage->position + 2 + arg1_size) % MEM_SIZE];
	if (reg_num > REG_NUMBER || reg_num < 1)
		error_exit(vm, "operation sti - too big register found");
	if (types >> 6 == DIR_CODE)
		carriage->reg[reg_num - 1] = arg1;
	else if (types >> 6 == IND_CODE)
		carriage->reg[reg_num - 1] = (unsigned int)vm->arena[arg1 % IDX_MOD]; // а что если число отрицательное или...
	else
		error_exit(vm, "operation sti - wrong argument");// kill carriage??
	carriage->carry ^= 1;
	carriage->step = 3 + arg1_size;
/*
	val = 0;
	reg = 0;
	fprint("operation ld\n");
	types = get_args_types(&vm->arena[carriage->position + 1]);
	if (types / 1000 == DIR_CODE)
	{
		get_bytes(&val, vm->arena, (carriage->position + 2) % MEM_SIZE, DIR_SIZE);
		get_bytes(&reg, vm->arena, \
			(carriage->position + 2 + DIR_SIZE) % MEM_SIZE, REG_SIZE);
		carriage->step = 2 + DIR_SIZE + REG_SIZE;
	}
	else if (types / 1000 == IND_CODE)
	{
		get_bytes(&arg, vm->arena, (carriage->position + 2) % MEM_SIZE, IND_SIZE);
		get_bytes(&val, vm->arena, \
			(carriage->position + arg % IDX_MOD) % MEM_SIZE, REG_SIZE);
		get_bytes(&reg, vm->arena, \
			(carriage->position + 2 + IND_SIZE) % MEM_SIZE, REG_SIZE);
		carriage->step = 2 + IND_SIZE + REG_SIZE;
	}
	carriage->reg[reg] = val;
	carriage->carry = 0;
	if (val == 0)
		carriage->carry = 1;
*/
}
