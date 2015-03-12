/* © Copyright 1994, 1996, Richard M. Troth, all rights reserved.
 *		(casita sourced) <plaintext>
 *
 *	  Name: msgcuftd.c
 *		part of multi-mode  'tell'  command for UNIX
 *		(message client talking to UFT daemon)
 *	Author: Rick Troth, Rice University, Houston, Texas, USA
 *	  Date: 1994-Jul-25 and prior, 1996-May-09 (split from tell.c)
 *
 */

#include	<stdio.h>
#include	<errno.h>
#include	"uft.h"

/* ------------------------------------------------------------- MSGUFTD
 *  That's UFTD, not just UFT, because messaging isn't part of
 *  UFT protocol, but may be a feature of some UFTD servers.
 */
int msgcuftd(user,text)
  char   *user, *text;
  {
    char	temp[256], ubuf[64], *host;
    int 	port, rc, s;

    /*  parse  */
    host = user;	user = ubuf;
    while (*host != '@' && *host != 0x00) *user++ = *host++;
    if (*host == '@') host++;  *user = 0x00;  user = ubuf;
    if (*host == 0x00) host = MSG_UFT_HOST;
    port = MSG_UFT_PORT;

    /*  try to contact the UFT server  */
    errno = 0;
    (void) sprintf(temp,"%s:%d",host,port);
    s = tcpopen(temp,0,0);
    if (s < 0) return s;

    /*  wait on a UFT/1 or UFT/2 herald  */
    (void) tcpgets(s,temp,sizeof(temp));

    /*  now try a UFT "MSG" command,  if available  */
    (void) sprintf(temp,"MSG %s %s",user,text);
    (void) tcpputs(s,temp);

    /*  wait for ACK/NAK  */
    rc = uftcwack(s,temp,sizeof(temp));

    /*  say goodbye politely  */
    (void) tcpputs(s,"QUIT");
    (void) uftcwack(s,temp,sizeof(temp));

    /*  return cleanly  */
    (void) close(s);
    return rc;
  }


