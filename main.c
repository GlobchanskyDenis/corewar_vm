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

t_vm	*create_vm_struct(int ac, char **av)
{
	t_vm	*s;
	short	i;

	if (!av)
		error_exit(NULL, "create_vm_struct - empty ptr found");
	if (!(s = (t_vm *)ft_memalloc(sizeof(t_vm))))
		error_exit(NULL, "create_vm_struct - malloc returned null");
	if (!(s->fd = (int *)ft_memalloc(sizeof(int) * (ac - 1))))
		error_exit(s, "create_vm_struct - malloc (arr) returned null");
	i = 0;
	while (i < ac - 1)
	{
		if ((s->fd[i] = open(av[i + 1], O_RDONLY)) < 3)
			error_exit(s, "cannot open file");
		if (read(s->fd[i], NULL, 0) < 0)
		{
			fprint("cannot take access to %s\n", av[i + 1]);
			error_exit(s, NULL);
		}
		i++;
	}
	return (s);
}

int		main(int ac, char **av)
{
	t_vm	*s;

	if (ac < 2 || ac > MAX_PLAYERS + 1)
		free_exit(NULL, "Wrong number of players");
	if (!(s = create_vm_struct(ac, av)))
		error_exit(s, "main - null ptr returned");
	free_exit(s, "its ok!");
	return (0);
}
