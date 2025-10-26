# [META] SEQUENCE

This meta command indicates the sequence number (if the file is
part of a set) or queue position or "spool ID" of the file
on the sending side.

The META SEQ statement must come after a FILE command
and should preceed any DATA commands.

The "sequence number" at the origin host may simply be a spool file number, or it may have other meaning. Other meanings are implementation dependent.


The syntax is
| verb          | value                                                |
| ------------- | ---------------------------------------------------- |
| META SEQUENCE | *sequence number*                                    |
where *sequence number* is typically a whole number.

The sequence number will almost certainly have local dependencies and/or restrictions.
This attribute implies that the original file resided in a spooling system or was part of a group of files. 


