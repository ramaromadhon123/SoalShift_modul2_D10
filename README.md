# SoalShift_modul2_D10

# Soal 1
*Soal*: Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.

*Solusi*: 
1. Membuka direktori file dan menyimpan direktori tersebut.
2. Lakukan loop dengan syarat:
    - Cek semua file yang ada di direktori satu per satu.
    - Cek apakah file berakhiran [.png]
    - Masukkan nama file tersebut ke dalam nama direktori file /home/user/modul2/gambar/
    - Hapus 4 karakter terakhir yaitu [.png] lalu ganti dengan [_grey.png]
    - Rename file tersebut ke direktori dengan nama file yang baru.

# Soal 2
*Soal*: Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.

*Solusi*: 
1. Deklarasi menggunakan _struct stat_ yang di dalamnya terdapat informasi mengenai owner dan group
2. Masuk dan mengecek isi folder "hatiku" dan mengecek apakah ada "www-data"
3. Jika ada, ubah permission menjadi 777 menggunakan chmod
4. Remove file dan gunakan (sleep (3)) agar dapat dijalankan setiap 3 detik.

# Soal 3
*Soal*: Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
Buatlah program C yang dapat :
i)  mengekstrak file zip tersebut.
ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 
Catatan:  
Gunakan fork dan exec.
Gunakan minimal 3 proses yang diakhiri dengan exec.
Gunakan pipe
Pastikan file daftar.txt dapat diakses dari text editor

*Solusi*:
1. Unzip file dengan menggunakan exec
2. Gunakan fungsi pipe 
3. Ada 4 child yang digunakan untuk menyelesaikan soal.

# Soal 4
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

# Soal 5a
</br>pada soal ini kami diminta untuk membuat program C yang dapat mencatat log setiap menit daroi file log pada syslog ke direktori /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log dengan ketentuan folder dibuat setiap 30 menit sekali dengan nama [dd:MM:yyyy-hh:mm] dan tiap menitnya memasukkan log#.log ke dalam folder tersebut dimana ‘#’ : increment per menit. Mulai dari 1</br>
penjelasan jawaban : </br>
pada soal ini kami menggunakan daemon agar program tetap berjalan terus menerus.</br>
langkah pertama kami meng-extract waktu untuk pembuatan nama file</br>
```
time_t now;
    time(&now);
    struct tm *local = localtime(&now);

    jam = local->tm_hour;
    mnt = local->tm_min;
    dtk = local->tm_sec;
    thn = local->tm_year + 1900;
    bln = local->tm_mon + 1;
    tgl = local->tm_mday;
```
</br>
karena daemonnya kami jalankan tiap menit menggunakan sleep(60) maka kami membuat sebuah variable untuk menyimpan  data menit keberapa daemon sedang di jalankan, ketika variabel tersebut bernilai 30 maka variable tersebut akan di reset menjadi 0 dan akan melakukan pembuatan direktori dengan ketentuan yang ada pada soal</br>
```
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
```
setelah itu program akan mengecek jumlah file yang ada didalam direktori tersebut yang nantinya akan digunakan untuk pembuatan file baru</br>

```
d = opendir(nama_dir);
    
    if(d){
      while((dir = readdir(d)) != NULL){
        if(dir->d_type == DT_REG){
          ++bnyk_file;
        }
      }
    }
```

setelah mendapatkan jumlah file maka program akan membuat file baru dan mengisinya dengan data log</br>
```
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
```

# Soal 5b
pada soal ini kami diminta membuat program yang bisa menghentikan program soal5a.</br>
kami menggunakan killall untuk menghentikan semua proses yang ada pada program soal5a</br>
```
int main(){
  char *argv[] = {"killall", "soal5a", NULL};
  execv("/usr/bin/killall", argv);
}
```


