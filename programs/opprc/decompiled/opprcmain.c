#include <stdint.h>

uint32_t opprcmain (void) {
	const char * request;
	const char * var_8h;
	int32_t var_ch;
	/* opprcmain() */
	eax = open (ebp, 2);
	*(gfd) = eax;
	if (eax < 0) {
		goto label_2;
	}
	request = sigterm(int);
	signal (0xf);
	request = sigsegvhandler(int);
	signal (0xb);
	request = sigterm(int);
	signal (2);
	request = sigterm(int);
	signal (9);
	eax = DictLoad(char*) (0);
	if (eax != 1) {
		goto label_3;
	}
	eax = gfd;
	eax = ioctl (eax, 0x7204);
	if (eax == 0) {
		goto label_4;
	}
label_0:
	eax = gszExtensionsAuth;
	eax = gfd;
	ioctl (eax, 0x720d, eax);
	eax = gfd;
	ioctl (eax, 0x7205);
	SetProtectFiles(int,int) (0x7208, 0x720b);
	eax = SetCDHistoryProtectFiles(int,int) (0x7208, 0x720b);
	eax = 0;
	*(rts_scan_list) = 0x80fa5e0;
	*(0x80fa5e4) = 0x80fa5e0;
	do {
		*((eax + scan_lock)) = 0;
		eax += 4;
	} while (eax < 0x18);
	eax = 0;
	do {
		*((eax + remove_lock)) = 0;
		eax += 4;
	} while (eax < 0x18);
	eax = pthread_create (threads_scan, 0, rt_scan_thread(void*), 0);
	edx = 0;
	if (eax != 0) {
		goto label_5;
	}
	do {
		*((edx + check_lock)) = 0;
		edx += 4;
	} while (edx < 0x18);
	eax = pthread_create (threads_check, 0, rt_check_thread(void*), 0);
	if (eax != 0) {
		goto label_6;
	}
	pause ();
	eax = threads_scan;
	eax = pthread_join (eax, 0);
	if (eax != 0) {
		goto label_7;
	}
	eax = threads_check;
	eax = pthread_join (eax, 0);
	if (eax != 0) {
		goto label_8;
	}
	DictFree() ();
	SetProtectFiles(int,int) (0x720a, 0x720c);
	SetCDHistoryProtectFiles(int,int) (0x720a, 0x720c);
	eax = gfd;
	ioctl (eax, 0x7209);
	eax = gfd;
	ioctl (eax, 0x7203);
	eax = gfd;
	close (eax);
	eax = 1;
	return eax;
label_4:
	*(rtscan_enable) = 1;
	goto label_0;
label_3:
	system ("reboot");
	eax = 0xffffffff;
	return eax;
label_5:
	do {
label_1:
		eax = *(stderr);
		fprintf_chk (eax, eax, "scan pthread_create failed: %d\n", 1);
		eax = 0xfffffffe;
		return eax;
label_6:
		var_ch = eax;
		var_8h = "check pthread_create failed: %d\n";
	} while (1);
label_7:
	var_ch = eax;
	var_8h = "scan pthread_join failed: %d\n";
	goto label_1;
label_8:
	var_ch = eax;
	var_8h = "check pthread_join failed: %d\n";
	goto label_1;
label_2:
	printf_chk (1, "/dev/res error!\n");
	eax = 0xffffffff;
	return eax;
}

