# UFT Development

UFT is based upon NJE networking which is the technology supporting
several large networks of the 1980s and 1990s, in particular BITNET/EARN
(academic and research) and VNET (IBM internal). With the advent of
consumer access to the Internet, these networks fell out of global use,
though NJE is still used within enterprises and some public networks,
such as HNET, persist today.

The design of UFT follows most closely the user interface of IBM's
RSCS product for their VM system (VM/SP, VM/HPO, VM/XA, VM/ESA,
and now z/VM). Some of the utilities in this package are specifically
for purpose of emulating RSCS functionality. These are *not* needed
by the core UFT client and server, so if you find them confusing,
please just ignore them.

# UFT Components

This document describes the components in POSIX UFT.
Most important are the `sf` client for sending files and the
`uftd` server for receiving files.

* sf

`sf` is short for "sendfile". <br/>
This is the UFT client program. It works like `sendfile` or `sf`
on VM/CMS systems or like `transmit` on MVS or z/OS systems.
There are also file sending or file transmitting programs for non-IBM
systems. This `sf` differs from the IBM implementation in that it uses
a direct TCP connection to the target host.

* uftd

`uftd` is the file receiver daemon. <br/>
This server program accepts connections on TCP port 608 and then
receives files according to UFT protocol. In the POSIX implementation
there is a master spool space `/var/spool/uft` with a sub-directory
for each user. Users cannot access each others individual UFT spaces.

* tell

The `tell` command is a multi-protocol client. <br/>
It mimics the behavior of the VM/CMS `tell` command except that it
uses TCP or UDP to convey interactive messages directly to the target.
It differs from other interactive messaging in that users need not
launch a client program. Thus `tell` does not offer "presence".
(For presence and a more complete interactive messaging implementation
see XMPP.)

* msgd

`msgd` is a crude receiver for interactive messages.
It follows MSP (Message Send Protocol). Other interactive message
inbound processing is handled by `uftd`.

* msgcat

`msgcat` is used for presenting interactive messages to the users
in a controlled way. Otherwise, messages might interrupt text mode
work much like Unix `talk` and `write` and similar utilities.

* msgpipe

`msgpipe` is an alias for `msgcat` but is launched from the library.

* cpq

`cpq` mimics the RSCS 'CPQ' command. <br/>
Further discussion is beyond the scope of this project.

* cpqu

`cpqu` mimics the RSCS 'CPQ USER' command. <br/>
Further discussion is beyond the scope of this project.

* maketext

`maketext` is a tool to normalize a plain text file
by removing carriage return (CR) from Unix plain text files or
by adding carriage return to MS Windows plain text files.











