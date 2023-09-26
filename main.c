#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LENGTH 80

int main() {
    char *args[MAX_LENGTH/2 + 1];
    char input[MAX_LENGTH + 2]; // +2 porque precisa levar em consideração o caractere de nova linha(\n) e o caractere nulo de fim de string (\0)
    int should_run = 1;

    while (should_run) {
        printf("osh > ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) != NULL) {

            if (input[strlen(input) - 1] != '\n') {
                printf("Comando muito longo. Limite é %d caracteres.\n", MAX_LENGTH);
                
                // limpando o restante da entrada para evitar problemas futuros
                while (getchar() != '\n');
            } else {
                input[strcspn(input, "\n")] = '\0';

                char *token = strtok(input, " ");
                int i = 0;
                int waitChildProcess = 1;

                // se o comando digitado for "exit" o processo pai será encerrado, pois o loop while será terminado
                if (strcmp(token, "exit") == 0) {
                    should_run = 0;
                } else {
                    while (token != NULL && i < MAX_LENGTH/2 + 1) {
                        args[i] = token;
                        token = strtok(NULL, " ");
                        i++;
                    }

                    if (strcmp(args[i-1], "&") == 0) {
                        waitChildProcess = 0;
                        args[i-1] = NULL;
                    }

                    args[i] = NULL; // definindo o último elemento como NULL para indicar o final da lista

                    pid_t pid = fork(); // criando um processo para executar o comando

                    if (pid < 0) {
                        perror("Ocorreu um erro ao tentar criar o processo filho");
                        return 1;
                    } else if (pid == 0) {
                        // apenas o processo filho executa o comando
                        execvp(args[0], args);
                        
                        perror("execvp");
                        return 1;
                    } else {
                        // o processo pai fica aguardando o processo filho finalizar o comando e terminar a execução do processo
                        if (waitChildProcess) {
                            int status;
                            waitpid(pid, &status, 0);
                        }
                    }
                }
            }

        } else {
            should_run = 0;
        }
    }

    return 0;
}
