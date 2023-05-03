#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

//Function that checks if the length of a name is 0, checks if firtst letter is upper case
// and the rest of the letters are lower case
bool check(char s[]) {
    if (strlen(s) == 0 || !isupper(s[0])) return false;
    for (int i = 1; i < strlen(s); i++) {
        if (!islower(s[i])) return false;
    }
    return true;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);


    int count = 0;
    int i = 0, j = 0;
    int n;
    scanf("%d" ,&n);

////    Making sure that 1 <= n <= 100
    if (n > 100 || n < 1) {
        printf("Error in the input.txt");
        return 0;
    }
////    Creating two arrays: sortedNames - where all the sorted names will be placing and name - all the names in file
    char sortedNames[1001][1001], name[1001];

////    Checking if amount of names is less than n
    for (i = 0; i < n; i++) {
        if (scanf("%s", name) == EOF || !check(name)) {
            printf("Error in the input.txt");
            return 0;
        }
        strcpy(sortedNames[count++], name); // copying current name in sortedNames
    }

//     Checking if amount of names is bigger than n
    if (scanf("%s", name) != EOF) {
        printf("Error in the input.txt");
        return 0;
    }

//    Sorting names with Bubble sort and comparing them with strcmp from string.h
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - 1; j++) {
            if (strcmp(sortedNames[j], sortedNames[j + 1]) > 0) {
                char name1[1001];
                strcpy(name1, sortedNames[j]);
                strcpy(sortedNames[j], sortedNames[j + 1]);
                strcpy(sortedNames[j + 1], name1);
            }
        }
    }

////    Putting sorted names in file output.txt
    for (int k = 0; k < n; k++) {
        printf("%s\n", sortedNames[k]);
    }
    printf("%d", 6);

    return 0;
}