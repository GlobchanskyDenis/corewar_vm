/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_dump_arena.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 20:47:56 by bsabre-c          #+#    #+#             */
/*   Updated: 2020/01/06 16:11:46 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_arena_hex(short nbr)
{
	if (nbr == 0)
		ft_putnbr(nbr);
	else
	{
		if (nbr < 10)
			ft_putnbr(nbr);
		else if (nbr == 10)
			ft_putchar('a');
		else if (nbr == 11)
			ft_putchar('b');
		else if (nbr == 12)
			ft_putchar('c');
		else if (nbr == 13)
			ft_putchar('d');
		else if (nbr == 14)
			ft_putchar('e');
		else if (nbr == 15)
			ft_putchar('f');
		else
			ft_putstr("|invalid_nbr|");
	}
}

static void	set_color(short i, short *arena_owner, t_car *carriage)
{
	if (!carriage || !arena_owner)
		return ;
	while (carriage && carriage->position != i)
		carriage = carriage->next;
	if (carriage && carriage->owner_id % 5 == 1)
		fprint("\x1b[30;2;%dm", 102);
	else if (carriage && carriage->owner_id % 5 == 2)
		fprint("\x1b[30;2;%dm", 104);
	else if (carriage && carriage->owner_id % 5 == 3)
		fprint("\x1b[30;2;%dm", 101);
	else if (carriage && carriage->owner_id % 5 == 4)
		fprint("\x1b[30;2;%dm", 106);
	else if (arena_owner[i] % 5 == 1)
		fprint("\x1b[%dm", 32);
	else if (arena_owner[i] % 5 == 2)
		fprint("\x1b[%dm", 34);
	else if (arena_owner[i] % 5 == 3)
		fprint("\x1b[%dm", 31);
	else if (arena_owner[i] % 5 == 4)
		fprint("\x1b[%dm", 36);
	else
		ft_putstr("\x1b[2m");
}

static void	print_iterator_nbr(short i)
{
	fprint("0x");
	print_arena_hex(i >> 12 & 15);
	print_arena_hex(i >> 8 & 15);
	print_arena_hex(i >> 4 & 15);
	print_arena_hex(i & 15);
	fprint(" : ");
}

void		dump_arena(unsigned char *arena, t_vm *vm)
{
	short	i;
	short	hex1;
	short	hex2;

	if (!arena || !vm)
		error_exit(vm, "print arena - empty ptr found");
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (!(i % DUMP_OCTETS_PER_LINE) && i != 0)
			ft_putchar('\n');
		if (!(i % DUMP_OCTETS_PER_LINE))
			print_iterator_nbr(i);
		hex1 = (short)(arena[i] >> 4);
		hex2 = (short)(arena[i] & 0xF);
		if (vm->flag & FLAG_COLOR_DUMP)
			set_color(i, vm->arena_owner, vm->car);
		print_arena_hex(hex1);
		print_arena_hex(hex2);
		if (vm->flag & FLAG_COLOR_DUMP)
			ft_putstr("\x1b[0m");
		ft_putchar(' ');
	}
	ft_putchar('\n');
}
