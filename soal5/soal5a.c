#include <sys/types.h>
#include<sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include<time.h>
#include<dirent.h>

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  //if ((chdir("/")) < 0) {
  //  exit(EXIT_FAILURE);
  //}

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  FILE *fp, *fb;
  DIR *d;  
  struct dirent *dir;
  char str[1000];
  int jam,mnt,dtk,thn,bln,tgl, count, status, wkt_fld=30, bnyk_file;
  while(1) {
    // main program here
    bnyk_file = 0;

    time_t now;
    time(&now);
    struct tm *local = localtime(&now);

    jam = local->tm_hour;
    mnt = local->tm_min;
    dtk = local->tm_sec;
    thn = local->tm_year + 1900;
    bln = local->tm_mon + 1;
    tgl = local->tm_mday;
    
    char nama_dir[100];  
  
    if(wkt_fld == 30){
      sprintf(nama_dir, "/home/ramrom/log/%02d:%02d:%d-%02d:%02d", tgl, bln, thn, jam, mnt);
      wkt_fld = 0; 

      pid_t child1;
      child1 = fork();
      
      if(child1 == 0){
        char *argv1[] = {"mkdir", nama_dir, NULL};
        execv("/bin/mkdir", argv1);
      }
      while((wait(&status)) > 0);
      
    }
    d = opendir(nama_dir);
    
    if(d){
      while((dir = readdir(d)) != NULL){
        if(dir->d_type == DT_REG){
          ++bnyk_file;
        }
      }
    }

    char nama_file[100] ;
    sprintf(nama_file, "%s/log%d.txt", nama_dir, bnyk_file + 1);

    pid_t child2;
    child2 = fork();
    if(child2 == 0){
      char *argv2[] = {"touch", nama_file, NULL};
      execv("/usr/bin/touch", argv2);
    }
    while((wait(&status)) > 0);

    fp = fopen("/var/log/syslog", "r");
    fb = fopen(nama_file, "w");

    while(fgets(str, sizeof(str), fp) !=NULL){
      fprintf(fb,"%s",str);
    }

    fclose(fp);
    fclose(fb);
    
    ++wkt_fld;
    sleep(60);
  }
  
  exit(EXIT_SUCCESS);
}
