/* ---------------------------------------------------------------------------
 * Linux_SysfsDeviceUtil.h
 * 
 * Copyright (c) IBM Corp. 2003, 2009
 *
 * THIS FILE IS PROVIDED UNDER THE TERMS OF THE ECLIPSE PUBLIC LICENSE
 * ("AGREEMENT"). ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE
 * CONSTITUTES RECIPIENTS ACCEPTANCE OF THE AGREEMENT.
 *
 * You can obtain a current copy of the Eclipse Public License from
 * http://www.opensource.org/licenses/eclipse-1.0.php
 *
 * Author:      Gareth S Bestor <bestorga@us.ibm.com>
 *
 * Description: Utility functions for Linux_Sysfs device providers
 * --------------------------------------------------------------------------- */

#include "cmpidt.h"
#include "cmpift.h"
#include "cmpimacs.h"
#include "OSBase_Common.h"
#include "cmpiOSBase_Common.h"

CMPIObjectPath * Linux_SysfsDeviceUtil_makeObjectPath( char * instancename, const CMPIBroker * broker, char * namespace, const char * classname );
CMPIInstance * Linux_SysfsDeviceUtil_makeInstance( char * instancename, const CMPIBroker * broker, char * namespace, const char * classname );

void * Linux_SysfsDeviceUtil_beginEnumeration( void * location );
int Linux_SysfsDeviceUtil_nextEnumeration( void * handle, char * name );
void Linux_SysfsDeviceUtil_endEnumeration( void * handle );

