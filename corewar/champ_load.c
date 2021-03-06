#include	"include.h"

t_champ	*loading_error(int error, char *name)
{
  my_putstr(name, 2, -1);
  my_putstr(" has a", 2, -1);
  if (error == 0)
    my_putstr("n incorrect header size\n", 2, -1);
  else if (error == 1)
    my_putstr("n incorrect magic number\n", 2, -1);
  else
    my_putstr(" size different from the size indicated in the file\n", 2, -1);
  return (NULL);
}

t_champ		*load_champ(int fd, int number, char *name)
{
  t_champ	*champ;
  char		*file;
  int		size;

  if (!(((size = get_bin_file(fd, &file)) > (int)sizeof(t_header))
        && (champ = malloc(sizeof(t_champ))) != NULL))
    return (loading_error(0, name));
  champ->freeme = file;
  my_strncpy((char*)(&(champ->header)), file, sizeof(t_header));
  switch_endian((char*)(&(champ->header.magic)), sizeof(int));
  if (champ->header.magic != COREWAR_EXEC_MAGIC)
    return (loading_error(1, name));
  switch_endian((char*)(&(champ->header.prog_size)), sizeof(int));
  if (size - (int)sizeof(t_header) != champ->header.prog_size)
    return (loading_error(2, name));
  file = &(file[sizeof(t_header)]);
  champ->champcode = file;
  champ->number = number;
  champ->alive = 0;
  return (champ);
}
