#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

int main()
{
	pid_t pid, sid;
  	pid = fork();

	if (pid < 0)
	{
		exit(EXIT_FAILURE);
  	}

	if (pid > 0)
	{
    		exit(EXIT_SUCCESS);
  	}

	umask(0);
  	sid = setsid();

  	if (sid < 0)
	{
    		exit(EXIT_FAILURE);
  	}

  	if ((chdir("/")) < 0)
	{
    		exit(EXIT_FAILURE);
  	}

  	close(STDIN_FILENO);
  	close(STDOUT_FILENO);
  	close(STDERR_FILENO);

	while(1)
	{
  		DIR *current;
		struct dirent *temp;
 		char *lama;
 		char baru[200];
		char old_dir[200];

		current = opendir("/home/seirzen/Modul2/");
		strcpy(old_dir, "/home/seirzen/Modul2/");

 		if(current)
		{
    			while((temp = readdir(current)) != NULL)
     	 		{
        			int panjang = strlen(temp->d_name);
			      	lama = temp->d_name;

        			if((lama[panjang-4] == '.') && (lama[panjang-3] == 'p')
				&& (lama[panjang-2] == 'n') && (lama[panjang-1] == 'g'))
        			{
            				strcpy(baru, "/home/seirzen/Modul2/gambar/");
            				strcat(baru, lama);

			            	panjang = strlen(baru);
            				baru[panjang-4] = '\0';

            				strcat(baru, "_grey.png");
          				strcat(old_dir, lama);
            				rename(old_dir, baru);

				        memset(baru, 0, 200);
        			}
    			}
		}

		closedir(current);
  		sleep(5);
	}

	exit(EXIT_SUCCESS);
}
