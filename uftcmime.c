/* © Copyright 1996, Richard M. Troth, all rights reserved.  <plaintext> 
 * 
 *        Name: uftcmime.c 
 *              Unsolicited File Transfer client MIME support 
 *      Author: Rick Troth, Houston, Texas, USA 
 *        Date: 1996-Mar-18 
 * 
 */ 
 
#include        "uft.h" 
#include        "uftcnote.h" 
#include        <time.h> 
#include        "putline.c" 
#include        "getline.c" 
#include        <ctype.h> 
 
static char *b64 = UFT_B64_CODE;        /*  Base 64 "digits" table  */ 
 
int main() { (void) uftcmime(0,1); return 0; } 
 
/* ------------------------------------------------------------------ */ 
int uftcmime(s,r) 
  int s, r; 
  { 
    char        temp[256], boundary[256], *name, *p, *verb, *args, 
                tstr[64], *day, *mon, *dd, *tttt, *yyyy, 
                meta[256], *from, *targ; 
    int         i, q; 
    time_t      t0, t1; 
 
    q = 1;  /*  until we really attach 'sendmail'  */ 
    name = "";  from = "";  targ = ""; 
 
    /*  compute a MIME multipart boundary string  */ 
    t1 = t0 = time(NULL); 
    (void) sprintf(boundary,"SIFT*%d",t0); 
 
    /*  output the RFC 822 header  */ 
    (void) sprintf(temp,"MIME-Version: 1.0"); 
    (void) putline(q,temp); 
 
    (void) strcpy(tstr,ctime(&t1)); 
    p = tstr; 
    day = p; 
        while (*p != 0x00 && *p != ' ' && *p != '\n') p++; *p++ = 0x00; 
    mon = p; 
        while (*p != 0x00 && *p != ' ' && *p != '\n') p++; *p++ = 0x00; 
    dd = p; 
        while (*p != 0x00 && *p != ' ' && *p != '\n') p++; *p++ = 0x00; 
    tttt = p; 
        while (*p != 0x00 && *p != ' ' && *p != '\n') p++; *p++ = 0x00; 
    yyyy = p; 
        while (*p != 0x00 && *p != ' ' && *p != '\n') p++; *p++ = 0x00; 
    (void) sprintf(temp,"Date: %s, %s %s %s %s",day,dd,mon,yyyy,tttt); 
    (void) putline(q,temp); 
 
    (void) sprintf(temp,"From: %s",from); 
    (void) putline(q,temp); 
    (void) sprintf(temp,"To: %s",targ); 
    (void) putline(q,temp); 
    (void) sprintf(temp,"Subject: FILE %s",name); 
    (void) putline(q,temp); 
    (void) sprintf(temp,"Content-Type: Multipart/X-SIFT"); 
    (void) putline(q,temp); 
 
    /*  mark end of header with an empty line  */ 
    (void) putline(q,""); 
 
    /*  output  "part zero"  (disclaimer)  */ 
    for (i = 0;  uftcnote[i][0] != 0x00; i++) 
      { 
        (void) sprintf(temp,"SIFT: %s",uftcnote[i]); 
        (void) putline(q,temp); 
      } 
    (void) sprintf(temp,"--%s",boundary); 
    (void) putline(q,temp); 
 
    /*  output  "part one",  the header or "metafile"  */ 
    (void) sprintf(temp,"Content-Type: X-SIFT/meta"); 
    (void) putline(q,temp); 
    /*  mark end of header with an empty line  */ 
    (void) putline(q,""); 
 
    (void) putline(q,"# For large files, get your local"); 
    (void) putline(q,"# sysadmin to install a UFT server."); 
 
        (void) putline(r,"1XX"); 
        (void) uft_pullline(s,temp,256);
        p = temp; 
        verb = p; 
        while (*p != 0x00 && *p != ' ' && *p != '=') 
          { *p = toupper(*p); p++; } 
        if (*p != 0x00) *p++ = 0x00; 
        args = p; 
        (void) sprintf(meta,"%s='%s'",verb,args); 
        (void) putline(q,meta); 
 
    (void) sprintf(temp,"--%s",boundary); 
    (void) putline(q,temp); 
 
    /*  output  "part two",  the body or "datafile"  */ 
    (void) sprintf(temp,"Content-Type: X-SIFT/data"); 
    (void) putline(q,temp); 
    /*  mark end of header with an empty line  */ 
    (void) putline(q,""); 
    (void) sprintf(temp,"--%s--",boundary); 
    (void) putline(q,temp); 
  } 
 
/* 
 * 
 *        Name: uftcmb64.c 
 *              Unsolicited File Transfer client "make Base 64" 
 *      Author: Rick Troth, Houston, Texas (Dunnethead) 
 *        Date: 1993-Nov-21 
 * 
 *        Note: this software comes with NO WARRANTY. 
 * 
 *              This module is a main, not a subroutine. 
 *              It may be found in either PATH or LIBPATH search. 
 * 
 */ 
 
/* ------------------------------------------------------------------ */ 
int uftcb64d(s,b,n) 
  int s;  char *b;  int n; 
  { 
    int         bc;             /*  byte count  */ 
    char        line[256];      /*  record buffer  */ 
    int         i;              /*  loop counter  */ 
    char        z[4];           /*  Base 64 input buffer  */ 
 
    i = 0;      /*  start at the beginning of the line  */ 
    while (1)   /*  and fill with Base 64 encoding  */ 
      { 
/*      bc = readspan(0,z,3);  */ 
        if (bc < 3) break; 
        line[i++] = b64[z[0]>>2]; 
        line[i++] = b64[((z[0]<<4)+(z[1]>>4))&0x3F]; 
        line[i++] = b64[((z[1]<<2)+(z[2]>>6))&0x3F]; 
        line[i++] = b64[z[2]&0x3F]; 
        if (i >= 72) 
          { 
            line[i] = 0x00;     /*  terminate the text line  */ 
            (void) putline(1,line); 
            i = 0; 
          } 
      } 
 
    switch (bc) 
      { 
        case 0: break; 
        case 1: line[i++] = b64[z[0]>>2]; 
                line[i++] = b64[(z[0]<<4)&0x3F]; 
                line[i++] = '='; 
                line[i++] = '='; 
                break; 
        case 2: line[i++] = b64[z[0]>>2]; 
                line[i++] = b64[((z[0]<<4)+(z[1]>>4))*0x3F]; 
                line[i++] = b64[(z[1]<<2)&0x3F]; 
                line[i++] = '='; 
      } 
    line[i] = 0x00;     /*  terminate the text line  */ 
    (void) putline(1,line); 
 
    return n; 
  } 
 

/* 
 
Date line should read like 
        Date: day, dd mmm yyyy hh:mm:ss -offset (tz) 
 
        Date: Mon Jan 20 02:03:35 1997 

        Date: Fri, 17 Jan 97 16:09:31 EST 
        Date: Fri, 17 Jan 1997 21:24:46 -0500 (EST) 
        Date: Fri, 17 Jan 1997 18:01:29 -0600 
        Date: Sat, 18 Jan 1997 18:00:18 -0500 (EST) 
        Date: Sat, 18 Jan 1997 17:17:34 +0000 
        Date: Sat, 18 Jan 1997 21:27:22 CST 
        Date: Sun, 19 Jan 1997 03:27:03 -0600 
        Date: Sun, 19 Jan 1997 09:44:03 -0500 (EST) 
 
        Date: Tue, 21 Jan 1997 06:52:16
 
 */ 
 

