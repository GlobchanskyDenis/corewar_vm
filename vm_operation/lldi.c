/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:39:05 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/01 21:32:58 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static short	is_invalid_parameters(unsigned char types, int arg1, int arg2, \
		int reg_num)
{
	if (reg_num > REG_NUMBER || reg_num < 1)
	{
		//fprint("wrong reg number, skip the command\n");
		return (1);
	}	
	if ((types & 3) != 0 || (types >> 2 & 3) != REG_CODE || \
			(types >> 4 & 3) == 0 || (types >> 4 & 3) == IND_CODE || \
			types >> 6 == 0)
	{
		//fprint("wrong argument type, skip the command\n");
		//fprint("types  %d\n", types);
		return (1);
	}
	if ((types >> 6) == REG_CODE && (arg1 > REG_NUMBER || arg1 < 1))
		return (1);
	if ((types >> 4 & 3) == REG_CODE && (arg2 > REG_NUMBER || arg2 < 1))
		return (1);	
	return (0);
}

inline static void	log_lldi(t_car *carriage, int arg1, int arg2, short reg_num)
{
	if (!DEBUG_LOG)
		return ;
	fprint("P ");
	if (carriage->id < 1000)
		ft_putchar(' ');
	if (carriage->id < 100)
		ft_putchar(' ');
	if (carriage->id < 10)
		ft_putchar(' ');
	fprint("%d | lldi %d %d r%d\n", carriage->id, arg1, arg2, reg_num);
	fprint("       | -> load from %d + %d = %d (with pc %d)\n", arg1, arg2, \
			arg1 + arg2, carriage->position + (arg1 + arg2));
}

/*
**	Задача этой операции состоит в загрузке значения в регистр. Но её поведение
**	отличается в зависимости от типа первого аргумента:
**	Аргумент #1 — T_DIR
**	Если тип первого аргумента это T_DIR, то число переданное в качестве
**	аргумента будет воспринято «как есть».
**	Задачи операции:
**	Записать полученное число в регистр, который был передан в качестве
**	второго аргумента.
**	Если в регистр записали число 0, то установить значение carry в 1. Если
**	было записано не нулевое значение, то установить carry в 0.
**	Аргумент #1 — T_IND
**	Если тип первого аргумента это T_IND, то в данном случае число
**	представляет собой адрес.
**	В случае получения аргумента такого типа он обрезается по модулю —
**	<ПЕРВЫЙ_АРГУМЕНТ> % IDX_MOD.
**
**	 Take a random argument and a registry. Load the value of the first
**	argument in the registry. Its opcode is 10 in binary and it will change
**	the carry
*/

/*
**	OPERATION	LLDI (long load index)
**	OPCODE		ARGUMENT_1			ARGUMENT_2		ARGUMENT_3
**	14 (0x0E)	T_REG/T_DIR/T_IND	T_REG/T_DIR		T_REG
**
**	Загружает значение в регистр из аргумента 3. Значением являются 4 байта
**	считанные по адресу суммы значений аргументов 1 и 2. Без ограничения
**	по IDX_MOD.
*/

void		operation_lldi(t_car *carriage, t_vm *vm)
{
	unsigned char	types;
	short			reg_num;
	int				arg1;
	int				arg2;
	int				ind;

	if (!vm || !carriage)
		error_exit(vm, "operation lldi - empty ptr found");
	// fprint("operation lldi\tcycle %d\tposition %d\n", (int)vm->cw->cycle, (int)carriage->position);
	types = vm->arena[(carriage->position + 1) % MEM_SIZE];

	carriage->step = 2 + get_arg_size(types >> 6, 10) + \
			get_arg_size(types >> 4 & 3, 10) + get_arg_size(types >> 2 & 3, 10);

	reg_num = vm->arena[(carriage->position + 2 + get_arg_size(types >> 6, 10) \
			+ get_arg_size(types >> 4 & 3, 10)) % MEM_SIZE];
	
	arg1 = get_bytes(vm->arena, (carriage->position + 2) % MEM_SIZE, \
			get_arg_size(types >> 6, 10), vm);
	arg2 = get_bytes(vm->arena, (carriage->position + 2 + \
		get_arg_size(types >> 6, 10)) % MEM_SIZE, \
		get_arg_size(types >> 4 & 3, 10), vm);

	if (is_invalid_parameters(types, arg1, arg2, reg_num))
		return ;

	ind = get_argument(arg1, types >> 6, carriage, vm) + \
			get_argument(arg2, types >> 4 & 3, carriage, vm);
	//fprint("arg type: %d %d %d\n", (int)(types >> 6), (int)(types >> 4 & 3), (int)(types >> 2 & 3));
	//fprint("arg1 %d arg2 %d addr %d\n", arg1, arg2, ind);
	//fprint("arg1 %d arg2 %d\n", get_argument(arg1, get_arg_size(types >> 6, 10), carriage, vm), get_argument(arg2, get_arg_size(types >> 4 & 3, 10), carriage, vm));
	carriage->reg[reg_num - 1] = get_bytes(vm->arena, \
				calc_long_ind_address(carriage->position, ind, vm), 4, vm);
	carriage->carry = (carriage->reg[reg_num - 1]) ? 0 : 1;

	log_lldi(carriage, arg1, arg2, reg_num);
}
