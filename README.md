# SoalShift_modul2_D10

# Soal4
pada soal ini menjelaskan bahwa pada direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt, kami diminta untuk membuat program C dimana program tersebut dapat mengetahui apakah file makan_enak.txt pernah diakses setidaknya 30 detik yang lalu. kalau makan_enak.txt pernah diakses setidaknya 30 detik yang lalu maka program harus dapat membuat file baru yaitu makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga.</br>
penjelasan jawaban : </br>
untuk menjawab soal ini kami memanfaatkan Daemon agar program bisa berjalan terus menerus.</br> 
langkah pertama yang kami lakukan adalah memeriksa apakah ada file makan_enak.txt pada direktori makanan dengan cara memeriksa semua file yang ada pada direktori makanan jika maka akan dicek waktu aksesnya apakah memenuhi kriteria yang ditentukan</br>

```
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
```
</br>langkah berikutnya menjumlahkan semua file yang nama filenya berawalan makan_sehat dan berakhiran .txt yang akan digunakan pada saat pembuatan file makan_sehat yang baru. 
</br>
```
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
```
</br> ketika waktu akses file makan_enak.txt kurang atau sama dari 30 detik maka kita akan membuat file sesuai dengan ketentuan soal yang telah ditentukan. </br>
```
har num[100];
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
```
agar program selalu memeriksa setiap 5 detik maka kami menggunakan sleep(5);

