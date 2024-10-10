/* © Copyright 1995, Richard M. Troth, all rights reserved.  <plaintext>
 *
 *	  Name: cpq.c
 *		for BITNET folks with a habit, CP Query <something>
 *	Author: Rick Troth, Houston, Texas, USA
 *	  Date: 1995-Oct-15
 *
 */

#include	<string.h>
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
    char	temp[BUFSIZ], cpqs[BUFSIZ], *host, *arg1;
    int 	s, i, j;
    char       *arg0, *p;

    /*  establish defaults  */
    host = "localhost";

    /*  process options  */
    arg0 = argv[0];
    for (i = 1; i < argc && argv[i][0] == '-' &&
			    argv[i][1] != 0x00; i++)
      {
	switch (argv[i][1])
	  {
	    case 'h':	i++;
			host = argv[i];
			break;
	    case 'v':	uftcflag |= UFT_VERBOSE;
			(void) sprintf(temp,
				"%s: %s Remote CP QUERY client",
				arg0,UFT_VERSION);
			(void) uft_putline(2,temp);
			break;
	    default:	(void) sprintf(temp,
				"%s: invalid option %s",
				arg0,argv[i]);
			(void) uft_putline(2,temp);
			return 20;
			break;
	  }
      }

    /*  verify sufficient arguments (1)  */
    if ((argc - i) < 1)
      {
	(void) sprintf(temp,
		"Usage: %s [-h <host>] <something>",argv[0]);
	(void) uft_putline(2,temp);
	return 24;
      }

    /*  connect  */
    (void) sprintf(temp,"%s:%d",host,608);
    s = tcpopen(temp,0,0);
    if (s < 0)
      {
	(void) perror(host);
	return s;
      }

    /*  read and discard the herald  */
    (void) uft_pullline(s,temp,BUFSIZ);

    /*  join commandline args into CPQuery string  */
    cpqs[0] = 0x00;
    for (j = i; j < argc; j++)
      {
	strcat(cpqs,argv[j]);
	strcat(cpqs," ");
      }
/*  (void) putline(1,cpqs);  */

    /*  send the CPQ request  */
    (void) sprintf(temp,"CPQ %s",cpqs);
    (void) tcpputs(s,temp);

    /*  and wait for the ACK  */
    while (1)
      {
	(void) uft_pullline(s,temp,BUFSIZ);
	p = temp;  while (*p > ' ') p++;  while (*p <= ' ') p++;
	if (temp[0] == '6') (void) uft_putline(1,p);
	else if (temp[0] != '2') (void) uft_putline(2,p);
	if (temp[0] != '1' && temp[0] != '6') break;
      }

    /*  exit cleanly  */
    (void) tcpputs(s,"QUIT");
    (void) uftcwack(s,temp,BUFSIZ);

    return 0;
  }


