/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_dump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 00:16:51 by bsabre-c          #+#    #+#             */
/*   Updated: 2020/01/03 19:33:41 by bsabre-c         ###   ########.fr       */
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

static void	print_code(short id, void *code, short size, t_vm *vm)
{
	short	i;
	int		hex;

	if (!code || !vm)
		error_exit(vm, "print all - empty ptr found");
	if (vm->flag & FLAG_COLOR_DUMP && id % 5 == 1)
		fprint("\x1b[%dm", 32);
	else if (vm->flag & FLAG_COLOR_DUMP && id % 5 == 2)
		fprint("\x1b[%dm", 34);
	else if (vm->flag & FLAG_COLOR_DUMP && id % 5 == 3)
		fprint("\x1b[%dm", 31);
	else if (vm->flag & FLAG_COLOR_DUMP && id % 5 == 4)
		fprint("\x1b[%dm", 36);
	i = -1;
	while (++i < size)
	{
		hex = (int)(((unsigned char *)code)[i] >> 4);
		print_hex(hex);
		hex = (int)(((unsigned char *)code)[i]) & 0xF;
		print_hex(hex);
		ft_putchar(' ');
	}
	if (vm->flag & FLAG_COLOR_DUMP)
		ft_putstr("\x1b[0m");
}

static void	print_carriages(t_car *car, t_vm *vm)
{
	short	i;

	if (!vm || !car)
		error_exit(vm, "print carriages - empty ptr found");
	while (car)
	{
		fprint("======= carriage =======\ncarry\t\t%d\t", car->carry);
		fprint("step\t\t%d\ncommand\t\t%d\t", car->step, car->command);
		fprint("cycles to exe\t%d\n", car->cycles_to_exe);
		fprint("position\t%d\tid\t\t%d\n", car->position, car->id);
		fprint("owner id\t%d\t", car->owner_id);
		fprint("last live cycle\t%d\nREGISTERS:\n", car->last_live_cycle);
		i = -1;
		while (++i < REG_NUMBER)
			fprint("%d\t\t", car->reg[i]);
		fprint("\n");
		i = -1;
		while (++i < REG_NUMBER)
		{
			print_code(car->owner_id, (char *)(&(car->reg[i])), 4, vm);
			ft_putchar('\t');
		}
		fprint("\n========================\n");
		car = car->next;
	}
}

static void	print_players(t_vm *vm)
{
	short	i;

	if (!vm)
		error_exit(vm, "print all - empty ptr found");
	i = -1;
	while (vm->player && ++i < vm->max_pl)
	{
		fprint("======= player %d: ======\n", (int)(i + 1));
		fprint("filename\t'%s'\n", vm->player[i].filename);
		fprint("fd\t\t%d\n", vm->player[i].fd);
		fprint("id\t\t%d\n", (int)vm->player[i].id);
		fprint("name:\t\t'%s'\n", vm->player[i].name);
		fprint("comment:\t'%s'\n", vm->player[i].comment);
		fprint("codesize:\t%d\ncode:\t\t", vm->player[i].codesize);
		print_code(vm->player[i].id, vm->player[i].code, \
				vm->player[i].codesize, vm);
		ft_putchar('\n');
	}
}

void		dump(t_vm *vm)
{
	if (!vm)
		error_exit(vm, "print all - empty ptr found");
	if (vm->flag & FLAG_INFO_DUMP)
	{
		fprint("=======================================\n\t\tFULL DUMP\n");
		fprint("number of players\t%d\n", (int)vm->max_pl);
		fprint("dump cycle\t\t%d\n", (int)vm->dump);
		fprint("grafix flag\t\t%s\n", (vm->flag & FLAG_GRAF) ? "ON" : "OFF");
		fprint("nbr flag\t\t%s\n", (vm->flag & FLAG_NBR) ? "ON" : "OFF");
		fprint("log flag\t\t%s\n", (vm->flag & FLAG_LOG) ? "ON" : "OFF");
		fprint("aff flag\t\t%s\n", (vm->flag & FLAG_AFF) ? "ON" : "OFF");
		fprint("dump flag\t\t%s\n", (vm->flag & FLAG_DUMP) ? "ON" : "OFF");
		fprint("\tcolor\t\t%s\n", (vm->flag & FLAG_COLOR_DUMP) ? "ON" : "OFF");
		fprint("\tinfo\t\t%s\n", (vm->flag & FLAG_INFO_DUMP) ? "ON" : "OFF");
		if (vm->player)
			print_players(vm);
		if (vm->car)
			print_carriages(vm->car, vm);
	}
	if (vm->arena)
		dump_arena(vm->arena, vm);
	free_exit(vm, NULL);
}
