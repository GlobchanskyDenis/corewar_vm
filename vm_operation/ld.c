/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:01:24 by jmaynard          #+#    #+#             */
/*   Updated: 2019/12/18 12:32:49 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

/*
**	static short	is_invalid_parameters(unsigned char types, short reg_num)
**	{
**		unsigned char	arg_type;
**	
**		if (reg_num > REG_NUMBER || reg_num < 1)
**		{
**			fprint("wrong reg number, skip the command\n");
**			return (1);
**		}	
**		arg_type = types >> 6;
**		if (!(arg_type == DIR_CODE || arg_type == IND_CODE))
**		{
**			fprint("wrong argument type, skip the command\n");
**			return (1);
**		}	
**		if (get_arg_size(arg_type, 2) == 0)
**		{
**			fprint("wrong argument size, skip the command\n");
**			return (1);
**		}	
**		return (0);
**	}
*/

static short	is_invalid_parameters(unsigned char types, short reg_num)
{
	//unsigned char	arg_type;

	if (reg_num > REG_NUMBER || reg_num < 1)
	{
		fprint("wrong reg number, skip the command\n");
		return (1);
	}	
	if (((DIR_CODE << 6) | (REG_CODE << 4)) != types && ((IND_CODE << 6) | (REG_CODE << 4)) != types)
	{
		fprint("wrong argument type, skip the command\n");
		fprint("types = %d => %d cases %d %d\n", types, types >> 6, (DIR_CODE << 0), (IND_CODE << 6));
		return (1);
	}	
	if (get_arg_size(types >> 6, 2) == 0)
	{
		fprint("wrong argument size, skip the command\n");
		return (1);
	}	
	return (0);
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

void		operation_ld(t_car *carriage, t_vm *vm)
{
	unsigned char	types;
	short			reg_num;
	short			arg1_size;
	int				arg1;

	if (!vm || !carriage)
		error_exit(vm, "operation ld - empty ptr found");
	fprint("operation ld\tcycle %d\tposition %d\n", (int)vm->cw->cycle, (int)carriage->position);
	/*
	**	types = get_args_types(&vm->arena[carriage->position + 1]);
	**	first of all we must get byte that tells us,
	**	what type of arguments do we have
	*/
	types = vm->arena[(carriage->position + 1) % MEM_SIZE];
	/*
	**	It need to make check for bad parameters !!!!!
	**	.name		"A-TEAM"
	**	.comment	"Plan B isn't exist"
	**	loop:
	**	ld 6, r2
	**	sti r2, %12, %1
	**	#this code couses seg fault !!!!
	*/
	/*
	**	step = 1(command byte) + 2 params(1-st xx byte 2-nd 1 byte) + 1;
	**	to know, what size is 2-nd and 3-d parameter, we will
	**	use function get_arg_size()
	*/
	arg1_size = get_arg_size(types >> 6, 2);
	arg1 = get_bytes(vm->arena, (carriage->position + 2) % MEM_SIZE, \
			arg1_size, vm);
	reg_num = vm->arena[(carriage->position + 2 + arg1_size) % MEM_SIZE];
	carriage->step = 3 + arg1_size;
	if (is_invalid_parameters(types, reg_num))
		return ;
	if (types >> 6 == DIR_CODE)
		carriage->reg[reg_num - 1] = arg1;
	else if (types >> 6 == IND_CODE)
	{
		carriage->reg[reg_num - 1] = get_ind_data(carriage->position, arg1, vm);
		carriage->carry = (carriage->reg[reg_num - 1]) ? 1 : 0;// change of carry differs !!!!
	}
	//else
	//	error_exit(vm, "operation ld - wrong argument");// kill carriage?? NO!!!! Mb we need to just skip this command??
	//carriage->carry ^= 1;
}
