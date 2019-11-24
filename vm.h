/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:18:03 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/11/23 16:24:44 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H

# define VM_H
# include "libft/libft.h"
# include "op.h"
# define MAX_BUF	PROG_NAME_LENGTH + CHAMP_MAX_SIZE + COMMENT_LENGTH + 1200
# define CHAMP_EXEC_CODE_SIZE	4
# define FLAG_GRAF				(1 << 0)
# define FLAG_DUMP				(1 << 1)
# define FLAG_NBR				(1 << 2)
# define FLAG_ARG				(1 << 3)
# define FLAG_FILE				(1 << 4)
# define GRAFIX					"-graf"
# define DUMP					"-dump"
# define NBR					"-n"
# define COMMAND_AMOUNT			17
# define USHRT_MAX				65535
# define UINT_MAX				4294967295

typedef struct	s_pl
{
	int				fd;
	unsigned short	id;
	short			codesize;
	char			*filename;
	char			*name;
	char			*comment;
	char			*code;
	size_t			last_live_cycle;
}				t_pl;

typedef struct	s_car
{
	short			carry;
	short			step;
	short			cycles_to_exe;
	short			command;
	short			position;
	unsigned int	*reg;
	struct s_car	*next;
	size_t			last_live_cycle;
}				t_car;

typedef struct	s_command
{
	short			carry;
	short			cycles_to_exe;
}				t_command;

typedef struct	s_vm
{
	t_pl			*player;
	short			*tab;
	unsigned char	*arena;
	t_car			*car;
	t_command		*command_tab;
	short			max_pl;
	short			flag;
	short			cycles_to_die;
	size_t			dump;
	size_t			cycle;
	int				lives_for_cycle;
}				t_vm;

void			error_exit(t_vm *s, char *message);
void			free_exit(t_vm *s, char *message);
short			*preliminary_parse_flags(int ac, char **av);
void			parse_flags(int ac, char **av, t_vm *s);
void			extract_data(t_pl *player, char *buf, t_vm *s);
void			read_files(t_vm *s);
void			print_all(t_vm *s);
size_t			extract_number(const char *str, t_vm *vm);
void			initialize_all(int ac, char **av, t_vm *vm);
void			initialize_game(unsigned char *arena, t_vm *vm);
t_car			*add_new_carriage_in_stack(t_vm *vm);
t_car			*carriage_duplicate(t_car *carriage, t_vm *vm);
void			carriage_read_command(t_car *carriage, t_vm *vm);
void			carriage_make_step(t_car *carriage, t_vm *vm);
void			find_n_del_carriage(t_car *carriage, t_vm *vm);
void			init_command(t_vm *vm);
void			*get_bytes(void *dst, unsigned char *arena, short start, \
		short len);
void			set_bytes(void *src, unsigned char *arena, short start, \
		short len);
short			get_info(unsigned char byte, short arg_nbr);

#endif
