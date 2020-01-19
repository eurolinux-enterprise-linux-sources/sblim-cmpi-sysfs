#!/bin/sh

# Test classes
#CLASSNAMES='Linux_SysfsBlockDevice Linux_SysfsBusDevice Linux_SysfsInputDevice Linux_SysfsNetworkDevice Linux_SysfsSCSIDevice Linux_SysfsSCSIHostDevice Linux_SysfsTTYDevice Linux_SysfsAttribute Linux_SysfsBlockDeviceHasAttribute Linux_SysfsBusDeviceHasAttribute Linux_SysfsInputDeviceHasAttribute Linux_SysfsNetworkDeviceHasAttribute Linux_SysfsSCSIDeviceHasAttribute Linux_SysfsSCSIHostDeviceHasAttribute Linux_SysfsTTYDeviceHasAttribute'

###########################
# IMPORTANT: The Linux_Sysfs*HasAttribute association provider tests will not run correctly at this time
# and therefore they have all have been removed from the list of classes tested.
###########################
CLASSNAMES='Linux_SysfsBlockDevice Linux_SysfsBusDevice Linux_SysfsInputDevice Linux_SysfsNetworkDevice Linux_SysfsSCSIDevice Linux_SysfsSCSIHostDevice Linux_SysfsTTYDevice Linux_SysfsAttribute'

for CLASSNAME in $CLASSNAMES; do
   echo "Running tests for $CLASSNAME..."
   ./run.sh $CLASSNAME
done

