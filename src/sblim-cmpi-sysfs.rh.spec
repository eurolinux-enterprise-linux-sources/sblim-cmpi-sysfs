#
# $Id: sblim-cmpi-sysfs.rh.spec,v 1.3 2009/05/22 02:45:47 tyreld Exp $
#
# Package spec for sblim-cmpi-sysfs - Fedora/RedHat flavor
#

BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

Summary: SBLIM Sysfs Instrumentation
Name: sblim-cmpi-sysfs
Version: 1.1.9
Release: 1
Group: Systems Management/Base
URL: http://www.sblim.org
License: EPL

Source0: http://prdownloads.sourceforge.net/sblim/%{name}-%{version}.tar.bz2

BuildRequires: tog-pegasus-devel >= 2.5.1
BuildRequires: sblim-cmpi-base-devel >= 1.5

Requires: tog-pegasus >= 2.5.1
Requires: sblim-cmpi-base >= 1.5

%Description
Standards Based Linux Instrumentation Sysfs Providers

%Package devel
Summary: SBLIM Sysfs Instrumentation Header Development Files
Group: Systems Management/Base
Requires: %{name} = %{version}-%{release}

%Description devel
SBLIM Base Sysfs Development Package

%Package test
Summary: SBLIM Sysfs Instrumentation Testcases
Group: Systems Management/Base
Requires: %{name} = %{version}-%{release}
Requires: sblim-testsuite

%Description test
SBLIM Base Sysfs Testcase Files for SBLIM Testsuite

%prep

%setup -q

%build

%configure TESTSUITEDIR=%{_datadir}/sblim-testsuite CIMSERVER=pegasus

make %{?_smp_mflags}

%clean

rm -rf $RPM_BUILD_ROOT

%install

rm -rf $RPM_BUILD_ROOT

make DESTDIR=$RPM_BUILD_ROOT install

# remove unused libtool files
rm -f $RPM_BUILD_ROOT/%{_libdir}/*a
rm -f $RPM_BUILD_ROOT/%{_libdir}/cmpi/*a

%pre
%define SCHEMA %{_datadir}/%{name}/Linux_SysfsAttribute.mof \
		%{_datadir}/%{name}/Linux_SysfsBlockDevice.mof \
		%{_datadir}/%{name}/Linux_SysfsBusDevice.mof \
		%{_datadir}/%{name}/Linux_SysfsInputDevice.mof \
		%{_datadir}/%{name}/Linux_SysfsNetworkDevice.mof \
		%{_datadir}/%{name}/Linux_SysfsSCSIDevice.mof \
		%{_datadir}/%{name}/Linux_SysfsSCSIHostDevice.mof \
		%{_datadir}/%{name}/Linux_SysfsTTYDevice.mof
%define REGISTRATION %{_datadir}/%{name}/Linux_SysfsAttribute.registration \
		%{_datadir}/%{name}/Linux_SysfsBlockDevice.registration \
		%{_datadir}/%{name}/Linux_SysfsBusDevice.registration \
		%{_datadir}/%{name}/Linux_SysfsInputDevice.registration \
		%{_datadir}/%{name}/Linux_SysfsNetworkDevice.registration \
		%{_datadir}/%{name}/Linux_SysfsSCSIDevice.registration \
		%{_datadir}/%{name}/Linux_SysfsSCSIHostDevice.registration \
		%{_datadir}/%{name}/Linux_SysfsTTYDevice.registration

# If upgrading, deregister old version
if [ $1 -gt 1 ]
then
  %{_datadir}/%{name}/provider-register.sh -d -t pegasus \
	-r %{REGISTRATION} -m %{SCHEMA} > /dev/null 2>&1
fi

%post
# Register Schema and Provider - this is higly provider specific

%{_datadir}/%{name}/provider-register.sh -t pegasus \
	-r %{REGISTRATION} -m %{SCHEMA} > /dev/null 2>&1

/sbin/ldconfig

%preun
# Deregister only if not upgrading 
if [ $1 -eq 0 ]
then
  %{_datadir}/%{name}/provider-register.sh -d -t pegasus \
	-r %{REGISTRATION} -m %{SCHEMA} > /dev/null 2>&1
fi

%postun -p  /sbin/ldconfig

%files

%defattr(-,root,root) 
%docdir %{_datadir}/doc/%{name}-%{version}
%{_datadir}/%{name}
%{_datadir}/doc/%{name}-%{version}
%{_libdir}/*.so.*
%{_libdir}/cmpi/*.so

%files devel

%defattr(-,root,root)
%{_includedir}/*
%{_libdir}/*.so

%files test

%defattr(-,root,root)
%{_datadir}/sblim-testsuite

%changelog
* Mon Dec 12 2005 Lynn Moss <lynnmoss@us.ibm.com>	1.0.11
  - initial support
