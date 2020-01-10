/* ---------------------------------------------------------------------------
 * Linux_SysfsTTYDevice.c
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
 * Author:      Dr. Gareth S. Bestor <bestorga@us.ibm.com>
 * Description:	Instance provider for Linux_SysfsTTYDevice class
 * Interface:   Common Manageability Programming Interface (CMPI)
 * ---------------------------------------------------------------------------*/

#include "cmpidt.h"
#include "cmpift.h"
#include "cmpimacs.h"
#include "OSBase_Common.h"
#include "cmpiOSBase_Common.h"

#include "../util/Linux_SysfsDeviceUtil.h"

static const CMPIBroker * _broker;
static const char * _CLASSNAME = "Linux_SysfsTTYDevice";
static char * _LOCATION = "/sys/class/tty";
#define _MAXNAMELENGTH 1024


/*---------------------------------------------------------------------------
 * INSTANCE PROVIDER METHODS
 * --------------------------------------------------------------------------- */

/*
 * EnumInstanceNames
 */
CMPIStatus Linux_SysfsTTYDeviceEnumInstanceNames(
		CMPIInstanceMI * mi, 
		const CMPIContext * context, 
		const CMPIResult * results, 
		const CMPIObjectPath * reference) 
{
   CMPIStatus status = {CMPI_RC_OK, NULL};      /* Return status of CIM operations */
   CMPIObjectPath * objectpath;                 /* CIM object path to store each new instance */
   void * instances;                            /* Handle to the list of instances */
   char instancename[_MAXNAMELENGTH];           /* Unique name of each new instance */

   _OSBASE_TRACE(1,("EnumInstanceNames() called"));

   /* Get the list of instance names stored at _LOCATION */
   instances = Linux_SysfsDeviceUtil_beginEnumeration(_LOCATION);
   if (instances == NULL) {
      _OSBASE_TRACE(1,("EnumInstanceNames() : Failed to get list of instances"));
      CMReturn(CMPI_RC_ERR_FAILED);
      CMSetStatusWithChars( _broker, &status, CMPI_RC_ERR_FAILED, "failed to get list of instances" );
      return status;
   }

   /* Enumerate all the instances and return a new CIM object path for each */
   while (Linux_SysfsDeviceUtil_nextEnumeration(instances, instancename)) {
      objectpath = Linux_SysfsDeviceUtil_makeObjectPath(instancename, _broker, CMGetCharPtr(CMGetNameSpace(reference,&status)), _CLASSNAME);
      if (objectpath != NULL) {
         _OSBASE_TRACE(1,("EnumInstanceNames() : Adding object path for %s",instancename));
         CMReturnObjectPath(results, objectpath);
      }
   }
   Linux_SysfsDeviceUtil_endEnumeration(instances);

   /* Finished */
   CMReturnDone(results);
   CMReturn(CMPI_RC_OK);
   _OSBASE_TRACE(1,("EnumInstanceNames() finished"));
   return status;
}

/*
 * EnumInstances
 */
CMPIStatus Linux_SysfsTTYDeviceEnumInstances(
		CMPIInstanceMI * mi, 
		const CMPIContext * context, 
		const CMPIResult * results, 
		const CMPIObjectPath * reference, 
		const char ** properties) 
{
   CMPIStatus status = {CMPI_RC_OK, NULL};      /* Return status of CIM operations */
   CMPIInstance * instance;                     /* CIM instance to store each new instance */
   void * instances;                            /* Handle to the list of instance names */
   char instancename[_MAXNAMELENGTH];           /* Unique name of each new instance */

   _OSBASE_TRACE(1,("EnumInstances() called"));

   /* Get the list of instance names stored at _LOCATION */
   instances = Linux_SysfsDeviceUtil_beginEnumeration(_LOCATION);
   if (instances == NULL) {
      _OSBASE_TRACE(1,("EnumInstances() : Failed to get list of instances"));
      CMReturn(CMPI_RC_ERR_FAILED);
      CMSetStatusWithChars( _broker, &status, CMPI_RC_ERR_FAILED, "failed to get list of instances" );
      return status;
   }

   /* Enumerate all the instances and return a new CIM instance for each */
   while (Linux_SysfsDeviceUtil_nextEnumeration(instances, instancename)) {
       instance = Linux_SysfsDeviceUtil_makeInstance(instancename, _broker, CMGetCharPtr(CMGetNameSpace(reference,&status)), _CLASSNAME);
       if (instance != NULL) {
          _OSBASE_TRACE(1,("EnumInstances() : Adding instance for %s",instancename));
          CMReturnInstance(results, instance);
       }
   }
   Linux_SysfsDeviceUtil_endEnumeration(instances);

   /* Finished */
   CMReturnDone(results);
   CMReturn(CMPI_RC_OK);
   _OSBASE_TRACE(1,("EnumInstances() finished"));
   return status;
}

/*
 * GetInstance
 */
CMPIStatus Linux_SysfsTTYDeviceGetInstance(
		CMPIInstanceMI * mi, 
		const CMPIContext * context, 
		const CMPIResult * results, 
		const CMPIObjectPath * reference, 
		const char ** properties) 
{
   CMPIStatus status = {CMPI_RC_OK, NULL};      /* Return status of CIM operations */
   CMPIInstance * instance;                     /* CIM instance to store the desired instance */
   CMPIData data;                               /* CIM data structure to store desired instance name */
   char * instancename;                         /* Name of the desired instance */

   _OSBASE_TRACE(1,("GetInstance() called"));

   /* Determine the instance name */
   /*** CHANGE THIS TO GENERATE THE UNIQUE INSTANCE NAME FROM THE KEY ATTRIBUTES ***/
   data = CMGetKey(reference, "Name", &status);
   instancename = CMGetCharPtr(data.value.string);

   _OSBASE_TRACE(1,("GetInstance() : Getting instance data for %s",instancename));

   /* Return a new CIM instance for the desired instance */
   instance = Linux_SysfsDeviceUtil_makeInstance(instancename, _broker, CMGetCharPtr(CMGetNameSpace(reference,&status)), _CLASSNAME);
   if (instance == NULL) {
      _OSBASE_TRACE(1,("GetInstance() : Failed to get instance %s",instancename));
      CMReturn(CMPI_RC_ERR_FAILED);
      CMSetStatusWithChars( _broker, &status, CMPI_RC_ERR_FAILED, "failed to get instance" );
      return status;
   }
   CMReturnInstance(results, instance);

   /* Finished */
   CMReturnDone(results);
   CMReturn(CMPI_RC_OK);
   _OSBASE_TRACE(1,("GetInstance() finished"));
   return status;
}

/*
 * SetInstance
 */
CMPIStatus Linux_SysfsTTYDeviceSetInstance(
		CMPIInstanceMI * mi, 
		const CMPIContext * context, 
		const CMPIResult * results, 
		const CMPIObjectPath * reference,
		const CMPIInstance * instance, 
		const char **properties) 
{
   /* Cannot change instances */
   CMPIStatus status = {CMPI_RC_ERR_NOT_SUPPORTED, NULL};
   CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
   return status;
}

/*
 * CreateInstance
 */
CMPIStatus Linux_SysfsTTYDeviceCreateInstance(
                CMPIInstanceMI * mi,
                const CMPIContext * context,
                const CMPIResult * results,
                const CMPIObjectPath * reference,
                const CMPIInstance * instance)
{
   /* Cannot create new instances */
   CMPIStatus status = {CMPI_RC_ERR_NOT_SUPPORTED, NULL};
   CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
   return status;
}

/*
 * DeleteInstance
 */
CMPIStatus Linux_SysfsTTYDeviceDeleteInstance(
		CMPIInstanceMI * mi, 
		const CMPIContext * context, 
		const CMPIResult * results, 
		const CMPIObjectPath * reference) 
{
   /* Cannot delete instances */
   CMPIStatus status = {CMPI_RC_ERR_NOT_SUPPORTED, NULL};
   CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
   return status;
}

/*
 * ExecQuery
 */
CMPIStatus Linux_SysfsTTYDeviceExecQuery(
		CMPIInstanceMI * mi, 
		const CMPIContext * context, 
		const CMPIResult * results, 
		const CMPIObjectPath * reference, 
		const char * language, 
		const char * query) 
{
   /* Cannot query instances */
   CMPIStatus status = {CMPI_RC_ERR_NOT_SUPPORTED, NULL};
   CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
   return status;
}

/*
 * Cleanup
 */
CMPIStatus Linux_SysfsTTYDeviceCleanup(
                CMPIInstanceMI * mi,
                const CMPIContext * context,
                CMPIBoolean terminate)
{
   /* Nothing needs to be done for cleanup */
   CMPIStatus status = {CMPI_RC_OK, NULL};
   CMReturn(CMPI_RC_OK);
   return status;
}

/*
 * Factory methods
 */
CMInstanceMIStub( Linux_SysfsTTYDevice,
		  Linux_SysfsTTYDevice,
		  _broker,
		  CMNoHook);

