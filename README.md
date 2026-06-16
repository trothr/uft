# UFT

Note:
This project has been moved and now lives at
https://github.com/trothtech/uft/

The new repository has both POSIX and VM/CMS components. <br/>
Since the move, this copy lags behind the other. <br/>
You *really* should be looking to the other repository, not here.

Unsolicited File Transfer

Here, "unsolicited" does not mean "unwanted"
but rather that the recipient did not fetch the file
and the sender might not have sign-on credentials on the target host.

A better expansion of the acronym might be <br/>
*Universal* File Transfer (a name with less baggage) <br/>
There is also the title "Sender-Initiated File Transfer" or SIFT,
which usually refers to an offline or batch variant of the protocol.

## UFT for POSIX Systems

The POSIX (Unix, Linux, and other Unix-like systems)
source is in the `src` directory.

The usual sequence of steps to build UFT on a POSIX system is ...

    ./configure
    make
    make install
    make clean

The `configure` script is not very sophisticated.
The only option it takes is `--prefix`.

The `sf` UFT client command sends files to UFT servers. <br/>
Use either "-a" for plain text files or "-i" for binary files.

Files received by the UFT server are held in a sort of "delivery dock"
for disposition by the target user. There are two commands: `rls`
to list files waiting on the dock, and `rcv` to receive selected files.

## UFT for VM/CMS

UFT mimics the operation of IBM's RSCS and other IBM mainframe
file transfer networking (specifically NJE). So naturally, there is a
VM/CMS implementation of UFT. That was not originally in this project
but is explicitly included in the new home. (see above)

See the `cms` directory.

The VM/CMS UFT implementation is intended to work with existing
commands and utilities on the VM/CMS system. `rdrlist` and `receive`
remain unchanged. There is a UFT-enabled `sf` command
which can be used in place of stock `sendfile`.

## Response Codes

Take note that UFT protocol response numbers are unique.
Contrast with SMTP and FTP where a particular numeric response code
can be produced for multiple conditions.

## Numbered Files

So call "spool files" on the z/VM system and similar systems
are numbered and may or may not be named. (Consider a print job
which does not strictly need a name.) UFT implementations follow
this behavior: all delivered files are numbered and are referred to
by their number. If the file was named on the sending side,
that name should persist when the file is formally received.

"If you have three pet dogs, give them names.
If you have 10,000 head of cattle, don't bother." <br/>
 -- David Gelernter <br/>
 -- recorded 2000-09-10, dunno when he actually said that

## Download

Pre-compiled and otherwise runnable packages are available from

http://www.casita.net/pub/uft/


