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
/*
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
*/

static short	count_files(short ac, short *tab)
{
	short	i;
	short	count;

	if (!tab)
		error_exit(NULL, "count files - empty ptr found");
	count = 0;
	i = 0;
	while (++i < ac)
	{
		if (tab[i] == FLAG_FILE)
			count++;
	}
	if (count == 0 || count > MAX_PLAYERS)
	{
		free(tab);
		fprint("Warning: incorrect number of players\n");
		fprint("found %d, must be > 0 and <= %d\n", (int)count, MAX_PLAYERS);
		exit(0);
	}
	return (count);
}

static short	is_all_digits(char *src, short *tab)
{
	char	*tmp;
	int		nbr;

	if (!src || !tab)
	{
		if (tab)
			free(tab);
		error_exit(NULL, "is all digits - empty ptr found");
	}
	nbr = ft_atoi(src);
	if (!(tmp = ft_itoa(nbr)))
	{
		free(tab);
		error_exit(NULL, "is all digits - malloc returned null");
	}
	if (ft_strcmp(src, tmp))
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

static short	is_file(char *src, short *tab)
{
	size_t	len;

	if (!src || !tab)
	{
		if (tab)
			free(tab);
		error_exit(NULL, "is_file - empty ptr found");
	}
	len = ft_strlen(src);
	if (len < 5 || src[len - 4] != '.' || \
			(src[len - 3] != 'c' && src[len - 3] != 'C') || \
			(src[len - 2] != 'o' && src[len - 2] != 'O') || \
			(src[len - 1] != 'r' && src[len - 1] != 'R'))
		return (0);
	return (1);
}

static short	parse_argument(char *src, short *tab)
{
	if (!src || !tab)
	{
		if (tab)
			free(tab);
		error_exit(NULL, "parse argument - empty ptr found");
	}
	if (!ft_strcmp(src, GRAFIX))
		return (FLAG_GRAF);
	if (!ft_strcmp(src, DUMP))
		return (FLAG_DUMP);
	if (!ft_strcmp(src, NBR))
		return (FLAG_NBR);
	if (is_all_digits(src, tab))
		return (FLAG_ARG);
	if (is_file(src, tab))
		return (FLAG_FILE);
	fprint("Warning: unknown argument '%s'\n", src);
	free(tab);
	exit(0);
}

short			*preliminary_parse_flags(int ac, char **av)
{
	short	*dst;
	short	i;

	if (!av)
		error_exit(NULL, "parse flags - empty ptr found");
	if (!(dst = (short *)ft_memalloc(sizeof(short) * ac)))
		error_exit(NULL, "parse flags - malloc returned null");
	i = 0;
	while (++i < ac)
		dst[i] = parse_argument(av[i], dst);
	dst[0] = count_files((short)ac, dst);
	return (dst);
}