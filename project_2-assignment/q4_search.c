#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct {
	char *keyword;
	char *filename;
	FILE *out_f;
} thread_data;

pthread_mutex_t file_mutex;

void *search_file(void *arg)
{
	thread_data *data = (thread_data *)arg;
	FILE *f = fopen(data->filename, "r");
	char buf[1024];
	int count = 0;

	if (!f) return (NULL);
	while (fscanf(f, "%1023s", buf) != EOF)
		if (strcmp(buf, data->keyword) == 0) count++;
	
	pthread_mutex_lock(&file_mutex);
	fprintf(data->out_f, "File %s: %d occurrences\n", data->filename, count);
	pthread_mutex_unlock(&file_mutex);
	
	fclose(f);
	return (NULL);
}

int main(int ac, char **av)
{
	int num_threads, i;
	pthread_t *t;
	thread_data *d;
	FILE *out_f;

	if (ac < 5) return (printf("Usage: ./search key out f1 f2 ... n\n"), 1);
	
	num_threads = atoi(av[ac - 1]);
	out_f = fopen(av[2], "w");
	pthread_mutex_init(&file_mutex, NULL);
	
	t = malloc(sizeof(pthread_t) * (ac - 4));
	d = malloc(sizeof(thread_data) * (ac - 4));

	for (i = 0; i < ac - 4; i++)
	{
		d[i].keyword = av[1];
		d[i].filename = av[i + 3];
		d[i].out_f = out_f;
		pthread_create(&t[i], NULL, search_file, &d[i]);
	}
	for (i = 0; i < ac - 4; i++) pthread_join(t[i], NULL);

	fclose(out_f);
	free(t); free(d);
	return (0);
}
