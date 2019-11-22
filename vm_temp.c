/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_temp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 00:16:51 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/15 00:16:53 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_hex(int nbr)
{
	if (nbr < 10)
		ft_putnbr(nbr);
	else if (nbr == 10)
		ft_putchar('A');
	else if (nbr == 11)
		ft_putchar('B');
	else if (nbr == 12)
		ft_putchar('C');
	else if (nbr == 13)
		ft_putchar('D');
	else if (nbr == 14)
		ft_putchar('E');
	else if (nbr == 15)
		ft_putchar('F');
	else
		ft_putstr("|invalid_nbr|");
}

static void	print_code(char *code, short size, t_vm *vm)
{
	short	i;
	int		hex;

	if (!code || !vm)
		error_exit(vm, "print all - empty ptr found");
	i = -1;
	while (++i < size)
	{
		hex = (int)((unsigned char)code[i] >> 4);
		print_hex(hex);
		hex = (int)((unsigned char)code[i]) & 0xF;
		print_hex(hex);
		ft_putchar(' ');
	}
	ft_putchar('\n');
}

static void	print_carriages(t_car *car, t_vm *vm)
{
	short	i;

	if (!vm || !car)
		error_exit(vm, "print carriages - empty ptr found");
	while (car)
	{
		fprint("-- carriage --\ncarry\t\t%d\n", car->carry);
		fprint("step\t\t%d\ncommand\t\t%d\n", car->step, car->command);
		fprint("cycles to exe\t%d\n", car->cycles_to_exe);
		fprint("position\t\t%d\n", car->position);
		fprint("last live cycle\t\t%d\nREGISTERS:\n", car->last_live_cycle);
		i = -1;
		while (++i < REG_NUMBER)
			fprint("%d\t", car->reg[i]);
		fprint("\n");
		print_code((char *)(car->reg), 4 * REG_NUMBER, vm);
		car = car->next;
	}
}

static void	print_arena(unsigned char *arena, t_vm *vm)
{
	short	i;

	if (!arena || !vm)
		error_exit(vm, "print arena - empty ptr found");
	fprint("ARENA:\n");
	i = -1;
	while (++i < 64)
		print_code((char *)(&(arena[i * 64])), 64, vm);
}

void		print_all(t_vm *vm)
{
	short	i;

	if (!vm)
		error_exit(vm, "print all - empty ptr found");
	fprint("=======================================\n\t\tPRINT ALL\n");
	fprint("max_pl (number of players)\t%d\n", (int)vm->max_pl);
	fprint("dump\t\t\t\t%d\n", (int)vm->dump);
	fprint("grafix flag\t\t\t%s\n", (vm->flag & FLAG_GRAF) ? "ON" : "OFF");
	fprint("dump flag\t\t\t%s\n", (vm->flag & FLAG_DUMP) ? "ON" : "OFF");
	fprint("nbr flag\t\t\t%s\n", (vm->flag & FLAG_NBR) ? "ON" : "OFF");
	i = -1;
	while (vm->player && ++i < vm->max_pl)
	{
		fprint("-- player %d: --\n", (int)(i + 1));
		fprint("filename\t'%s'\n", vm->player[i].filename);
		fprint("fd\t\t%d\n", vm->player[i].fd);
		fprint("id\t\t%d\n", (int)vm->player[i].id);
		fprint("name:\t\t'%s'\n", vm->player[i].name);
		fprint("comment:\t'%s'\n", vm->player[i].comment);
		fprint("codesize:\t%d\ncode:\t\t", vm->player[i].codesize);
		print_code(vm->player[i].code, vm->player[i].codesize, vm);
	}
	(vm->car) ? print_carriages(vm->car, vm) : fprint("carriages not found\n");
	(vm->arena) ? print_arena(vm->arena, vm) : fprint("arena not found\n");
	fprint("---------------------------------------\n");
}
