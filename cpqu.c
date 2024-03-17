/* © Copyright 1995, Richard M. Troth, all rights reserved.  <plaintext>
 *
 *	  Name: cpqu.c
 *		for BITNET folks with a habit, CPQ USER <someone>
 *	Author: Rick Troth, Houston, Texas, USA
 *	  Date: 1995-Mar-09, Oct-14
 *
 */

#include	<stdio.h>
#include	"uft.h"

#ifndef 	BUFSIZ
#define 	BUFSIZ		4096
#endif

int		uftcflag;

/* ------------------------------------------------------------------ */
int main(argc,argv)
  int     argc;
  char   *argv[];
  {
    char	temp[BUFSIZ], user[BUFSIZ], *host, *arg1;
    int 	s, i;
    char       *arg0, *p, *def_host;

    /*  establish defaults  */
    def_host = "localhost";

    /*  process options  */
    arg0 = argv[0];
    for (i = 1; i < argc && argv[i][0] == '-' &&
			    argv[i][1] != 0x00; i++)
      {
	switch (argv[i][1])
	  {
	    case 'h':	i++;
			def_host = argv[i];
			break;
	    case 'v':	uftcflag |= UFT_VERBOSE;
			(void) sprintf(temp,
				"%s: %s Remote CPQ USER client",
				arg0,UFT_VERSION);
			(void) putline(2,temp);
			break;
	    default:	(void) sprintf(temp,
				"%s: invalid option %s",
				arg0,argv[i]);
			(void) putline(2,temp);
			return 20;
			break;
	  }
      }

    /*  verify sufficient arguments (1)  */
    if ((argc - i) < 1)
      {
	(void) sprintf(temp,"Usage: %s <user[@host]>",argv[0]);
	(void) putline(2,temp);
	return 24;
      }

    /*  parse user@host into user and host  */
    host = user;
    arg1 = argv[i];
    while (*arg1 != 0x00 && *arg1 != '@') *host++ = *arg1++;
    *host = *arg1;
    if (*host == '@') { *host++ = 0x00; host = ++arg1; }
    if (host[0] == 0x00) host = def_host;

    /*  connect  */
    (void) sprintf(temp,"%s:%d",host,608);
    s = tcpopen(temp,0,0);
    if (s < 0)
      {
	(void) perror(host);
	return s;
      }

    /*  read and discard the herald  */
    (void) uft_getline(s,temp,BUFSIZ);

    /*  send the CPQ request  */
    (void) sprintf(temp,"CPQ USER %s",user);
    (void) tcpputs(s,temp);

    /*  and wait for the ACK  */
    while (1)
      {
	(void) uft_getline(s,temp,BUFSIZ);
	p = temp;  while (*p > ' ') p++;  while (*p <= ' ') p++;
	if (temp[0] == '6') (void) putline(1,p);
	else if (temp[0] != '2') (void) putline(2,p);
	if (temp[0] != '1' && temp[0] != '6') break;
      }

    /*  exit cleanly  */
    (void) tcpputs(s,"QUIT");
    (void) uftcwack(s,temp,BUFSIZ);

    return 0;
  }


