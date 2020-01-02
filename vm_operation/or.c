/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <bsabre-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:26:18 by jmaynard          #+#    #+#             */
/*   Updated: 2020/01/01 21:33:05 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static short	is_invalid_parameters(unsigned char types, int arg1, int arg2, \
		int reg)
{	
	if ((types & 3) != 0 || (types >> 2 & 3) != REG_CODE || \
			(types >> 4 & 3) == 0 || (types >> 6) == 0)
	{
		//fprint("wrong argument type, skip the command\n");
		//fprint("types = %d\tshould be %d\n", types, (REG_CODE << 6) | (REG_CODE << 4) | (REG_CODE << 2));
		return (1);
	}
	if (reg > REG_NUMBER || reg < 1)
	{
		//fprint("wrong reg number, skip the command\n");
		//fprint("reg1 %d\n", reg);
		return (1);
	}
	if ((types >> 6) == REG_CODE && (arg1 > REG_NUMBER || arg1 < 1))
		return (1);
	if ((types >> 4 & 3) == REG_CODE && (arg2 > REG_NUMBER || arg2 < 1))
		return (1);
	return (0);
}

static void	log_or(short carriage_id, int arg1, int arg2, short reg_num)
{
	if (!DEBUG_LOG)
		return ;
	fprint("P ");
	if (carriage_id < 1000)
		ft_putchar(' ');
	if (carriage_id < 100)
		ft_putchar(' ');
	if (carriage_id < 10)
		ft_putchar(' ');
	fprint("%d | or %d %d r%d\n", carriage_id, arg1, arg2, reg_num);
}

/*
**	OPERATION	OR (bitwise OR)
**	OPCODE		ARGUMENT_1			ARGUMENT_2			ARGUMENT_3
**	7			T_REG/T_DIR/T_IND	T_REG/T_DIR/T_IND	T_REG
**
**	Записывает в регистр заданный аргументом 3 результат побитового ИЛИ
**	аргументов 1 и 2. Меняет carry.
*/

void	operation_or(t_car *carriage, t_vm *vm)
{
	int		types;
	int		arg1;
	int		arg2;
	int		reg_num;

	if (!vm || !carriage)
		error_exit(vm, "operation or - empty ptr found");
	// fprint("operation or\tcycle %d\tposition %d\n", (int)vm->cw->cycle, (int)carriage->position);
	types = vm->arena[(carriage->position + 1) % MEM_SIZE];

	carriage->step = 2 + get_arg_size(types >> 6, 6) + \
			get_arg_size(types >> 4 & 3, 6) + \
			get_arg_size(types >> 2 & 3, 6);

	reg_num = vm->arena[(carriage->position + 2 + get_arg_size(types >> 6, 6) + \
			get_arg_size(types >> 4 & 3, 6)) % MEM_SIZE];

	arg1 = get_bytes(vm->arena, carriage->position + 2, \
			get_arg_size(types >> 6, 6), vm);
	arg2 = get_bytes(vm->arena, carriage->position + 2 + \
			get_arg_size(types >> 6, 6), get_arg_size(types >> 4 & 3, 6), vm);
	
	if (is_invalid_parameters(types, arg1, arg2, reg_num))
		return ;

	carriage->reg[reg_num - 1] = get_argument(arg1, types >> 6, carriage, vm) \
			| get_argument(arg2, types >> 4 & 3, carriage, vm);

	carriage->carry = (carriage->reg[reg_num - 1]) ? 0 : 1;

	log_or(carriage->id, arg1, arg2, reg_num);
}
