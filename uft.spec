#%package 
Summary: Universal File Transfer
Name: uft
Version: 1.6.4
Release: 0
Group: Utilities/System
Source: ftp://casita.houston.tx.us/pub/uft/rpm-%{version}.tar.gz
Copyright: GPL
BuildRoot: /tmp/uft
#Conflicts: patch < 2.5

%description
UFT is Universal File Transfer, aka is Unsolicited File Transfer. 
One may also call it  "Internet SENDFILE"  or  "Internet TRANSMIT". 
It does over TCP/IP what other tools do over IBM NJE protocol. 

%prep
#%setup -q

%build
#CFLAGS="$RPM_OPT_FLAGS" ./configure --prefix=/usr
#make

%install
#rm -rf $RPM_BUILD_ROOT
#mkdir -p $RPM_BUILD_ROOT/usr/lib

##mkdir -p $RPM_BUILD_ROOT/usr/src/redhat/SOURCES
##mkdir -p $RPM_BUILD_ROOT/usr/src/redhat/RPMS/${RPM_ARCH}

#make installprefix="$RPM_BUILD_ROOT/uft" install 

%clean
#rm -rf $RPM_BUILD_ROOT/uft 

%post
#/bin/rpm --initdb

%files
#%defattr(-,root,root)
#%doc README 
#%doc docs/*
/usr/bin/sf
#/usr/man/man1/uft.1
#/usr/lib/rpmrc
/usr/sbin/in.uftd
%dir /usr/spool/uft
#/usr/src/redhat/RPMS/*

