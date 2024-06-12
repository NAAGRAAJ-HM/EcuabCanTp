#pragma once
/******************************************************************************/
/* File   : EcuabCanTp.hpp                                                    */
/* Author : Nagaraja HULIYAPURADA-MATA                                        */
/* Date   : 01.02.1982                                                        */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "infEcuabCanTp_ServiceNvM_Types.hpp"
#include "CfgEcuabCanTp.hpp"
#include "EcuabCanTp_core.hpp"
#include "infEcuabCanTp_Exp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class module_EcuabCanTp:
      INTERFACES_EXPORTED_ECUABCANTP
      public abstract_module
   ,  public class_EcuabCanTp_Functionality
{
   private:
/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
      const ConstModule_TypeAbstract* lptrNvMBlocksRom = (ConstModule_TypeAbstract*)NULL_PTR;
      infServicePduRClient_Lo infServicePduRClient_EcuabCanTp;

   public:
/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
      FUNC(void, ECUABCANTP_CODE) InitFunction(
            CONSTP2CONST(ConstModule_TypeAbstract, ECUABCANTP_CONST,       ECUABCANTP_APPL_CONST) lptrNvMBlocksRomModule
         ,  CONSTP2CONST(CfgModule_TypeAbstract,   ECUABCANTP_CONFIG_DATA, ECUABCANTP_APPL_CONST) lptrCfgModule
      );
      FUNC(void, ECUABCANTP_CODE) DeInitFunction (void);
      FUNC(void, ECUABCANTP_CODE) MainFunction   (void);
      ECUABCANTP_CORE_FUNCTIONALITIES
};

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
extern VAR(module_EcuabCanTp, ECUABCANTP_VAR) EcuabCanTp;

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

