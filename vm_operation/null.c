#include "../vm.h"

void	op_null(t_car *carriage, t_vm *vm)
{
	if (!vm || !carriage)
		error_exit(vm, "operation null - empty ptr found");
	fprint("operation null\n");
	carriage->cycles_to_exe = 1;
	carriage->step = 1;
}