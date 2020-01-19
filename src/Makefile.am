# $Id: Makefile.am,v 1.2 2009/05/22 02:45:47 tyreld Exp $ 
# ==================================================================
# (C) Copyright IBM Corp. 2005, 2009
#
# THIS FILE IS PROVIDED UNDER THE TERMS OF THE ECLIPSE PUBLIC LICENSE
# ("AGREEMENT"). ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE
# CONSTITUTES RECIPIENTS ACCEPTANCE OF THE AGREEMENT.
#
# You can obtain a current copy of the Eclipse Public License from
# http://www.opensource.org/licenses/eclipse-1.0.php
#
# Author:       Lynn Moss <lynnmoss@us.ibm.com>
# Description:  Automake input file for Sysfs Providers
# ==================================================================


# SBLIM Include Directory
sblimincdir = $(includedir)/sblim

# Start from an empty extra distribution file list
EXTRA_DIST=

# docdir defines where the documentation goes
docdir=$(datadir)/doc/$(PACKAGE)-$(VERSION)

#
# Automake instructions for documentation
#
doc_DATA=README AUTHORS COPYING 

# ADD EXTRA DOC FILES IF PRESENT
doc_DATA+=DEBUG README.tog-pegasus sysfs.txt
EXTRA_DIST+=DEBUG README.tog-pegasus sysfs.txt

# providerdir defines where provider libraries will be installed (@PROVIDERDIR@ is set by the configure script). 
providerdir = @PROVIDERDIR@

# Automake instructions for main dir
#

# Look for headers in util
AM_CPPFLAGS = -I./util

#  Sysfs CMPI provider libraries
provider_LTLIBRARIES = 	libLinux_SysfsAttribute.la \
			libLinux_SysfsBlockDevice.la \
			libLinux_SysfsBusDevice.la \
			libLinux_SysfsInputDevice.la \
			libLinux_SysfsNetworkDevice.la \
			libLinux_SysfsSCSIDevice.la \
			libLinux_SysfsSCSIHostDevice.la \
			libLinux_SysfsTTYDevice.la \
			libLinux_SysfsBlockDeviceHasAttribute.la \
			libLinux_SysfsBusDeviceHasAttribute.la \
			libLinux_SysfsInputDeviceHasAttribute.la \
			libLinux_SysfsNetworkDeviceHasAttribute.la \
			libLinux_SysfsSCSIDeviceHasAttribute.la \
			libLinux_SysfsSCSIHostDeviceHasAttribute.la \
			libLinux_SysfsTTYDeviceHasAttribute.la

# SysfsAttribute
libLinux_SysfsAttribute_la_SOURCES = \
		AttributeProvider/Linux_SysfsAttribute.c
libLinux_SysfsAttribute_la_LIBADD = \
		-lpthread -lcmpiOSBase_Common \
		-lLinux_SysfsAttributeUtil
libLinux_SysfsAttribute_la_LDFLAGS = -avoid-version -shared

# SysfsBlockDevice
libLinux_SysfsBlockDevice_la_SOURCES = \
		DeviceProvider/Linux_SysfsBlockDevice.c
libLinux_SysfsBlockDevice_la_LIBADD = \
		-lpthread -lcmpiOSBase_Common \
		-lLinux_SysfsDeviceUtil
libLinux_SysfsBlockDevice_la_LDFLAGS = -avoid-version -shared

# SysfsBusDevice
libLinux_SysfsBusDevice_la_SOURCES = \
		DeviceProvider/Linux_SysfsBusDevice.c
libLinux_SysfsBusDevice_la_LIBADD = \
		-lpthread -lcmpiOSBase_Common \
		-lLinux_SysfsDeviceUtil
libLinux_SysfsBusDevice_la_LDFLAGS = -avoid-version -shared

# SysfsInputDevice
libLinux_SysfsInputDevice_la_SOURCES = \
		DeviceProvider/Linux_SysfsInputDevice.c
libLinux_SysfsInputDevice_la_LIBADD = \
		-lpthread -lcmpiOSBase_Common \
		-lLinux_SysfsDeviceUtil
libLinux_SysfsInputDevice_la_LDFLAGS = -avoid-version -shared

# SysfsNetworkDevice
libLinux_SysfsNetworkDevice_la_SOURCES = \
		DeviceProvider/Linux_SysfsNetworkDevice.c
libLinux_SysfsNetworkDevice_la_LIBADD = \
		-lpthread -lcmpiOSBase_Common \
		-lLinux_SysfsDeviceUtil
libLinux_SysfsNetworkDevice_la_LDFLAGS = -avoid-version -shared

# SysfsSCSIDevice
libLinux_SysfsSCSIDevice_la_SOURCES = \
		DeviceProvider/Linux_SysfsSCSIDevice.c
libLinux_SysfsSCSIDevice_la_LIBADD = \
		-lpthread -lcmpiOSBase_Common \
		-lLinux_SysfsDeviceUtil
libLinux_SysfsSCSIDevice_la_LDFLAGS = -avoid-version -shared

# SysfsSCSIHostDevice
libLinux_SysfsSCSIHostDevice_la_SOURCES = \
		DeviceProvider/Linux_SysfsSCSIHostDevice.c
libLinux_SysfsSCSIHostDevice_la_LIBADD = \
		-lpthread -lcmpiOSBase_Common \
		-lLinux_SysfsDeviceUtil
libLinux_SysfsSCSIHostDevice_la_LDFLAGS = -avoid-version -shared

# SysfsTTYDevice
libLinux_SysfsTTYDevice_la_SOURCES = \
		DeviceProvider/Linux_SysfsTTYDevice.c
libLinux_SysfsTTYDevice_la_LIBADD = \
		-lpthread -lcmpiOSBase_Common \
		-lLinux_SysfsDeviceUtil
libLinux_SysfsTTYDevice_la_LDFLAGS = -avoid-version -shared

# SysfsBlockDeviceHasAttribute
libLinux_SysfsBlockDeviceHasAttribute_la_SOURCES = \
		AssociationProvider/Linux_SysfsBlockDeviceHasAttribute.c
libLinux_SysfsBlockDeviceHasAttribute_la_LIBADD = \
		-lpthread -lcmpiOSBase_Common \
		-lLinux_SysfsAttributeUtil
libLinux_SysfsBlockDeviceHasAttribute_la_LDFLAGS = -avoid-version -shared

# SysfsBusDeviceHasAttribute
libLinux_SysfsBusDeviceHasAttribute_la_SOURCES = \
		AssociationProvider/Linux_SysfsBusDeviceHasAttribute.c
libLinux_SysfsBusDeviceHasAttribute_la_LIBADD = \
		-lpthread -lcmpiOSBase_Common \
		-lLinux_SysfsAttributeUtil
libLinux_SysfsBusDeviceHasAttribute_la_LDFLAGS = -avoid-version -shared

# SysfsInputDeviceHasAttribute
libLinux_SysfsInputDeviceHasAttribute_la_SOURCES = \
		AssociationProvider/Linux_SysfsInputDeviceHasAttribute.c
libLinux_SysfsInputDeviceHasAttribute_la_LIBADD = \
		-lpthread -lcmpiOSBase_Common \
		-lLinux_SysfsAttributeUtil
libLinux_SysfsInputDeviceHasAttribute_la_LDFLAGS = -avoid-version -shared

# SysfsNetworkDeviceHasAttribute
libLinux_SysfsNetworkDeviceHasAttribute_la_SOURCES = \
		AssociationProvider/Linux_SysfsNetworkDeviceHasAttribute.c
libLinux_SysfsNetworkDeviceHasAttribute_la_LIBADD = \
		-lpthread -lcmpiOSBase_Common \
		-lLinux_SysfsAttributeUtil
libLinux_SysfsNetworkDeviceHasAttribute_la_LDFLAGS = -avoid-version -shared

# SysfsSCSIDeviceHasAttribute
libLinux_SysfsSCSIDeviceHasAttribute_la_SOURCES = \
		AssociationProvider/Linux_SysfsSCSIDeviceHasAttribute.c
libLinux_SysfsSCSIDeviceHasAttribute_la_LIBADD = \
		-lpthread -lcmpiOSBase_Common \
		-lLinux_SysfsAttributeUtil
libLinux_SysfsSCSIDeviceHasAttribute_la_LDFLAGS = -avoid-version -shared

# SysfsSCSIHostDeviceHasAttribute
libLinux_SysfsSCSIHostDeviceHasAttribute_la_SOURCES = \
		AssociationProvider/Linux_SysfsSCSIHostDeviceHasAttribute.c
libLinux_SysfsSCSIHostDeviceHasAttribute_la_LIBADD = \
		-lpthread -lcmpiOSBase_Common \
		-lLinux_SysfsAttributeUtil
libLinux_SysfsSCSIHostDeviceHasAttribute_la_LDFLAGS = -avoid-version -shared

# SysfsTTYDeviceHasAttribute
libLinux_SysfsTTYDeviceHasAttribute_la_SOURCES = \
		AssociationProvider/Linux_SysfsTTYDeviceHasAttribute.c
libLinux_SysfsTTYDeviceHasAttribute_la_LIBADD = \
		-lpthread -lcmpiOSBase_Common \
		-lLinux_SysfsAttributeUtil
libLinux_SysfsTTYDeviceHasAttribute_la_LDFLAGS = -avoid-version -shared

# Sysfs support utility libraries
lib_LTLIBRARIES = libLinux_SysfsAttributeUtil.la \
			libLinux_SysfsDeviceUtil.la

libLinux_SysfsAttributeUtil_la_SOURCES = \
		util/Linux_SysfsAttributeUtil.c
libLinux_SysfsAttributeUtil_la_LIBADD = \
		-lpthread -lcmpiOSBase_Common 
libLinux_SysfsAttributeUtil_la_LDFLAGS = -avoid-version -shared

libLinux_SysfsDeviceUtil_la_SOURCES = \
		util/Linux_SysfsDeviceUtil.c
libLinux_SysfsDeviceUtil_la_LIBADD = \
		-lpthread -lcmpiOSBase_Common 
libLinux_SysfsDeviceUtil_la_LDFLAGS = -avoid-version -shared

# Installable Header Files

# Non-Installable Header Files
noinst_HEADERS = util/Linux_SysfsAttributeUtil.h \
	util/Linux_SysfsDeviceUtil.h

# We must explicity add the RPM spec files to the distribution package
EXTRA_DIST+=$(PACKAGE).spec $(PACKAGE).rh.spec

#
# Automake instructions for ./mof subdir
#
SCHEMAS=mof/Linux_SysfsAttribute.mof \
		mof/Linux_SysfsBlockDevice.mof \
		mof/Linux_SysfsBusDevice.mof \
		mof/Linux_SysfsInputDevice.mof \
		mof/Linux_SysfsNetworkDevice.mof \
		mof/Linux_SysfsSCSIDevice.mof \
		mof/Linux_SysfsSCSIHostDevice.mof \
		mof/Linux_SysfsTTYDevice.mof 
REGISTRATIONS=mof/Linux_SysfsAttribute.registration \
		mof/Linux_SysfsBlockDevice.registration \
		mof/Linux_SysfsBusDevice.registration \
		mof/Linux_SysfsInputDevice.registration \
		mof/Linux_SysfsNetworkDevice.registration \
		mof/Linux_SysfsSCSIDevice.registration \
		mof/Linux_SysfsSCSIHostDevice.registration \
		mof/Linux_SysfsTTYDevice.registration 

# We must explicity add all the schema files to the distribution package
pkgdata_DATA=$(SCHEMAS) $(REGISTRATIONS)
pkgdata_SCRIPTS=provider-register.sh
EXTRA_DIST+=mof $(pkgdata_SCRIPTS)

# Register the provider(s) and class definition(s) to the current CIM server/CIMOM
postinstall:
	sh provider-register.sh -t @CIMSERVER@ -r $(REGISTRATIONS) -m $(SCHEMAS)

preuninstall:
	sh provider-register.sh -d -t @CIMSERVER@ -r $(REGISTRATIONS) -m $(SCHEMAS)

dist-hook:
	test -d "$(distdir)" &&	rm -rf `find $(distdir) -type d -name CVS`
#
# Automake instructions for ./test subdir
#
EXTRA_DIST+=test README.TEST
if TESTSUITE
testsuitedir=@TESTSUITEDIR@
testsuitesystemdir=@TESTSUITEDIR@/system/linux
testsuitecimdir=@TESTSUITEDIR@/cim

testsuite_SCRIPTS=test/sblim-cmpi-sysfs-test.sh

testsuitesystem_DATA=test/system/linux/Linux_SysfsAttribute.system \
	test/system/linux/Linux_SysfsBlockDevice.system \
	test/system/linux/Linux_SysfsBusDevice.system \
	test/system/linux/Linux_SysfsInputDevice.system \
	test/system/linux/Linux_SysfsNetworkDevice.system \
	test/system/linux/Linux_SysfsSCSIDevice.system \
	test/system/linux/Linux_SysfsSCSIHostDevice.system \
	test/system/linux/Linux_SysfsTTYDevice.system \
	test/system/linux/Linux_SysfsBlockDeviceHasAttribute.system \
	test/system/linux/Linux_SysfsBusDeviceHasAttribute.system \
	test/system/linux/Linux_SysfsInputDeviceHasAttribute.system \
	test/system/linux/Linux_SysfsNetworkDeviceHasAttribute.system \
	test/system/linux/Linux_SysfsSCSIDeviceHasAttribute.system \
	test/system/linux/Linux_SysfsSCSIHostDeviceHasAttribute.system \
	test/system/linux/Linux_SysfsTTYDeviceHasAttribute.system 

testsuitesystem_SCRIPTS=test/system/linux/Linux_SysfsAttribute.sh \
	test/system/linux/Linux_SysfsBlockDevice.sh \
	test/system/linux/Linux_SysfsBusDevice.sh \
	test/system/linux/Linux_SysfsInputDevice.sh \
	test/system/linux/Linux_SysfsNetworkDevice.sh \
	test/system/linux/Linux_SysfsSCSIDevice.sh \
	test/system/linux/Linux_SysfsSCSIHostDevice.sh \
	test/system/linux/Linux_SysfsTTYDevice.sh 

testsuitecim_DATA=test/cim/Linux_SysfsAttribute.cim \
	test/cim/Linux_SysfsBlockDevice.cim \
	test/cim/Linux_SysfsBusDevice.cim \
	test/cim/Linux_SysfsInputDevice.cim \
	test/cim/Linux_SysfsNetworkDevice.cim \
	test/cim/Linux_SysfsSCSIDevice.cim \
	test/cim/Linux_SysfsSCSIHostDevice.cim \
	test/cim/Linux_SysfsTTYDevice.cim \
	test/cim/Linux_SysfsBlockDeviceHasAttribute.cim \
	test/cim/Linux_SysfsBusDeviceHasAttribute.cim \
	test/cim/Linux_SysfsInputDeviceHasAttribute.cim \
	test/cim/Linux_SysfsNetworkDeviceHasAttribute.cim \
	test/cim/Linux_SysfsSCSIDeviceHasAttribute.cim \
	test/cim/Linux_SysfsSCSIHostDeviceHasAttribute.cim \
	test/cim/Linux_SysfsTTYDeviceHasAttribute.cim 

runtest: install
	cd $(DESTDIR)$(TESTSUITEDIR) &&	./sblim-cmpi-sysfs-test.sh

doc_DATA+=README.TEST
endif

# Add files which can be used to create new sysfs classes.
EXTRA_DIST += \
	AssociationProvider/create_files \
	DeviceProvider/create_files \
	mof/create_files \
	AssociationProvider/TEMPLATE.c \
	DeviceProvider/TEMPLATE.c \
	mof/TEMPLATE.mof
