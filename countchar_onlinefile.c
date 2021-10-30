#include <stdio.h>

// Detta program ska läsa in symboler i sträng från rader i fil och räkna antalet symboler per rad och sedan printa ut det för varje rad

int main(void) {
    int linecount = 0, i = 0;
    char c;

    FILE *fp;    // Declaring fp as file pointer

    fp = fopen("file.txt","r");
    if(fp == NULL) {
	perror("Error in opening file");
	return 1;
    }

    do {
	c = fgetc(fp);

	if(feof(fp)) {
	    break;
	}

	if(c == '\n') {
	    printf("Amount symbols on line[%d] = %d\n", linecount, i);
	    i = -1;
	    linecount++;
	}

	i++;
    } while(1);

    fclose(fp);
    return(0);
}
