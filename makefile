
LDFLAGS 	=	
LIBS		=	
CFLAGS		=	
PREFIX		=	/home/rmt/devel/uft/24327

.PHONY: 	clean distclean config help

all:		uftd sf maketext cpq cpqu \
			tell msgpipe msgcat msgd

uftd:		makefile uftd.o \
			uftdnext.o uftddata.o uftduser.o \
			uftdmove.o uftdimsg.o uftdlmsg.o uftdlist.o \
			getline.o putline.o abbrev.o tcpio.o aecs.o
		$(CC) $(CFLAGS) -o uftd uftd.o \
			uftdnext.o uftddata.o uftduser.o \
			uftdmove.o uftdimsg.o uftdlmsg.o uftdlist.o \
			getline.o putline.o abbrev.o tcpio.o aecs.o $(LIBS)

uftdnext.o:	makefile uft.h uftdnext.c
		$(CC) $(CFLAGS) -c uftdnext.c

uftddata.o:	makefile uft.h uftddata.c
		$(CC) $(CFLAGS) -c uftddata.c

uftduser.o:	makefile uft.h uftduser.c
		$(CC) $(CFLAGS) -c uftduser.c

uftdmove.o:	makefile uft.h uftdmove.c
		$(CC) $(CFLAGS) -c uftdmove.c

uftdimsg.o:	makefile uft.h uftdimsg.c
		$(CC) $(CFLAGS) -c uftdimsg.c

uftdlmsg.o:	makefile uft.h uftdlmsg.c
		$(CC) $(CFLAGS) -c uftdlmsg.c

uftdlist.o:	makefile uft.h uftdlist.c
		$(CC) $(CFLAGS) -c uftdlist.c

uftd.o: 	makefile uft.h uftd.c
		$(CC) $(CFLAGS) -c uftd.c

sf:		makefile uftc.o \
			uftcwack.o uftctext.o uftcprot.o \
			tcpio.o getline.o putline.o \
			userid.o aecs.o readspan.o
		$(CC) $(CFLAGS) -o sf uftc.o \
			uftcwack.o uftctext.o uftcprot.o \
			tcpio.o getline.o putline.o \
			userid.o aecs.o readspan.o $(LIBS)

uftc.o: 	makefile uft.h uftc.c
		$(CC) $(CFLAGS) -c uftc.c

uftcwack.o:	makefile uft.h uftcwack.c
		$(CC) $(CFLAGS) -c uftcwack.c

uftctext.o:	makefile uft.h uftctext.c
		$(CC) $(CFLAGS) -c uftctext.c

uftcprot.o:	makefile uft.h uftcprot.c
		$(CC) $(CFLAGS) -c uftcprot.c

uftcnote.h:	makefile uftcnote.txt
		cat uftcnote.txt > uftcnote.tmp
		echo "" >> uftcnote.tmp
		echo "char *uftcnote[" \
			`cat uftcnote.tmp | wc -l` "] = {" > uftcnote.h
		rm uftcnote.tmp
		awk '{print "\"" $$0 " \","}' \
			< uftcnote.txt >> uftcnote.h
		echo "\"\"};" >> uftcnote.h

uftcmime:	makefile uftcmime.c uftcnote.h
		$(CC) $(CFLAGS) -o uftcmime uftcmime.c $(LIBS)

maketext:	makefile maketext.o getline.o putline.o tcpio.o aecs.o
		$(CC) $(CFLAGS) -o maketext \
			maketext.o getline.o putline.o tcpio.o aecs.o $(LIBS)

cpq:		makefile cpq.o uftcwack.o \
			tcpio.o getline.o putline.o aecs.o
		$(CC) $(CFLAGS) -o cpq cpq.o uftcwack.o \
			tcpio.o getline.o putline.o aecs.o $(LIBS)

cpqu:		makefile cpqu.o uftcwack.o \
			tcpio.o getline.o putline.o aecs.o
		$(CC) $(CFLAGS) -o cpqu cpqu.o uftcwack.o \
			tcpio.o getline.o putline.o aecs.o $(LIBS)

clean:
		rm -f core a.out *.o *.a *.lst CEEDUMP.* \
			uftd sf maketext cpq cpqu uftcmime \
			tell msgpipe msgcat msgd imsg

distclean:
		rm -f core a.out *.o *.a *.lst CEEDUMP.* \
			uftd sf maketext cpq cpqu uftcmime \
			tell msgpipe msgcat msgd imsg \
			*:* *';'* makefile Makefile



help:
	@echo "$(MAKE):"
	@echo "$(MAKE): this is the build logic for UFT, POSIX 'sendfile'"
	@echo "$(MAKE):"


getline.o:	makefile getline.c
		$(CC) $(CFLAGS) -c getline.c

putline.o:	makefile putline.c
		$(CC) $(CFLAGS) -c putline.c

abbrev.o:	makefile abbrev.c
		$(CC) $(CFLAGS) -c abbrev.c

tcpio.o:	makefile tcpio.c
		$(CC) $(CFLAGS) -c tcpio.c

userid.o:	makefile userid.c
		$(CC) $(CFLAGS) -c userid.c

maketext.o:	makefile maketext.c
		$(CC) $(CFLAGS) -c maketext.c

cpq.o:		makefile cpq.c
		$(CC) $(CFLAGS) -c cpq.c

cpqu.o:		makefile cpqu.c
		$(CC) $(CFLAGS) -c cpqu.c

aecs.o: 	makefile aecs.c aecs.h
		$(CC) $(CFLAGS) -c aecs.c

readspan.o: 	makefile readspan.c
		$(CC) $(CFLAGS) -c readspan.c




secure: 	default
		chgrp msg tell msgd
		chmod g+s tell msgd

msgcat: 	makefile msgpipe
		rm -f msgcat
		ln msgpipe msgcat

msgpipe:	makefile msgpipe.o putline.o
		$(CC) -o msgpipe msgpipe.o putline.o
		strip msgpipe

msgd:		makefile msgd.o msgdlmsg.o \
			putline.o tcpio.o aecs.o homedir.o
		$(CC) -o msgd msgd.o msgdlmsg.o \
			putline.o tcpio.o aecs.o homedir.o
		strip msgd

tell:		makefile msgc.o msgcmsp.o msgcuftd.o msglocal.o \
			getline.o tcpio.o userid.o putline.o aecs.o homedir.o
		$(CC) -o tell msgc.o msgcmsp.o msgcuftd.o msglocal.o \
			getline.o tcpio.o userid.o putline.o aecs.o homedir.o
		strip tell

imsg:		makefile imsg.o putline.o getline.o aecs.o
		$(CC) -o imsg imsg.o putline.o getline.o aecs.o
		strip imsg

imsg.o: 	makefile uft.h imsg.c
		$(CC) -c imsg.c

msgcmsp.o: 	makefile uft.h msgcmsp.c
		$(CC) -c msgcmsp.c

msgcuftd.o:	makefile uft.h msgcuftd.c
		$(CC) -c msgcuftd.c

msglocal.o:	makefile uft.h msglocal.c
		$(CC) -c msglocal.c

msgpipe.o:	makefile msgpipe.c
		$(CC) -c msgpipe.c

msgc.o: 	makefile uft.h msgc.c
		$(CC) -c msgc.c

msgd.o: 	makefile uft.h msgd.c
		$(CC) -c msgd.c

msgdlmsg.o:	makefile uft.h msgdlmsg.c
		$(CC) -c msgdlmsg.c

homedir.o:	makefile homedir.c
		$(CC) -c homedir.c





install:	sf uftd 
		mkdir -p $(PREFIX)/bin $(PREFIX)/sbin $(PREFIX)/etc/xinetd.d
		cp -p sf $(PREFIX)/bin/.
		cp -p uftd $(PREFIX)/sbin/.
		cp -p uft.inet $(PREFIX)/etc/xinetd.d/uft

rpm:
		rpm -bb uft.spec
		new -d /usr/src/*/RPMS/*/uft-*.rpm .





rpmbuild:
		rpm -bc --short-circuit uft.spec


