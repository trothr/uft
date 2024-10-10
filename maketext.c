/* 
 * 
 *        Name: maketext.c 
 *              convert plain text to/from canonical forms 
 *      Author: Rick Troth, Rice University, Information Systems 
 *      Author: Rick Troth, Houston, Texas, USA 
 *        Date: 1995-Jan-31 
 * 
 *     Co-reqs: getline, putline, and tcpio 
 * 
 */ 
 
#include        <stdlib.h>
#include        <string.h>
#include        <stdio.h> 
#include        <sys/types.h> 
#include        <sys/stat.h> 
#include        <fcntl.h> 
#include        <unistd.h> 
#include        <errno.h> 
#include        "uft.h" 
 
/* ------------------------------------------------------------ MKTXTLCL 
 *  This routine makes "local" text for UNIX/POSIX. 
 */ 
int mktxtlcl(int i, int o) 
  { 
    char        buffer[4096]; 
    int         rc; 
    while (1) 
      { 
        rc = uft_pullline(i,buffer,4096);
        if (rc < 0 && errno == 0) return 0; 
        if (rc < 0) return rc; 
        rc = uft_putline(o,buffer);
        if (rc < 0) return rc; 
      } 
  } 
 
/* ------------------------------------------------------------ MKTXTNET 
 *  This routine makes "network" plain text from local. 
 */ 
int mktxtnet(int i, int o) 
  { 
    char        buffer[4096]; 
    int         rc; 
    while (1) 
      { 
        rc = uft_pullline(i,buffer,4096);
        if (rc < 0 && errno == 0) return 0; 
        if (rc < 0) return rc; 
        rc = tcpputs(o,buffer); 
        if (rc < 0) return rc; 
      } 
  } 
 
/* ------------------------------------------------------------------ */ 
int main(int argc, char *argv[]) 
  { 
    char        temp[256], *arg0, tmp2[256], *fn1, fn2[64];
    int         rc, fd1, fd2, n, mode; 
    struct  stat  statbuf; 
 
    arg0 = argv[0]; 
    if (argc < 2) 
      { 
        (void) sprintf(temp,
                "Usage:  %s  [ -local | -network ]  [ file ] ",arg0); 
        (void) uft_putline(2,temp);
        return 24; 
      } 
 
    mode = ' ';   n = 1; 
    /*  support old-style command line  */ 
    switch (argv[1][0]) 
      { 
        case 'l':   case 'L': 
                mode = 'L'; 
                n++; 
                break; 
        case 'n':   case 'N': 
                mode = 'N'; 
                n++; 
                break; 
        case 'u':   case 'U': 
                mode = 'L'; 
                n++; 
                break; 
        case 'a':   case 'A': 
                mode = 'N'; 
                n++; 
                break; 
      } 
 
    while (n < argc && argv[n][0] == '-') 
      { 
        switch (argv[n][1]) 
          { 
            case 'a':  case 'n': 
                        mode = 'n'; 
                        break; 
            case 't':  case 'l': 
                        mode = 'l'; 
                        break; 
            case 'r':  case 'R': 
                        break; 
            case 'v':  case 'V': 
                        (void) sprintf(temp, 
                "%s: %s Internet SENDFILE text stream processor",
                                arg0,UFT_VERSION); 
                        (void) uft_putline(2,temp);
                        break; 
            case '?':  case 'h': 
                        (void) sprintf(temp,
                "Usage:  %s  { -local | -network }  [ file ] ",arg0); 
                        (void) uft_putline(2,temp);
                        return 0; 
                        break; 
          } 
        if (argv[n++][1] == 'f') break; 
      } 
 
    /*  must supply either -l or -n  */ 
    if (mode != 'n' && mode != 'l') 
      { 
        (void) sprintf(temp,
                "Usage:  %s  [ -local | -network ]  [ file ] ",arg0); 
        (void) uft_putline(2,temp);
        return 24; 
      } 
 
    /*  now go to work  */ 
/*  fn2 = tmpnam(tmp2);  */
    (void) strcpy(fn2,"/tmp/maketext-XXXXXX");
    fd2 = mkstemp(fn2);

    errno = 0; 
    if (n == argc) 
      { 
        if (mode == 'n') rc = mktxtnet(0,1); 
                else    rc = mktxtlcl(0,1); 
      } 
    else while (n < argc)
      { 
        fn1 = argv[n++]; 
        stat(fn1,&statbuf); 
        if (statbuf.st_mode & S_IFDIR) 
          { 
            (void) sprintf(temp,
"find '%s' -type f -print | xargs -i '%s' -%c '{}'", 
fn1,arg0,mode); 
            (void) system(temp); 
          } 
        else 
          { 
            fd1 = open(fn1,O_RDONLY); 
/*          fd2 = open(fn2,O_WRONLY|O_CREAT,0666);  */
            if (mode == 'N') rc = mktxtnet(fd1,fd2); 
                else         rc = mktxtlcl(fd1,fd2); 
            close(fd1); 
            close(fd2); 
            if (rc != 0 || errno != 0) 
              { 
                (void) sprintf(temp,"RC=%d; ERRNO=%d",rc,errno); 
                (void) uft_putline(2,temp);
                return rc; 
              } 
            (void) sprintf(temp,"touch -r '%s' '%s'",fn1,fn2); 
            (void) system(temp); 
            (void) sprintf(temp,"mv '%s' '%s'",fn2,fn1); 
            (void) system(temp); 
          } 
      } 
    return 0; 
  } 
 

