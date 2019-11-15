/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:16:17 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/13 12:16:18 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	check_name(t_vm *s, char *name)
{
	int		len;

	if (!s || !name)
		error_exit(s, "check name - null pointer found");
	len = (int)ft_strlen(name);
	if (len < 5 || name[len - 4] != '.' || \
			(name[len - 3] != 'c' && name[len - 3] != 'C') || \
			(name[len - 2] != 'o' && name[len - 2] != 'O') || \
			(name[len - 1] != 'r' && name[len - 1] != 'R'))
	{
		fprint("check name - '%s' - filename incorrect\n", name);
		free_exit(s, NULL);
	}
}

static void	carefully_open(t_pl *player, char *filename, t_vm *s)
{
	if (!player || !filename || !s)
		free_exit(s, "carefully open - empty ptr found");
	player->filename = filename;
	if ((player->fd = open(filename, O_RDONLY)) < 3)
	{
		fprint("Warning: cannot open file '%s'\n", filename);
		free_exit(s, NULL);
	}
	if (read(player->fd, NULL, 0) < 0)
	{
		fprint("Warning: cannot take access to '%s'\n", filename);
		free_exit(s, NULL);
	}
	check_name(s, filename);
}

static t_vm	*create_vm_struct(int ac, char **av)
{
	t_vm	*s;
	short	i;

	if (!av)
		error_exit(NULL, "create_vm_struct - empty ptr found");
	if (!(s = (t_vm *)ft_memalloc(sizeof(t_vm))))
		error_exit(NULL, "create_vm_struct - malloc returned null");
	if (!(s->player = (t_pl *)ft_memalloc(sizeof(t_pl) * (ac - 1))))
		error_exit(s, "create_vm_struct - malloc (arr) returned null");
	parse_flags(ac, av, s);
	i = -1;
	while (++i < (short)ac - 1 - s->flags_exists)
		carefully_open(&(s->player[i]), av[i + 1 + s->flags_exists], s);
	return (s);
}

int			main(int ac, char **av)
{
	t_vm	*s;

	if (ac < 2 || (ac < 3 && av[1][0] == '-') || ac > MAX_PLAYERS + 2 || \
			(ac > MAX_PLAYERS + 1 && av[1][0] != '-'))
		free_exit(NULL, "Wrong number of players - ./corewar <pl1> ...");
	if (!(s = create_vm_struct(ac, av)))
		error_exit(s, "main - null ptr returned");
	read_files(s);
	print_all(s);
	free_exit(s, "its ok!");
	return (0);
}
