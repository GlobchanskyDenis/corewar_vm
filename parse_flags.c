/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:26:00 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/14 19:26:02 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	turn_on_flag(char flag, t_vm *s)
{
	if (!s)
		error_exit(s, "turn on flag - empty ptr found");
	if (flag == GRAFIX)
		s->flag = s->flag | FLAG_GRAF;
	else if (flag == FL_1)
		s->flag = s->flag | FLAG_1;
	else if (flag == FL_2)
		s->flag = s->flag | FLAG_2;
}

static void	parser(short len, char *flags, t_vm *s)
{
	short	i;

	if (!flags || !s)
		error_exit(s, "parser - empty ptr found");
	i = 0;
	while (++i < len)
	{
		if (flags[i] != GRAFIX && flags[i] != FL_1 && flags[i] != FL_2)
		{
			fprint("Error: flag '%c' doesnt exists\n", flags[i]);
			error_exit(s, NULL);
		}
		if ((flags[i] == GRAFIX && s->flag & FLAG_GRAF) || \
				(flags[i] == FL_1 && s->flag & FLAG_1) || \
				(flags[i] == FL_2 && s->flag & FLAG_2))
		{
			fprint("Error: double flag '%c' inclusion found - '%s'\n", \
					flags[i], flags);
			error_exit(s, NULL);
		}
		turn_on_flag(flags[i], s);
	}
}

void		parse_flags(int ac, char **av, t_vm *s)
{
	size_t	len;

	if (!av || !s)
		error_exit(s, "parse flags - empty ptr found");
	if (av[1][0] != '-')
	{
		s->max_pl = (short)ac - 1;
		return ;
	}
	s->flags_exists = 1;
	s->max_pl = (short)ac - 2;
	len = ft_strlen(av[1]);
	if (len < 2 || len > 4)
	{
		fprint("Error: wrong flag length '%s'\n", av[1]);
		error_exit(s, NULL);
	}
	parser((short)len, av[1], s);
}
