/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_initialize_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:00:10 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/24 18:47:23 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static short	get_iscarry(unsigned c)
{
	if (c == 2 || (c >= 4 && c <= 8) || c == 13 || c == 14)
		return (1);
	return (0);
}

static short	get_cycles_to_exe(unsigned c)
{
	if (c == 2 || c == 3)
		return (5);
	else if (c >= 6 && c <= 8)
		return (6);
	else if (c == 1 || c == 4 || c == 5 || c == 13)
		return (10);
	else if (c == 9)
		return (20);
	else if (c == 10 || c == 11)
		return (25);
	else if (c == 14)
		return (50);
	else if (c == 12)
		return (800);
	else if (c == 15)
		return (1000);
	else if (c == 16)
		return (2);
	return (1);
}

void		set_func(t_vm *vm)
{
	vm->op[1] = &op_live;
	vm->op[2] = &op_ld;
	vm->op[3] = &op_st;
	vm->op[4] = &op_add;
	vm->op[5] = &op_sub;
	vm->op[6] = &op_and;
	vm->op[7] = &op_or;
	vm->op[8] = &op_xor;
	vm->op[9] = &op_zjmp;
	vm->op[10] = &op_ldi;
	vm->op[11] = &op_sti;
	vm->op[12] = &op_fork;
	vm->op[13] = &op_lld;
	vm->op[14] = &op_lldi;
	vm->op[15] = &op_lfork;
	vm->op[16] = &op_aff;
	vm->op[0] = NULL;
}

void		init_command(t_vm *vm)
{
	short i;

	i = 0;
	set_func(vm);
	while (i < COMMAND_AMOUNT)
	{
		vm->command_tab[i].carry = get_iscarry(i);
		vm->command_tab[i].cycles_to_exe = get_cycles_to_exe(i);
		i++;
	}
}