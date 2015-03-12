/* © Copyright 1996, Richard M. Troth, all rights reserved.  <plaintext> 
 * 
 *	  Name: uftapi.c 
 *		Unsolicited File Transfer general C API 
 *	Author: Rick Troth, Houston, Texas, USA 
 *	  Date: 1996-Dec-19 
 * 
 */ 
 
/*  this API suite needs to be re-written 
    to support protocols other than TCP/IP  */ 
 
#include	<errno.h> 
#include	"uft.h" 
 
/* ------------------------------------------------------------- UFTOPEN 
 */ 
int uftopen(q,f) 
  { 
    struct  UFTFILE  *uftfile, uftfile0; 
    extern  void  *malloc(); 
 
    errno = 0; 
    uftfd = malloc(sizeof(uftfd0)); 
    if (uftfd == NULL) return NULL; 
 
    switch (f & O_ACCMODE) 
      { 
	O_RDONLY:	/*  receive a file  */ 
		break; 
	O_WRONLY:	/*  send a file  */ 
		break; 
	default: 
		errno = EINVAL; 
		return NULL; 
  } 
 
/* ------------------------------------------------------------ UFTCLOSE 
 */ 
int uftclose(s) 
  { 
    char buffer[256]; 
    (void) tcpputs("QUIT"); 
    (void) uftcwack(s,buffer,sizeof(buffer)); 
    return close(s); 
  } 
 
/*  fopen()?  */ 
/*  fclose()?  */ 
 
 
/*  sending  */ 
uftopen(,O_WRONLY) 
uftwrite(s,b,l) 
  { 
    (void) sprintf("DATA %d",l); 
    (void) putline(s,q); 
  } 
uftwaux(s,b,l) 
uftsetmd()	/*  int setenv(const char *name, const char *value)  */ 
uftputmd()	/*  int putenv(const char *string)  */ 
 
 
/*  receiving  */ 
uftopen(,O_RDONLY) 
uftread() 
uftraux() 
uftgetmd()	/*  getenv  */ 
 
/*  ssize_t getdirentries(int fd, char *buf, size_t nbytes, off_t *basep);
uftstat() 
 






#define 	UFT_PROTOCOL	"UFT/1" 
#define 	UFT_VERSION	"POSIXUFT/1.5" 
#define 	UFT_COPYRIGHT	"© Copyright 1995 Richard M. Troth" 
#define 	UFT_VRM 	"1.5.1" 
 
#define 	UFT_SPOOLDIR	"/usr/spool/uft" 
#define 	UFT_GID 	0 
 
#define 	UFT_SEQFILE		".seq" 
#define 	UFT_SEQFILE_ALT 	"seqno" 
 
#define 	UFT_BINARY	0x8000 
#define 	UFT_VERBOSE	0x4000 
 
#define 	UFT_PORT	608 
#define 	IDENT_PORT	113 
 
#define 	BUFSIZ		64512 
#define 	NULL		0x0000 
 
 

int uftopen(const char *pathname, int flags); 

int uftopens(const char *pathname, int flags); 
int uftopenr(const char *pathname, int flags); 

int uftopen(const char *pathname, int flags, mode_t mode);

int creat(const char *pathname, mode_t mode);

O_CREAT

O_EXCL 

O_NOCTTY

O_TRUNC

O_APPEND

O_NONBLOCK or O_NDELAY

O_SYNC

/*  minimal environment  */ 
REMOTE=@
SIZE=22178
FROM=root
AUTH=IDENT
USER=troth
TYPE=I
NAME=sf


