#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{

    while (1)
    {
        char input[30];
        printf("$ ");

        fflush(0);

        fgets(input, sizeof(input), stdin);

        if (strlen(input) < 2)
            continue;

        input[strlen(input) - 1] = '\0';

        int pid = fork();

        if (pid == -1)
        {
            perror("Could not create child process.\n");
        }
        else if (pid > 0)
        {
            int status = waitpid(pid, NULL, 0);
        }
        else if (pid == 0)
        {
            char *argv[50];
            char *envarg[] = {NULL};
            char *split;
            char *command;

            split = strtok(input, " ");
            command = split;

            int i = 0;
            while (split != NULL)
            {
                argv[i] = split;
                i++;
                split = strtok(NULL, " ");
            }
            char path[] = "/usr/bin/";
            strcat(path, command);

            execve(path, argv, envarg);
            memset(argv, 0, sizeof(argv));
        }
    }
    return 0;
}
