/* © Copyright 1995, Richard M. Troth, all rights reserved.  <plaintext> 
 * 
 *	  Name: uftdlog.c 
 *		Unsolicited File Transfer daemon log function 
 *	Author: Rick Troth, Houston, Texas, USA (concerto) 
 *	  Date: 1995-Mar-25 (happy b'day GHN) 
 * 
 */ 
 
/* ------------------------------------------------------------- UFTDLOG 
 */ 
int uftdlog(s,b) 
  int     s; 
  char   *b; 
  { 
    char	temp[256]; 
 
    (void) sprintf(temp,"#*%s",b); 
    (void) putline(s,temp); 
 
    return 0; 
  } 
 

