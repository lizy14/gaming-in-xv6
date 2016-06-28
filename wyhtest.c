#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  //set_console_parameters(1);
  //if (atoi(argv[4]) == 1)
    clear_screen();
  //write_at(atoi(argv[1]), atoi(argv[2]), *argv[3]);
  set_cursor(0, 24);
  printf(1, "%s", "2333");
  sleep(1000000);
  exit();
}
