/*
** pars for pars in /home/sinet_l//corewar/corewar
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Tue Jan 22 15:41:27 2013 luc sinet
** Last update Fri Jan 25 00:35:51 2013 luc sinet
*/

#include "include.h"

void	error_msg(int type)
{
  if (type == 0)
    my_putstr("Error, please verifie your arguments\n"
              "./corewar [-dump nbr_cycle][[-n prog_number]"
              "[-a load_address ] prog_name]\n", 2, -1);
  else if (type == 1)
    my_putstr("Error while laoding the champ file\n", 2, -1);
  else if (type == 2)
    my_putstr("Error while using the function malloc", 2, -1);
}

int	check_args(char **av, t_arg *parg)
{
  int	error;

  parg->pos = 0;
  parg->num_val = -1;
  while (parg->pos < parg->nb_arg)
    {
      if ((error = opt_compare(av, parg)) < 0)
        {
          if (error == -2 || (error = check_champ(av[parg->pos])) < 0)
            {
	      if (error == -1)
		error_msg(0);
            }
	  return (-1);
        }
      parg->pos += 1;
    }
  return (0);
}

int	pars(char **av, int ac)
{
  t_arg	*parg;

  if ((parg = malloc(sizeof(*parg))) == NULL)
    {
      error_msg(2);
      return (-1);
    }
  parg->dump = 0;
  parg->num = 0;
  parg->addr = 0;
  parg->nb_arg = ac;
  if (ac == 0 || check_args(av, parg) == -1)
    return (-1);
  return (0);
}

