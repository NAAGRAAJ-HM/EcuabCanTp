/******************************************************************************/
/* File   : CanTp.cpp                                                         */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "CanTp.hpp"
#include "infCanTp_Imp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define CANTP_AR_RELEASE_VERSION_MAJOR                                         4
#define CANTP_AR_RELEASE_VERSION_MINOR                                         3

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if(CANTP_AR_RELEASE_VERSION_MAJOR != STD_AR_RELEASE_VERSION_MAJOR)
   #error "Incompatible CANTP_AR_RELEASE_VERSION_MAJOR!"
#endif

#if(CANTP_AR_RELEASE_VERSION_MINOR != STD_AR_RELEASE_VERSION_MINOR)
   #error "Incompatible CANTP_AR_RELEASE_VERSION_MINOR!"
#endif

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_CanTp, CANTP_VAR) CanTp;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, CANTP_CODE) module_CanTp::InitFunction(
      CONSTP2CONST(ConstModule_TypeAbstract, CANTP_CONST,       CANTP_APPL_CONST) lptrConstModule
   ,  CONSTP2CONST(CfgModule_TypeAbstract,   CANTP_CONFIG_DATA, CANTP_APPL_CONST) lptrCfgModule
){
#if(STD_ON == CanTp_InitCheck)
   if(
         E_OK
      != IsInitDone
   ){
#endif
      if(
            (NULL_PTR != lptrConstModule)
         && (NULL_PTR != lptrCfgModule)
      ){
         lptrConst = (const ConstCanTp_Type*)lptrConstModule;
         lptrCfg   = lptrCfgModule;
      }
      else{
#if(STD_ON == CanTp_DevErrorDetect)
         Det_ReportError(
               0 //TBD: IdModule
            ,  0 //TBD: IdInstance
            ,  0 //TBD: IdApi
            ,  0 //TBD: IdError
         );
#endif
      }
#if(STD_ON == CanTp_InitCheck)
      IsInitDone = E_OK;
   }
   else{
#if(STD_ON == CanTp_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  CANTP_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, CANTP_CODE) module_CanTp::DeInitFunction(
   void
){
#if(STD_ON == CanTp_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == CanTp_InitCheck)
      IsInitDone = E_NOT_OK;
   }
   else{
#if(STD_ON == CanTp_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  CANTP_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, CANTP_CODE) module_CanTp::MainFunction(
   void
){
#if(STD_ON == CanTp_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == CanTp_InitCheck)
   }
   else{
#if(STD_ON == CanTp_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  CANTP_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, CANTP_CODE) module_CanTp::dummy(
   void
){
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

