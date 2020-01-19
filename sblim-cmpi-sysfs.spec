%global provider_dir %{_libdir}/cmpi

Name:           sblim-cmpi-sysfs
Version:        1.2.0
Release:        10%{?dist}
Summary:        SBLIM sysfs instrumentation

Group:          Applications/System
License:        EPL
URL:            http://sblim.wiki.sourceforge.net/
Source0:        http://downloads.sourceforge.net/sblim/%{name}-%{version}.tar.bz2

# Patch0: already upstream,
#         see http://sourceforge.net/tracker/index.php?func=detail&aid=2818227&group_id=128809&atid=712784
Patch0:         sblim-cmpi-sysfs-1.2.0-provider-segfault.patch
# Patch1: issue reported upstream, patch not accepted yet,
#         see http://sourceforge.net/tracker/index.php?func=detail&aid=2818223&group_id=128809&atid=712784
Patch1:         sblim-cmpi-sysfs-1.2.0-sysfs-links.patch
# Patch2: use Pegasus root/interop instead of root/PG_Interop
Patch2:         sblim-cmpi-sysfs-1.2.0-pegasus-interop.patch

BuildRequires:  sblim-cmpi-devel sblim-cmpi-base-devel
Requires:       sblim-cmpi-base cim-server

%description
Standards Based Linux Instrumentation Sysfs Providers

%package        test
Summary:        SBLIM Sysfs Instrumentation Testcases
Group:          Applications/System
Requires:       sblim-cmpi-sysfs = %{version}-%{release}
Requires:       sblim-testsuite

%description test
SBLIM Base Params Testcase Files for SBLIM Testsuite

%prep
%setup -q
%patch0 -p1 -b .provider-segfault
%patch1 -p1 -b .sysfs-links
%patch2 -p1 -b .pegasus-interop
sed -ri 's,-type d -maxdepth 1 -mindepth 1,-maxdepth 1 -mindepth 1 -type d,g' \
        ./test/system/linux/*.{sh,system}


%build
%ifarch s390 s390x ppc ppc64
export CFLAGS="$RPM_OPT_FLAGS -fsigned-char"
%else
export CFLAGS="$RPM_OPT_FLAGS"
%endif

%configure \
        TESTSUITEDIR=%{_datadir}/sblim-testsuite \
        PROVIDERDIR=%{provider_dir}
sed -i 's|^hardcode_libdir_flag_spec=.*|hardcode_libdir_flag_spec=""|g' libtool
sed -i 's|^runpath_var=LD_RUN_PATH|runpath_var=DIE_RPATH_DIE|g' libtool
make


%install
make install DESTDIR=$RPM_BUILD_ROOT
# remove unused libtool files
rm -f $RPM_BUILD_ROOT/%{_libdir}/*a
rm -f $RPM_BUILD_ROOT/%{provider_dir}/*a
# shared libraries
mkdir -p $RPM_BUILD_ROOT/%{_sysconfdir}/ld.so.conf.d
echo "%{_libdir}/cmpi" > $RPM_BUILD_ROOT/%{_sysconfdir}/ld.so.conf.d/%{name}-%{_arch}.conf
mv $RPM_BUILD_ROOT/%{_libdir}/libLinux_SysfsAttributeUtil.so $RPM_BUILD_ROOT/%{provider_dir}
mv $RPM_BUILD_ROOT/%{_libdir}/libLinux_SysfsDeviceUtil.so $RPM_BUILD_ROOT/%{provider_dir}


%files
%dir %{provider_dir}
%{provider_dir}/libLinux_Sysfs*
%{_datadir}/sblim-cmpi-sysfs
%docdir %{_datadir}/doc/sblim-cmpi-sysfs-%{version}
%{_datadir}/doc/sblim-cmpi-sysfs-%{version}
%config(noreplace) %{_sysconfdir}/ld.so.conf.d/%{name}-%{_arch}.conf


%files test
%{_datadir}/sblim-testsuite/sblim-cmpi-sysfs-test.sh
%{_datadir}/sblim-testsuite/cim/Linux_Sysfs*
%{_datadir}/sblim-testsuite/system/linux/Linux_Sysfs*


%global SCHEMA %{_datadir}/%{name}/Linux_SysfsAttribute.mof %{_datadir}/%{name}/Linux_SysfsBlockDevice.mof %{_datadir}/%{name}/Linux_SysfsBusDevice.mof %{_datadir}/%{name}/Linux_SysfsInputDevice.mof %{_datadir}/%{name}/Linux_SysfsNetworkDevice.mof %{_datadir}/%{name}/Linux_SysfsSCSIDevice.mof %{_datadir}/%{name}/Linux_SysfsSCSIHostDevice.mof %{_datadir}/%{name}/Linux_SysfsTTYDevice.mof
%global REGISTRATION %{_datadir}/%{name}/Linux_SysfsAttribute.registration %{_datadir}/%{name}/Linux_SysfsBlockDevice.registration %{_datadir}/%{name}/Linux_SysfsBusDevice.registration %{_datadir}/%{name}/Linux_SysfsInputDevice.registration %{_datadir}/%{name}/Linux_SysfsNetworkDevice.registration %{_datadir}/%{name}/Linux_SysfsSCSIDevice.registration %{_datadir}/%{name}/Linux_SysfsSCSIHostDevice.registration %{_datadir}/%{name}/Linux_SysfsTTYDevice.registration

%pre
function unregister()
{
  %{_datadir}/%{name}/provider-register.sh -d \
        $1 \
        -m %{SCHEMA} \
        -r %{REGISTRATION} > /dev/null 2>&1 || :;
  # don't let registration failure when server not running fail upgrade!
}
 
# If upgrading, deregister old version
if [ $1 -gt 1 ]
then
        unregistered=no
        if [ -e /usr/sbin/cimserver ]; then
           unregister "-t pegasus";
           unregistered=yes
        fi  
 
        if [ -e /usr/sbin/sfcbd ]; then
           unregister "-t sfcb";
           unregistered=yes
        fi  
 
        if [ "$unregistered" != yes ]; then
           unregister
        fi  
fi

%post
function register()
{
  # The follwoing script will handle the registration for various CIMOMs.
  %{_datadir}/%{name}/provider-register.sh \
        $1 \
        -m %{SCHEMA} \
        -r %{REGISTRATION} > /dev/null 2>&1 || :;
  # don't let registration failure when server not running fail install!
}
 
/sbin/ldconfig
if [ $1 -ge 1 ]
then
        registered=no
        if [ -e /usr/sbin/cimserver ]; then
          register "-t pegasus";
          registered=yes
        fi  
 
        if [ -e /usr/sbin/sfcbd ]; then
          register "-t sfcb";
          registered=yes
        fi
 
        if [ "$registered" != yes ]; then
          register
        fi
fi

%preun
function unregister()
{
  %{_datadir}/%{name}/provider-register.sh -d \
        $1 \
        -m %{SCHEMA} \
        -r %{REGISTRATION} > /dev/null 2>&1 || :;
  # don't let registration failure when server not running fail erase!
}
 
if [ $1 -eq 0 ]
then
        unregistered=no
        if [ -e /usr/sbin/cimserver ]; then
          unregister "-t pegasus";
          unregistered=yes
        fi
 
        if [ -e /usr/sbin/sfcbd ]; then
          unregister "-t sfcb";
          unregistered=yes
        fi
 
        if [ "$unregistered" != yes ]; then
          unregister
        fi
fi
 
%postun -p /sbin/ldconfig


%changelog
* Fri Jan 24 2014 Daniel Mach <dmach@redhat.com> - 1.2.0-10
- Mass rebuild 2014-01-24

* Fri Dec 27 2013 Daniel Mach <dmach@redhat.com> - 1.2.0-9
- Mass rebuild 2013-12-27

* Wed Aug 14 2013 Vitezslav Crhonek <vcrhonek@redhat.com> - 1.2.0-8
- Use Pegasus root/interop instead of root/PG_Interop

* Thu Feb 14 2013 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 1.2.0-7
- Rebuilt for https://fedoraproject.org/wiki/Fedora_19_Mass_Rebuild

* Thu Sep 06 2012 Vitezslav Crhonek <vcrhonek@redhat.com> - 1.2.0-6
- Fix issues found by fedora-review utility in the spec file

* Sat Jul 21 2012 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 1.2.0-5
- Rebuilt for https://fedoraproject.org/wiki/Fedora_18_Mass_Rebuild

* Sat Jan 14 2012 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 1.2.0-4
- Rebuilt for https://fedoraproject.org/wiki/Fedora_17_Mass_Rebuild

* Tue Nov 08 2011 Vitezslav Crhonek <vcrhonek@redhat.com> - 1.2.0-3
- Fix provider segfaults when enumerating instances of Linux_SysfsAttribute class
- Fix provider doesn't show much sysfs entries
- Add mofs registration for various CIMOMs

* Wed Feb 09 2011 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 1.2.0-2
- Rebuilt for https://fedoraproject.org/wiki/Fedora_15_Mass_Rebuild

* Mon Oct  4 2010 Vitezslav Crhonek <vcrhonek@redhat.com> - 1.2.0-1
- Update to sblim-cmpi-sysfs-1.2.0
- Remove CIMOM dependencies

* Wed Oct 14 2009 Vitezslav Crhonek <vcrhonek@redhat.com> - 1.1.9-1
- Initial support
