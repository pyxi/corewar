#include "../misc/op.h"
#include "../misc/get_file.h"
#include "asm.h"
#include "parse_cmd.h"

void	freelabel(t_cmd *cmd)
{
  int	i;

  i = 0;
  if (cmd->lablengh != 0)
    {
      while (i < cmd->lablengh)
	free(cmd->lab[i++].label);
      free(cmd->lab);
    }
}

void	freefile(char **file)
{
  int	i;

  i = 0;
  while (file[i] != NULL)
    free(file[i++]);
  free(file);
}

int	main(int argc, char **argv)
{
  int	fd;
  char	**file;

  if (argc > 1)
    {
      if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
	  my_putstr("File ", 2, 5);
	  my_putstr(argv[1], 2, -1);
	  my_putstr(" not accessible\n", 2, 16);
	  return (-1);
	}
      file = get_data_ffile(fd);
      if (file == 0 || file[0] == 0)
	{
	  my_putstr("Error File\n", 2, 11);
	  return (-1);
	}
      if (parse(file, argv[1]) == -1)
	my_putstr("Parse Error\n", 2, 12);
    }
  else
    my_putstr("No File\n", 2, 8);
  freefile(file);
  return (0);
}
