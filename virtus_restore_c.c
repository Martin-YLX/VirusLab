#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

#define VIRUS_FUNCTION_1 "spread_virus();"
#define VIRUS_FUNCTION_2 "printf(\"Welcome to HNU CSAPP!\\n\");"

// 删除 main 函数中的病毒代码
void remove_virus_code_in_main(const char *filename) {
    FILE *sourceFile = fopen(filename, "r");
    FILE *tempFile = fopen("temp.c", "w");
    char line[256];
    int insideMain = 0;

    if (!sourceFile || !tempFile) {
        perror("Error opening file");
        return;
    }

    // 逐行读取文件内容
    while (fgets(line, sizeof(line), sourceFile)) {
        // 查找 main 函数的开始
        if (strstr(line, "int main(")) {
            insideMain = 1;
        }

        // 如果在 main 函数内，检查并删除病毒相关代码
        if (insideMain) {
            if (strstr(line, VIRUS_FUNCTION_1) || strstr(line, VIRUS_FUNCTION_2)) {
                continue;  // 删除病毒代码行
            }
            // 如果 main 函数结束，则退出
            if (strstr(line, "}")) {
                insideMain = 0;
            }
        }

        // 无论是否在 main 函数内，保留其他代码
        fprintf(tempFile, "%s", line);
    }

    fclose(sourceFile);
    fclose(tempFile);

    // 用临时文件替换原始文件
    remove(filename);
    rename("temp.c", filename);
    printf("%s has been cleaned!\n", filename);
}

// 遍历当前目录并处理所有 .c 文件
void check_and_restore() {
    DIR *dir = opendir(".");
    struct dirent *entry;

    if (dir == NULL) {
        perror("opendir() error");
        return;
    }

    // 遍历目录，查找所有的 .c 文件
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".c") != NULL) {  // 如果文件是 .c 文件
            printf("Cleaning %s...\n", entry->d_name);
            remove_virus_code_in_main(entry->d_name);  // 调用清理函数
        }
    }

    closedir(dir);
}

int main() {
    check_and_restore();  // 执行清理操作
    return 0;
}