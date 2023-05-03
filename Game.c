#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

//                                  ASSIGNMENT 2 !!!!!

//Function that checks names(length, first letter is capital and other letters are letters)
bool check(char s[]) {
    if (strlen(s) == 0 || strlen(s) > 20) return false;
    if (!isupper(s[0])) return false;
    for (int i = 0; i < strlen(s); i++) {
        if (!isalpha(s[i])) {
            return false;
        }
    }
    return true;
}

//Structure which has information about players
struct Player {
    char names[3001][1001];
    int team[3001];
    int power[3001];
    int visibility[3001];
};


int main() {

    //Opening input and output files using function freopen()
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);



    char magicians[5001][1001]; //Array for magicians' names


    int n; //Amount of magicians names
    scanf("%d", &n);

    //Checking if n is not in [1, 10]
    if (n > 10 || n < 1) {
        printf("Invalid inputs\n");
        return 0;
    }

    //Putting magician names in array magicians
    for (int i = 0; i < n; i++) {
        scanf("%s", magicians[i]);
    }

    //Checking if there are errors in magician names
    for (int i = 0; i < n; i++) {
        if ((check(magicians[i]) == false)) {
            printf("Invalid inputs\n");
            return 0;
        }
    }

    int m; //Amount of players
    scanf("%d", &m);

    //Checking if m is not [n, 100]
    if (m > 100 || m < n) {
        printf("Invalid inputs");
        return 0;
    }


    struct Player pl; //Declaration of a structure


    char visibility[1001]; //Array for visibility of a player, which contains 0s and 1s

    //Putting players' names, powers, team and visibility in structure Player
    for (int i = 0; i < m; i++) {
        scanf("%s", pl.names[i]);
        scanf("%d", &pl.team[i]);
        scanf("%d", &pl.power[i]);
        scanf("%s", visibility);
        if (strcmp(visibility, "False") == 0) {
            pl.visibility[i] = 0;
        } else if (strcmp(visibility, "True") == 0) {
            pl.visibility[i] = 1;
        } else {
            printf("Invalid inputs");
            return 0;
        }
    }



    // Checking if there are error in players names
    for (int i = 0; i < m; i++) {
        if ((check(pl.names[i]) == false)) {
            printf("%s\n", "Invalid inputs");
            return 0;
        }
    }

    // Checking if there are errors in players teams
    for (int i = 0; i < m; i++) {
        if (pl.team[i] >= n || pl.team[i] < 0) {
            printf("%s\n", "Invalid inputs");
            return 0;
        }
    }

    // Checking if there are errors in players powers
    for (int i = 0; i < m; i++) {
        if (pl.power[i] > 1000 || pl.power[i] < 0) {
            printf("%s\n", "Invalid inputs");
            return 0;
        }
    }

    //Creating array of errors which will contain all errors in program, excluding invalid inputs
    char array_of_errors[2001][1001];
    int error_index = 0;


    char action[10001]; //Array which contains action names
    int count_s = 0; //Counter of actions
    int super_index = 0;
    while (scanf("%s", action) != EOF) {

        count_s += 1;
        //Checking if amount of actions is more than 1000
        if (count_s > 1000) {
            printf("%s\n", "Invalid inputs");
            return 0;
        }

        //Flip_visibility action
        if (strcmp(action, "flip_visibility") == 0) {
            char name[1001];
            scanf("%s", name);
            int pl_index = -1;
            for (int i = 0; i < m; i++) {
                if (strcmp(name, pl.names[i]) == 0) {
                    pl_index = i;
                    break;
                }
            }
            if (pl_index == -1) {
                printf("%s\n", "Invalid inputs");
                return 0;
            }

            //Checking if player is frozen
            if (pl.power[pl_index] == 0) {
                strcpy(array_of_errors[error_index], "This player is frozen");
                error_index++;
                continue;
            }

            // Changing visibility for a player
            if (pl.visibility[pl_index] == 0) {
                pl.visibility[pl_index] = 1;
            } else {
                pl.visibility[pl_index] = 0;
            }
            continue;
        }

        char player1[1001]; //Array for playeri
        char player2[1001]; //Array for playerj

        scanf("%s", player1);
        scanf("%s", player2);

        int pl_index1 = -1; //Index of a playeri in structure
        int pl_index2 = -1; //Index of a playerj in structure

        for (int i = 0; i < m; i++) {

            if ((strcmp(player1, pl.names[i]) == 0)) {
                pl_index1 = i;
            }
            if ((strcmp(player2, pl.names[i]) == 0)) {
                pl_index2 = i;
            }
        }
        //Checking if there are no such players in structure
        if (pl_index1 == -1 || pl_index2 == -1) {
            printf("%s\n", "Invalid inputs");
            return 0;
        }


        //Attack action
        if (strcmp(action, "attack") == 0) {
            //Checking if playeri has visibility equal to 0
            if (pl.visibility[pl_index1] == 0) {
                strcpy(array_of_errors[error_index], "This player can't play");
                error_index++;
                continue;
            }
            //Checking if playeri is frozen
            if (pl.power[pl_index1] == 0) {
                strcpy(array_of_errors[error_index], "This player is frozen");
                error_index++;
                continue;
            }

            //Performing attack action(also checking if sum of players powers is more than 1000)
            if (pl.visibility[pl_index2] == 0) {
                pl.power[pl_index1] = 0;
            } else if (pl.power[pl_index1] == pl.power[pl_index2]) {
                pl.power[pl_index1] = 0;
                pl.power[pl_index2] = 0;
            } else if (pl.power[pl_index1] > pl.power[pl_index2]) {
                pl.power[pl_index1] += (pl.power[pl_index1] - pl.power[pl_index2]);
                if (pl.power[pl_index1] > 1000) {
                    pl.power[pl_index1] = 1000;
                }
                pl.power[pl_index2] = 0;
            } else if (pl.power[pl_index1] < pl.power[pl_index2]) {
                pl.power[pl_index2] += (pl.power[pl_index2] - pl.power[pl_index1]);
                if (pl.power[pl_index2] > 1000) {
                    pl.power[pl_index2] = 1000;
                }
                pl.power[pl_index1] = 0;
            }
            continue;
        }




        //Heal action
        if (strcmp(action, "heal") == 0) {
            //Checking if visibility of playeri is equal to 0
            if (pl.visibility[pl_index1] == 0) {
                strcpy(array_of_errors[error_index], "This player can't play");
                error_index++;
                continue;
            }
            //Checking if playeri is frozen
            if (pl.power[pl_index1] == 0) {
                strcpy(array_of_errors[error_index], "This player is frozen");
                error_index++;
                continue;
            }
            //Checking if players are not from the same team
            if (pl.team[pl_index1] != pl.team[pl_index2]) {
                strcpy(array_of_errors[error_index], "Both players should be from the same team");
                error_index++;
                continue;
            }

            if (pl_index1 == pl_index2) {
                strcpy(array_of_errors[error_index], "The player cannot heal itself");
                error_index++;
                continue;
            }

            //Performing heal action(also checking if we can divide players' power by 2)
            if (pl.power[pl_index1] % 2 == 0) {
                pl.power[pl_index2] += pl.power[pl_index1] / 2;
                if (pl.power[pl_index2] > 1000) {
                    pl.power[pl_index2] = 1000;
                }
                pl.power[pl_index1] /= 2;
            } else {
                pl.power[pl_index2] += pl.power[pl_index1] / 2 + 1;
                if (pl.power[pl_index2] > 1000) {
                    pl.power[pl_index2] = 1000;
                }
                pl.power[pl_index1] = pl.power[pl_index1] / 2 + 1;
            }
            continue;
        }



        //Super action
        if (strcmp(action, "super") == 0) {
            //Checking if visibility of playeri is equal to 0
            if (pl.visibility[pl_index1] == 0) {
                strcpy(array_of_errors[error_index], "This player can't play");
                error_index++;
                continue;
            }
            //Checking if playeri is frozen
            if (pl.power[pl_index1] == 0) {
                strcpy(array_of_errors[error_index], "This player is frozen");
                error_index++;
                continue;
            }
            //Checking if players are not from the same team
            if (pl.team[pl_index1] != pl.team[pl_index2]) {
                strcpy(array_of_errors[error_index], "Both players should be from the same team");
                error_index++;
                continue;
            }

            if (pl_index1 == pl_index2) {
                strcpy(array_of_errors[error_index], "The player cannot do super action with itself");
                error_index++;
                continue;
            }

            char str_index[1001];
            sprintf(str_index, "%d", super_index);
            super_index += 1;
            strcpy(pl.names[pl_index1], "S_");
            strcat(pl.names[pl_index1], str_index);

            //Performing super action(also checking if sum of powers of players' is more than 1000)
            if (pl.power[pl_index1] + pl.power[pl_index2] > 1000) {
                pl.power[pl_index1] = 1000;
            } else {
                pl.power[pl_index1] = pl.power[pl_index1] + pl.power[pl_index2];
            }
            pl.visibility[pl_index1] = 1;

            //Deleting name of playerj from structure
            strcpy(pl.names[pl_index2], "");
            pl.power[pl_index2] = 0;
            continue;
        }

        printf("%s\n", "Invalid inputs"); //Printing invalid inputs if there is unknown action
        return 0;
    }


    //Printing all errors
    for (int i = 0; i < error_index; i++) {
        printf("%s\n", array_of_errors[i]);
    }


    int team_power[100]; // Array that will contain sum of all players' power who are from the same team
    for (int i = 0; i < n; i++) {
        team_power[i] = 0;
    }

    // Filling array with sums
    for (int i = 0; i < m; i++) {
        team_power[pl.team[i]] += pl.power[i];
    }

    int max_wizard = -123;
    int wizard_index;
    int count = 0;

    //Finding wizard or printing "It's a tie" if there are more than one wizard
    for (int i = 0; i < n; i++) {
        if (max_wizard < team_power[i]) {
            max_wizard = team_power[i];
            wizard_index = i;
            count = 1;
        } else if (max_wizard == team_power[i]) {
            count += 1;
        }
    }
    if (count > 1) {
        printf("%s\n", "It's a tie");
    } else {
        printf("The chosen wizard is %s\n", magicians[wizard_index]);
    }

    return 0;
}