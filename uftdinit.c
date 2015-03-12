/* © Copyright 1998, Richard M. Troth, all rights reserved.  <plaintext> 
 * 
 *	  Name: uftdinit.c 
 *	Author: Rick Troth, Houston, Texas, USA 
 *	  Date: 1998-Feb-11 
 * 
 */ 
 
#include	"uft.h" 
 
void uftdinit() 
    {   
	uftfile0.cfd = 0;	/*  control file  */ 
	uftfile0.dfd = 0;	/*  data file  */ 
	uftfile0.efd = 0;	/*  ext attr file  */ 
	uftfile0.lfd = 0;	/*  log file  */ 
	uftfile0.sfd = 0;	/*  server stream  */ 
	uftfile0.rfd = 0;	/*  response stream  */ 
	uftfile0.cfn = "";	/*  control file  */ 
	uftfile0.dfn = "";	/*  data file  */ 
	uftfile0.efn = "";	/*  ext attr file  */ 
	uftfile0.lfn = "";	/*  log file  */ 
 
	uftfile0.from[0] = '-'; 
	uftfile0.from[1] = 0x00; 
	uftfile0.name[0] = 0x00; 
	uftfile0.type[0] = '-'; 
	uftfile0.type[1] = 0x00; 
	uftfile0.cc[0] = '-'; 
	uftfile0.cc[1] = 0x00; 
	uftfile0.hold[0] = '-'; 
	uftfile0.hold[1] = 0x00; 
	uftfile0.class[0] = '-'; 
	uftfile0.class[1] = 0x00; 
	uftfile0.devtype[0] = '-'; 
	uftfile0.devtype[1] = 0x00; 
	uftfile0.keep[0] = '-'; 
	uftfile0.keep[1] = 0x00; 
	uftfile0.msg[0] = '-'; 
	uftfile0.msg[1] = 0x00; 
 
	uftfile0.form[0] = '-';  
	uftfile0.form[1] = 0x00; 
	uftfile0.dist[0] = '-'; 
	uftfile0.dist[1] = 0x00; 
	uftfile0.dest[0] = '-'; 
	uftfile0.dest[1] = 0x00; 
	uftfile0.size = 0; 
	uftfile0.copies = 0; 
	uftfile0.title[0] = 0x00; 
 
	return; 
    }   
 

