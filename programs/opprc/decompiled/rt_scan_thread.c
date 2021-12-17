#include <stdint.h>

int32_t rt_scan_thread_void (int32_t arg_8h) {
	int32_t var_103ch;
	int32_t var_1038h;
	int32_t var_1034h;
	int32_t var_1030h;
	int32_t var_102ch;
	unsigned long var_1020h;
	int32_t var_101ch;
	const char * path;
	int32_t var_1ch;
	const char * request;
	size_t n;
	int32_t var_ch;
	/* rt_scan_thread(void*) */
	eax = arg_8h;
	edx = *(gs:0x14);
	var_1ch = *(gs:0x14);
	edx = 0;
	ebx = &var_101ch;
	var_1030h = eax;
	eax = gfd;
	if (eax < 0) {
		goto label_5;
	}
	ioctl (eax, 0x7205);
	eax = printf_chk (1, "scan thread main\n");
	eax = var_1030h * 0x18;
	edx = eax + scan_lock;
	eax += remove_lock;
	var_1034h = eax;
	eax = var_1030h;
	var_102ch = edx;
	edx = &path;
	var_103ch = edx;
	eax = eax*8 + rts_scan_list;
	var_1038h = eax;
	do {
label_0:
		eax = 0;
		edi = ebx;
		ecx = 0x400;
		memset (edi, eax, ecx);
		edx = var_102ch;
		pthread_mutex_lock (edx);
		eax = gfd;
		eax = get_file(int,char*,unsignedint,int) (eax, 0x1f4, 0x1000, ebx);
		esi = eax;
		eax = var_102ch;
		pthread_mutex_unlock (eax);
		if (esi != 0) {
			goto label_6;
		}
		var_1020h = 0;
		if (*((ebx + 0x1c)) != 0) {
			esi = var_103ch;
			ecx = 0x23;
			edi = "/root/.kde/share/config/kdeglobals";
			__asm ("repe cmpsb byte [esi], byte ptr es:[edi]");
			if (*((ebx + 0x1c)) == 0) {
				goto label_1;
			}
			esi = var_103ch;
			ecx = 0x13;
			edi = "/root/debuglog.txt";
			__asm ("repe cmpsb byte [esi], byte ptr es:[edi]");
			if (*((ebx + 0x1c)) != 0) {
				goto label_7;
			}
		}
label_1:
		eax = *((ebx + 0x10));
		if (eax == 1) {
			goto label_8;
		}
	} while (eax != 7);
label_8:
	eax = gfd;
	*((ebx + 0x10)) = 4;
	ioctl (eax, ebx, 0x7207);
	goto label_0;
label_6:
	usleep (1);
	goto label_0;
label_7:
	edx = var_102ch;
	pthread_mutex_lock (edx);
	eax = *(ebx);
	eax = GetViewerPID(int,char const*) (eax, "./soffice.bin");
	if (eax == 0) {
		goto label_9;
	}
	eax = var_102ch;
	pthread_mutex_unlock (eax);
	eax = gszOSTemp;
	edx = &path;
	eax = strncmp (edx, 5, eax);
	if (eax == 0) {
		goto label_1;
	}
label_9:
	eax = var_102ch;
	pthread_mutex_unlock (eax);
	edx = &var_1020h;
	eax = *((ebx + 0x10));
	eax = &path;
	eax = isRegularFile(char*,long,int*) (eax, edx, *((ebx + 0x10)));
	if (eax == 0) {
		goto label_1;
	}
	eax = *((ebx + 0x10));
	if (eax == 1) {
		goto label_10;
	}
	if (eax == 7) {
		goto label_11;
	}
	if (eax == 3) {
		goto label_12;
	}
	do {
label_3:
		eax = &path;
		access (eax, 0);
		goto label_1;
label_10:
		edx = &path;
		al = our_filter_file(char*) (edx);
		*((ebx + 0x14)) = ax;
	} while (al < 0);
label_2:
	eax = *((ebx + 0x18));
	eax += 0x1c;
	eax = malloc (eax);
	esi = eax;
	if (eax == 0) {
		goto label_0;
	}
	eax = *((ebx + 0x18));
	edi = esi + 4;
	eax += 0x1c;
	memcpy (esi, ebx, eax);
	edx = var_102ch;
	*((esi + 4)) = edi;
	*((esi + 8)) = edi;
	pthread_mutex_lock (edx);
	edx = var_1030h;
	eax = *((edx*8 + rts_scan_list));
	*((eax + 4)) = edi;
	*((esi + 4)) = eax;
	eax = var_1038h;
	*((edx*8 + rts_scan_list)) = edi;
	edx = var_102ch;
	*((esi + 8)) = eax;
	pthread_mutex_unlock (edx);
	goto label_0;
label_11:
	eax = &path;
	ax = our_filter_file(char*) (eax);
	*((ebx + 0x14)) = ax;
	eax = (int32_t) al;
	if (eax >= 0) {
label_4:
		eax = var_1020h;
		*((ebx + 0x16)) = ax;
		goto label_2;
label_12:
		edx = var_1034h;
		pthread_mutex_lock (edx);
		eax = &path;
		RemoveOpenFile(SEncodedFileMgr*,char*) (gsEncodedFileMgr, eax);
		edx = var_1034h;
		eax = pthread_mutex_unlock (edx);
		goto label_0;
	}
	if (eax == 0xfffffff6) {
		goto label_3;
	}
	if (var_1020h != 1) {
		goto label_3;
	}
	eax = *(ebx);
	eax = GetViewerPID(int,char const*) (eax, 0);
	if (eax != 1) {
		goto label_3;
	}
	goto label_4;
label_5:
	eax = 0;
	edx = var_1ch;
	edx ^= *(gs:0x14);
	if (eax == 1) {
		return eax;
	}
	return stack_chk_fail ();
}

