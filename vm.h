/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:18:03 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/13 12:21:44 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H

# define VM_H
# define MAX_BUF	PROG_NAME_LENGTH + CHAMP_MAX_SIZE + COMMENT_LENGTH + 1200
# define CHAMP_EXEC_CODE_SIZE	4
# define FLAG_GRAF	(1 << 0)
# define FLAG_DUMP	(1 << 1)
# define FLAG_NBR	(1 << 2)
# define GRAFIX		"-graf"
# define DUMP		"-dump"
# define NBR		"-n"
# define FLAG_ARG	(1 << 3)
# define FLAG_FILE	(1 << 4)
# include "libft/libft.h"
# include "op.h"

typedef struct	s_pl
{
	int		fd;
	short	id;
	short	codesize;
	char	*filename;
	char	*name;
	char	*comment;
	char	*code;
}				t_pl;

typedef struct	s_vm
{
	t_pl	*player;
	short	*tab;
	short	max_pl;
	short	flag;
	int		dump;
}				t_vm;

void			error_exit(t_vm *s, char *message);		// free_exit.c
void			free_exit(t_vm *s, char *message);		// free_exit.c

short			*preliminary_parse_flags(int ac, char **av);// parse_flags_1.c
void			parse_flags(int ac, char **av, t_vm *s);	// parse_flags_2.c

void			extract_data(t_pl *player, char *buf, t_vm *s);	// extract.c

void			read_files(t_vm *s);	// reader.c

void			print_all(t_vm *s);		// temp.c



#endif
