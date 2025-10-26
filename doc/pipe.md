# HELP

HELP is an optional command,
but is implemented in both VM/CMS UFT and in POSIX UFT.

The server responds to HELP with a number of 600 series replies
providing quick help (with the protocol), ending with a 200 ACK.


# [META] VERSION

This meta command indicates the version number or revision number
of the file as it appears on the sending side. UFT does not limit
the implementation or meaning of "version", but one example is found
in the DEC VMS filesystem where files are assigned version numbers automatically.

This statement is not implemented in either VM/CMS UFT nor POSIX UFT.


# AGENT

UFT protocol `AGENT` command

Use the `AGENT` command to confirm the authenticity of a client
acting on behalf of a peer. This will likely be a client connecting
from the same IP address as the known peer, but the AGENT function
adds assurance and is difficult for an un-privileged user to spoof.

Note: this command is not issued by a sending UFT client
but is issued by a receiving UFT server (in client mode, of course)
which has contacted the UFT server on the sending end.
This is a mind bender.

## Command Format

The format of the `AGENT` command is:

    AGENT *verifierstring*

where

    *verifierstring*

is the peer verifier, a sort of "key", which is confirmed or denied
by the UFT server which processes the command.

## Command Response

The `AGENT` command responds with either an ACK (200 series) or NAK
(either 400 series or 500 series). If the server responds with 200 ACK,
then the originating client has been proven authentic as a sending agent.

If the server processing the `AGENT` command returns a 500 series NAK,
it means that the agent string did not match and the originating client
is not a genuine sending agent for users on the sending host.

If the server processing the command responds with a 400 series NAK,
it means that it does not understand the `AGENT` command (not implemented).

## In Plain Language

The `AGENT` command is saying, in effect, "I was given this string by a
sending client assuring that I'm talking to you. Is the string correct?".
If the string matches, then the response should be a 200 series message.
If the string does not match, then the response should be a 500 series message.

A 400 series response indicates that the target system does not support `AGENT`.
This has security implications: how can a sending UFT client provide
an agent string if the UFT server on that host cannot process the
`AGENT` command?

## Security

The agent string (the verifier string) is arbitrary
and implementation dependent.
We recommend a SHA256 message digest of some protected reference.
Longer hashes are stronger, but the SHA256 is perhaps more practical,
being only 64 bytes when represented in hexadecimal.

The verifier string must never be returned by the server.
That would render it copyable by a rogue client.

The verifier string is to be provided by a client, as illustrated above.
The client will either be operating as a privileged service or will have
acquired the agent string through secure means. The fact that a client
posesses a correct verifier string confirms its peer authenticity.

The agent string may change at any time, based on conditions at the
owning peer, even on each client transaction.


# [META] NAME

UFT protocol NAME command

A UFT client uses the NAME command to name the file being sent.
Unlike for FTP, in practice, UFT does not require files to be named.

This meta command names the file being sent.

Note that a filename is optional in UFT
because, while files are named in normal use, a file being sent
might be the output of a command (and thus not yet named).

## Command Format

The format of the FILE command is:

    [META] NAME filename

where

    filename   is the name of the file about to be sent

Quoting of special characters is not discussed.

## Command Response



-rw-r--r-- 1 ttech ttech  173 Apr  3 15:02 doc/meta.md
-rw-r--r-- 1 ttech ttech  150 Apr  3 15:02 doc/date.md
-rw-r--r-- 1 ttech ttech  152 Apr  3 15:02 doc/xdate.md
-rw-r--r-- 1 ttech ttech  447 Apr  3 14:58 doc/user.md
-rw-r--r-- 1 ttech ttech  758 Apr  3 14:58 doc/msg.md
-rw-r--r-- 1 ttech ttech  824 Apr  3 14:58 doc/cpq.md
-rw-r--r-- 1 ttech ttech  649 Apr  3 14:58 doc/auxdata.md
-rw-r--r-- 1 ttech ttech  666 Apr  3 14:58 doc/eof.md
-rw-r--r-- 1 ttech ttech  648 Apr  3 14:58 doc/data.md
-rw-r--r-- 1 ttech ttech  837 Apr  3 14:58 doc/file.md
-rw-r--r-- 1 ttech ttech  585 Apr  3 14:57 doc/quit.md
-rw-r--r-- 1 ttech ttech  984 Apr  3 14:57 doc/type.md
