/* 
 * 
 *        Name: uftcmb64.c 
 *              Unsolicited File Transfer client "make Base 64" 
 *      Author: Rick Troth, Houston, Texas (Dunnethead) 
 *        Date: 1993-Nov-21 
 * 
 *	  Note: this software comes with NO WARRANTY. 
 * 
 *		This module is a main, not a subroutine. 
 *		It may be found in either PATH or LIBPATH search. 
 * 
 */ 
 
/* ------------------------------------------------------------------ */ 
int main() 
  { 
    int         bc;		/*  byte count  */ 
    char        line[256];	/*  record buffer  */ 
    int         i;		/*  loop counter  */ 
    char       *b64;		/*  Base 64 "digits" table  */ 
    char	b[4];		/*  Base 64 input buffer  */ 
 
    /*  define the Base 64 character set  */ 
    b64 = 
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; 
 
    (void) close(2); 
 
    i = 0;	/*  start at the beginning of the line  */ 
    while (1)	/*  and fill with Base 64 encoding  */ 
      { 
	bc = readspan(0,b,3); 
	if (bc < 3) break; 
	line[i++] = b64[b[0]>>2]; 
	line[i++] = b64[((b[0]<<4)+(b[1]>>4))&0x3F]; 
	line[i++] = b64[((b[1]<<2)+(b[2]>>6))&0x3F]; 
	line[i++] = b64[b[2]&0x3F]; 
	if (i >= 64) 
	  { 
	    line[i] = 0x00;	/*  terminate the text line  */ 
	    (void) uftxputs(1,line); 
	    i = 0; 
	  } 
      } 
 
    switch (bc) 
      { 
	case 0: break; 
	case 1: line[i++] = b64[b[0]>>2]; 
		line[i++] = b64[(b[0]<<4)&0x3F]; 
		line[i++] = '='; 
		line[i++] = '='; 
		break; 
	case 2: line[i++] = b64[b[0]>>2]; 
		line[i++] = b64[((b[0]<<4)+(b[1]>>4))*0x3F]; 
		line[i++] = b64[(b[1]<<2)&0x3F]; 
		line[i++] = '='; 
      } 
    line[i] = 0x00;	/*  terminate the text line  */ 
    (void) uftxputs(1,line); 
 
    /*  be sure files are cleanly closed  */ 
    (void) close(1); 
    (void) close(0); 
 
    return 0; 
  } 
 

