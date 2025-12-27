#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <string.h>

#define FILENAME "users.txt"

void goodRemarks(int i);
void badRemarks(int i);
int MixtureQuiz(int level, int range, int operationChoice);
int levelOneMixture(int operationChoice, int level);
int levelTwoMixture(int operationChoice, int level);
int levelThreeMixture(int operationChoice, int level);
int MixtureChoice(int operationChoice);
int welcomeMessage(void);
int getIntWithTimeout(time_t startTime, int TIME_LIMIT);
float getFloatWithTimeout(time_t startTime, int TIME_LIMIT);
void removeNewline(char *str);
int usernameExists(const char *username);
void signup();
int login();

void removeNewline(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}

int usernameExists(const char *username)
{
    FILE *fp = fopen(FILENAME, "r");
    if (!fp) return 0;

    char line[200];
    while (fgets(line, sizeof(line), fp))
    {
        char fileUser[100], filePass[100];
        sscanf(line, "%[^|]|%[^\n]", fileUser, filePass);
        if (strcmp(username, fileUser) == 0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void signup()
{
    char username[100], password[100];

    while (1)
    {
        printf("Enter a username: ");
        fgets(username, sizeof(username), stdin);
        removeNewline(username);

        if (usernameExists(username))
        {
            printf("This username already exists! Choose another.\n");
        }
        else
            break;
    }

    printf("Enter a password: ");
    fgets(password, sizeof(password), stdin);
    removeNewline(password);

    FILE *fp = fopen(FILENAME, "a");
    if (!fp)
    {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp, "%s|%s\n", username, password);
    fclose(fp);

    printf("Signup successful! You can now login.\n");
}

int login()
{
    char username[100], password[100];
    int attempts = 3;

    while (attempts--)
    {
        printf("Enter username: ");
        fgets(username, sizeof(username), stdin);
        removeNewline(username);

        printf("Enter password: ");
        fgets(password, sizeof(password), stdin);
        removeNewline(password);

        FILE *fp = fopen(FILENAME, "r");
        if (!fp)
        {
            printf("No users found! Please signup first.\n");
            return 0;
        }

        int found = 0;
        char line[200];
        while (fgets(line, sizeof(line), fp))
        {
            char fileUser[100], filePass[100];
            sscanf(line, "%[^|]|%[^\n]", fileUser, filePass);
            if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0)
            {
                found = 1;
                break;
            }
        }
        fclose(fp);

        if (found)
        {
            printf("\nLogin successful!\n");
            return 1;
        }
        else
        {
            printf("Invalid username or password. ");
            if (attempts > 0) printf("Try again.\n");
            else printf("No attempts left.\n");
        }
    }
    return 0;
}


int getIntWithTimeout(time_t startTime, int TIME_LIMIT)
{
    int value = 0, digit, finished = 0, negative = 0;

    while (!finished)
    {
        if (time(NULL) - startTime >= TIME_LIMIT)
            return -1;

        if (kbhit())
        {
            int ch = getch();
            if (ch >= '0' && ch <= '9')
            {
                digit = ch - '0';
                value = value * 10 + digit;
                putchar(ch);
            }
            else if (ch == '\r')
            {
                finished = 1;
                printf("\n");
            }
            else if (ch == '\b')
            {
                value /= 10;
                printf("\b \b");
            }
            else if (ch == '-' && value == 0)
            {
                negative = 1;
                putchar(ch);
            }
        }
    }
    if (negative)
        value = -value;
    return value;
}

float getFloatWithTimeout(time_t startTime, int TIME_LIMIT)
{
    float value = 0.0f, fraction = 0.0f, divisor = 10.0f;
    int decimal_point = 0, finished = 0, negative = 0;

    while (!finished)
    {
        if (time(NULL) - startTime >= TIME_LIMIT)
            return -9999.0f;

        if (kbhit())
        {
            int ch = getch();
            if (ch >= '0' && ch <= '9')
            {
                int digit = ch - '0';
                if (!decimal_point)
                    value = value * 10 + digit;
                else
                {
                    fraction += digit / divisor;
                    divisor *= 10.0f;
                }
                putchar(ch);
            }
            else if (ch == '.')
            {
                if (!decimal_point)
                {
                    decimal_point = 1;
                    putchar(ch);
                }
            }
            else if (ch == '\r')
            {
                finished = 1;
                value += fraction;
                if (negative) value = -value;
                printf("\n");
            }
            else if (ch == '-' && value == 0)
            {
                negative = 1;
                putchar(ch);
            }
        }
    }
    return value;
}

void goodRemarks(int i)
{
    if (i == 0 || i == 7 || i == 4)
        printf("Very Good\n");
    else if (i == 1 || i == 3 || i == 5)
        printf("Excellent\n");
    else if (i == 6 || i == 8)
        printf("Nice Work\n");
    else
        printf("Keep up the good work!\n");
}

void badRemarks(int i)
{
    if (i == 0 || i == 7 || i == 4)
        printf("No, Please try again\n");
    else if (i == 1 || i == 3 || i == 5)
        printf("Wrong, Try once more\n");
    else if (i == 6 || i == 8)
        printf("Don't give up!\n");
    else
        printf("No, Keep trying\n");
}
// Main quiz function
int MixtureQuiz(int level, int range, int operationChoice)
{
    int correctAns = 0, wrongAns = 0;
    int inputAns = 0, ans = 0;
    float inputAnsdiv = 0.0f, ansdiv = 0.0f;
    int random1, random2, operation;
    int proceed;
    int TIME_LIMIT = 2 * 60;
    int timeUp = 0;

    time_t startTime = time(NULL);

    if (level == 1)
        printf("\n\033[1;32mWelcome to the easy level difficulty\033[0m\n");
    else if (level == 2)
        printf("\n\033[1;32mWelcome to the medium level difficulty\033[0m\n");
    else if (level == 3)
        printf("\n\033[1;32mWelcome to the hard level difficulty\033[0m\n");

    printf("\033[1;31mYou have the time limit of 2min best of luck!\033[0m\n");
    printf("\n--------------------------------------------------\n");
    for (int i = 0; i < 10; i++)
    {
        if (time(NULL) - startTime >= TIME_LIMIT)
        {
            timeUp = 1;
            break;
        }

        random1 = 1 + rand() % range;
        random2 = (random1 > 1) ? (1 + rand() % (random1 - 1)) : 1;
        operation = (operationChoice == 5) ? 1 + rand() % 4 : operationChoice;

        if (operation == 1)
        {
            ans = random1 + random2;
            printf("What is the answer of \033[1;32m%d\033[0m + \033[1;32m%d\033[0m : ", random1, random2);
            inputAns = getIntWithTimeout(startTime, TIME_LIMIT);
            if (inputAns == -1)
            {
                timeUp = 1;
                break;
            }
            if (inputAns == ans)
            {
                goodRemarks(i);
                correctAns++;
            }
            else
            {
                printf("\033[1;31mWrong Answer! The correct answer is \033[1;32m%d\033[0m\033[0m\n", ans);
                badRemarks(i);
                wrongAns++;
            }
        }
        else if (operation == 2)
        {
            ans = random1 - random2;
            printf("What is the answer of \033[1;32m%d\033[0m - \033[1;32m%d\033[0m : ", random1, random2);
            inputAns = getIntWithTimeout(startTime, TIME_LIMIT);
            if (inputAns == -1)
            {
                timeUp = 1;
                break;
            }
            if (inputAns == ans)
            {
                goodRemarks(i);
                correctAns++;
            }
            else
            {
                printf("\033[1;31mWrong Answer! The correct answer is \033[1;32m%d\033[0m\033[0m\n", ans);
                badRemarks(i);
                wrongAns++;
            }
        }
        else if (operation == 3)
        {
            ans = random1 * random2;
            printf("What is the answer of \033[1;32m%d\033[0m X \033[1;32m%d\033[0m : ", random1, random2);
            inputAns = getIntWithTimeout(startTime, TIME_LIMIT);
            if (inputAns == -1)
            {
                timeUp = 1;
                break;
            }
            if (inputAns == ans)
            {
                goodRemarks(i);
                correctAns++;
            }
            else
            {
                printf("\033[1;31mWrong Answer! The correct answer is \033[1;32m%d\033[0m\033[0m\n", ans);
                badRemarks(i);
                wrongAns++;
            }
        }
        else if (operation == 4)
        {
            ansdiv = (float)random1 / random2;
            printf("What is the answer of \033[1;32m%d\033[0m / \033[1;32m%d\033[0m : ", random1, random2);
            inputAnsdiv = getFloatWithTimeout(startTime, TIME_LIMIT);
            if (inputAnsdiv == -9999.0f)
            {
                timeUp = 1;
                break;
            }
            if (fabs(inputAnsdiv - ansdiv) < 0.01f)
            {
                goodRemarks(i);
                correctAns++;
            }
            else
            {
                printf("\033[1;31mWrong Answer! The correct answer is \033[1;32m%.2f\033[0m\033[0m\n", ansdiv);
                badRemarks(i);
                wrongAns++;
            }
        }
    }

    printf("\n--------------------------------------------------\n");
    if (timeUp)
    {
        printf("\033[1;31mTime's up! Level ended.\033[1;32m\n");
        printf("\n--------------------------------------------------\n");
    }

    printf("\n\033[1;36mYou got \033[1;32m%d \033[1;36mcorrect and \033[1;31m%d \033[1;36mwrong.\033[0m\n", correctAns, wrongAns);
    float percentage = (correctAns / 10.0f) * 100;
    printf("\033[1;33mYour score: \033[1;32m%.1f%%\n\033[0m", percentage);
    printf("\n--------------------------------------------------\n");

    if (percentage >= 70.0)
    {
        printf("\033[1;32mYou are ready to go for the next level\033[0m\n");
        printf("Would you like to proceed to the next level? (yes=1/no=2): ");
        proceed = getIntWithTimeout(startTime, TIME_LIMIT);
        printf("\n--------------------------------------------------\n");
        if (proceed == -1)
            return 2;
        return (proceed == 1) ? 1 : 2;

    }
    else
    {
        printf("\n--------------------------------------------------\n");   
        printf("\033[1;31mPlease ask your teacher for extra help\033[0m\n");
        printf("\n--------------------------------------------------\n");    
        return 0;
    }
}

// Level functions
int levelOneMixture(int operationChoice, int level)
{
    int pass = MixtureQuiz(1, 10, operationChoice);
    if (pass == 1)
        levelTwoMixture(operationChoice, level);
    else if (pass == 2)
        printf("\033[1;33mThank you for playing! Goodbye!\033[0m\n");
    printf("\n--------------------------------------------------\n");
    return 0;
}
int levelTwoMixture(int operationChoice, int level)
{
    int pass = MixtureQuiz(2, 100, operationChoice);
    if (pass == 1)
        levelThreeMixture(operationChoice, level);
    else if (pass == 2)
        printf("\033[1;33mThank you for playing! Goodbye!\033[0m\n");
    return 0;
}
int levelThreeMixture(int operationChoice, int level)
{
    int pass = MixtureQuiz(3, 1000, operationChoice);
    if (pass == 1)
        printf("\n\033[1;32mCongratulations! You have completed all levels successfully!\033[0m\n");
    return 0;
}

// Choice selection
int MixtureChoice(int operationChoice)
{
    int choice = 0;
    switch (operationChoice)
    {
    case 1:
        printf("\033[1;32mYou have chosen Addition Quiz!\033[0m\n");
        break;
    case 2:
        printf("\033[1;32mYou have chosen Subtraction Quiz!\033[0m\n");
        break;
    case 3:
        printf("\033[1;32mYou have chosen Multiplication Quiz!\033[0m\n");
        break;
    case 4:
        printf("\033[1;32mYou have chosen Division Quiz!\033[0m\n");
        break;
    case 5:
        printf("\033[1;32mYou have chosen Mixture Quiz!\033[0m\n");
        break;
    default:
        printf("\033[1;31mInvalid choice!\033[0m\n");
        break;
    }
    printf("Select Difficulty Level:\n1. Easy\n2. Medium\n3. Hard\n");
    while (choice < 1 || choice > 3)
    {
        printf("\nEnter your choice (1-3): ");
        choice = getIntWithTimeout(time(NULL), 5 * 60);
        if (choice == -1)
            break;
        if (choice < 1 || choice > 3)
            printf("\033[1;31mInvalid input! Please enter 1,2 or 3: \033[0m\n");
    }
    printf("\n--------------------------------------------------\n");
    if (choice == 1)
        levelOneMixture(operationChoice, choice);
    else if (choice == 2)
        levelTwoMixture(operationChoice, choice);
    else if (choice == 3)
        levelThreeMixture(operationChoice, choice);
    return 0;
}

// Welcomem,
int welcomeMessage()
{
    int op = 0;    
    printf("\n--------------------------------------------------\n");
    printf("\033[1;32mChoose the operation:\033[0m\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Mixture of all operations\n");

    // Infinite loop until valid input
    while (1)
    {
        printf("Enter your choice (1-5): ");
        op = getIntWithTimeout(time(NULL), 5*60);  // 5-minute timeout for input

        if (op >= 1 && op <= 5)
        {
            break; // valid input, exit loop
        }
        else if (op == -1)
        {
            printf("\n\033[1;31mTime's up while waiting for input!\033[0m\n");
            return 5; // default to mixture quiz if time runs out
        }
        else
        {
            printf("\033[1;31mInvalid input! Please enter a number from 1 to 5: \033[0m\n");
        }
    }
    printf("\n--------------------------------------------------\n");
    return op;
}

/* ================== MAIN ================== */

int main(void)
{
    srand(time(0));
    int choice;
    printf("\n--------------------------------------------------\n\n");
    printf("================**** \033[1;32mWELLCOME\033[0m ****================\n\n");
    printf("\033[1;32mHello! Welcome to Arithmetic Quiz Center!\033[0m\n");
    printf("Please sign up if you donot have any account\n");
    printf("\n--------------------------------------------------\n");

    while (1)
    {
        printf("\n1. Signup\n2. Login\n3. Exit\nEnter choice: ");
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // clear buffer
            continue;
        }
        getchar();

        if (choice == 1)
        {
            signup();
        }
        else if (choice == 2)
        {
            if (login())
                break; // login successful, exit loop
        }
        else if (choice == 3)
        {
            printf("Exiting...\n");
            return 0;
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }

    int operationChoice = welcomeMessage();
    MixtureChoice(operationChoice);

    return 0;
}
