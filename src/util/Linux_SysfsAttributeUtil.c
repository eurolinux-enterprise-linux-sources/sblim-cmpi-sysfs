/* ---------------------------------------------------------------------------
 * Linux_SysfsAttributeUtil.c
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
 * Description:	Utility functions for Linux_SysfsAttribute providers
 * --------------------------------------------------------------------------- */

#include "cmpidt.h"
#include "cmpift.h"
#include "cmpimacs.h"
#include "OSBase_Common.h"
#include "cmpiOSBase_Common.h"

#include "Linux_SysfsAttributeUtil.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


/* ---------------------------------------------------------------------------
 * MISC UTILITY FUNCTIONS
 * --------------------------------------------------------------------------- */

/* Compare two strings containing multiple whitespace separated values, token by token */
static int _valuecmp( char * value1, char * value2 )
{
   char * token1;
   char * token2;
   char * charptr1 = NULL;
   char * charptr2 = NULL;

   /* Get the first pair of tokens */
   token1 = strtok_r(value1, " \t\n", &charptr1);
   token2 = strtok_r(value2, " \t\n", &charptr2);
   do {
      if (strcmp(token1,token2) != 0) return 0;

      /* Get the next pair of tokens */
      token1 = strtok_r(NULL, " \t\n", &charptr1);
      token2 = strtok_r(NULL, " \t\n", &charptr2);
   } while (token1 != NULL && token2 != NULL);

   /* Check that both values had exactly the same number of tokens */
   if (token1 != NULL || token2 != NULL) return 0;

   return 1;
}


/* ---------------------------------------------------------------------------
 * UTILITY FUNCTIONS TO READ/WRITE INSTANCES
 * --------------------------------------------------------------------------- */

/* Read instance data into a CIM object path (i.e. set key attributes only) */
CMPIObjectPath *  Linux_SysfsAttributeUtil_makeObjectPath( char * instancename, const CMPIBroker * broker, char * namespace, const char * classname )
{
   CMPIObjectPath * objectpath;
   CMPIStatus status = {CMPI_RC_OK, NULL};
  
   /* Create a new CIM object path for this instance */
   objectpath = CMNewObjectPath(broker, namespace, classname, &status);
   if (CMIsNullObject(objectpath)) {
      _OSBASE_TRACE(1,("_makeObjectPath() : Failed to create new object path - %s",CMGetCharPtr(status.msg)));
      return NULL;
   }

   /* Store this instance's key attributes in the new CIM object path */
   CMAddKey(objectpath, "SystemCreationClassName", CSCreationClassName, CMPI_chars);
   CMAddKey(objectpath, "SystemName", get_system_name(), CMPI_chars);
   CMAddKey(objectpath, "CreationClassName", classname, CMPI_chars);
   CMAddKey(objectpath, "SettingID", instancename, CMPI_chars);

   return objectpath;
}


/* Read instance data into a CIM instance (i.e. set all attributes) */
CMPIInstance *  Linux_SysfsAttributeUtil_makeInstance( char * instancename, const CMPIBroker * broker, char * namespace, const char * classname )
{
   CMPIInstance * instance;
   CMPIStatus status = {CMPI_RC_OK, NULL};

   struct stat fileinfo;
   CMPIValue value;
   FILE * instancefile;
   char buffer[getpagesize()+2];
   char val[getpagesize()];
   int  i, hasbadchar;
   
   /* Create a new CIM instance for this instance */
   instance = CMNewInstance(broker,  Linux_SysfsAttributeUtil_makeObjectPath(instancename,broker,namespace,classname), &status);
   if (CMIsNullObject(instance)) {
      _OSBASE_TRACE(1,("_makeInstance() : Failed to create new instance - %s",CMGetCharPtr(status.msg)));
      return NULL;
   }

   /* Store this instance's attributes in the new CIM instance */
   CMSetProperty(instance, "SystemCreationClassName", CSCreationClassName, CMPI_chars);
   CMSetProperty(instance, "SystemName", get_system_name(), CMPI_chars);
   CMSetProperty(instance, "CreationClassName", classname, CMPI_chars);
   CMSetProperty(instance, "SettingID", instancename, CMPI_chars);

   /* Determine if the instance file is writeable */
   if (stat(instancename, &fileinfo) == 0) {
      value.boolean = fileinfo.st_mode & S_IWUSR;
      CMSetProperty(instance, "Writeable", &value, CMPI_boolean);
   } else {
      _OSBASE_TRACE(1,("_makeInstance() : Cannot stat instance file %s",instancename));
   }

   /* Read the instance value from the instance file */
   if ( (fileinfo.st_mode & S_IRUSR) && (instancefile = fopen(instancename,"r")) != NULL) {
      /* Read in each of the whitespace separated values from the file */
      fscanf(instancefile, " %s", buffer);
      while (fscanf(instancefile, " %s", val) != EOF) {
	 strcat(strcat(buffer," "),val);
      }
      fclose(instancefile);
      
      if (buffer[strlen(buffer)-1] == ' ') buffer[strlen(buffer)-1] = '\0'; /* Remove trailing blank */


      /* Make sure the characters that were read are printable */
      hasbadchar = 0; 
      for(i=0;i<strlen(buffer);i++){
         if (!isprint(buffer[i])) {
         hasbadchar = 1;
         _OSBASE_TRACE(1,("_makeInstance() : Unprintable char in value for %s",instancename));
         break;
         }
      }

      if (hasbadchar) {
         CMSetProperty(instance, "Value", "NULL", CMPI_chars);
      } else {
         CMSetProperty(instance, "Value", buffer, CMPI_chars);
      }

   } else {
      _OSBASE_TRACE(1,("_makeInstance() : Cannot read value from instance file %s",instancename));
      CMSetProperty(instance, "Value", "NULL", CMPI_chars);
   }

   return instance;
}


/* Write CIM instance data back to system */
int  Linux_SysfsAttributeUtil_writeInstance( const CMPIInstance * instance )
{
   CMPIStatus status = {CMPI_RC_OK, NULL};
   CMPIData data;
   char * instancename;
   char * value;
   FILE * instancefile;
   char buffer[getpagesize()+1];

   /* Determine the instance name */
   data = CMGetProperty(instance, "SettingID", &status);
   instancename = CMGetCharPtr(data.value.string);

   /* Check if the instance is writeable */
   data = CMGetProperty(instance, "Writeable", &status);
   if (! data.value.boolean) {
      _OSBASE_TRACE(1,("_writeInstance() : Instance %s is not writeable",instancename));
      return 0;
   }

   /* Determine the instance value */
   data = CMGetProperty(instance, "Value", &status);
   value = CMGetCharPtr(data.value.string);

   /* Write the instance value to the instance file */
   if ( (instancefile = fopen(instancename,"w")) == NULL) {
      _OSBASE_TRACE(1,("_writeInstance() : Cannot write to instance file %s",instancename));
      return 0;
   }
   fprintf(instancefile, "%s\n", value);
   fclose(instancefile);

   /* Re-read the instance value from the instance file to confirm the changes */
   if ( (instancefile = fopen(instancename,"r")) == NULL) {
      _OSBASE_TRACE(1,("_writeInstance() : Cannot re-read value from instance file %s",instancename));
      return 0;
   }
   fgets(buffer,getpagesize(),instancefile);
   fclose(instancefile);

   /* Compare the desired value to the new value that was stored in the instance file */
   if (! _valuecmp(value,buffer)) {
      _OSBASE_TRACE(1,("_writeInstance() : New instance value '%s' does not match intended value '%s'",buffer,value));
      return 0;
   }

   return 1;
}


/* ---------------------------------------------------------------------------
 * UTILITY FUNCTIONS TO ENUMERATE INSTANCES
 * --------------------------------------------------------------------------- */

/* Return a handle to the list of instances */
void *  Linux_SysfsAttributeUtil_beginEnumeration( void * location )
{
   FILE * handle;
   char * findcommand = malloc(strlen((char *)location)+22); 
   
   /* Find all the instance names in the target location */
   sprintf(findcommand, "find %s -noleaf -type f", (char *)location);
   handle = popen(findcommand,"r");
   free(findcommand); 
   return handle; 
}


/* Get the next instance name on the list */
int  Linux_SysfsAttributeUtil_nextEnumeration( void * handle, char * name )
{
   if ( handle != NULL ) {
      /* Read the next instance name from the instance name file */
      if ( fscanf((FILE *)handle, "%[^\n]\n", name) != EOF ) return 1;
   }
   return 0;
}


/* Close and cleanup the list of instances */
void  Linux_SysfsAttributeUtil_endEnumeration( void * handle )
{
   if ( handle != NULL ) {
      pclose((FILE *)handle);
   }
}

