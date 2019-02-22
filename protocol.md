# UFT Protocol

This is an overview of Unsolicited File Transfer Protocol in markdown format.


## UFT Control Verbs

* FILE
* PIPE
* USER
* TYPE
* DATA
* AUXDATA
* EOF
* ABORT
* META


## UFT Meta Verbs

* NAME
* DATE
* XDATE
* TITLE
* OWNER
* GROUP
* XPERM
* VERSION
* RECFMT
* RECLEN
* CLASS
* FORM
* HOLD
* COPY
* FCB
* UCS
* DEST
* DIST
* SEQ


## UFT Response Codes

UFT response code numbers are unique.
Any single response code can be mapped to a specific condition, status, or meaning
and can thus be accurately mapped to human-readable text in national language
or regional dialect.

Response code space has gaps.
That is, there are places where response code numbers appear to have been skipped.

* 100s range: a spontaneous response from the server, an "info" message
* 200s range: acknowledgment (ACK)
* 300s range: more input requried; the client must supply additional information
* 400s range: temporary error (NAK), typically a client error
* 500s range: permanent error (NAK), typically a server error
* 600s range: a required response from the server, contrast with 100s range spontaneous responses


## UFT File Types

* TYPE A: ASCII, plain text with CR/LF (0x0D/0x0A) delimited lines, NVT format
* TYPE B: "binary", an alias for TYPE I
* TYPE C
* TYPE E: EBCDIC, IBM mainframe plain text with NL (0x15) delimited lines

Indicates padding with 0x40 blanks if appropriate.

* TYPE F: reserved, implies fixed-length records which canonicalize as binary
* TYPE I: "image" (binary)
* TYPE M: mail, canonicalized as TYPE A but intended for email delivery, routing, or forwarding

The expectation is an RFC 822 message with header and body but no RFC 821 protocol directives.

* TYPE N: NETDATA (IBM proprietary, but an intentinal use case)
* TYPE T: "text", an alias for TYPE I
* TYPE V: variable-length record-oriented, a 16-bit length in network byte order preceeds each record
* TYPE W: "wide" variable-length record-oriented, a 32-bit length in network byte order preceeds each record
* TYPE X: extra-wide (this is gratuitous, almost silly)




