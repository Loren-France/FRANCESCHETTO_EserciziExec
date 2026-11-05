#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    /* fork(), execvp() */
#include <sys/wait.h>  /* wait() */

int main() {
    printf("[Padre] PID: %d -- sto per fare fork()\n", getpid());

    pid_t pid = fork();

    if (pid == -1) {
        /* fork() fallita */
        perror("Errore fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        /* === PROCESSO FIGLIO === */
        printf("[Figlio] PID: %d -- chiamo execvp()\n", getpid());

        /* Prepara gli argomenti come array (come argv) */
        //char *args[] = { "date", NULL };

        /* Sostituisce questo processo con 'ls' */
        //execvp("date", args);

        //char *args2[] = { "echo", "ciao dal figlio", NULL };

        //execvp("echo", args2);

        char *args3[] = { "cat", "/etc/hostname", NULL };

        execvp("cat", args3);

        /* Se arriviamo qui, execvp() ha fallito */
        perror("Errore execvp");
        exit(EXIT_FAILURE);
    }

    /* === PROCESSO PADRE === */
    /* pid contiene il PID del figlio */
    printf("[Padre] ho creato il figlio con PID %d\n", pid);

    /* Aspetta che il figlio termini */
    int status;
    wait(&status);

    if (WIFEXITED(status))
        printf("[Padre] figlio terminato con codice %d\n",
               WEXITSTATUS(status));

    printf("[Padre] continuo la mia esecuzione.\n");
    return 0;
}

