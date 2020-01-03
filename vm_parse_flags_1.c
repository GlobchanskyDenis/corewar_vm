/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parse_flags_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:26:00 by bsabre-c          #+#    #+#             */
/*   Updated: 2020/01/03 13:46:26 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
	if (!ft_strcmp(src, GRAFIX))
		return (FLAG_GRAF);
	if (!ft_strcmp(src, DUMP))
		return (FLAG_DUMP);
	if (!ft_strcmp(src, NBR))
		return (FLAG_NBR);
	if (ft_isall_digit(src))
		return (FLAG_ARG);
	if (is_file(src, tab))
		return (FLAG_FILE);
	if (!ft_strcmp(src, AFF))
		return (FLAG_AFF);
	if (!ft_strcmp(src, LOG))
		return (FLAG_LOG);
	if (!ft_strcmp(src, COLOR_DUMP))
		return (FLAG_COLOR_DUMP);
	if (!ft_strcmp(src, INFO_DUMP))
		return (FLAG_INFO_DUMP);
	if (!ft_strcmp(src, FULL_DUMP))
		return (FLAG_FULL_DUMP);
	fprint("Warning: unknown argument '%s'\n", src);
	free(tab);
	exit(0);
}

/*
**	dst is array of flags, that fits in size with array of arguments **av
**	and explains, what data is each argument consists of.
**	In dst[0] stores amount of players
*/

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
