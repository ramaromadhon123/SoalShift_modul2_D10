#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
 	int a[2];
	int b[2];

  	pid_t child_id;
  	pid_t child_id_2;
  	pid_t child_id_3;
  	pid_t child_id_4;

	int status;
  	int r;
  	char temp[10000]={0};

  	child_id = fork();
  	if (child_id == 0)
	{
        	char *argv[3] = {"touch", "daftar.txt", NULL};
        	execv("/usr/bin/touch", argv);
  	}

	else
	{
    		child_id_2 = fork();
    		if (child_id_2 == 0)
		{
        		char *argv[3] = {"unzip", "campur2.zip", NULL};
        		execv("/usr/bin/unzip", argv);
    		}

		else
		{
      			while ((wait(&status)) > 0);
        		char *ls[] = {"ls", "campur2", NULL};
        		char *grep[] = {"grep", ".*.txt$", NULL};

        		pipe(a);
        		pipe(b);

        		child_id_3 = fork();
        		if (child_id_3 == 0)
			{
                		dup2 (a[1],1);
               	 		close(a[0]);
                		close(a[1]);
                		execvp("ls", ls);
        		}
			else
			{
                		child_id_4 = fork();
                		if (child_id_4 == 0)
				{
                        		dup2 (a[0],0);
                        		dup2 (b[1],1);
                        		close(a[1]);
                        		close(a[0]);
                        		close(b[1]);
                        		close(b[0]);
                        		execvp("grep", grep);
				}
				else
				{
                        		close(a[0]);
                        		close(a[1]);
                        		close(b[1]);

                        		r = read(b[0], temp, sizeof(temp));

                        		FILE *out_file = fopen("daftar.txt","w+");
                        		fprintf(out_file,"%.*s\n", r, temp);
                		}
        		}
    		}
  	}
}
