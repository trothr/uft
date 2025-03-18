# UFT

Unsolicited File Transfer

Here, "unsolicited" does not mean "unwanted"
but rather that the recipient did not fetch the file
and the sender might not have sign-on credentials on the target host.

A better expansion of the acronym might be <br/>
Universal File Transfer

Note:
This project has been moved and now lives at
https://github.com/trothtech/uft/

The new repository has both POSIX and VM/CMS components.

## README for POSIX UFT

This is the README file for POSIX UFT.
For more information,  see the HTML files in the "doc" directory
or find the same content on the web at ...

    http://www.casita.net/pub/uft/

The usual sequence of steps to build UFT on a POSIX system is ...

    ./configure
    make
    make install
    make clean

The only option 'configure' takes is "--prefix".

For Solaris, if 'make' fails, try

    cc -lnsl -lsocket -o sf uftc.o tcpopen.o getline.o netline.o putline.o

in this directory.

Feel free to use $(CC) and other more orthodox methods in the makefile.
I will eventually clean that up.   Feel free to contribute improvements!

## UFT for VM/CMS

UFT mimics the operation of IBM's RSCS and other IBM mainframe
file transfer networking (specifically NJE). So naturally, there is a
VM/CMS implementation of UFT. That was not originally in this project
but is explicitly included in the new home. (see above)

## Response Codes

"The numbers are all wrong".   The response code numbers have been
hastily slapped into the code and may change.   But PLEASE NOTE that
one significant aspect of UFT is that the response numbers are UNIQUE.
Contrast with SMTP and FTP where a particular numeric response code
can be produced for multiple conditions.

"If you have three pet dogs, give them names.
If you have 10,000 head of cattle, don't bother." <br/>
 -- David Gelernter <br/>
 -- recorded 2000-09-10, dunno when he actually said that


