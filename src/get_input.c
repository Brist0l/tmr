#include "get_input.h"

#include <stdbool.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void get_input() {
  bool running = true;
  struct termios old_tio, new_tio;
  unsigned char c;

  tcgetattr(STDIN_FILENO, &old_tio);  // get terminal settings for stdin

  new_tio = old_tio;

  new_tio.c_lflag &=
      (~ICANON &
       ~ECHO);  // disable cannonical and echo in the new termial settings

  tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

  while ((c = getchar()) == 32)
    ;

  tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}
