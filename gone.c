/* 
 *	  Name: gone.c 
 *		first try at a UNIX implementation 
 *		of an endeared VM/CMS application 
 *	  Date: 1994-Sep-23 and prior 
 */ 
 
#include	"gone.h" 
#include	<signal.h> 
 
/* ------------------------------------------------------------------ */ 
int main(argc,argv) 
  int     argc; 
  char   *argv[]; 
  { 
    int 	ppid, dpid; 
    extern int	getppid(); 
    char	temp[4096]; 
 
    ppid = getppid(); 
    (void) printf("PPID=%d (to kill)\n",ppid); 
 
    dpid = daemon(); 
 
    if (dpid) 
      { 
	(void) printf("DPID=%d (to run)\n",dpid); 
	if (dpid > 0) 
	  { 
	    (void) putline(1,GONEMSG); 
	    (void) sprintf(temp,"echo %d > $HOME/.gonepid"); 
	    (void) system(temp); 
	  } 
	return 0; 
      } 
 
    (void) sleep(3); 
    (void) kill(ppid,SIGKILL); 
 
(void) sleep(60); 
(void) system("tell troth@ua1vm.ua.edu *GONE Hi!"); 
  } 
 

