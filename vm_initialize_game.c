/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_initialize_game.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:25:51 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/12/22 21:16:04 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		initialize_operations_array(t_vm *vm)
{
	vm->operation[0] = &operation_null;
	vm->operation[OP_LIVE] = &operation_live;
	vm->operation[OP_LD] = &operation_ld;
	vm->operation[OP_ST] = &operation_st;
	vm->operation[OP_ADD] = &operation_add;
	vm->operation[OP_SUB] = &operation_sub;
	vm->operation[OP_AND] = &operation_and;
	vm->operation[OP_OR] = &operation_or;
	vm->operation[OP_XOR] = &operation_xor;
	vm->operation[OP_ZJMP] = &operation_zjmp;
	vm->operation[OP_LDI] = &operation_ldi;
	vm->operation[OP_STI] = &operation_sti;
	//vm->operation[OP_FORK] = &op_fork;
	//vm->operation[OP_LLD] = &op_lld;
	//vm->operation[OP_LLDI] = &op_lldi;
	//vm->operation[OP_LFORK] = &op_lfork;
	//vm->operation[OP_AFF] = &op_aff;
}

/*
**	Function copy players code to the Arena, creates carriages for them
**	and fills them
*/

void		initialize_game(unsigned char *arena, t_vm *vm)
{
	short	step;
	short	i;
	t_car	*carriage;

	if (!arena || !vm)
		error_exit(vm, "initialize game - empty ptr found");
	step = MEM_SIZE / vm->max_pl;
	i = -1;
	while (++i < vm->max_pl)
	{
		ft_memcpy(&(arena[i * step]), vm->player[i].code, \
				vm->player[i].codesize);
		carriage = add_new_carriage_in_stack(vm);
		carriage->position = i * step;
		carriage->reg[0] = -vm->player[i].id;
		carriage_read_command(carriage, vm);
	}
}
