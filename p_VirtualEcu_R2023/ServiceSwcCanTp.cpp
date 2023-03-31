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
#define ServiceSwcCanTp_MaskTypeFrame                                       0xF0
#define ServiceSwcCanTp_IndexTypeFrame                                         0

#define ServiceSwcCanTp_MaskLengthTypeFrameSingle                           0x0F
#define ServiceSwcCanTp_IndexLengthTypeFrameSingle                             0
#define ServiceSwcCanTp_MaxLengthTypeFrameSingle                               8

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef enum{
      ServiceSwcCanTp_eTypeFrameSingle      = 0x00
   ,  ServiceSwcCanTp_eTypeFrameFirst       = 0x10
   ,  ServiceSwcCanTp_eTypeFrameConsecutive = 0x20
   ,  ServiceSwcCanTp_eTypeFrameFlowControl = 0x30
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
FUNC(void, SERVICESWCCANTP_CODE) infServiceSwcCanTpServiceSwcEcuM_InitFunction   (const CfgServiceSwcCanTp_tst* CfgServiceSwcCanTp_ptr){UNUSED(CfgServiceSwcCanTp_ptr);}
FUNC(void, SERVICESWCCANTP_CODE) infServiceSwcCanTpServiceSwcEcuM_DeInitFunction (void){}
FUNC(void, SERVICESWCCANTP_CODE) infServiceSwcCanTpServiceSwcSchM_MainFunction   (void){}

FUNC(void, SERVICESWCCANTP_CODE) infServiceSwcCanTpEcuabCanIf_RxIndication(uint8 lu8IndexBufferRx){
   switch(
         ServiceSwcCanTp_MaskTypeFrame
      &  McalCan_astRxFifio[lu8IndexBufferRx].McalCan_stFrameExtended.data[ServiceSwcCanTp_IndexTypeFrame]
   ){
      case ServiceSwcCanTp_eTypeFrameSingle:
         if(
               ServiceSwcCanTp_MaxLengthTypeFrameSingle
            >  (
                     ServiceSwcCanTp_MaskLengthTypeFrameSingle
                  &  McalCan_astRxFifio[lu8IndexBufferRx].McalCan_stFrameExtended.data[ServiceSwcCanTp_IndexLengthTypeFrameSingle]
               )
         ){
            infServiceSwcPduRServiceSwcCanTp_RxIndication(lu8IndexBufferRx);
         }
         else{
            //TBD: Handle invalid length case
         }
         break;
      case ServiceSwcCanTp_eTypeFrameFirst:       break; //TBD: Case not yet handled
      case ServiceSwcCanTp_eTypeFrameConsecutive: break; //TBD: Case not yet handled
      case ServiceSwcCanTp_eTypeFrameFlowControl: break; //TBD: Case not yet handled
   }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

