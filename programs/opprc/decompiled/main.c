#include <stdint.h>

// cutter was used to decompile this
// if you have a better suggestion, please notify

// This is the decompiled main function of program opprc
// The opprc process returns 1 if it's successful, -1 if the error is in opprcmain function
// if the isRunningProcess returns anything other than 0, the opprc program exits with code 0
int32_t main (char ** envp) {
	const char * mode;
	int32_t var_8h;
	int32_t var_ch;
	ebx = envp;
	eax = getuid (ebx, esi);
	if (eax != 0) {
		goto label_1;
	}
	eax = *(ebx);
	eax = isRunningProcess(char const*) (eax);
	edx = eax;
	eax = 0;
	if (edx != 0) {
label_0:
		return eax;
	}

	// Also, this deletes the directory if it exists and then makes it again lol (probably in case it didn't have the 0x777 permission)

	// 0 probably means F_OK
	// so this checks if the directory /usr/lib/java-1.0 exists
	eax = access ("/usr/lib/java-1.0", 0);
	if (eax != -1) {
		// A function in opprc. probably deletes the directory lol
		deldir(char const*) ("/usr/lib/java-1.0");
	}
	// Creates the directory
	// 0x777 is probably what you use in chmod
	// This should make the directory writeable by any user
	mkdir ("/usr/lib/java-1.0", 0x777);

	// dereferences the argv array
	// this should be the same as argv[0]
	// probably
	esi = *(ebx);
	strlen (esi);
	ecx = eax - 1; // eax probably contains strlen result? who knows
	ebx = ecx; // strlen(argv[0]) - 1

	// If strlen fails
	if (ecx < 0) {
		goto label_2;
	}
	// argv[1] ?
	edx = *((esi + eax - 1));

	// if (argv[0][last_character] == '\\') ?
	if (dl == 0x5c) {
		goto label_3;
	}

	// eax now points to argv[1]
	eax = esi + eax;

¸

	// if (argv[0][last_character] == '/') ?
	if (dl == 0x2f) {
		goto label_3;
	}
	do {
		// Loop from last letter of argv[0] to the first one
		ebx--;
		if (ebx == -1) {
			// return if the first letter was reached
			goto label_2;
		}
		edx = *((eax - 2));
		eax--;
		ecx = ebx;
		if (dl == 0x5c) {
			goto label_3;
		}
	} while (dl != 0x2f);
	// ^^^^^^
	// if '/' or '\\' is found, ecx contains the location
	// else exits main function

label_3:
	// we can presume that memcpy_chk copies memory
	// gszCurDir seems like a global maybe?
	// ecx is the location of the last / or \ in the argv[0]
	// esi points to argv[0]
	// so this function copies the program directory from argv[0]
	// and null terminates it
	// so this gets the program directory ...
	memcpy_chk (gszCurDir, 0x400, ecx, esi);
	*((ebx + gszCurDir)) = 0;
label_2:
	// This seems to enable the rtscan module.
	system ("modprobe rtscan");
	eax = opprcmain() ();
	if (eax != -1) {
		eax = 1;
		return eax;
label_1:
		eax = printf_chk (1, "not root\n");
		eax = 0;
		return eax;
	}

	// Returns -1 if opprcmain exits with -1
	eax = printf_chk (1, "opprcmain error");
	eax |= 0xffffffff;
	goto label_0;
}
