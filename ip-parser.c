#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("Usage: %s [input file] [output file]\n", argv[0]);
		exit(1);
	}

	clock_t start_time = clock();

	FILE* input_file = fopen(argv[1], "r");

	if (input_file == NULL) {
		printf("Error opening %s\n", argv[1]);
		exit(1);
	}

	FILE* output_file = fopen(argv[2], "w");

	if (output_file == NULL) {
		printf("Error opening %s\n", argv[2]);
		exit(1);
	}

	char buffer[BUFFER_SIZE];
	char* tokens[4];
	int tokens_count;

	while (fgets(buffer, sizeof(buffer), input_file) != NULL) {
		tokens_count = 0;
		char* token = strtok(buffer, " ");

		// Проверка количества слов в строке
		while (token != NULL) {
			if (tokens_count < 4) {
				tokens[tokens_count++] = token;
				token = strtok(NULL, " ");
			} else {
				break;
			}
		}

		if (tokens_count > 3) {
			fprintf(output_file, "%s\n", tokens[3]);
		}
	}

	fclose(input_file);
	fclose(output_file);

	clock_t end_time = clock();
	float seconds = (float) (end_time - start_time) / CLOCKS_PER_SEC;

	printf("Done! (%fs)\n", seconds);

	return 0;
}