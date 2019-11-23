/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_initialize_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:00:10 by jmaynard          #+#    #+#             */
/*   Updated: 2019/11/23 16:19:00 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

short		get_iscarry(unsigned c)
{
	if (c == 2 || (c >= 4 && c <= 8) || c == 13 || c == 14)
		return (1);
	return (0);
}

short		get_cycles_to_exe(unsigned c)
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

// short		get_step(unsigned c)
// {
// 	if (c == 1)
// 		return (4);
// 	if (c == 9 || c == 12 || c == 15)
// 		return (2);
// 	else if (c == 12)
// 		return (800);
// 	else if (c == 15)
// 		return (1000);
// 	else if (c == 16)
// 		return (2);
// }

void		init_command(t_vm *vm)
{
	short i;

	i = 0;
	while (i < COMMAND_AMOUNT)
	{
		vm->command_tab[i].carry = get_iscarry(i);
		vm->command_tab[i].cycles_to_exe = get_cycles_to_exe(i);
		i++;
	}
}