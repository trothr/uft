/* © Copyright 1994, 1996, 1997, Richard M. Troth, all rights reserved. 
 *		(casita sourced) <plaintext> 
 * 
 *	  Name: homedir.c 
 *	Author: Rick Troth, Houston, Texas, USA 
 *	  Date: 1994-Jul-25 and prior 
 * 
 */ 
 
#include	<pwd.h> 
 
/* ------------------------------------------------------------- HOMEDIR
 *  Try to determine the home directory from the system. 
 *  If that fails,  return a best guess. 
 */ 
char *homedir ( char *u ) 
  { 
    /*  variables for this function  */ 
    struct  passwd     *pwdent; 
    static  char        failsafe[64]; 
    char               *p, *q; 
    int 		i; 
 
    /*  try to get the real home directory from the system  */ 
    pwdent = getpwnam(u); 
    if (pwdent) return pwdent->pw_dir; 
 
    /*  if that failed then make a good guess  */ 
    p = failsafe;   q = "/home/"; 
    for (i = 0; *q != 0x00 && i < 63; i++) *p++ = *q++; 
    for (     ; *u != 0x00 && i < 63; i++) *p++ = *u++; 
    *p = 0x00; 
    return failsafe; 
  } 
 

