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
/*
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
*/
static void	sort_players_by_id(t_pl *player, short max_pl, t_vm *s)
{
	short	i;
	t_pl	tmp_player;

	if (!s || !player)
		error_exit(s, "sort players by id - empty ptr found");
	i = -1;
	while(++i < max_pl - 1)
	{
		if (player[i].id > player[i + 1].id)
		{
			tmp_player = player[i + 1];
			player[i + 1] = player[i];
			player[i] = tmp_player;
			i = -1;
		}
	}
}

static t_vm	*create_vm_struct(short *tab)
{
	t_vm	*s;

	if (!tab)
		error_exit(NULL, "create_vm_struct - empty ptr found");
	if (!(s = (t_vm *)ft_memalloc(sizeof(t_vm))))
		error_exit(NULL, "create_vm_struct - malloc returned null");
	if (!(s->player = (t_pl *)ft_memalloc(sizeof(t_pl) * tab[0])))
		error_exit(s, "create_vm_struct - malloc (arr) returned null");
	s->tab = tab;
	s->max_pl = tab[0];
	return (s);
}

int			main(int ac, char **av)
{
	t_vm	*s;

	if (ac < 2 || (ac < 3 && av[1][0] == '-') || ac > MAX_ARGS_NUMBER + 10) // + 1
	{
		fprint("Wrong number of parameters. ");
		fprint("Flags: [-grafix] [-dump nbr_cycles]\n");
		free_exit(NULL, "Use: ./corewar [-flags] [[-n number]champion] ...");
	}
	if (!(s = create_vm_struct(preliminary_parse_flags(ac, av))))
		error_exit(s, "main - null ptr returned");
	parse_flags(ac, av, s);
	sort_players_by_id(s->player, s->max_pl, s);
	read_files(s);
	print_all(s);
	free_exit(s, "its ok!");
	return (0);
}
