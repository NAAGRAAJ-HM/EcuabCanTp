#pragma once
/******************************************************************************/
/* File   : EcuabCanTp_Version.hpp                                            */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define ECUABCANTP_AR_RELEASE_VERSION_MAJOR                                    4
#define ECUABCANTP_AR_RELEASE_VERSION_MINOR                                    3

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if(ECUABCANTP_AR_RELEASE_VERSION_MAJOR != STD_AR_RELEASE_VERSION_MAJOR)
   #error "Incompatible ECUABCANTP_AR_RELEASE_VERSION_MAJOR!"
#endif

#if(ECUABCANTP_AR_RELEASE_VERSION_MINOR != STD_AR_RELEASE_VERSION_MINOR)
   #error "Incompatible ECUABCANTP_AR_RELEASE_VERSION_MINOR!"
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

