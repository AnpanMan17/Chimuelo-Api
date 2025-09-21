#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_cpu_usage()
{
    FILE *fp;
    char buffer[1024];

    // Abrir el archivo /proc/stat para lectura
    fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        perror("Error al abrir /proc/stat");
        exit(EXIT_FAILURE);
    }

    // Leer el contenido del archivo
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Buscar la línea que comienza con "cpu "
        if (strncmp(buffer, "cpu ", 4) == 0) {
            printf("Datos de uso de CPU: %s", buffer);
            break;
        }
    }

    fclose(fp);
}

int main()
{
    read_cpu_usage();
    
    return 0;
}