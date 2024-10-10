/* © Copyright 1994, 1996, Richard M. Troth, all rights reserved.
 *              (casita sourced) <plaintext>
 *
 *        Name: msglocal.c
 *      Author: Rick Troth, Houston, Texas, USA
 *        Date: 1994-Jul-25 and prior
 *
 */

#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <pwd.h>

#include "uft.h"

/* ------------------------------------------------------------ MSGLOCAL
 */
int msglocal(char*user,char*text)
  {
    static char *eyecatch = "msglocal()";

    int         fd, i, j;
    char        temp[BUFSIZ], *from;
    extern  char  *getenv();

    /*  first, look for the FIFO in /tmp  */
    (void) sprintf(temp,"/tmp/%s.msgpipe",user);
    fd = open(temp,O_WRONLY|O_NDELAY);

    /*  if that didn't work,  look in his home directory  */
    if (fd < 0 && errno == ENOENT)
      {
        /*  a 'mknod' with 622 perms (writable) might work too  */
        (void) sprintf(temp,"%s/.msgpipe",homedir(user));
        fd = open(temp,O_WRONLY|O_NDELAY);
      }

    /*  if there's no listener ...  */
    if (fd < 0 && errno == ENXIO)
      {
        /*  launch our special application to listen  */
        fd = open(temp,O_WRONLY|O_NDELAY);
        /*  ... or NOT ...  */
      }
    if (fd < 0) return fd;

    /*  who's the message from?  */
    from = getenv("LOGNAME");
    if (*from == 0x00) from = getenv("USER");
    /*  (we should probably do something a little more secure!)  */
    j = BUFSIZ;  j -= strlen(from);  j -= 24;   /*  leave some room  */
                 j -= strlen(from);  j -= 24;   /*  this is temporary  */

    /* message text comes first */
    i = 0;   /*  start at the beginning of the buffer  */
    while (*text != 0x00 && i < j) temp[i++] = *text++;
    temp[i++] = 0x00;

    /*  environment style strings follow  */
    text = "MSGTYPE=U";         /*  denote that this is a "U msg"  */
    while (*text != 0x00 && i < j) temp[i++] = *text++;
    temp[i++] = 0x00;

    /*  who is this user message from?  */
    text = "MSGFROM=";          /*  start of that line  */
    while (*text != 0x00 && i < j) temp[i++] = *text++;
    while (*from != 0x00 && i < j) temp[i++] = *from++;
    temp[i++] = 0x00;

    /*  who is this user message to?  */
    text = "MSGUSER=";          /*  start of that line  */
    while (*text != 0x00 && i < j) temp[i++] = *text++;
    while (*user != 0x00 && i < j) temp[i++] = *user++;
    temp[i++] = 0x00;

    /*  and one more NULL terminates the environment  */
    temp[i++] = 0x00;

    /*  send it  */
    (void) write(fd,temp,i);
    (void) close(fd);

    return 0;
  }

/*
     O_NDELAY       When  opening  a  FIFO  (named  pipe  -   see
                    mknod(2V)) with O_RDONLY or O_WRONLY set:

                    If O_NDELAY is set:
                         An  open()  for   reading-only   returns
                         without  delay.   An open() for writing-
                         only returns  an  error  if  no  process
                         currently has the file open for reading.

                    If O_NDELAY is clear:
                         A call to open() for reading-only blocks
                         until a process opens the file for writ-
                         ing.  A call to open() for  writing-only
                         blocks  until  a  process opens the file
                         for reading.
 */


