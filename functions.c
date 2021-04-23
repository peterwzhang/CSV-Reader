#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
    Peter Zhang
    10/18/2019
    Zybooks Grades Functions
    This program has five functions that take in a csv file and return either
    the min, max, count, average, or student grade and returns the value to
    main.c
*/
int IsBlank(char arr[]);
double getMin(char csvfile[], char column[]) {
    char type1, typeString[30], type2, line[3000];
    int ch1, ch2, sec1, sec2, weight;
    sscanf(column, "%c%d.%d", &type1, &ch1, &sec1);  // get column to look for
    // open file
    FILE *fileToOpen;
    fileToOpen = fopen(csvfile, "r");

    // get first line
    fgets(line, 3000, fileToOpen);
    char temp[strlen(line) + 1];
    strcpy(temp, line);
    int i = 0, colNum = 0;
    double min = 100;
    char *start = temp;
    while (1) {
        // try to extract next field
        char *token = strsep(&start, ",");
        if (token == NULL) return -2.0;  // no more
        i++;
        if (i < 3) {
            continue;
        }
        sscanf(token, "%d.%d - %s (%d)", &ch2, &sec2, typeString, &weight);
        type2 = typeString[0];
        if (ch1 == ch2 && sec1 == sec2 && type1 == type2) {  // found column
            colNum = i;
            //    printf("Found %s at %d\n", token, i);
            if (weight == 0) {
                return -1.0;
            }
            break;
        }
    }

    while (1) {
        fgets(line, 3000, fileToOpen);  // get next student
        if (feof(fileToOpen)) {
            break;
        }
        char temp[strlen(line) + 1];
        strcpy(temp, line);
        int i = 1;
        char *start = temp;
        while (1) {
            // try to extract next field
            char *token = strsep(&start, ",");
            if (token == NULL) break;  // no more
            // if (i == 2 && strlen(token) > 0){
            //     max = atof(token);
            // }
            else if (i == colNum && IsBlank(token) == 0) {
                if (min > atof(token)) {
                    min = atof(token);
                }
            }

            i++;
        }
    }

    // printf("are extracted from %s\n", line);
    fclose(fileToOpen);
    return min;
}

double getMax(char csvfile[], char column[]) {
    char type1, typeString[30], type2, line[3000];
    int ch1, ch2, sec1, sec2, weight;
    sscanf(column, "%c%d.%d", &type1, &ch1, &sec1);  // get column to look for
    // open file
    FILE *fileToOpen;
    fileToOpen = fopen(csvfile, "r");

    // get first line
    fgets(line, 3000, fileToOpen);
    char temp[strlen(line) + 1];
    strcpy(temp, line);
    int i = 0, colNum = 0;
    double max = 0;
    char *start = temp;
    while (1) {
        // try to extract next field
        char *token = strsep(&start, ",");
        if (token == NULL) return -2.0;  // no more
        i++;
        if (i < 3) {
            continue;
        }
        sscanf(token, "%d.%d - %s (%d)", &ch2, &sec2, typeString, &weight);
        type2 = typeString[0];
        if (ch1 == ch2 && sec1 == sec2 && type1 == type2) {  // found column
            colNum = i;
            //    printf("Found %s at %d\n", token, i);
            if (weight == 0) {
                return -1.0;
            }
            break;
        }
    }

    while (1) {
        fgets(line, 3000, fileToOpen);  // get next student
        if (feof(fileToOpen)) {
            break;
        }
        char temp[strlen(line) + 1];
        strcpy(temp, line);
        int i = 1;
        char *start = temp;
        while (1) {
            // try to extract next field
            char *token = strsep(&start, ",");
            if (token == NULL) break;  // no more
            // if (i == 2 && strlen(token) > 0){
            //     max = atof(token);
            // }
            else if (i == colNum && IsBlank(token) == 0) {
                if (max < atof(token)) {
                    max = atof(token);
                }
            }

            i++;
        }
    }

    // printf("are extracted from %s\n", line);
    fclose(fileToOpen);
    return max;
}

double getAvg(char csvfile[], char column[]) {
    char type1, typeString[30], type2, line[3000];
    int ch1, ch2, sec1, sec2, weight;
    sscanf(column, "%c%d.%d", &type1, &ch1, &sec1);  // get column to look for
    // open file
    FILE *fileToOpen;
    fileToOpen = fopen(csvfile, "r");

    // get first line
    fgets(line, 3000, fileToOpen);
    char temp[strlen(line) + 1];
    strcpy(temp, line);
    int i = 0, colNum = 0, count = 0;
    double avg = 0;
    char *start = temp;
    while (1) {
        // try to extract next field
        char *token = strsep(&start, ",");
        if (token == NULL) return -2.0;  // no more
        i++;
        if (i < 3) {
            continue;
        }
        sscanf(token, "%d.%d - %s (%d)", &ch2, &sec2, typeString, &weight);
        type2 = typeString[0];
        if (ch1 == ch2 && sec1 == sec2 && type1 == type2) {  // found column
            colNum = i;
            //    printf("Found %s at %d\n", token, i);
            if (weight == 0) {
                return -1.0;
            }
            break;
        }
    }

    while (1) {
        fgets(line, 3000, fileToOpen);  // get next student
        if (feof(fileToOpen)) {
            break;
        }
        char temp[strlen(line) + 1];
        strcpy(temp, line);
        int i = 1;
        char *start = temp;
        while (1) {
            // try to extract next field
            char *token = strsep(&start, ",");
            if (token == NULL) break;  // no more
            // if (i == 2 && strlen(token) > 0){
            //     max = atof(token);
            // }
            else if (i == colNum && IsBlank(token) == 0) {
                avg = avg + atof(token);
                count++;
            }

            i++;
        }
    }
    avg = avg / count;
    // printf("are extracted from %s\n", line);
    fclose(fileToOpen);
    return avg;
}

int getCount(char csvfile[], char column[], double threshold) {
    char type1, typeString[30], type2, line[3000];
    int ch1, ch2, sec1, sec2, weight;
    sscanf(column, "%c%d.%d", &type1, &ch1, &sec1);  // get column to look for
    // open file
    FILE *fileToOpen;
    fileToOpen = fopen(csvfile, "r");

    // get first line
    fgets(line, 3000, fileToOpen);
    char temp[strlen(line) + 1];
    strcpy(temp, line);
    int i = 0, colNum = 0;
    double count = 0;
    char *start = temp;
    while (1) {
        // try to extract next field
        char *token = strsep(&start, ",");
        if (token == NULL) return -2.0;  // no more
        i++;
        if (i < 3) {
            continue;
        }
        sscanf(token, "%d.%d - %s (%d)", &ch2, &sec2, typeString, &weight);
        type2 = typeString[0];
        if (ch1 == ch2 && sec1 == sec2 && type1 == type2) {  // found column
            colNum = i;
            //    printf("Found %s at %d\n", token, i);
            if (weight == 0) {
                return -1.0;
            }
            break;
        }
    }

    while (1) {
        fgets(line, 3000, fileToOpen);  // get next student
        if (feof(fileToOpen)) {
            break;
        }
        char temp[strlen(line) + 1];
        strcpy(temp, line);
        int i = 1;
        char *start = temp;
        while (1) {
            // try to extract next field
            char *token = strsep(&start, ",");
            if (token == NULL) break;  // no more
            // if (i == 2 && strlen(token) > 0){
            //     max = atof(token);
            // }
            else if (i == colNum && IsBlank(token) == 0) {
                if (atof(token) >= threshold) {
                    count++;
                }
            }

            i++;
        }
    }

    // printf("are extracted from %s\n", line);
    fclose(fileToOpen);
    return count;
}

double getGrade(char csvfile[], char first[], char last[]) {
    char line[3000], header[3000];
    // open file
    FILE *fileToOpen;
    fileToOpen = fopen(csvfile, "r");
    double grade = 0, totalWeight = 0;
    // get first line
    fgets(header, 3000, fileToOpen);
    char temp[strlen(header) + 1];
    strcpy(temp, header);
    // printf("%s\n", temp);
    char *start = temp;
    char *token = strsep(&start, ",");
    token = strsep(&start, ",");
    token = token + 1 - 1;

    // printf("%s\n", token);
    while (1) {
        fgets(line, 3000, fileToOpen);
        if (feof(fileToOpen)) {
            break;
        }

        // line vars
        char temp2[strlen(line) + 1];
        strcpy(temp2, line);
        // printf("%s\n", temp2);
        int i = 0;
        char *start2 = temp2;
        char *token2 = strsep(&start2, ",");
        // printf("%s ", token2);
        if (strcasecmp(last, token2) != 0) {
            continue;
        }
        token2 = strsep(&start2, ",");
        // printf("%s\n", token2);
        if (strcasecmp(first, token2)) {
            continue;
        }
        // printf("%s\n", start2);
        // header vars
        while (1) {
            // try to extract next field
            char *token2 = strsep(&start2, ",");         // line
            char *token = strsep(&start, ",");           // header
            if (token == NULL || token2 == NULL) break;  // no more
            // printf("%s\n%s", token, token2);
            int ch, sec, weight;
            char typeString[30];
            sscanf(token, "%d.%d - %s (%d)", &ch, &sec, typeString, &weight);
            totalWeight = totalWeight + weight;
            // printf("%d\n", weight);
            if (IsBlank(token) == 0) {
                grade = grade + (atof(token2) * weight);
            }
        }

        i++;
    }
    grade = grade / totalWeight;
    fclose(fileToOpen);
    return grade;
}

int IsBlank(char arr[]) {
    for (int i = 0; i < strlen(arr); i++) {
        if (!isspace(arr[i])) {
            return 0;
        }
    }

    return 1;
}
