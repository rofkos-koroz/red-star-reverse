#include <stdint.h>

int32_t rt_check_thread_void (int32_t arg_8h) {
	unsigned long var_1ch;
	const char * request;
	int32_t var_8h;
	/* rt_check_thread(void*) */
	eax = gfd;
	edi = arg_8h;
	if (eax < 0) {
		goto label_1;
	}
	esi = edi * 0x18;
	ioctl (eax, 0x7205);
	esi += check_lock;
	printf_chk (1, "check thread main\n");
	eax = edi*8 + rts_scan_list;
	var_1ch = eax;
	while (var_1ch != ebx) {
		edx = *(ebx);
		eax = *((ebx + 4));
		*((edx + 4)) = eax;
		*(eax) = edx;
		*((ebx + 4)) = 0;
		*(ebx) = 0;
		ebx -= 4;
		pthread_mutex_unlock (esi);
		file_check(rts_file_struct*,int) (ebx, edi);
		eax = gfd;
		ioctl (eax, ebx, 0x7207);
		free (ebx);
label_0:
		pthread_mutex_lock (esi);
		ebx = *((edi*8 + rts_scan_list));
	}
	pthread_mutex_unlock (esi);
	eax = usleep (1);
	goto label_0;
label_1:
	eax = 0;
	return eax;
}

