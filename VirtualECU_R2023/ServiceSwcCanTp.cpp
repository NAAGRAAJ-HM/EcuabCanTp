/******************************************************************************/
/* File   : ServiceSwcCanTp.cpp                                               */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "ServiceSwcCanTp.hpp"
#include "infServiceSwcCanTpEcuabCanIf.hpp"
#include "infServiceSwcCanTpServiceSwcEcuM.hpp"

#include "infServiceSwcPduRServiceSwcCanTp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef enum{
      ServiceSwcCanTp_eErrorNone
   ,  ServiceSwcCanTp_eErrorDlc
}ServiceSwcCanTp_teError;

typedef enum{
      ServiceSwcCanTp_eTypeFrameSingle
   ,  ServiceSwcCanTp_eTypeFrameFirst
   ,  ServiceSwcCanTp_eTypeFrameConsecutive
   ,  ServiceSwcCanTp_eTypeFrameFlowControl
}ServiceSwcCanTp_teTypeFrame;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, SERVICESWCCANTP_CODE) infServiceSwcCanTpServiceSwcEcuM_InitFunction   (const CfgServiceSwcCanTp_Type* CfgServiceSwcCanTp_ptr){UNUSED(CfgServiceSwcCanTp_ptr);}
FUNC(void, SERVICESWCCANTP_CODE) infServiceSwcCanTpServiceSwcEcuM_DeInitFunction (void){}
FUNC(void, SERVICESWCCANTP_CODE) infServiceSwcCanTpServiceSwcSchM_MainFunction   (void){}



FUNC(ServiceSwcCanTp_teError, SERVICESWCCANTP_CODE) ServiceSwcCanTp_CheckLengthPduRx(uint8 lu8IndexBufferRx){
   UNUSED(lu8IndexBufferRx);
   return ServiceSwcCanTp_eErrorNone; //TBD: Update context and return errors, if any
}

FUNC(ServiceSwcCanTp_teTypeFrame, SERVICESWCCANTP_CODE) ServiceSwcCanTp_GetTypeFramePduRx(uint8 lu8IndexBufferRx){ //TBD: Evaluate frame type and update Pdu length in this function
   UNUSED(lu8IndexBufferRx);
   return /*McalCan_auBufferRx[lu8IndexBufferRx].ContextServiceSwcCanTp.*/ServiceSwcCanTp_eTypeFrameSingle;//TBD: move to message buffer - Cantp context
}

FUNC(void, SERVICESWCCANTP_CODE) infServiceSwcCanTpEcuabCanIf_RxIndication(uint8 lu8IndexBufferRx){
   if(ServiceSwcCanTp_eErrorNone == ServiceSwcCanTp_CheckLengthPduRx(lu8IndexBufferRx)){
      switch(ServiceSwcCanTp_GetTypeFramePduRx(lu8IndexBufferRx)){
         case ServiceSwcCanTp_eTypeFrameSingle:
            switch(infServiceSwcPduRServiceSwcCanTp_StartOfReception(lu8IndexBufferRx)){
               case teStatusRequestBuffer_OK:
                  if(/*RemBufSize >= SduLength*/1){
                     teStatusRequestBuffer eStatusRequestBuffer = infServiceSwcPduRServiceSwcCanTp_CopyRxData(lu8IndexBufferRx);
                     UNUSED(eStatusRequestBuffer);
                  }
                  break;
               case teStatusRequestBuffer_E_NOT_OK:   break; //TBD: Case not yet handled
               case teStatusRequestBuffer_E_BUSY:     break; //TBD: Case not yet handled
               case teStatusRequestBuffer_E_OVERFLOW: break; //TBD: Case not yet handled
            }
            break;
         case ServiceSwcCanTp_eTypeFrameFirst:       break; //TBD: Case not yet handled
         case ServiceSwcCanTp_eTypeFrameConsecutive: break; //TBD: Case not yet handled
         case ServiceSwcCanTp_eTypeFrameFlowControl: break; //TBD: Case not yet handled
      }
   }
   else{
      //TBD: report errors associated with Rx Pdu length
   }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

