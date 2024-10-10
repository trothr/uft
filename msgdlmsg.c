/* © Copyright 1996, Richard M. Troth, all rights reserved.  <plaintext>
 *
 *        Name: msgdlmsg.c
 *              syslog the arrival of this message
 *      Author: Rick Troth, Houston, Texas, USA
 *        Date: 1997-Jan-08
 *
 * this routine cuts SYSLOG records something like
 *      mmm dd hh:mm:ss localhost msgd[]: to uuuu from hhhh(ffff): mmmm
 *
 */

#include <syslog.h>

#include "uft.h"

/* ------------------------------------------------------------------ */
int msgdlmsg(char*user,char*host,char*from,char*text)
  {
    static char *eyecatch = "msgdlmsg()";

    (void) openlog("msgd",LOG_PID,LOG_USER);

    (void) syslog(LOG_DEBUG,"to %s from %s(%s): %s",
                user,host,from,text);

    (void) closelog();

    return 0;
  }


