#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#define LENGTH 1000000
#define MIN "-2147483648"
#define MAX "2147483647"

int main()
{
	FILE *f;
	f = fopen("input.txt", "w");
	fprintf(f, "%ld\n", LENGTH);

	long length = 0;
	char *num = NULL, num_length = 0;
	srand(time(0));
	while(length++ < LENGTH){
		num_length = rand() % 10 + 1;	// 1 -> 10

		if(rand() % 2){	// < 0
			num = (char*)malloc((num_length + 2) * sizeof(char));

			num[0] = '-';
			num[1] = rand() % 9 + 1 + '0';	// 1 -> 9
			for(char i = 2; i <= num_length; i++)
				num[i] = rand() % 10 + '0';
			num[num_length + 1] = '\0';

			// Tran so
			if(num_length == 10 && strcmp(num, MIN) > 0){
				length--;
				free(num);
				continue;
			}
		}
		else{	// >= 0
			num = (char*)malloc((num_length + 1) * sizeof(char));

			if(num_length == 1) num[0] = rand() % 10 + '0';
			else{
				num[0] = rand() % 9 + 1 + '0';
				for(char i = 1; i < num_length; i++)
					num[i] = rand() % 10 + '0';
			}
			num[num_length] = '\0';

			// Tran so
			if(num_length == 10 && strcmp(num, MAX) > 0){
				length--;
				free(num);
				continue;
			}
		}

		fprintf(f, "%s ", num);
		free(num);
	}

	fclose(f);

	return 0;
}