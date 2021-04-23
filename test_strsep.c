#include <stdio.h>
#include <string.h>

int main(void) {
    char fullname[300] = "Trump,Donald,John";

    // make a copy as strsep is destructive
    char temp[strlen(fullname) + 1];
    strcpy(temp, fullname);

    int i = 0;
    char *start = temp;
    while (1) {
        // try to extract next field
        char *token = strsep(&start, ",");
        if (token == NULL) break;  // no more
        i++;
        printf("%d: token=%s\n", i, token);
    }

    printf("are extracted from %s\n", fullname);
    return 0;
}
