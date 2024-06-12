/******************************************************************************/
/* File   : EcuabCanTp.cpp                                                    */
/* Author : Nagaraja HULIYAPURADA-MATA                                        */
/* Date   : 01.02.1982                                                        */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "EcuabCanTp.hpp"
#include "infEcuabCanTp_Imp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

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
VAR(module_EcuabCanTp, ECUABCANTP_VAR) EcuabCanTp;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, ECUABCANTP_CODE) module_EcuabCanTp::InitFunction(
      CONSTP2CONST(ConstModule_TypeAbstract, ECUABCANTP_CONST,       ECUABCANTP_APPL_CONST) lptrNvMBlocksRomModule
   ,  CONSTP2CONST(CfgModule_TypeAbstract,   ECUABCANTP_CONFIG_DATA, ECUABCANTP_APPL_CONST) lptrCfgModule
){
#if(STD_ON == EcuabCanTp_InitCheck)
   if(
         E_OK
      != IsInitDone
   ){
#endif
      if(
            (NULL_PTR != lptrNvMBlocksRomModule)
         && (NULL_PTR != lptrCfgModule)
      ){
         lptrNvMBlocksRom = lptrNvMBlocksRomModule;
         lptrCfg   = lptrCfgModule;
      }
      else{
#if(STD_ON == EcuabCanTp_DevErrorDetect)
         ServiceDet_ReportError(
               0 //TBD: IdModule
            ,  0 //TBD: IdInstance
            ,  0 //TBD: IdApi
            ,  0 //TBD: IdError
         );
#endif
      }
#if(STD_ON == EcuabCanTp_InitCheck)
      IsInitDone = E_OK;
   }
   else{
#if(STD_ON == EcuabCanTp_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  ECUABCANTP_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, ECUABCANTP_CODE) module_EcuabCanTp::DeInitFunction(
   void
){
#if(STD_ON == EcuabCanTp_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == EcuabCanTp_InitCheck)
      IsInitDone = E_NOT_OK;
   }
   else{
#if(STD_ON == EcuabCanTp_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  ECUABCANTP_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, ECUABCANTP_CODE) module_EcuabCanTp::MainFunction(
   void
){
#if(STD_ON == EcuabCanTp_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == EcuabCanTp_InitCheck)
   }
   else{
#if(STD_ON == EcuabCanTp_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  ECUABCANTP_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, ECUABCANTP_CODE) module_EcuabCanTp::dummy(
   void
){
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

