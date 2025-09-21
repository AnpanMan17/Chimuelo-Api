#include <prom.h>
#include <promhttp.h>
#include <pthread.h>
#include <stdio.h>

#include <metrics.h>

// Define the metric for CPU usage
static prom_gauge_t *cpu_usage;
pthread_mutex_t lock;

// Function to start the HTTP server
void* expose_metrics(void* arg) {
    // Ensure that the HTTP handler is properly attached to the default registry
    promhttp_set_active_collector_registry(NULL);

    // Start the HTTP server on port 8000
    if (promhttp_start_daemon(MHD_USE_SELECT_INTERNALLY, 8000, NULL, NULL) == 0) {
        fprintf(stderr, "Error starting HTTP server\n");
        return NULL;
    }

    // Keep the server running
    while (1) {
        sleep(10);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <prom.h>

// Define the metrics for CPU and memory usage
static prom_gauge_t *cpu_usage;
static prom_gauge_t *memory_usage;
extern pthread_mutex_t lock;

// Function to update the Prometheus gauge with the CPU usage
void update_cpu_gauge() {
    double usage = get_cpu_usage();
    if (usage >= 0) {
        pthread_mutex_lock(&lock);
        prom_gauge_set(cpu_usage, usage, NULL); // Pass NULL as the third argument
        pthread_mutex_unlock(&lock);
    } else {
        fprintf(stderr, "Error getting CPU usage\n");
    }
}

// Function to update the Prometheus gauge with the memory usage
void update_memory_gauge() {
    double usage = get_memory_usage();
    if (usage >= 0) {
        pthread_mutex_lock(&lock);
        prom_gauge_set(memory_usage, usage, NULL); // Pass NULL as the third argument
        pthread_mutex_unlock(&lock);
    } else {
        fprintf(stderr, "Error getting memory usage\n");
    }
}

int main() {
    // Initialize the mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        fprintf(stderr, "Error initializing mutex\n");
        return EXIT_FAILURE;
    }

    // Initialize the Prometheus collector registry
    if (prom_collector_registry_default_init() != 0) {
        fprintf(stderr, "Error initializing Prometheus registry\n");
        return EXIT_FAILURE;
    }

    // Create a metric for CPU usage
    cpu_usage = prom_gauge_new("cpu_usage", "CPU Usage", 0, NULL);
    if (cpu_usage == NULL) {
        fprintf(stderr, "Error creating CPU usage metric\n");
        return EXIT_FAILURE;
    }

    // Create a metric for memory usage
    memory_usage = prom_gauge_new("memory_usage", "Memory Usage", 0, NULL);
    if (memory_usage == NULL) {
        fprintf(stderr, "Error creating memory usage metric\n");
        return EXIT_FAILURE;
    }

    // Register the metrics in the default registry
    if (prom_collector_registry_must_register_metric(cpu_usage) == NULL || 
        prom_collector_registry_must_register_metric(memory_usage) == NULL) {
        fprintf(stderr, "Error registering metrics\n");
        return EXIT_FAILURE;
    }

    // Create a thread to expose metrics via HTTP
    pthread_t tid;
    if (pthread_create(&tid, NULL, expose_metrics, NULL) != 0) {
        fprintf(stderr, "Error creating HTTP server thread\n");
        return EXIT_FAILURE;
    }

    // Main loop to update metrics every second
    while (1) {
        update_cpu_gauge();
        update_memory_gauge();
        sleep(1);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    return 0;
}
