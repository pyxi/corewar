/*
** pars.h for pars in /home/sinet_l//corewar/corewar
**
** Made by luc sinet
** Login   <sinet_l@epitech.net>
**
** Started on  Wed Jan 23 15:40:32 2013 luc sinet
** Last update Thu Jan 24 14:23:35 2013 luc sinet
*/

#ifndef PARS_H_
# define PARS_H_

int	pars(char **av, int ac);
int	check_args(char **av, int nb_arg);
void	error_msg(int type);
int	pars_opt(char **av, int *pos, int max);
int	pars_champ(char *name);

#endif
