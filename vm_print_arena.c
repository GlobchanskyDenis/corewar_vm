/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print_arena.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 20:47:56 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/12/21 13:22:40 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_arena_hex(int nbr)
{
	if (nbr == 0)
		ft_putnbr(nbr);
	else
	{
		//ft_putstr("\x1b[1;30;41m");
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
		//ft_putstr("\x1b[0m");
	}
}

// static void	print_arena_code(void *code, short size, t_vm *vm)
// {
// 	short	i;
// 	int		hex1;
// 	int		hex2;

// 	if (!code || !vm)
// 		error_exit(vm, "print all - empty ptr found");
// 	i = -1;
// 	while (++i < size)
// 	{
// 		hex1 = (int)(((unsigned char *)code)[i] >> 4);		
// 		hex2 = (int)(((unsigned char *)code)[i]) & 0xF;
// 		if (!hex1 && !hex2)
// 			ft_putstr("\x1b[1;30;1m");
// 		else
// 			ft_putstr("\x1b[1;1;1m");
// 		print_arena_hex(hex1);
// 		print_arena_hex(hex2);
// 		ft_putchar(' ');
// 		ft_putstr("\x1b[0m");
// 	}
// 	ft_putchar('\n');
// }

void		set_color(short i, int hex, t_car *carriage)
{
	short	carriage_set;

	if (!carriage)
		return ;
	carriage_set = 0;
	while (carriage)
	{
		if (carriage->position == i)
			carriage_set = 1;
		carriage = carriage->next;
	}
	if (carriage_set == 1 && hex)
		ft_putstr("\x1b[1;1;41m");
	else if (carriage_set == 1 && !hex)
		ft_putstr("\x1b[1;2;41m");
	else if (hex)
		ft_putstr("\x1b[1;1;1m");
	else
		ft_putstr("\x1b[1;30;1m");
}

void		print_arena(unsigned char *arena, t_vm *vm)
{
	short	i;
	int		hex1;
	int		hex2;

	if (!arena || !vm)
		error_exit(vm, "print arena - empty ptr found");
	fprint("ARENA:\n");
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (!(i % 64) && i != 0)
			ft_putchar('\n');
		hex1 = (int)(arena[i] >> 4);		
		hex2 = (int)(arena[i] & 0xF);
		set_color(i, hex1 + hex2, vm->car);
		print_arena_hex(hex1);
		print_arena_hex(hex2);
		ft_putstr("\x1b[0m");
		ft_putchar(' ');
	}
	ft_putchar('\n');
}