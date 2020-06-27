#include <pthread.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define VK_ESCAPE       0x1B // esc key

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

static void* thread_proc(void* arg) {
  pthread_t thread = pthread_self();
  printf("thread_proc: %ld\n", thread);

  for (int i = 10; i >= 0; --i) {
    fprintf(stdout, "%d ", i);
    fflush(stdout);

    // sleep - is cancellation point
    sleep(1);
  }

  return NULL;
}

int main() {
  printf("pthread demo\n");

  pthread_t thread = pthread_self();
  printf("Main thread: %ld\n", thread);

  int res = pthread_create(&thread, NULL, thread_proc, NULL);
  if (res == 0) {
    printf("New thread was created successfuly (%ld)\n", thread);
  } else {
    printf("Error: pthread_create res=%d\n", res);
  }

  printf("Press <ESC> for cancel.\n");

  int c = getch();
  if (c == VK_ESCAPE) {
    res = pthread_cancel(thread);
    if (res != 0) {
      printf("Error: pthread_cancel res=%d\n", res);
    }
  }

  pthread_join(thread, NULL);

  printf("\n");

  return 0;
}
