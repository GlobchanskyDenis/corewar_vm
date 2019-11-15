/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 00:16:51 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/15 00:16:53 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void print_hex(int nbr)
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

static void	print_code(char *code, short size, t_vm *s)
{
	short	i;
	int		hex;

	if (!code || !s)
		error_exit(s, "print all - empty ptr found");
	fprint("code:\t\t");
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

void	print_all(t_vm *s)
{
	short	i;

	if (!s)
		error_exit(s, "print all - empty ptr found");
	fprint("=======================================\n\t\tPRINT ALL\n");
	fprint("max_pl (number of players)\t%d\n", (int)s->max_pl);
	fprint("flags_exists\t\t\t%d\n", (int)s->flags_exists);
	fprint("grafix flag\t\t\t%s\n", (s->flag & FLAG_GRAF) ? "ON" : "OFF");
	fprint("flag 1\t\t\t\t%s\n", (s->flag & FLAG_1) ? "ON" : "OFF");
	fprint("flag 2\t\t\t\t%s\n", (s->flag & FLAG_2) ? "ON" : "OFF");
	i = -1;
	while (s->player && ++i < s->max_pl)
	{
		fprint("-- player %d: --\n", (int)(i + 1));
		fprint("filename\t'%s'\n", s->player[i].filename);
		fprint("fd\t\t%d\n", s->player[i].fd);
		fprint("name:\t\t'%s'\n", s->player[i].name);
		fprint("comment:\t'%s'\n", s->player[i].comment);
		fprint("codesize:\t%d\n", s->player[i].codesize);
		print_code(s->player[i].code, s->player[i].codesize, s);
	}
	fprint("---------------------------------------\n");
}
