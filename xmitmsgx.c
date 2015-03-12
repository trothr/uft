/* 
 * 
 *	  Name: xmitmsgx.c, "transmit message" for POSIX 
 *		read and emit enumerated messages from the repository 
 *	Author: Rick Troth, Rice University, Information Systems 
 *	  Date: 1993-May-24 
 *		2003-Sep-03 
 * 
 */ 
 
#include	<stdio.h> 
#include	<ctype.h> 
 
/* 
 *  See how SYSLOG does it. 
 */ 
 
/* ------------------------------------------------------------- SPRINTM 
 *  Read a message from the repository; fill-in the blanks. 
 */ 
int sprintm( 
  char   *s, 
  char   *msgf, 	/*  message file (short, basename), APPLID  */ 
  char   *msgu, 	/*  "caller" or user  */ 
  int     msgn, 	/*  message number  */ 
  char    msgl, 	/*  message level byte  */ 
  int     msgc, 	/*  count of replacement tokens  */ 
  char   *msgv[]) 	/*  vector of replacement tokens  */ 
  { 
    FILE       *msgfile; 
    char	msgrecord[256],     msgtext[256],   temp[256]; 
    char	msg1[4],    msg2[4],   *punt[2]; 
    static char msgstring[4096]; 
    int 	i,  j; 
    char       *p, *q; 
    char	escape; 
    extern  FILE       *dfopen(); 
 
    if (msgf) (void) sprintf(temp,"%s.msgs",msgf); 
	else  (void) sprintf(temp,".msgs"); 
    msgfile = dfopen(temp,"r"); 
    if (msgfile == NULL) 
      { 
	punt[1] = msgf; 
	if (msgf) return msgread(NULL,NULL,813,'E',2,punt); 
	    else  return "*813"; 
      } 
 
    if (msgf) (void) strncpy(msg1,msgf,3); 
	else msg1[0] = 0x00; 
    if (msgu) (void) strncpy(msg2,msgu,3); 
	else msg2[0] = 0x00; 
 
    escape = 0x00; 
    while (1) 
      { 
	(void) fgets(msgrecord,255,msgfile); 
	if (feof(msgfile)) break; 
	if (msgrecord[0] == '*') continue; 
	i = strlen(msgrecord) - 1; 
	if (msgrecord[i] == '\n') msgrecord[i] = 0x00; 
	for (p = msgrecord; *p <= ' ' && *p != 0x00; p++); 
	if (*p) escape = *p; 
	  else	escape = '&'; 
	break; 
      } 
    if (escape == 0x00) 
      { 
	/*  give "not found" message on premature EOF  */ 
	(void) sprintf(temp,"%03d",msgn); 
	punt[1] = temp; 
	if (msgf) return msgread(NULL,NULL,814,'E',2,punt); 
	    else  return "*814"; 
      } 
 
    msgstring[0] = 0x00; 
    while (1) 
      { 
	(void) fgets(msgrecord,255,msgfile);
	if (feof(msgfile)) break; 
	if (msgrecord[0] == '*') continue; 
	for (i = 0; i < 4; i++) temp[i] = msgrecord[i];
	temp[4] = 0x00;
	if (atoi(temp) == msgn)
	  { 
	    for (i = 0; i < 3; i++) 
		if (islower(msg1[i])) 
		    msg1[i] = toupper(msg1[i]); 
	    msg1[3] = 0x00; 
	    for (i = 0; i < 3; i++) 
		if (islower(msg2[i])) 
		    msg2[i] = toupper(msg2[i]); 
	    msg2[3] = 0x00; 
 
	    if (islower(msgl)) msgl = toupper(msgl); 
	    if (msgl == 0x00) msgl = msgrecord[8]; 
	    i = strlen(msgrecord) - 1; 
	    if (msgrecord[i] == '\n') msgrecord[i] = 0x00; 

	    p = &msgrecord[10]; 
	    q = msgtext; 
	    while (*p) 
	      { 
		if (*p == escape) 
		  { 
		    p++; 
		    j = *p & 0x0F; 
		    if (j < msgc) 
			for (i = 0; msgv[j][i]; i++) 
			    *q++ = msgv[j][i]; 
		    p++; 
		  } 
		else *q++ = *p++; 
	      } 
	    *q = 0x00; 
            (void) sprintf(msgstring,"%s%s%03d%c %s", 
			msg1,msg2,msgn,msgl,msgtext);
	  } 
      } 
    if (msgstring[0]) return msgstring; 
 
    /*  not found  */ 
    (void) sprintf(temp,"%03d",msgn); 
    punt[1] = temp; 
    if (msgf) return msgread(NULL,NULL,814,'E',2,punt); 
	else  return "*814"; 
  }
 
/* ------------------------------------------------------------- MSGREAD
 *  Read the message repository source file. 
 */ 
char *msgread(msgf,msgu,msgn,msgl,msgc,msgv) 
  char   *msgf; 	/*  message file (short, basename), APPLID  */ 
  char   *msgu; 	/*  "caller" or user  */ 
  int     msgn; 	/*  message number  */ 
  char    msgl; 	/*  message level byte  */ 
  int     msgc; 	/*  count of replacement tokens  */ 
  char   *msgv[]; 	/*  vector of replacement tokens  */ 
  { 
    FILE       *msgfile; 
    char	msgrecord[256],     msgtext[256],   temp[256]; 
    char	msg1[4],    msg2[4],   *punt[2]; 
    static char msgstring[4096]; 
    int 	i,  j; 
    char       *p, *q; 
    char	escape; 
    extern  FILE       *dfopen(); 
 
    if (msgf) (void) sprintf(temp,"%s.msgs",msgf); 
	else  (void) sprintf(temp,".msgs"); 
    msgfile = dfopen(temp,"r"); 
    if (msgfile == NULL) 
      { 
	punt[1] = msgf; 
	if (msgf) return msgread(NULL,NULL,813,'E',2,punt); 
	    else  return "*813"; 
      } 
 
    if (msgf) (void) strncpy(msg1,msgf,3); 
	else msg1[0] = 0x00; 
    if (msgu) (void) strncpy(msg2,msgu,3); 
	else msg2[0] = 0x00; 
 
    escape = 0x00; 
    while (1) 
      { 
	(void) fgets(msgrecord,255,msgfile); 
	if (feof(msgfile)) break; 
	if (msgrecord[0] == '*') continue; 
	i = strlen(msgrecord) - 1; 
	if (msgrecord[i] == '\n') msgrecord[i] = 0x00; 
	for (p = msgrecord; *p <= ' ' && *p != 0x00; p++); 
	if (*p) escape = *p; 
	  else	escape = '&'; 
	break; 
      } 
    if (escape == 0x00) 
      { 
	/*  give "not found" message on premature EOF  */ 
	(void) sprintf(temp,"%03d",msgn); 
	punt[1] = temp; 
	if (msgf) return msgread(NULL,NULL,814,'E',2,punt); 
	    else  return "*814"; 
      } 
 
    msgstring[0] = 0x00; 
    while (1) 
      { 
	(void) fgets(msgrecord,255,msgfile);
	if (feof(msgfile)) break; 
	if (msgrecord[0] == '*') continue; 
	for (i = 0; i < 4; i++) temp[i] = msgrecord[i];
	temp[4] = 0x00;
	if (atoi(temp) == msgn)
	  { 
	    for (i = 0; i < 3; i++) 
		if (islower(msg1[i])) 
		    msg1[i] = toupper(msg1[i]); 
	    msg1[3] = 0x00; 
	    for (i = 0; i < 3; i++) 
		if (islower(msg2[i])) 
		    msg2[i] = toupper(msg2[i]); 
	    msg2[3] = 0x00; 
 
	    if (islower(msgl)) msgl = toupper(msgl); 
	    if (msgl == 0x00) msgl = msgrecord[8]; 
	    i = strlen(msgrecord) - 1; 
	    if (msgrecord[i] == '\n') msgrecord[i] = 0x00; 

	    p = &msgrecord[10]; 
	    q = msgtext; 
	    while (*p) 
	      { 
		if (*p == escape) 
		  { 
		    p++; 
		    j = *p & 0x0F; 
		    if (j < msgc) 
			for (i = 0; msgv[j][i]; i++) 
			    *q++ = msgv[j][i]; 
		    p++; 
		  } 
		else *q++ = *p++; 
	      } 
	    *q = 0x00; 
            (void) sprintf(msgstring,"%s%s%03d%c %s", 
			msg1,msg2,msgn,msgl,msgtext);
	  } 
      } 
    if (msgstring[0]) return msgstring; 
 
    /*  not found  */ 
    (void) sprintf(temp,"%03d",msgn); 
    punt[1] = temp; 
    if (msgf) return msgread(NULL,NULL,814,'E',2,punt); 
	else  return "*814"; 
  }
 
/* ------------------------------------------------------------------ */
int main(argc,argv)
  int     argc;
  char   *argv[];
  { 
    char       *applid,    *caller,     level, 
	      **msgv; 
    int 	msgc; 
    int 	n; 
    FILE       *output; 
    char	buffer[256]; 
 
    applid = ""; 
    caller = ""; 
    level  = 0x00; 
    output = stdout;	/*  may be changed to "stderr"  */ 
 
    for (n = 1; n < argc && argv[n][0] == '-'; n++)
      {
	switch (argv[n][1])
	  { 
	    case 'a': 
			if (++n >= argc) break; 
			applid = argv[n]; 
			break; 
	    case 'c': 
			if (++n >= argc) break; 
			caller = argv[n]; 
			break; 
	    case 'l': 
			if (++n >= argc) break; 
			level = argv[n][0]; 
			if (level == 0x00) level = ' '; 
			break; 
	    case '1':	output = stdout; break; 
	    case '2':	output = stderr; break; 
	    default: 
			break; 
	  } 
      } 
 
    msgc = argc - n; 
    msgv = &argv[n]; 
 
    if (msgc <= 0) 
      { 
	(void) sprintm(buffer,NULL,NULL,386,'E',0,NULL); 
	(void) fprintf(stderr,"%s\n",buffer); 
	return 24; 
      } 
 
    else 
      { 
     (void) sprintm(buffer,applid,caller,atoi(argv[n]),level,msgc,msgv); 
	(void) fprintf(output,"%s\n",buffer); 
	return 0; 
      } 
  } 
 

