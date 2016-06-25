#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if (atoi(argv[4]) == 1)
    clear_screen();
  write_at(atoi(argv[1]), atoi(argv[2]), *argv[3]);
  exit();
}
