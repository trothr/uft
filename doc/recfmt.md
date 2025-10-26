# [META] RECFMT

This meta command indicates the record format, if any,
of the file being sent. Some operating systems, and many applications,
have the concept of a "record", which might be FIXED or VARIABLE
or some other structure description.

Any record structure is lost if the file is not
properly canonicalized or "wrapped" to preserve that structure.
The default record format would be "UNSTRUCTURED" if a default
is needed, which fits with sending files as a stream of bytes.


