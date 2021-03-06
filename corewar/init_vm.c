#include	"include.h"

void	init_instr_c_tab(t_vm *vm)
{
  vm->instr_nb_cycle[0] = 10;
  vm->instr_nb_cycle[1] = 5;
  vm->instr_nb_cycle[2] = 5;
  vm->instr_nb_cycle[3] = 10;
  vm->instr_nb_cycle[4] = 10;
  vm->instr_nb_cycle[5] = 6;
  vm->instr_nb_cycle[6] = 6;
  vm->instr_nb_cycle[7] = 6;
  vm->instr_nb_cycle[8] = 20;
  vm->instr_nb_cycle[9] = 25;
  vm->instr_nb_cycle[10] = 25;
  vm->instr_nb_cycle[11] = 800;
  vm->instr_nb_cycle[12] = 10;
  vm->instr_nb_cycle[13] = 50;
  vm->instr_nb_cycle[14] = 1000;
  vm->instr_nb_cycle[15] = 2;
}

void	init_instr_f_tab(t_vm *vm)
{
  vm->f[0] = &op_live;
  vm->f[1] = &op_ld;
  vm->f[2] = &op_st;
  vm->f[3] = &op_add;
  vm->f[4] = &op_sub;
  vm->f[5] = &op_and;
  vm->f[6] = &op_or;
  vm->f[7] = &op_xor;
  vm->f[8] = &op_zjmp;
  vm->f[9] = &op_ldi;
  vm->f[10] = &op_sti;
  vm->f[11] = &op_fork;
  vm->f[12] = &op_lld;
  vm->f[13] = &op_lldi;
  vm->f[14] = &op_lfork;
  vm->f[15] = &op_aff;
}

t_vm		*init_vm_stats(int cycle_t_die, int cycle_t_dump, t_vm *vm)
{
  vm->process_list = NULL;
  vm->champs = NULL;
  vm->cycle_count = 0;
  vm->nbr_live = 0;
  vm->flag = 0;
  vm->cycle_to_die = cycle_t_die;
  vm->cycle_to_dump = cycle_t_dump;
  if ((vm->mem = malloc(MEM_SIZE * sizeof(char))) == NULL)
    return (NULL);
  my_memsetc(vm->mem, MEM_SIZE, 0x0);
  init_instr_f_tab(vm);
  init_instr_c_tab(vm);
  return (vm);
}

t_champ		**add_champ_t_tab(t_champ **tab, t_champ *add)
{
  t_champ	**newtab;
  int		i;

  i = 0;
  if (tab != NULL)
    while (tab[i] != NULL)
      i++;
  if ((newtab = malloc((i + 2) * sizeof(t_champ))) == NULL)
    return (NULL);
  i = 0;
  if (tab != NULL)
    while (tab[i] != NULL)
      {
        newtab[i] = tab[i];
        i++;
      }
  newtab[i] = add;
  newtab[i + 1] = NULL;
  free(tab);
  return (newtab);
}

t_process	*up_champ_t_mem(t_vm *vmstat, t_champ *champ, int pc)
{
  t_process	*proc;
  int		i;

  i = 0;
  if (((proc = malloc(1 * sizeof(t_process))) == NULL)
      || (champ->header.prog_size > MEM_SIZE))
    return (NULL);
  proc->pc = pc;
  proc->carry = 0;
  proc->associated_champ = champ;
  proc->nb_cycle_t_next = 0;
  while (i < REG_NUMBER)
    proc->reg[i++] = 0;
  proc->reg[0] = (champ->number);
  i = 0;
  while (i < champ->header.prog_size)
    {
      vmstat->mem[MOD_MEM(pc + i)] = champ->champcode[i];
      i++;
    }
  proc->instr = GET_INSTR;
  if ((proc->instr >= 0) && (proc->instr <= 15))
    proc->nb_cycle_t_next = vmstat->instr_nb_cycle[(int)proc->instr];
  fill_param_struct(vmstat, proc);
  return (proc);
}
