#include "utils.h"

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

/* reads from keypress, doesn't echo */
/* https://stackoverflow.com/questions/3276546/how-to-implement-getch-function-of-c-in-linux*/
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

void zero_array(size_t N, double *arr) {
  for (size_t i = 0; i < N; ++i) {
    arr[i] = 0.0;
  }
}
