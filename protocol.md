# UFT Protocol

This is an overview of Unsolicited File Transfer (UFT) protocol
in markdown format.

## UFT Primary Control Verbs

* FILE
* PIPE
* USER
* TYPE
* DATA
* AUXDATA
* EOF
* ABORT
* META
* QUIT

A sample sequence might be ...

    FILE size from auth
    (wait for actknowledgement from server)
    USER recipient
    (wait for actknowledgement from server)
    TYPE A
    (wait for actknowledgement from server)
    DATA 1234
    (send 1234 bytes and wait for actknowledgement)
    EOF
    (wait for actknowledgement from server)
    QUIT

That transaction uses 6 primary commands and does not require any
meta commands nor secondary commands. Simplicity is the first objective.

## UFT Supplemental Commands

* CPQ
* MSG
* AGENT
* HELP
* NOOP

These are optional and not widely implemented.
`CPQ` and `MSG` are specifically for emulating IBM "NJE" networking.

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

All of the above were originally implemented without the `META` prefix
so it can be helpful to allow them in near-term implementations.
But ideally, they are "meta". Any *new* meta-data *must* be prefixed
with `META` for clarity and for simplifying implementations.

## UFT Response Codes

UFT response code numbers are unique. <br/>
Any single response code can be mapped to a specific condition, status,
or meaning and can thus be accurately mapped to human-readable text
in national language or regional dialect.

Response code space has gaps. That is, there are places
where response code numbers appear to have been skipped.
This is okay.

* 100s range: a spontaneous response from the server, an "info" message
* 200s range: acknowledgment (ACK)
* 300s range: more input requried;
              the client must supply additional information
* 400s range: temporary error (NAK), typically a client error
* 500s range: permanent error (NAK), typically a server error
* 600s range: a required response from the server,
              contrast with 100s range spontaneous responses

## UFT File Types

* TYPE A: ASCII, plain text with CR/LF (0x0D/0x0A) delimited lines
          (see NVT format)
* TYPE B: "binary", an alias for TYPE I (image)
* TYPE C
* TYPE E: EBCDIC, IBM mainframe plain text with NL (0x15) delimited lines

Indicates padding with 0x40 blanks if appropriate.

* TYPE F: reserved, implies fixed-length records
          which canonicalize as binary
* TYPE I: "image" (binary)
* TYPE M: mail, canonicalized as TYPE A but intended for email
          delivery, routing, or forwarding

The expectation with `TYPE M` is an RFC 822 message with header and body
but no RFC 821 protocol directives. (Transport being handled by UFT.)

* TYPE N: NETDATA (IBM proprietary, but an intentional use case)
* TYPE T: "text", an alias for TYPE A
* TYPE V: variable-length record-oriented,
          a 16-bit length in network byte order preceeds each record
* TYPE W: "wide" variable-length record-oriented,
          a 32-bit length in network byte order preceeds each record
* TYPE X: extra-wide (this is gratuitous, almost silly),
          a 64-bit length in network byte order

This seems excessive, but canonicalization is at the heart of UFT. <br/>
There are a finite number of conversions that must be applied to files
to be carried between unlike hosts. Proper application of these conversions
(canonicalizations) ensures file integrity. At a minimum, types "A" and "I"
are needed. All other types should be interpreted as "I" for most systems.


