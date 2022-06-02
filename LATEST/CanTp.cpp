/******************************************************************************/
/* File   : CanTp.cpp                                                         */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "CfgCanTp.hpp"
#include "CanTp_core.hpp"
#include "infCanTp_Exp.hpp"

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
class module_CanTp:
      INTERFACES_EXPORTED_CANTP
      public abstract_module
   ,  public class_CanTp_Functionality
{
   private:
/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
            Std_TypeReturn          IsInitDone{E_NOT_OK};
      const CfgModule_TypeAbstract* lptrCfg{(CfgModule_TypeAbstract*)NULL_PTR};

   public:
      module_CanTp(Std_TypeVersionInfo lVersionInfo) : abstract_module(lVersionInfo){
      }
      FUNC(void, CANTP_CODE) InitFunction(
         CONSTP2CONST(CfgModule_TypeAbstract, CANTP_CONFIG_DATA, CANTP_APPL_CONST) lptrCfgModule
      );
      FUNC(void, CANTP_CODE) DeInitFunction (void);
      FUNC(void, CANTP_CODE) MainFunction   (void);
      CANTP_CORE_FUNCTIONALITIES
};

extern VAR(module_CanTp, CANTP_VAR) CanTp;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
CONSTP2VAR(infEcuMClient, CANTP_VAR, CANTP_CONST) gptrinfEcuMClient_CanTp = &CanTp;
CONSTP2VAR(infDcmClient,  CANTP_VAR, CANTP_CONST) gptrinfDcmClient_CanTp  = &CanTp;
CONSTP2VAR(infSchMClient, CANTP_VAR, CANTP_CONST) gptrinfSchMClient_CanTp = &CanTp;

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_CanTp, CANTP_VAR) CanTp(
   {
#if(STD_ON == _ReSIM)
// char strModuleName[6];
#else
#endif
         CANTP_AR_RELEASE_VERSION_MAJOR
      ,  CANTP_AR_RELEASE_VERSION_MINOR
      ,  0x00
      ,  0xFF
      ,  0x01
      ,  '0'
      ,  '1'
      ,  '0'
   }
);

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, CANTP_CODE) module_CanTp::InitFunction(
   CONSTP2CONST(CfgModule_TypeAbstract, CANTP_CONFIG_DATA, CANTP_APPL_CONST) lptrCfgModule
){
#if(STD_ON == CanTp_InitCheck)
   if(
         E_OK
      != IsInitDone
   ){
#endif
      if(NULL_PTR != lptrCfgModule){
         if(STD_HIGH){
            lptrCfg = lptrCfgModule;
         }
         else{
            lptrCfg = &PBcfgCanTp;
         }
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

FUNC(void, CANTP_CODE) module_CanTp::DeInitFunction(void){
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

FUNC(void, CANTP_CODE) module_CanTp::MainFunction(void){
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

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

