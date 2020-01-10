/* ---------------------------------------------------------------------------
 * Linux_SysfsTTYDeviceHasAttribute.c
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
 * Description: Association provider for Linux_SysfsTTYDevice class.
 * 		Associates a Linux_SysfsTTYDevice instance with its respective
 * 		Linux_SysfsAttribute instances.
 * Interface:   Common Manageability Programming Interface (CMPI)
 * ---------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "cmpidt.h"
#include "cmpift.h"
#include "cmpimacs.h"
#include "OSBase_Common.h"
#include "cmpiOSBase_Common.h"

#include "../util/Linux_SysfsAttributeUtil.h"

static const CMPIBroker * _broker;
static const char * _CLASSNAME = "Linux_SysfsTTYDeviceHasAttribute";
static char * _SOURCECLASSNAME = "Linux_SysfsTTYDevice";
static const char * _TARGETCLASSNAME = "Linux_SysfsAttribute";
#define _MAXNAMELENGTH 1024


/* ---------------------------------------------------------------------------
 * ASSOCIATION PROVIDER METHODS
 * --------------------------------------------------------------------------- */

/*
 * AssociatorNames
 */
CMPIStatus Linux_SysfsTTYDeviceHasAttributeAssociatorNames(
		CMPIAssociationMI * mi,
		const CMPIContext * context,
		const CMPIResult * results,
		const CMPIObjectPath * reference,
		const char * assocClass,
		const char * resultClass,
		const char * role,
		const char * resultRole )
{
   CMPIStatus status = {CMPI_RC_OK, NULL};      /* Return status of CIM operations */
   CMPIObjectPath * objectpath;                 /* CIM object path to store each new instance */
   CMPIData data;                               /* CIM data structure to store reference object name */
   char * classname;                            /* Class of the reference object */
   char * location;		                /* Location of the associated instances */
   void * instances;                            /* Handle to the list of instance names */
   char instancename[_MAXNAMELENGTH];           /* Unique name of each new instance */

   _OSBASE_TRACE(1,("AssociatorNames() called"));

   /* Check if the reference object is a sysfs attribute file */
   /* NOTE: Attribute-to-Device associations are NOT yet supported! */
   classname = CMGetCharPtr(CMGetClassName(reference, &status));
   if (strcmp(classname, _TARGETCLASSNAME) == 0) {
      _OSBASE_TRACE(1,("AssociatorNames() :  Unsupported reference class %s",classname));
      CMReturnDone(results);
      CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
      return status;
   }

   /* Check that the reference object is of Linux_SysfsTTYDevice */
   if (strcmp(classname, _SOURCECLASSNAME) != 0) {
      _OSBASE_TRACE(1,("AssociatorNames() : Unrecognized reference class %s",classname));
      CMReturnDone(results);
      CMReturn(CMPI_RC_OK);
      return status;
   }

   /* Determine the location of the associated instances */
   /*** CHANGE THIS TO DETERMINE THE TARGET LOCATION FROM THE REFERENCE NAME ***/
   data = CMGetKey(reference, "Name", &status);
   location = CMGetCharPtr(data.value.string);

   _OSBASE_TRACE(1,("AssociatorNames() : Getting associated instances in %s",location));
   /*** NOTE - EVERYTHING BELOW IS THE SAME AS TARGET CLASS'S ENUMINSTANCENAMES() ***/

   /* Get the list of instance names stored at the location */
   instances = Linux_SysfsAttributeUtil_beginEnumeration(location);
   if (instances == NULL) {
      _OSBASE_TRACE(1,("AssociatorNames() : Failed to get list of instances"));
      CMReturn(CMPI_RC_ERR_FAILED);
      CMSetStatusWithChars( _broker, &status, CMPI_RC_ERR_FAILED, "failed to get list of instances" );
      return status;
   }

   /* Enumerate all the instances and return a new CIM object path for each */
   while (Linux_SysfsAttributeUtil_nextEnumeration(instances, instancename)) {
      objectpath = Linux_SysfsAttributeUtil_makeObjectPath(instancename, _broker, CMGetCharPtr(CMGetNameSpace(reference,&status)), _TARGETCLASSNAME);
      if (objectpath != NULL) {
         _OSBASE_TRACE(1,("AssociatorNames() : Adding object path for %s",instancename));
         CMReturnObjectPath(results, objectpath);
      }
   }
   Linux_SysfsAttributeUtil_endEnumeration(instances);

   /* Finished */
   CMReturnDone(results);
   CMReturn(CMPI_RC_OK);
   _OSBASE_TRACE(1,("AssociatorNames() finished"));
   return status;
}

/*
 * Associators
 */
CMPIStatus Linux_SysfsTTYDeviceHasAttributeAssociators(
		CMPIAssociationMI * mi,
		const CMPIContext * context, 
		const CMPIResult * results,
		const CMPIObjectPath * reference,
		const char * assocClass,
		const char * resultClass,
		const char * role,
		const char * resultRole,
		const char ** propertyList )
{
   CMPIStatus status = {CMPI_RC_OK, NULL};      /* Return status of CIM operations */
   CMPIInstance * instance;                     /* CIM instance to store each new instance */
   CMPIData data;                               /* CIM data structure to store reference object name */
   char * classname;				/* Class of the reference object */
   char * location;				/* Location of the associated instances */
   void * instances;                            /* Handle to the list of instance names */
   char instancename[_MAXNAMELENGTH];           /* Unique name of each new instance */

   _OSBASE_TRACE(1,("Associators() called"));

   /* Check if the reference object is a sysfs attribute file */
   /* NOTE: Attribute-to-Device associations are NOT yet supported! */
   classname = CMGetCharPtr(CMGetClassName(reference, &status));
   if (strcmp(classname, _TARGETCLASSNAME) == 0) {
      _OSBASE_TRACE(1,("Associators() :  Unsupported reference class %s",classname));
      CMReturnDone(results);
      CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
      return status;
   }

   /* Check that the reference object is of Linux_SysfsTTYDevice */
   if (strcmp(classname, _SOURCECLASSNAME) != 0) {
      _OSBASE_TRACE(1,("Associators() : Unrecognized reference class %s",classname));
      CMReturnDone(results);
      CMReturn(CMPI_RC_OK);
      return status;
   }

   /* Determine the location of the associated instances */
   /*** CHANGE THIS TO DETERMINE THE TARGET LOCATION FROM THE REFERENCE NAME ***/
   data = CMGetKey(reference, "Name", &status);
   location = CMGetCharPtr(data.value.string);

   _OSBASE_TRACE(1,("Associators() : Getting associated instances in %s",location));
   /*** NOTE - EVERYTHING BELOW IS THE SAME AS TARGET CLASS'S ENUMINSTANCES() ***/

   /* Get the list of instance names stored at the location */
   instances = Linux_SysfsAttributeUtil_beginEnumeration(location);
   if (instances == NULL) {
      _OSBASE_TRACE(1,("Associators() : Failed to get list of instances"));
      CMReturn(CMPI_RC_ERR_FAILED);
      CMSetStatusWithChars( _broker, &status, CMPI_RC_ERR_FAILED, "failed to get list of instances" );
      return status;
   }

   /* Enumerate all the instances and return a new CIM instance for each */
   while (Linux_SysfsAttributeUtil_nextEnumeration(instances, instancename)) {
      instance = Linux_SysfsAttributeUtil_makeInstance(instancename, _broker, CMGetCharPtr(CMGetNameSpace(reference,&status)), _TARGETCLASSNAME);
      if (instance != NULL) {
         _OSBASE_TRACE(1,("Associators() : Adding instance for %s",instancename));
         CMReturnInstance(results, instance);
      }
   }
   Linux_SysfsAttributeUtil_endEnumeration(instances);

   /* Finished */
   CMReturnDone(results);
   CMReturn(CMPI_RC_OK);
   _OSBASE_TRACE(1,("Associators() finished"));
   return status;
}

/*
 * ReferenceNames
 */
CMPIStatus Linux_SysfsTTYDeviceHasAttributeReferenceNames(
		CMPIAssociationMI * mi,
                const CMPIContext * context,
                const CMPIResult * results,
                const CMPIObjectPath * reference,
                const char * assocClass,
                const char * role)
{
   CMPIStatus status = {CMPI_RC_OK, NULL};      /* Return status of CIM operations */
   CMPIObjectPath * objectpath;                 /* CIM object path to store each new instance */
   CMPIObjectPath * refobjectpath;              /* CIM object path to store each new reference */
   CMPIData data;                               /* CIM data structure to store desired instance name */
   char * classname;                            /* Class of the reference object */
   char * location;		                /* Location of the associated instances */
   void * instances;                            /* Handle to the list of instance names */
   char instancename[_MAXNAMELENGTH];           /* Unique name of each new instance */

   _OSBASE_TRACE(1,("ReferenceNames() called"));

   /* Check if the reference object is a sysfs attribute file */
   /* NOTE: Attribute-to-Device associations are NOT yet supported! */
   classname = CMGetCharPtr(CMGetClassName(reference, &status));
   if (strcmp(classname, _TARGETCLASSNAME) == 0) {
      _OSBASE_TRACE(1,("ReferenceNames() :  Unsupported reference class %s",classname));
      CMReturnDone(results);
      CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
      return status;
   }

   /* Check that the reference object is of Linux_SysfsTTYDevice */
   if (strcmp(classname, _SOURCECLASSNAME) != 0) {
      _OSBASE_TRACE(1,("ReferenceNames() : Unrecognized reference class %s",classname));
      CMReturnDone(results);
      CMReturn(CMPI_RC_OK);
      return status;
   }

   /* Determine the location of the associated instances */
   /*** CHANGE THIS TO DETERMINE THE TARGET LOCATION FROM THE REFERENCE NAME ***/
   data = CMGetKey(reference, "Name", &status);
   location = CMGetCharPtr(data.value.string);

   _OSBASE_TRACE(1,("ReferenceNames() : Getting associated instances in %s",location));

   /* Get the list of instance names stored at the location */
   instances = Linux_SysfsAttributeUtil_beginEnumeration(location);
   if (instances == NULL) {
      _OSBASE_TRACE(1,("ReferenceNames() : Failed to get list of instances"));
      CMReturn(CMPI_RC_ERR_FAILED);
      CMSetStatusWithChars( _broker, &status, CMPI_RC_ERR_FAILED, "failed to get list of instances" );
      return status;
   }

   /* Enumerate all the instances and return a new CIM reference instance for each */
   while (Linux_SysfsAttributeUtil_nextEnumeration(instances, instancename)) {
      objectpath = Linux_SysfsAttributeUtil_makeObjectPath(instancename, _broker, CMGetCharPtr(CMGetNameSpace(reference,&status)), _TARGETCLASSNAME);
      if (objectpath != NULL) {
         /* Create a new reference object path for this association */
         refobjectpath = CMNewObjectPath(_broker,CMGetCharPtr(CMGetNameSpace(reference,&status)),_CLASSNAME,&status);
         if (CMIsNullObject(refobjectpath)) {
            _OSBASE_TRACE(1,("ReferenceNames() : Failed to create new reference object path - %s",CMGetCharPtr(status.msg)));
            CMSetStatusWithChars( _broker, &status, CMPI_RC_ERR_FAILED, "failed to create new reference object path" );
            CMReturn(CMPI_RC_ERR_FAILED);
         }
         _OSBASE_TRACE(1,("ReferenceNames() : Adding reference object path for %s",instancename));

         /* Store the reference key attributes in the newly created object path */
         CMAddKey(refobjectpath, "Context", &reference, CMPI_ref);
         CMAddKey(refobjectpath, "Setting", &objectpath, CMPI_ref);
         CMReturnObjectPath(results, refobjectpath);
      }
   }
   Linux_SysfsAttributeUtil_endEnumeration(instances);

    /* Finished */
   CMReturnDone(results);
   CMReturn(CMPI_RC_OK);
   _OSBASE_TRACE(1,("ReferenceNames() finished"));
   return status;
}

/*
 * References
 */
CMPIStatus Linux_SysfsTTYDeviceHasAttributeReferences(
		CMPIAssociationMI * mi,
		const CMPIContext * context,
		const CMPIResult * results,
		const CMPIObjectPath * reference,
		const char * assocClass,
		const char * role,
		const char ** propertyList )
{
   CMPIStatus status = {CMPI_RC_OK, NULL};      /* Return status of CIM operations */
   CMPIObjectPath * objectpath;                 /* CIM object path to store each new instance */
   CMPIInstance * refinstance;                  /* CIM instance to store each new reference */
   CMPIData data;                               /* CIM data structure to store desired instance name */
   char * classname;                            /* Class of the reference object */
   char * location;		                /* Location of the associated instances */
   void * instances;                            /* Handle to the list of instance names */
   char instancename[_MAXNAMELENGTH];           /* Unique name of each new instance */

   _OSBASE_TRACE(1,("References() called"));

   /* Check if the reference object is a sysfs attribute file */
   /* NOTE: Attribute-to-Device associations are NOT yet supported! */
   classname = CMGetCharPtr(CMGetClassName(reference, &status));
   if (strcmp(classname, _TARGETCLASSNAME) == 0) {
      _OSBASE_TRACE(1,("References() :  Unsupported reference class %s",classname));
      CMReturnDone(results);
      CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
      return status;
   }

   /* Check that the reference object is of Linux_SysfsTTYDevice */
   if (strcmp(classname, _SOURCECLASSNAME) != 0) {
      _OSBASE_TRACE(1,("References() : Unrecognized reference class %s",classname));
      CMReturnDone(results);
      CMReturn(CMPI_RC_OK);
      return status;
   }

   /* Determine the location of the associated instances */
   /*** CHANGE THIS TO DETERMINE THE TARGET LOCATION FROM THE REFERENCE NAME ***/
   data = CMGetKey(reference, "Name", &status);
   location = CMGetCharPtr(data.value.string);

   _OSBASE_TRACE(1,("References() : Getting associated instances in %s",location));

   /* Get the list of instance names stored at the location */
   instances = Linux_SysfsAttributeUtil_beginEnumeration(location);
   if (instances == NULL) {
      _OSBASE_TRACE(1,("References() : Failed to get list of instances"));
      CMReturn(CMPI_RC_ERR_FAILED);
      CMSetStatusWithChars( _broker, &status, CMPI_RC_ERR_FAILED, "failed to get list of instances" );
      return status;
   }

   /* Enumerate all the instances and return a new CIM reference instance for each */
   while (Linux_SysfsAttributeUtil_nextEnumeration(instances, instancename)) {
      objectpath = Linux_SysfsAttributeUtil_makeObjectPath(instancename, _broker, CMGetCharPtr(CMGetNameSpace(reference,&status)), _TARGETCLASSNAME);

      if (objectpath != NULL) {
	 refinstance = CMNewInstance(_broker, CMNewObjectPath(_broker,CMGetCharPtr(CMGetNameSpace(reference,&status)),_CLASSNAME,&status), &status);
         if (refinstance == NULL || CMIsNullObject(refinstance)) {
            _OSBASE_TRACE(1,("References() : Failed to create new reference instance - %s",CMGetCharPtr(status.msg)));
            CMSetStatusWithChars( _broker, &status, CMPI_RC_ERR_FAILED, "failed to create new reference instance" );
            CMReturn(CMPI_RC_ERR_FAILED);
         }
         _OSBASE_TRACE(1,("References() : Adding reference instance for %s",instancename));

         /* Store the reference attributes in the newly created instance */
	 CMSetProperty(refinstance, "Context", &reference, CMPI_ref);
	 CMSetProperty(refinstance, "Setting", &objectpath, CMPI_ref);
	 CMReturnInstance(results, refinstance);
      }
   }
   Linux_SysfsAttributeUtil_endEnumeration(instances);

   /* Finished */
   CMReturnDone(results);
   CMReturn(CMPI_RC_OK);
   _OSBASE_TRACE(1,("References() finished"));
   return status;
}

/*
 * Cleanup
 */
CMPIStatus Linux_SysfsTTYDeviceHasAttributeAssociationCleanup(
		CMPIAssociationMI * mi,
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
CMAssociationMIStub( Linux_SysfsTTYDeviceHasAttribute,
      	     Linux_SysfsTTYDeviceHasAttribute,
	     _broker,
	     CMNoHook);

