#include "Logic.h"


void saveUser(User user) {
    FILE *file = fopen(USERS_FILE, "ab");
    if (file == NULL) {
        printf("无法打开用户文件\n");
        return;
    }
    fwrite(&user, sizeof(User), 1, file);
    fclose(file);
}

int findUser(const char *username, User *user) {
    FILE *file = fopen(USERS_FILE, "rb");
    if (file == NULL) {
        printf("无法打开用户文件\n");
        return 0;
    }
    User temp;
    while (fread(&temp, sizeof(User), 1, file) == 1) {
        if (strcmp(temp.username, username) == 0) {
            *user = temp;
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void registerUser() {
    User newUser;
    printf("请输入用户名: ");
    scanf("%s", newUser.username);
    printf("请输入密码: ");
    scanf("%s", newUser.password);
    saveUser(newUser);
    printf("注册成功!\n");
}

int loginUser() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    printf("请输入用户名: ");
    scanf("%s", username);
    printf("请输入密码: ");
    scanf("%s", password);

    User user;
    if (findUser(username, &user)) {
        if (strcmp(user.password, password) == 0) {
            printf("登录成功!\n");
            return 1;
        } else {
            printf("密码错误!\n");
        }
    } else {
        printf("用户名不存在!\n");
    }
    return 0;
}

void userManagement() {
    int choice;
    do {
        printf("1. 注册\n");
        printf("2. 登录\n");
        printf("3. 退出\n");
        printf("请选择: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser()) {
                    // 登录成功后可以进行游戏选择等操作
                    UserSelectGame();
                }
                break;
            case 3:
                printf("退出用户管理\n");
                break;
            default:
                printf("无效选择，请重新选择\n");
                break;
        }
    } while (choice != 3);
}

int Logic_main() {
    userManagement();
    return 0;
}
