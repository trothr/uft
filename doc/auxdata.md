# AUXDATA

UFT protocol AUXDATA command

A UFT client uses the AUXDATA command to signal a burst of
supplemental or auxiliary data not part of the file body nor part of
the standard metadata.

This extra data would be the "resource fork" found in original MacOS.
It can be content of the "external attribute buffer" (XAB) on z/VM.
It might be used for "extended attributes" for various filesystems
on Windows and Linux.

## Command Format

The format of the AUXDATA command is:

    AUXDATA *burst-size*

where

       *burst-size* is the number of octets to be sent
                    before the next command will be sent

## Command Response




