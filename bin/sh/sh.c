/*
 * sh - shell
 * Usage: up to you
 */

#ifdef HOST
#include "hostcompat.h"
#endif

int
main(int argc, char *argv[])
{
#ifdef HOST
	hostcompat_init(argc, argv);
#endif

	/* Write this */

	(void)argc;
	(void)argv;

	return 1;
}

/*
 *  Simple workaround for system call read(int, char *, int).
 *  This is not how a system call should be implemented. 
 *  But, for now, it works.
 */
int
sys_read(int filehandle, char *buf, size_t size)
{
	(void) filehandle;
	(void) size;
	
	char ch = getch();	
	if(ch == '\r') {
		ch = '\n';
	}
	buf[0] = ch;
	return 1;
}

/*
 *  Implementation of system call write(int, char *, int).
 *  This is not how a system call should be implemented. 
 *  But, for now, it works.
 */
 
int
sys_write(int filehandle, char *buf, size_t size)
{
	(void) filehandle;
	
	size_t i;	
	for (i = 0; i < size; ++i) {
		putch((int)buf[i]);
	}	
	return i;
}
