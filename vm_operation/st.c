/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:28:25 by jmaynard          #+#    #+#             */
/*   Updated: 2019/12/21 21:22:56 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static short	is_invalid_parameters(unsigned char types, short reg_num)
{

	if (reg_num > REG_NUMBER || reg_num < 1)
	{
		fprint("wrong reg number, skip the command\n");
		return (1);
	}
	if ((types >> 6 != REG_CODE) || ((types >> 4 & 3) != REG_CODE && \
			(types >> 4 & 3) != IND_CODE))
	{
		fprint("wrong argument type, skip the command\n");
		return (1);
	}	
	if (get_arg_size(types >> 4 & 3, 2) == 0)
	{
		fprint("wrong argument size, skip the command\n");
		return (1);
	}
	return (0);
}

/*
**	st: take a registry and a registry or an indirect and store the value of
**	the registry toward a second argument. Its opcode is 0x03. For example,
**	st r1, 42 store the value of r1 at the address (PC + (42 % IDX_MOD))
**
**	st "store index": 2 params T_REG, T_REG|T_IND
**	command number 3,	cycles to exe 5, do not changes carry
**	Эта операция записывает значение регистра, переданного в качестве первого
**	параметра, по адресу — текущая позиция + (<ЗНАЧЕНИЕ_ВТОРОГО_АРГУМЕНТА> +
**	<ЗНАЧЕНИЕ_ТРЕТЕГО_АРГУМЕНТА>) % IDX_MOD.
**	Как получить значение для каждого типа аргумента описано выше.
*/

void	operation_st(t_car *carriage, t_vm *vm)
{
	unsigned char	types;
	short			reg_num;
	short			value;

	if (!vm || !carriage)
		error_exit(vm, "operation st - empty ptr found");
	fprint("operation st\tcycle %d\tposition %d\n", (int)vm->cw->cycle, (int)carriage->position);
	types = vm->arena[(carriage->position + 1) % MEM_SIZE];
	/*
	**	step = 1(command byte) + 2params(1-st 1 byte 2-nd xx) + 1;
	**	to know, what size is 2-nd and 3-d parameter, we will
	**	use function get_arg_size()
	*/
	carriage->step = 2 + get_arg_size(types >> 6, 3) + get_arg_size((types >> 4) & 3, 3);//
	reg_num = vm->arena[(carriage->position + 2) % MEM_SIZE];
	//fprint("reg number %d\n", reg_num);
	if (is_invalid_parameters(types, reg_num))
		return ;
	value = get_bytes(vm->arena, (carriage->position + 3) % MEM_SIZE, \
			get_arg_size((types >> 4) & 3, 3), vm) % IDX_MOD;
	//fprint("value %d\n", (int)value);
	if ((types >> 4 & 3) == REG_CODE && (value > REG_NUMBER || value < 1))
		return ;
	if ((types >> 4 & 3) == IND_CODE)
		set_bytes(&carriage->reg[reg_num - 1], vm->arena, \
			calc_ind_address(carriage->position, value, vm), 4);
	else
		carriage->reg[value - 1] = carriage->reg[reg_num - 1];
}
