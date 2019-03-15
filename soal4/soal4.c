#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include<dirent.h>
#include <time.h>


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

  //if ((chdir("/home/ramrom/Documents/makanan/")) < 0) {
  //  exit(EXIT_FAILURE);
  //}

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  

  while(1) {
    // main program here

    DIR *d;
    time_t now;
    time(&now);
    int l, n, cek, bnyk, tgll, jaml, mntl, dtkl,  tgln, jamn, mntn, dtkn;
    struct dirent *dir;
    struct stat filestat;
    char *ptr;
    char targetsave[100] = "makan_sehat";
    char targetfile[100] = "makan_enak.txt";
    char *synt = malloc(sizeof(char));
    char *waktu_lastaccess = malloc(sizeof(char));
    char *waktu_now = malloc(sizeof(char));
    char *thn_wlt = malloc(sizeof(char)), *tgl_wlt  = malloc(sizeof(char)), *bln_wlt = malloc(sizeof(char)), *jam_wlt  = malloc(sizeof(char)), *mnt_wlt  = malloc(sizeof(char)), *dtk_wlt  = malloc(sizeof(char));
    char *thn_now = malloc(sizeof(char)), *tgl_now  = malloc(sizeof(char)), *bln_now = malloc(sizeof(char)), *jam_now  = malloc(sizeof(char)), *mnt_now= malloc(sizeof(char)), *dtk_now  = malloc(sizeof(char));

    synt[0] = ' ';
    synt[21] = ' ';
    synt[3] = ' ';
    synt[7] = ' ';
    synt[12] = ' ';
    synt[15] = ':';
    synt[18] = ':';

    d = opendir("/home/rammrom/Documents/makanan");
    if(d){
      bnyk=0;
      while((dir = readdir(d)) != NULL){
        if(!strcmp(targetfile, dir->d_name)){
          stat("/home/ramrom/Documents/makanan/makan_enak.txt", &filestat);
          strcpy(waktu_lastaccess, ctime(&filestat.st_atime));
          strcpy(waktu_now, ctime(&now));
          int i = 0;

          while(i < 5){
            if(i < 4){ thn_wlt[i] = waktu_lastaccess[20+i];}
            if(i < 2){ tgl_wlt[i] = waktu_lastaccess[8+i];}
            if(i < 3){ bln_wlt[i] = waktu_lastaccess[4+i];}
            if(i < 2){ jam_wlt[i] = waktu_lastaccess[11+i];}
            if(i < 2){ mnt_wlt[i] = waktu_lastaccess[14+i];}
            if(i < 2){ dtk_wlt[i] = waktu_lastaccess[17+i];}
            if(i < 4){ thn_now[i] = waktu_now[20+i];}
            if(i < 2){ tgl_now[i] = waktu_now[8+i];}
            if(i < 3){ bln_now[i] = waktu_now[4+i];}
            if(i < 2){ jam_now[i] = waktu_now[11+i];}
            if(i < 2){ mnt_now[i] = waktu_now[14+i];}
            if(i < 2){ dtk_now[i] = waktu_now[17+i];}
            i++;
          }

          tgln = strtol(tgl_now, &ptr , 10);
          jamn = strtol(jam_now, &ptr , 10);
          mntn = strtol(mnt_now, &ptr , 10);
          dtkn = strtol(dtk_now, &ptr , 10);
          tgll = strtol(tgl_wlt, &ptr , 10);
          jaml = strtol(jam_wlt, &ptr , 10);
          mntl = strtol(mnt_wlt, &ptr , 10);
          dtkl = strtol(dtk_wlt, &ptr , 10);

          l = (3600*jaml)+(60*mntl)+dtkl;
          n = (3600*jamn)+(60*mntn)+dtkn;

        }
        
          char *smpn = malloc(sizeof(char));
          char smpnnm[100];
          strcpy(smpnnm, dir->d_name);
          cek = 0;
 	  smpn[11] = '\0';
          while(cek < 11){
            if(smpnnm[cek]){
               smpn[cek] = smpnnm[cek];
            }cek++;
          }
          if(!strcmp(targetsave, smpn)){
            bnyk++;
          }
      }

      int i=0;
      while(i < 5){
        if(i < 2){synt[1+i] = tgl_now[i];}
        if(i < 3){synt[4+i] = bln_now[i];}
        if(i < 4){synt[8+i] = thn_now[i];}
        if(i < 2){synt[13+i] = jam_now[i];}
        if(i < 2){synt[16+i] = mnt_now[i];}
        if(i < 2){synt[19+i] = dtk_now[i];}
        i++;
      }

      char *argv[]={"touch", "-m", "-d", synt, "/home/ramrom/Documents/makanan/makan_enak.txt", NULL};
      
      pid_t pro_modif;
      pro_modif = fork();

     if (pro_modif < 0) {
       exit(EXIT_FAILURE);
     }else if(pro_modif == 0){
        if(execv("/usr/bin/touch", argv) < 0) printf("error disini");
     }

      char num[100];
      ++bnyk;
      sprintf(num, "%d", bnyk);
      char nama_file[100] = "/home/ramrom/Documents/makanan/makan_sehat";
      int k;
      for(k=0; k < strlen(num); k++){
        nama_file[42+k] = num[k];
      }
      nama_file[42+k] = '.';
      nama_file[43+k] = 't';
      nama_file[44+k] = 'x';
      nama_file[45+k] = 't';

      char *argv1[] = {"touch", nama_file, NULL};
      if((n-l)<=30){
          pid_t pro_create;
          pro_create = fork();

          if (pro_create < 0) {
             exit(EXIT_FAILURE);
          }else if(pro_create == 0){
             if(execv("/usr/bin/touch", argv1) < 0)printf("error disana");
          }
      }
 
      closedir(d);

    }

    sleep(5);
  }
  
  exit(EXIT_SUCCESS);
}
