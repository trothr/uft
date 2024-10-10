/* © Copyright 1996, Richard M. Troth, all rights reserved.  <plaintext> 
 *              (casita sourced) 
 * 
 *        Name: imsg.c 
 *              issue informational messages to yourself 
 *      Author: Rick Troth, Houston, Texas, USA 
 *        Date: 1995-Jun-11, built from msgd.c, msgcat.c, 
 *                              and from msgc.c (tell.c) 
 * 
 *       To do: an option to issue IMSGs to others 
 * 
 *              An IMSG is a local thing. 
 *              At this time,  IMSGs from  user@host 
 *              are meaningless unles  host  is the local system. 
 * 
 */ 
 
#include        <errno.h> 
#include        <fcntl.h> 
#include        <sys/types.h> 
#include        <stdlib.h> 
 
#include        "uft.h" 
 
char *from; 
 
/* ------------------------------------------------------------ SENDIMSG 
 */ 
int sendimsg ( char *user , char *text ) 
  { 
    char        buffer[4096], *p; 
    int         fd, i; 
 
    errno = 0; 
    sprintf(buffer,"/tmp/%s.msgpipe",user); 
    fd = open(buffer,O_WRONLY); 
    if (fd < 0) 
      { 
        sprintf(buffer,"%s/.msgpipe",getenv("HOME")); 
        fd = open(buffer,O_WRONLY); 
      } 
    if (fd < 0) return fd; 
 
    /*  build the buffer;  begin at offset zero  */ 
    i = 0; 
 
    /*  copy the message text  */ 
    p = text;  while (*p) buffer[i++] = *p++;  buffer[i++] = 0x00; 
 
    /*  now environment variables;  first, who from?  */ 
    p = "MSGFROM=";  while (*p) buffer[i++] = *p++; 
    p = from;  while (*p) buffer[i++] = *p++;  buffer[i++] = 0x00; 
 
    /*  what type of message?  (MSP if by way of this server)  */ 
    p = "MSGTYPE=IMSG";  while (*p) buffer[i++] = *p++; 
                                             buffer[i++] = 0x00; 
 
    /*  also ... who's it too?  (in case that isn't obvious)  */ 
    p = "MSGUSER=";  while (*p) buffer[i++] = *p++; 
    p = user;  while (*p) buffer[i++] = *p++;  buffer[i++] = 0x00; 
 
    /*  an additional NULL terminates the environment buffer  */ 
    buffer[i++] = 0x00; 
 
    /*  hand it off;  feed the FIFO  (hoping there's a listener)  */ 
    (void) write(fd,buffer,i); 
 
    /*  all done,  so close the file descriptor  */ 
    (void) close(fd); 
 
    /*  get outta here  */ 
    return 0; 
  } 
 
 
/* ------------------------------------------------------------------ */ 
int main ( int argc , char *argv[] ) 
  { 
    char        buffer[4096], *arg0, *user; 
    int         i, j, k; 
 
    arg0 = argv[0]; 
 
    /*  process options  */ 
    for (i = 1; i < argc && argv[i][0] == '-' && 
                            argv[i][1] != 0x00; i++) 
      { 
        switch (argv[i][1]) 
          { 
            case 'v':   (void) sprintf(buffer, 
                                "%s: %s local IMSG source", 
                                arg0,UFT_VERSION); 
                        (void) putline(2,buffer); 
                        return 0; 
                        break; 
            default:    (void) sprintf(buffer, 
                                "%s: invalid option %s", 
                                arg0,argv[i]); 
                        (void) putline(2,buffer); 
                        return 20; 
                        break; 
          } 
      } 
 
    from = getenv("LOGNAME"); 
    user = from; 
 
    /*  parse them  */ 
    if (argc > 1) 
      { 
        k = 0; 
        for (i = 1; i < argc; i++) 
          { 
            for (j = 0; argv[i][j] != 0x00; j++) 
            buffer[k++] = argv[i][j]; 
            buffer[k++] = ' '; 
          } 
        buffer[k++] = 0x00; 
        (void) sendimsg(user,buffer); 
      } 
    else while (1) 
      { 
        (void) uft_getline(0,buffer);
        if (buffer[0] == '.' && buffer[1] == 0x00) break; 
        (void) sendimsg(user,buffer); 
      } 
    return 0; 
  } 
 

