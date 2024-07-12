#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <minwindef.h>
#include "Common.h"

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define USERS_FILE "users.dat"
#define Height 25

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void saveUser(User user);

int UserSelectGame();

int GetUserSelect();


int findUser(const char *username, User *user);

void registerUser();

int loginUser();

void userManagement();

int Logic_main();