/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:33:08 by jmaynard          #+#    #+#             */
/*   Updated: 2019/12/20 20:03:02 by bsabre-c         ###   ########.fr       */
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
**		arg_type = types >> 4 & 3;
**		if (!(arg_type == REG_CODE))
**		{
**			fprint("wrong argument type, skip the command\n");
**			return (1);
**		}
**		return (0);
**	}
*/

static short	is_invalid_parameters(unsigned char types, short reg_num)
{
	if (reg_num > REG_NUMBER || reg_num < 1)
	{
		fprint("wrong reg number, skip the command\n");
		return (1);
	}
	if ((types >> 6 != REG_CODE) || ((types >> 4 & 3) == 0) || \
			((types >> 2 & 3) != REG_CODE && (types >> 2 & 3) != DIR_CODE))
	{
		fprint("wrong argument type, skip the command\n");
		fprint("types = %d => %d %d cases %d %d\n", types, types >> 6, (types >> 4) &3, (DIR_CODE << 6) + (REG_CODE << 4), (IND_CODE << 6) + (REG_CODE << 4));
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
**	sti: Opcode 11. Take a registry, and two indexes (potentially registries)
**	add the two indexes, and use this result as an address where the value of
**	the first parameter will be copied.
**	sti "store index": 3 params T_REG, T_REG|T_DIR|T_IND, T_DIR|T_REG
**	command number 11,	cycles to exe 25,
**	1, 1 - mb carry and something else
**	Эта операция записывает значение регистра, переданного в качестве первого
**	параметра, по адресу — текущая позиция + (<ЗНАЧЕНИЕ_ВТОРОГО_АРГУМЕНТА> +
**	<ЗНАЧЕНИЕ_ТРЕТЕГО_АРГУМЕНТА>) % IDX_MOD.
**	Как получить значение для каждого типа аргумента описано выше.
*/

void	operation_sti(t_car *carriage, t_vm *vm)
{
	unsigned char	types;
	short			reg_num;
	int				arg2;
	int				arg3;
	int				value;

	if (!vm || !carriage)
		error_exit(vm, "operation sti - empty ptr found");
	fprint("operation sti\tcycle %d\tposition %d\n", (int)vm->cw->cycle, (int)carriage->position);
	/*
	**	types = get_args_types(&vm->arena[carriage->position + 1]);
	**	first of all we must get byte that tells us,
	**	what type of arguments do we have
	*/
	types = vm->arena[(carriage->position + 1) % MEM_SIZE];
	/*
	**	step = 1(command byte) + 3params(1-st 1 byte 2-nd xx 3-d xx) + 1;
	**	to know, what size is 2-nd and 3-d parameter, we will
	**	use function get_arg_size()
	*/
	carriage->step = 3 + get_arg_size((types >> 4) & 3, 11) + \
			get_arg_size((types >> 2) & 3, 11);
	reg_num = vm->arena[(carriage->position + 2) % MEM_SIZE];
	if (is_invalid_parameters(types, reg_num))
		return ;
	value = get_bytes(vm->arena, (carriage->position + 3) % MEM_SIZE, \
			get_arg_size((types >> 4) & 3, 11), vm);
	arg2 = get_argument(value, (types >> 4) & 3, carriage, vm);
	value = get_bytes(vm->arena, (carriage->position + 3 + \
			get_arg_size((types >> 4) & 3, 11)) % MEM_SIZE, \
			get_arg_size((types >> 2) & 3, 11), vm);
	arg3 = get_argument(value, (types >> 2) & 3, carriage, vm);
	set_bytes(&carriage->reg[reg_num - 1], vm->arena, \
			get_ind_after_idx(carriage->position, arg2 + arg3, vm), 4);
}
