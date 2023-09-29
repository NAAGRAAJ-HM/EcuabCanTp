#if !defined (CANTP_CBK_H)
#define CANTP_CBK_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "SwcServiceCanTp.hpp"

#define CANTP_START_SEC_CODE
#include "MemMap.hpp"

FUNC(void, CANTP_CODE) CanTp_RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) PduInfoPtr);
FUNC(void, CANTP_CODE) CanTp_TxConfirmation(PduIdType TxPduId);

#if(CANTP_STMIN_BY_APPL == STD_ON)
FUNC(void, CANTP_CODE) CanTp_StopSeparationTime(PduIdType CanTpTxSduId);
#endif

#if(CANTP_APPL_RX_SF_INDICATION == STD_ON)
FUNC(void, CANTP_CODE) Appl_CanTpRxSFIndication(PduIdType PduRRxPduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) PduInfoPtr);
#endif

#if(CANTP_APPL_RX_FF_INDICATION == STD_ON)
FUNC(void, CANTP_CODE) Appl_CanTpRxFFIndication(PduIdType PduRRxPduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) PduInfoPtr);
#endif

#if(CANTP_APPL_RX_CF_INDICATION == STD_ON)
FUNC(void, CANTP_CODE) Appl_CanTpRxCFIndication(PduIdType PduRRxPduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) PduInfoPtr);
#endif

#if(CANTP_APPL_FRAME_TRANSMISSION == STD_ON)
FUNC(void, CANTP_CODE) Appl_CanTpFrameTransmission(PduIdType CanIfTxPduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) PduInfoPtr);
#endif

#if(CANTP_APPL_FRAME_CONFIRMATION == STD_ON)
FUNC(void, CANTP_CODE) Appl_CanTpFrameTxConfirmation(PduIdType CanIfTxPduId);
#endif

#define CANTP_STOP_SEC_CODE
#include "MemMap.hpp"

#ifdef __cplusplus
}
#endif
#endif

