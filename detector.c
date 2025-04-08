#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define OBJDUMP_CMD "objdump -d %s | grep -A 20 '<_start>:'"


void patch_call_to_nop(const char *filename, unsigned long call_offset) {
    FILE *file = fopen(filename, "r+b"); // 二进制读写模式
    if (!file) {
        perror("无法打开文件");
        exit(1);
    }

    // 定位到 call 指令的位置
    fseek(file, call_offset, SEEK_SET);
    printf("call_offset in func: %ld ",call_offset);

    // 验证是否是 call 指令（可选）
    unsigned char opcode;
    fread(&opcode, 1, 1, file);
    printf("opcode: %hx ",opcode);
    if (opcode != 0xe8) {
        printf("错误：预期位置不是 call 指令\n");
        fclose(file);
        return;
    }

    fseek(file, call_offset, SEEK_SET);
    fputc(0xeb, file);
    fputc(0x03, file);
    fputc(0x90, file);
    fputc(0x90, file);
    fputc(0x90, file);

    fclose(file);
    printf("成功修补文件：替换 call 指令为 jmp\n");
}


char* is_infected(const char *binary) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), OBJDUMP_CMD, binary);
    
    FILE *pipe = popen(cmd, "r");
    if (!pipe) {
        perror("popen failed");
        return 0;
    }

    char line[256];
    int found_suspicious_call = 0;
    char *address = NULL;
    while (fgets(line, sizeof(line), pipe)) {
        if (strstr(line, "call") && 
            !strstr(line, "__libc_start_main") && 
            !strstr(line, "__stack_chk_fail") &&
            !strstr(line, "syscall") &&
            !strstr(line, "main")
        ) {
            printf("发现可疑调用: %s", line);
            address = strtok(line, ":");
            printf("line: %s\n", line);
            found_suspicious_call = 1;
            break;
        }
    }
    pclose(pipe);
    return address;
}



int main(int argc, char **argv) {
    
    if (argc < 2) {
        printf("用法: %s <可执行文件>\n", argv[0]);
        return 1;
    }

    // unsigned long text_va, text_offset;
    // get_text_section_info(argv[1], &text_va, &text_offset);

    char * line = is_infected(argv[1]);
    printf("line in main:%s\n",line);
    char* endptr;
    unsigned long call_va;
    call_va = strtol(line, &endptr, 16);

    // unsigned long call_file_offset = call_va ;
    // printf("call_file_offset: %ld\n",call_file_offset);
    // printf("call_via: %ld\n",call_va);
    // printf("text_va: %ld\n",text_va);
    // printf("text_offset: %ld\n",text_offset);

    if (line!=NULL) {
        printf("[%s] 可能被感染！\n", argv[1]);
        // TODO: 可以在这里修补二进制文件，跳过恶意调用
        patch_call_to_nop(argv[1],call_va);
    } else {
        printf("[%s] 未检测到感染\n", argv[1]);
    }

    return 0;
}