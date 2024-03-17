#!/bin/sh
#
#         Name: buildrpm.sh (shell script)
#         Date: 2024-03-17 (Sun) St. Patty's Day
#     See also: script by the same name in the VMLINK package
#

# run from the resident directory
cd `dirname "$0"`
D=`pwd`

# establish certain variables
APPLID=uft
APPVRM=`grep '^#define' uft.h | grep UFT_VERSION \
                         | awk -F\" '{print $2}' | awk -F/ '{print $2}'`
BUILDD=$D/$$

if [ ! -s .rpmseq ] ; then echo "1" > .rpmseq ; fi
RPMSEQ=`cat .rpmseq`

UNAMEM=`uname -m`
#UNAMEM=`uname -m | sed 's#^i.86$#i386#' | sed 's#^armv.l$#arm#'`

# create the "sed file"
rm -f uft.rpm.sed

echo "s#%PREFIX%#$PREFIX#g" >> uft.rpm.sed
echo "s#%APPLID%#$APPLID#g" >> uft.rpm.sed
echo "s#%APPVRM%#$APPVRM#g" >> uft.rpm.sed
echo "s#%RPMSEQ%#$RPMSEQ#g" >> uft.rpm.sed
echo "s#%UNAMEM%#$UNAMEM#g" >> uft.rpm.sed
echo "s#%BUILDD%#$BUILDD#g" >> uft.rpm.sed

# process the skeletal spec file into a usable spec file
sed -f uft.rpm.sed < uft.spec.in > uft.spec
RC=$? ; if [ $RC -ne 0 ] ; then exit $RC ; fi
rm uft.rpm.sed

#
# clean up from any prior run
make clean 1> /dev/null 2> /dev/null
rm -rf $BUILDD
#find . -print | grep ';' | xargs -r rm

#
# configure for test
./configure --prefix=$BUILDD
#RC=$? ; if [ $RC -ne 0 ] ; then exit $RC ; fi

#
# 'just make'
#make
make sf uftd
RC=$? ; if [ $RC -ne 0 ] ; then exit $RC ; fi

#
# now try an install
make install
RC=$? ; if [ $RC -ne 0 ] ; then exit $RC ; fi

#
# make it "properly rooted"
mkdir $BUILDD/usr
mv $BUILDD/bin $BUILDD/sbin $BUILDD/usr/.
RC=$? ; if [ $RC -ne 0 ] ; then exit $RC ; fi

#
# check our work
#sh -c " cd $BUILDD ; exec $SHELL "

#
# build the RPM file (and keep a log of the process)
rm -f uft.rpm.log
rpmbuild -bb --nodeps uft.spec | tee uft.rpm.log
RC=$? ; if [ $RC -ne 0 ] ; then exit $RC ; fi
rm uft.spec

#
# recover the RPM file
cp -p $HOME/rpmbuild/RPMS/$UNAMEM/$APPLID-$APPVRM-$RPMSEQ.$UNAMEM.rpm .
#                          UNAMEM  APPLID- APPVRM- RPMSEQ. UNAMEM

#
# remove temporary build directory
rm -r $BUILDD

# increment the sequence number for the next build
expr $RPMSEQ + 1 > .rpmseq

exit


