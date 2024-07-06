#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definiere die Struktur für ein Umgebungsvariablenpaar
typedef struct EnvVar {
    char *key;
    char *value;
    struct EnvVar *next;
} EnvVar;

// Funktion zum Hinzufügen einer neuen Umgebungsvariablen zur Liste (am Ende)
void add_env_var(EnvVar **head, const char *key, const char *value) {
    EnvVar *new_var = malloc(sizeof(EnvVar));
    new_var->key = strdup(key);
    new_var->value = strdup(value);
    new_var->next = NULL;

    if (*head == NULL) {
        *head = new_var;
    } else {
        EnvVar *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_var;
    }
}

// Funktion zum Parsen der Umgebungsvariablen
void parse_envp(EnvVar **head, char **envp) {
    for (int i = 0; envp[i] != NULL; i++) {
        char *entry = strdup(envp[i]);
        char *equal_sign = strchr(entry, '=');
        if (equal_sign != NULL) {
            *equal_sign = '\0'; // Trenne den String in key und value
            char *key = entry;
            char *value = equal_sign + 1;
            add_env_var(head, key, value);
        }
        free(entry);
    }
}

// Funktion zum Freigeben des Speichers der verketteten Liste
void free_env_list(EnvVar *head) {
    EnvVar *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
}

int main(int argc, char *argv[], char *envp[]) {
    (void) argc;
	(void) argv;
	EnvVar *env_list = NULL;

    parse_envp(&env_list, envp);

    // Ausgabe der Umgebungsvariablen aus der Liste
    EnvVar *current = env_list;
    while (current != NULL) {
        if (current->value == NULL || current->value[0] == '\0')
        {
            printf("%s", current->key);
            current = current->next;
        }
        else
        {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
        }
    }

    // Freigeben des Speichers
    free_env_list(env_list);

    return 0;
}
