#include "vm.h"

static void	carefully_open(t_pl *player, char **av, short i, t_vm *s)
{
	if (!player || !av || !s)
		free_exit(s, "carefully open - empty ptr found");
	player->filename = av[i];
	if ((player->fd = open(player->filename, O_RDONLY)) < 3)
	{
		fprint("Warning: cannot open file '%s'\n", player->filename);
		free_exit(s, NULL);
	}
	if (read(player->fd, NULL, 0) < 0)
	{
		fprint("Warning: cannot take access to '%s'\n", player->filename);
		free_exit(s, NULL);
	}
}

static void	check_other_flags(char **av, short i, t_vm *s)
{
	if (!av || !s)
		error_exit(s, "check other flags - empty ptr found");
	if (s->tab[i] == FLAG_GRAF)
	{
		if (s->flag & FLAG_GRAF)
			free_exit(s, "Warning: grafix flag double inclusion");
		s->flag = s->flag | FLAG_GRAF;
	}
	else if (s->tab[i] == FLAG_ARG && s->tab[i - 1] == FLAG_DUMP)
	{
		if (s->flag & FLAG_DUMP)
			free_exit(s, "Warning: dump flag double inclusion");
		s->flag = s->flag | FLAG_DUMP;
		s->dump = ft_atoi(av[i]);
		if (s->dump < 0)
			free_exit(s, "Warning: dump must be positive");
	}
}

static void	check_invalid_flag_cases(int ac, char **av, t_vm *s)
{
	short	i;

	if (!av || !s)
		error_exit(s, "check invalid flag cases - empty ptr found");
	i = 0;
	while (++i < (short)ac)
	{
		if (s->tab[i] == FLAG_DUMP && i + 1 < ac && s->tab[i + 1] != FLAG_ARG)
			free_exit(s, "Warning: dump flag without argument");
		if (s->tab[i] == FLAG_NBR && i + 1 < ac && s->tab[i + 1] != FLAG_ARG)
			free_exit(s, "Warning: number flag without argument");
		if (s->tab[i] == FLAG_ARG && s->tab[i - 1] != FLAG_DUMP && \
				s->tab[i - 1] != FLAG_NBR)
			free_exit(s, "Warning: argument without flag");
		if (s->tab[i] == FLAG_ARG && s->tab[i - 1] == FLAG_NBR && \
				(i + 1 == ac && s->tab[i + 1] != FLAG_FILE))
			free_exit(s, "Warning: flag nbr and argument without file");
	}
}

static void	assign_id_to_files(t_pl *player, short max_pl, t_vm *s)
{
	short	i;
	short	j;
	short	id;

	if (!s)
		error_exit(s, "assign id to files - empty ptr found");
	id = 1;
	i = -1;
	while (++i < max_pl)
	{
		j = -1;
		while (++j < max_pl)
		{
			if (id == player[j].id)
			{
				id++;
				j = 0;
			}
		}
		if (player[i].id == 0)
			player[i].id = id;
	}
}

void		parse_flags(int ac, char **av, t_vm *s)
{
	short	i;
	short	j;

	if (!s || !s->tab|| !av)
		error_exit(s, "fill vm struct - empty ptr found");
	j = 0;
	i = 0;
	while (++i < (short)ac)
	{
		if (s->tab[i] == FLAG_FILE)
		{
			carefully_open(&(s->player[j]), av, i, s);
			if (i > 1 && s->tab[i - 2] == FLAG_NBR && s->tab[i - 1] == FLAG_ARG)
			{
				s->player[j].id = ft_atoi(av[i - 1]);
				if (s->player[j].id < 1)
					free_exit(s, "Warning: id must be bigger than 0");
				s->flag = s->flag | FLAG_NBR;
			}
			j++;
		}
		check_other_flags(av, i, s);
	}
	check_invalid_flag_cases(ac, av, s);
	assign_id_to_files(s->player, s->max_pl, s);
}