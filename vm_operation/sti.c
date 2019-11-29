/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:33:08 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/29 20:15:35 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

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

	if (!vm || !carriage)
		error_exit(vm, "operation sti - empty ptr found");
	fprint("operation sti\n");
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
	/*
	**	! I need to use array of cycles_to_exe before call this function
	**	carriage->cycles_to_exe = 25;
	*/
	carriage->carry = 1;
	reg_num = vm->arena[(carriage->position + 2) % MEM_SIZE];
	if (reg_num > REG_NUMBER)
		error_exit(vm, "operation sti - too big register found");
	arg2 = get_bytes(vm->arena, (carriage->position + 3) % MEM_SIZE, \
			get_arg_size((types >> 4) & 3, 11), vm);
	arg3 = get_bytes(vm->arena, (carriage->position + 3 + \
			get_arg_size((types >> 4) & 3, 11)) % MEM_SIZE, \
			get_arg_size((types >> 2) & 3, 11), vm);
	/*
	**	if ((types >> 4) & 3 == DIR_CODE && (types >> 2) & 3 == DIR_CODE)
	*/
	set_bytes(&carriage->reg[reg_num], vm->arena, (arg2 + arg3) % \
			IDX_MOD % MEM_SIZE, 1);
	fprint("operation sti ended\n");
}

/*
**	reg = get_arg(carriage, vm, types / 1000, 2);
**	arg2 = get_arg(carriage, vm, (types / 100) % 10, 2);
**	arg3 = get_arg(carriage, vm, (types / 10) % 10, 2);
**	adr = (carriage->position + (arg2 + arg3) % IDX_MOD) % MEM_SIZE;
**	ft_memcpy(&vm->arena[adr], &reg, REG_SIZE);//// PIZDETS NAXYI YA PISAL FYNKTSIYU SET_BYTE ?????
*/