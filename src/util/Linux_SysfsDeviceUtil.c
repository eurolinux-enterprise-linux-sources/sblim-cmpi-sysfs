/* ---------------------------------------------------------------------------
 * Linux_SysfsDeviceUtil.c
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
 * Author:	Dr. Gareth S. Bestor <bestorga@us.ibm.com>
 *
 * Description:	Utility functions for Linux_Sysfs device providers
 * --------------------------------------------------------------------------- */

#include "cmpidt.h"
#include "cmpift.h"
#include "cmpimacs.h"
#include "OSBase_Common.h"
#include "cmpiOSBase_Common.h"

#include "Linux_SysfsDeviceUtil.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


/* ---------------------------------------------------------------------------
 * UTILITY FUNCTIONS TO READ/WRITE INSTANCES
 * --------------------------------------------------------------------------- */

/* Read instance data into a CIM object path (i.e. set key attributes only) */
CMPIObjectPath * Linux_SysfsDeviceUtil_makeObjectPath( char * instancename, const CMPIBroker * broker, char * namespace, const char * classname )
{
   CMPIObjectPath * objectpath;
   CMPIStatus status = {CMPI_RC_OK, NULL};
  
   /* Create a new CIM object path for this instance */
   _OSBASE_TRACE(1,("_makeObjectPath() : Creating new object path for %s",instancename));
   objectpath = CMNewObjectPath(broker, namespace, classname, &status);
   if (CMIsNullObject(objectpath)) {
      _OSBASE_TRACE(1,("_makeObjectPath() : Failed to create new object path - %s",CMGetCharPtr(status.msg)));
      return NULL;
   }

   /* Store this instance's key attributes in the new CIM object path */
   CMAddKey(objectpath, "SystemCreationClassName", CSCreationClassName, CMPI_chars);
   CMAddKey(objectpath, "SystemName", get_system_name(), CMPI_chars);
   CMAddKey(objectpath, "CreationClassName", classname, CMPI_chars);
   CMAddKey(objectpath, "Name", instancename, CMPI_chars);

   return objectpath;
}


/* Read instance data into a CIM instance (i.e. set all attributes) */
CMPIInstance * Linux_SysfsDeviceUtil_makeInstance( char * instancename, const CMPIBroker * broker, char * namespace, const char * classname )
{
   CMPIInstance * instance;
   CMPIStatus status = {CMPI_RC_OK, NULL};

   /* Create a new CIM instance for this instance */
   _OSBASE_TRACE(1,("_makeInstance() : Creating new instance for %s",instancename));
   instance = CMNewInstance(broker, Linux_SysfsDeviceUtil_makeObjectPath(instancename,broker,namespace,classname), &status);
   if (CMIsNullObject(instance)) {
      _OSBASE_TRACE(1,("_makeInstance() : Failed to create new instance - %s",CMGetCharPtr(status.msg)));
      return NULL;
   }

   /* Store this instance's attributes in the new CIM instance */
   CMSetProperty(instance, "SystemCreationClassName", CSCreationClassName, CMPI_chars);
   CMSetProperty(instance, "SystemName", get_system_name(), CMPI_chars);
   CMSetProperty(instance, "CreationClassName", classname, CMPI_chars);
   CMSetProperty(instance, "Name", instancename, CMPI_chars);

   return instance;
}


/* ---------------------------------------------------------------------------
 * UTILITY FUNCTIONS TO ENUMERATE INSTANCES
 * --------------------------------------------------------------------------- */

/* Return a handle to the list of instances */
void * Linux_SysfsDeviceUtil_beginEnumeration( void * location )
{
   FILE * handle;
   char * findcommand = malloc(strlen((char *)location)+38); 

   /* Find all the instance names in the target location */
   sprintf(findcommand, "find %s -maxdepth 1 -mindepth 1 -type d", (char *)location);
   handle = popen(findcommand,"r");
   free(findcommand); 
   return handle; 
}


/* Get the next instance name on the list */
int Linux_SysfsDeviceUtil_nextEnumeration( void * handle, char * name )
{
   if ( handle != NULL ) {
      /* Read the next instance name from the instance name file */
      if ( fscanf((FILE *)handle, "%s\n", name) != EOF ) return 1;
   }
   return 0;
}


/* Close and cleanup the list of instances */
void Linux_SysfsDeviceUtil_endEnumeration( void * handle )
{
   if ( handle != NULL ) {
      pclose((FILE *)handle);
   }
}

