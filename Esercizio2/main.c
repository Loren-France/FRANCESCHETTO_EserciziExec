#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>    /* fork(), execvp() */
#include <sys/wait.h>  /* wait() */

int main(void) {
    printf("Mini shell in parallelo\n");

    char command[256];

    do {
        printf("Inserisci un comando: ");

        fgets(command, sizeof(command), stdin); // Legge il comando da input

        command[strlen(command) - 1] = '\0';

        pid_t pid = fork();

        if (pid == 0) {
            // Processo figlio

            char *args[] = {command, NULL};

            execvp(command, args);

            perror("execvp");
            exit(EXIT_FAILURE);
        }

        if (pid == -1) {
            perror("Errore fork");
            exit(EXIT_FAILURE);
        }

    }
    while (strcmp(command, "exit") != 0);

    waitpid(-1, NULL, WNOHANG);

    return 0;
}
