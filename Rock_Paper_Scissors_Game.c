#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* userInputChecker();
int* gameLogic(char* computerChoice, char* userChoice, int userScore, int computerScore);

int main() {
    srand(time(NULL));
    char* choices[] = { "rock", "paper", "scissors" };

    printf("Welcome to the game!\n");
    printf("Enter:\n");
    printf("r for rock\n");
    printf("p for paper\n");
    printf("s for scissors\n");

    printf("Enter your name: ");
    char playerName[100];
    fgets(playerName, sizeof(playerName), stdin);
    playerName[strcspn(playerName, "\n")] = '\0';

    int userScoreTotal = 0;
    int computerScoreTotal = 0;
    int i = 1;

    while (i == 1) {
        char* userChoice = userInputChecker();
        while (strcmp(userChoice, "") == 0) {
            userChoice = userInputChecker();
        }

        char* computerChoice = choices[rand() % 3];
        printf("Computer chooses: %s\n", computerChoice);

        int* scores = gameLogic(computerChoice, userChoice, userScoreTotal, computerScoreTotal);
        i = scores[0];
        userScoreTotal = scores[1];
        computerScoreTotal = scores[2];

        if (i == 0) {
            printf("Scores for this match are as follows:\n");
            printf("%s's score: %d\n", playerName, userScoreTotal);
            printf("Computer's score: %d\n", computerScoreTotal);
            printf("Thank you for playing the game.\n");
            printf("Have a nice day!\n");
        }
        else if (i != 0 && i != 1) {
            printf("Invalid Input!\n");
            printf("Please enter 1 to continue or 0 to leave the game: ");
            scanf("%d", &i);
            getchar();
        }
    }

    return 0;
}

char* userInputChecker() {
    printf("Enter your choice: ");
    char userChoice[2];
    fgets(userChoice, sizeof(userChoice), stdin);
    userChoice[strcspn(userChoice, "\n")] = '\0';
    if (strcmp(userChoice, "r") == 0 || strcmp(userChoice, "p") == 0 || strcmp(userChoice, "s") == 0) {
        return strdup(userChoice);
    }
    else {
        printf("Wrong Input!!\n");
        return "";
    }
}

int* gameLogic(char* computerChoice, char* userChoice, int userScore, int computerScore) {
    static int scores[3];
    if (strcmp(computerChoice, "rock") == 0 && strcmp(userChoice, "p") == 0) {
        printf("Player Wins\n");
        printf("Enter 1 to continue and 0 to leave the game\n");
        userScore += 1;
        scanf("%d", &scores[0]);
        getchar();
        scores[1] = userScore;
        scores[2] = computerScore;
        return scores;
    }
    else if (strcmp(computerChoice, "rock") == 0 && strcmp(userChoice, "s") == 0) {
        printf("Computer Wins\n");
        printf("Enter 1 to continue and 0 to leave the game\n");
        computerScore += 1;
        scanf("%d", &scores[0]);
        getchar();
        scores[1] = userScore;
        scores[2] = computerScore;
        return scores;
    }
    else if (strcmp(computerChoice, "paper") == 0 && strcmp(userChoice, "r") == 0) {
        printf("Computer Wins\n");
        printf("Enter 1 to continue and 0 to leave the game\n");
        computerScore += 1;
        scanf("%d", &scores[0]);
        getchar();
        scores[1] = userScore;
        scores[2] = computerScore;
        return scores;
    }
    else if (strcmp(computerChoice, "paper") == 0 && strcmp(userChoice, "s") == 0) {
        printf("Player Wins\n");
        printf("Enter 1 to continue and 0 to leave the game\n");
        userScore += 1;
        scanf("%d", &scores[0]);
        getchar();
        scores[1] = userScore;
        scores[2] = computerScore;
        return scores;
    }
    else if (strcmp(computerChoice, "scissors") == 0 && strcmp(userChoice, "r") == 0) {
        printf("Player Wins\n");
        printf("Enter 1 to continue and 0 to leave the game\n");
        userScore += 1;
        scanf("%d", &scores[0]);
        getchar();
        scores[1] = userScore;
        scores[2] = computerScore;
        return scores;
    }
    else if (strcmp(computerChoice, "scissors") == 0 && strcmp(userChoice, "p") == 0) {
        printf("Computer Wins\n");
        printf("Enter 1 to continue and 0 to leave the game\n");
        computerScore += 1;
        scanf("%d", &scores[0]);
        getchar();
        scores[1] = userScore;
        scores[2] = computerScore;
        return scores;
    }
    else if (strcmp(computerChoice, userChoice) == 0) {
        printf("Draw\n");
        printf("Enter 1 to continue and 0 to leave the game\n");
        userScore += 1;
        computerScore += 1;
        scanf("%d", &scores[0]);
        getchar();
        scores[1] = userScore;
        scores[2] = computerScore;
        return scores;
    }

    return scores;
}
