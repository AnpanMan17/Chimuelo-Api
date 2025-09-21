#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Function to get the memory usage from /proc/meminfo
double get_memory_usage() {
    FILE *fp;
    char buffer[256];
    unsigned long long total_mem, free_mem;

    // Open the /proc/meminfo file
    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        perror("Error opening /proc/meminfo");
        exit(EXIT_FAILURE);
    }

    // Read the total memory and free memory values
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (sscanf(buffer, "MemTotal: %llu kB", &total_mem) == 1) {
            // MemTotal found
        }
        if (sscanf(buffer, "MemAvailable: %llu kB", &free_mem) == 1) {
            break; // MemAvailable found, we can stop reading further
        }
    }

    fclose(fp);

    // Calculate memory usage percentage
    if (total_mem > 0) {
        return 1 - (double)free_mem / total_mem;
    }

    return -1; // Return -1 in case of an error or division by zero
}

// Function to get the CPU usage from /proc/stat
double get_cpu_usage() {
    FILE *fp;
    char buffer[1024];
    unsigned long long user, nice, system, idle;

    // Open the /proc/stat file
    fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        perror("Error opening /proc/stat");
        exit(EXIT_FAILURE);
    }

    // Read the first line of CPU stats
    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
        perror("Error reading /proc/stat");
        fclose(fp);
        return -1;
    }
    sscanf(buffer, "cpu %llu %llu %llu %llu", &user, &nice, &system, &idle);

    fclose(fp);

    // Calculate total CPU usage
    unsigned long long total = user + nice + system + idle;
    if (total > 0) {
        return (double)(user + nice + system) / total;
    }

    return -1; // Return -1 in case of an error or division by zero
}
