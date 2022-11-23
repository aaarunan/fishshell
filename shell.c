#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <termios.h>
#include <errno.h>

void handler(int num)
{
    signal(SIGINT, handler);
    signal(SIGTSTP, handler);
    puts("\nlol");
}
int main()
{
    // signal(SIGINT, handler);
    // signal(SIGTSTP, handler);

    puts("Oi! ser ut til at du har blitt fiska!");
    puts("Her er et sikkelig dårlig skall som kan hjelpe deg med å fiske problemen dine \n");
    puts("Skulle vært en måte å endre directory på en eller annen måte ellerhva?");

    char input[256];
    while (1)
    {
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
            if (strcmp("bash", command) == 0 || strcmp("zsh", command) == 0)
            {
                puts("Bra prøvd, men ikke godt nok, kanskje noe annet kan hjelpe?");
                continue;
            } else if (strcmp("tmux", command) == 0) {
                puts("tmux???? hva er det? Hæææø");
                continue;
            }

            int i = 0;
            while (split != NULL)
            {
                argv[i] = split;
                split = strtok(NULL, " ");
                i++;
            }
            argv[i] = NULL;
            char path[] = "/usr/bin/";
            strcat(path, command);
            printf("%s \n", path);

            execve(path, argv, envarg);
            memset(argv, 0, sizeof(argv));
        }
    }
    return 0;
}
