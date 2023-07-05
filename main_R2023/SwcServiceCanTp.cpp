/******************************************************************************/
/* File   : SwcServiceCanTp.cpp                                               */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "SwcServiceCanTp.hpp"
#include "infSwcServiceCanTpEcuabCanIf.hpp"
#include "infSwcServiceCanTpSwcServiceEcuM.hpp"

#include "infSwcServicePduRSwcServiceCanTp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define SwcServiceCanTp_MaskTypeFrame                                       0xF0
#define SwcServiceCanTp_IndexTypeFrame                                         0

#define SwcServiceCanTp_MaskLengthTypeFrameSingle                           0x0F
#define SwcServiceCanTp_IndexLengthTypeFrameSingle                             0
#define SwcServiceCanTp_MaxLengthTypeFrameSingle                               8

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef enum{
      SwcServiceCanTp_eTypeFrameSingle      = 0x00
   ,  SwcServiceCanTp_eTypeFrameFirst       = 0x10
   ,  SwcServiceCanTp_eTypeFrameConsecutive = 0x20
   ,  SwcServiceCanTp_eTypeFrameFlowControl = 0x30
}SwcServiceCanTp_teTypeFrame;

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
FUNC(void, SWCSERVICECANTP_CODE) infSwcServiceCanTpSwcServiceEcuM_InitFunction   (const CfgSwcServiceCanTp_tst* CfgSwcServiceCanTp_ptr){UNUSED(CfgSwcServiceCanTp_ptr);}
FUNC(void, SWCSERVICECANTP_CODE) infSwcServiceCanTpSwcServiceEcuM_DeInitFunction (void){}
FUNC(void, SWCSERVICECANTP_CODE) infSwcServiceCanTpSwcServiceSchM_MainFunction   (void){}

FUNC(void, SWCSERVICECANTP_CODE) infSwcServiceCanTpEcuabCanIf_RxIndication(uint8 lu8IndexBufferRx){
   switch(
         SwcServiceCanTp_MaskTypeFrame
      &  McalCan_astRxFifio[lu8IndexBufferRx].McalCan_stFrameExtended.data[SwcServiceCanTp_IndexTypeFrame]
   ){
      case SwcServiceCanTp_eTypeFrameSingle:
         if(
               SwcServiceCanTp_MaxLengthTypeFrameSingle
            >  (
                     SwcServiceCanTp_MaskLengthTypeFrameSingle
                  &  McalCan_astRxFifio[lu8IndexBufferRx].McalCan_stFrameExtended.data[SwcServiceCanTp_IndexLengthTypeFrameSingle]
               )
         ){
            infSwcServicePduRSwcServiceCanTp_RxIndication(lu8IndexBufferRx);
         }
         else{
            //TBD: Handle invalid length case
         }
         break;
      case SwcServiceCanTp_eTypeFrameFirst:       break; //TBD: Case not yet handled
      case SwcServiceCanTp_eTypeFrameConsecutive: break; //TBD: Case not yet handled
      case SwcServiceCanTp_eTypeFrameFlowControl: break; //TBD: Case not yet handled
   }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

