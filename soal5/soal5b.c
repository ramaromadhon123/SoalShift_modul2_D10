#include <stdio.h>
#include <unistd.h>

int main(){
  char *argv[] = {"killall", "soal5a", NULL};
  execv("/usr/bin/killall", argv);
}
