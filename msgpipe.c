/* © Copyright 1995, Richard M. Troth, all rights reserved.  <plaintext>
 *              (casita sourced)
 *
 *        Name: msgpipe.c (formerly msgcat.c)
 *              writes incoming messages to standard output
 *      Author: Rick Troth, Houston, Texas, USA
 *        Date: 1995-Oct-26 and prior
 *
 *   Operation: I think the original idea came from David Lippke,
 *              that there should be a FIFO in the home directory
 *              to which the user could attach any custom listener.
 *              This is a quick and easy solution using that technique.
 *
 *              This implementation does NOT use the same protocol
 *              on the FIFO that David's code used.   Further,
 *              the FIFO might be in /tmp rather than $HOME.
 *
 *       To do: direct MSG/UMSG (default) to stdout
 *              and IMSG/EMSG to file handle 2 (stderr).
 *              Not sure about WNG (WMSG) and SMSG.
 *
 *       Types: UMSG (MSG) standard (remote or local)
 *              IMSG informational
 *              WMSG (WNG) warning
 *              EMSG error
 *              SMSG "special message" (server message), eg: commands
 *
 *              Need to decide on #1 or #2 output for GONE work.
 *
 */

#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#include "uft.h"

/* -------------------------------------------------------------- ENVGET
 * Returns a pointer to the value of the requested variable,
 * or points to the end of the environment buffer.
 */
char *envget(env,var)
  char   *env, *var;
  {
    char   *p, *q;

    if (*env == 0x00) return env;

    p = env;    q = var;
    while (*p)
      {
        while (*p == *q && *p && *q && *p != '=') { p++; q++; }
        if (*p == '=' && *q == 0x00) return ++p;
        while (*p++);   q = var;
      }

    return p;
  }

/* ------------------------------------------------------------------ */
int main(int argc,char*argv[])
  {
    int         i, fd, pid;
    char        buffer[4096], *p, *q, *arg0, *envbuf, *user;
    char        outbuf[4096], *type;
    extern  char  *getenv();
    char        pipefn[256];
    char       *host, *from;

    arg0 = argv[0];
    user = "";
    pid = 0;

    /*  process options  */
    for (i = 1; i < argc && argv[i][0] == '-' &&
                            argv[i][1] != 0x00; i++)
      {
        switch (argv[i][1])
          {
            case 'v':   (void) sprintf(buffer,
                                "%s: %s Internet TELL messaging agent",
                                arg0,UFT_VERSION);
                        (void) uft_putline(2,buffer);
                        return 0;
                        break;
            case 'u':   (void) close(1);
                        (void) open("/dev/console",O_WRONLY|O_NOCTTY,0);
                        (void) close(2);
                        (void) close(0);
                        user = argv[++i];
                        pid = fork();  if (pid < 0) return i;
                        break;
            default:    (void) sprintf(buffer,
                                "%s: invalid option %s",
                                arg0,argv[i]);
                        (void) uft_putline(2,buffer);
                        return 20;
                        break;
          }
      }

    /*  close stdin  */
    (void) close(0);

    /*  who am i?  */
    if (user == 0x0000 || *user == 0x00) user = getenv("LOGNAME");
    if (user == 0x0000 || *user == 0x00) user = getenv("USER");

    /*  try opening message pipe FIFO R/W first;  if another
        'msgcat' (or similar) is listening,  then bail out  */
    (void) sprintf(pipefn,"/tmp/%s.msgpipe",user);
    errno = 0;  fd = open(pipefn,O_WRONLY|O_NDELAY);
    if (fd < 0 && errno == ENOENT)
      {
        sprintf(pipefn,"%s/.msgpipe",getenv("HOME"));
        errno = 0;  fd = open(pipefn,O_WRONLY|O_NDELAY);
      }
#ifdef          TRY_UFTMSG
    if (fd < 0 && errno == ENOENT)
      {
        sprintf(pipefn,"/usr/spool/uft/%s/.msgpipe",user);
        errno = 0;  fd = open(pipefn,O_WRONLY|O_NDELAY);
      }
#endif
#ifdef          TRY_VARMSG
    if (fd < 0 && errno == ENOENT)
      {
        sprintf(pipefn,"/var/msg/%s.msgpipe",user);
        errno = 0;  fd = open(pipefn,O_WRONLY|O_NDELAY);
      }
#endif
    if (fd < 0 && errno == ENOENT)
      {
        (void) sprintf(pipefn,"/tmp/%s.msgpipe",user);
        /*  try creating the FIFO;  world writable, yes!  */
        umask(0x0000);  /*  blow-off the UMASK here  */
        (void) mknod(pipefn,S_IFIFO|0622,0);
        errno = 0;  fd = open(pipefn,O_WRONLY|O_NDELAY);
      }
    if (fd == 0)
      {
        /*  ooopppsss...  there is another listener  */
        (void) close(fd);
        /*  silently terminate  */
        return 0;
      }
    if (errno != ENXIO)
      {
        /*  some other error,  report it  */
        (void) perror("");
        /*  and then quit  */
        return fd;
      }

    /*  we didn't really want to write  */
    (void) close(fd);
    /*  we'll re-open R/O shortly  */

    /*  if we're the parent of a -u child,  then exit now  */
    if (pid > 0) return 0;

    /*  loop forever  */
    while (1)
      {
        fd = open(pipefn,O_RDONLY);
        if (fd < 0) break;

        /*  loop on message instance  */
        while (1)
          {
            i = read(fd,buffer,4096);
            if (i < 1)
            i = read(fd,buffer,4096);
            if (i < 1) break;

            /*  be sure it's environment terminated (double NULL)  */
            buffer[i++] = 0x00; buffer[i++] = 0x00; buffer[i++] = 0x00;
            /*  and reference the environment  */
            envbuf = buffer; while (*envbuf) envbuf++;  envbuf++;

            /*  remove trailing line breaks and white space  */
            i = strlen(buffer) - 1;
            while (i >= 0 &&
                (buffer[i] == '\n' || buffer[i] == '\r'
                        || buffer[i] == ' ')) buffer[i--] = 0x00;

            /*  remove CTRLs and canonicalize line breaks  */
            for (p = q = buffer; *p != 0x00; p++)
              {
                if (*p < '\r') *q++ = ' ';
                if (*p < ' ' && *p != '\t') *q++ = '.';
                else *q++ = *p;
              }
 
            /*  now write the message text  */
            errno = 0;
            type = envget(envbuf,"MSGTYPE");
            from = envget(envbuf,"MSGFROM");
            host = envget(envbuf,"MSGHOST");
            switch (type[0])
              {
                case  'E':
                case  'I':  (void) strncpy(outbuf,buffer,4096);
                            break;
                case  'M':
                case  'W':
                case  'S':  case  'U':
                default:    sprintf(outbuf,
                                "From %s(%s): %s",host,from,buffer);
/*                          sprintf(outbuf,
                                "From %s@%s: %s",from,host,buffer);   */
              }
            if (uft_putline(1,outbuf) < 0) break;
          }
        (void) close(fd);
      }
/*  (void) sprintf(buffer,"xmitmsg -2 -a errno %d",errno);
    (void) system(buffer);                      */
    (void) perror(arg0);
    return 0;
  }



/*

        When type 1             "MSG" (UMSG)
        When type 2             "WNG" (WMSG)
        When type 3             "CPCONIO"
        When type 4             "SMSG"
        When type 5             "VMCONIO"
        When type 6             "EMSG"
        When type 7             "IMSG"
        When type 8             "SCIF"
        When type               "FILE" (is an IMSG)
        When type               "MAIL" (is an IMSG)
        When type               "TIME" (is an IMSG)


 */
