#define CANTP_SOURCE
#ifdef __cplusplus
extern "C"
{
#endif

#include "SwcServiceCanTp.hpp"
#include "CanTp_Cbk.hpp"

#include "infSwcServicePduRSwcServiceCanTp.hpp"
#if(CANTP_LOLAYER_CANIF == STD_ON)
#include "EcuabCanIf.hpp"
#endif

#if(CANTP_DCM_REQUEST_DETECT == STD_ON)
#include "SwcApplDcm.hpp"
#endif

#include "SchM_CanTp.hpp"

#if(CANTP_DEV_ERROR_REPORT == STD_ON)

#include "SwcServiceDet.hpp"
#endif

#if(CANTP_CONFIGURATION_VARIANT == CANTP_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)

#include "EcuM_Error.hpp"
#endif

#include "CanTp_Priv.hpp"

#if(  (CANTP_SW_MAJOR_VERSION != (3u)) \
    || (CANTP_SW_MINOR_VERSION != (5u)) \
    || (CANTP_SW_PATCH_VERSION != (0u)) )
# error "Version numbers of CanTp.c and CanTp.h are inconsistent"
#endif

#if(  (CANTP_CFG_GEN_MAJOR_VERSION != (4u)) \
    || (CANTP_CFG_GEN_MINOR_VERSION != (4u)) )
# error "Version numbers of CanTp.c and CanTp_Cfg.h are inconsistent!"
#endif

#if !defined (CANTP_LOCAL)
#define CANTP_LOCAL                   static
#endif

#if !defined (CANTP_LOCAL_INLINE)
#define CANTP_LOCAL_INLINE            LOCAL_INLINE
#endif

#if !defined (CanTp_PduRRxIndication)
#define CanTp_PduRRxIndication(CanTpRxPduId, Result)                               (PduR_CanTpRxIndication( (CanTpRxPduId), (Result) ))
#endif
#if !defined (CanTp_PduRTxConfirmation)
#define CanTp_PduRTxConfirmation(CanTpTxPduId, Result)                             (PduR_CanTpTxConfirmation( (CanTpTxPduId), (Result) ))
#endif
#if !defined (CanTp_PduRStartOfReception)
#if(CANTP_PDUR_API_403_ENABLED == STD_ON)
#define CanTp_PduRStartOfReception(CanTpRxPduId, PduInfoPtr, SduLength, RxBufSizePtr)     (CanTp_BufferStateType)(PduR_CanTpStartOfReception( (CanTpRxPduId), (SduLength), (RxBufSizePtr) ))
#else
#if(CANTP_GENERIC_CONNECTIONS == STD_ON)
#define CanTp_PduRStartOfReception(CanTpRxPduId, PduInfoPtr, SduLength, RxBufSizePtr)    (CanTp_BufferStateType)(PduR_CanTpStartOfReception( (CanTpRxPduId), (PduInfoPtr), (SduLength), (RxBufSizePtr) ))
#else
#define CanTp_PduRStartOfReception(CanTpRxPduId, PduInfoPtr, SduLength, RxBufSizePtr)    (CanTp_BufferStateType)(PduR_CanTpStartOfReception( (CanTpRxPduId), (PduInfoType*)NULL_PTR,     (SduLength), (RxBufSizePtr) ))
#endif
#endif
#endif
#if !defined (CanTp_PduRCopyRxData)
#define CanTp_PduRCopyRxData(CanTpRxPduId, PduInfoPtr, RxBufSizePtr)               (CanTp_BufferStateType)(PduR_CanTpCopyRxData( (CanTpRxPduId), (PduInfoPtr), (RxBufSizePtr) ))
#endif
#if !defined (CanTp_PduRCopyTxData)
#define CanTp_PduRCopyTxData(CanTpRxPduId, PduInfoPtr, RetryInfoPtr, RxBufSizePtr) (CanTp_BufferStateType)(PduR_CanTpCopyTxData( (CanTpRxPduId), (PduInfoPtr), (RetryInfoType*)NULL_PTR, (RxBufSizePtr) ))
#endif

#if !defined (CanTp_DetReportError)
#if(CANTP_DEV_ERROR_REPORT == STD_ON)
#define CanTp_DetReportError(ApiId, ErrorId)                       ((void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID_DET, (ApiId), (ErrorId) ));
#else
#define CanTp_DetReportError(ApiId, ErrorId)
#endif
#endif

#if !defined (CanTp_EcuMReportBswError)
#if(CANTP_CONFIGURATION_VARIANT == CANTP_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)
#define CanTp_EcuMReportBswError(EcuMErrorId)                      (EcuM_BswErrorHook((uint16) CANTP_MODULE_ID, (EcuMErrorId)));
#else
#define CanTp_EcuMReportBswError(EcuMErrorId)
#endif
#endif

#if !defined (CanTp_DcmForwardNAE)
#if((CANTP_DCM_REQUEST_DETECT == STD_ON))
#define CanTp_DcmForwardNAE(CanTpRxPduId, N_AE)                  (Dcm_OnRequestDetection( (CanTpRxPduId), (N_AE) ))
#else
#define CanTp_DcmForwardNAE(CanTpRxPduId, N_AE)
#endif
#endif

#if(CANTP_APPL_RX_SF_INDICATION == STD_ON)
#define CanTp_ApplRxSFIndication(PduRRxPduId, PduInfo)              (Appl_CanTpRxSFIndication( (PduRRxPduId), (PduInfo)));
#else
#define CanTp_ApplRxSFIndication(PduRRxPduId, PduInfo)
#endif

#if(CANTP_APPL_RX_FF_INDICATION == STD_ON)
#define CanTp_ApplRxFFIndication(PduRRxPduId, PduInfo)              (Appl_CanTpRxFFIndication( (PduRRxPduId), (PduInfo)));
#else
#define CanTp_ApplRxFFIndication(PduRRxPduId, PduInfo)
#endif

#if(CANTP_APPL_RX_CF_INDICATION == STD_ON)
#define CanTp_ApplRxCFIndication(PduRRxPduId, PduInfo)              (Appl_CanTpRxCFIndication( (PduRRxPduId), (PduInfo)));
#else
#define CanTp_ApplRxCFIndication(PduRRxPduId, PduInfo)
#endif

#if(CANTP_APPL_FRAME_TRANSMISSION == STD_ON)
#define CanTp_ApplFrameTransmission(CanIfTxPduId, PduInfo)          (Appl_CanTpFrameTransmission((CanIfTxPduId), (PduInfo)));
#else
#define CanTp_ApplFrameTransmission(CanIfTxPduId, PduInfo)
#endif

#if(CANTP_APPL_FRAME_CONFIRMATION == STD_ON)
#define CanTp_ApplFrameTxConfirmation(CanIfTxPduId)                 (Appl_CanTpFrameTxConfirmation((CanIfTxPduId)));
#else
#define CanTp_ApplFrameTxConfirmation(CanIfTxPduId)
#endif

#if(CANTP_TX_FC_FROM_ISR == STD_ON)

#define CanTp_RxTransmitFrame_ISR(ptr)                              (CanTp_RxTransmitFrame( (ptr) ));
#else

#define CanTp_RxTransmitFrame_ISR(ptr)
#endif

#if(CANTP_RX_GET_BUFFER_FROM_ISR == STD_ON)

#define CanTp_RxGetBuffer_ISR(ptr)                                  (CanTp_RxGetBuffer( (ptr) ));
#else

#define CanTp_RxGetBuffer_ISR(ptr)
#endif

#if(CANTP_TX_GET_BUFFER_FROM_ISR == STD_ON)

#define CanTp_TxGetBuffer_ISR(ptr)                                  (CanTp_TxGetBuffer( (ptr) ));
#else

#define CanTp_TxGetBuffer_ISR(ptr)
#endif

#if !defined (CanTp_DetAssert)
#if(CANTP_DEV_ERROR_DETECT == STD_ON)
#define CanTp_DetAssert(Check, ApiId, ErrorId)                     { if(!(Check)) {CanTp_DetReportError( (ApiId), (ErrorId) ) }}
#else
#define CanTp_DetAssert(Check, ApiId, ErrorId)
#endif
#endif

#define CanTp_EnterCritical()                                        SchM_Enter_CanTp_CANTP_EXCLUSIVE_AREA_0()
#define CanTp_LeaveCritical()                                        SchM_Exit_CanTp_CANTP_EXCLUSIVE_AREA_0()

#define CANTP_START_SEC_VAR_INIT_8BIT
#include "MemMap.hpp"
CANTP_LOCAL VAR(SwcServiceCanTp_InitFunctionStatusType, CANTP_VAR_INIT) SwcServiceCanTp_InitFunctionState = CANTP_STATUS_NOT_INITIALIZED;
#define CANTP_STOP_SEC_VAR_INIT_8BIT
#include "MemMap.hpp"

#if(CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
#define CANTP_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.hpp"
CANTP_LOCAL VAR(PduIdType, CANTP_VAR_NOINIT) CanTp_NumRxChannelsAvail;
CANTP_LOCAL VAR(PduIdType, CANTP_VAR_NOINIT) CanTp_NumTxChannelsAvail;
#define CANTP_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.hpp"
#endif

#if(CANTP_USE_INIT_POINTER == STD_ON)
#define CANTP_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.hpp"
CANTP_LOCAL P2CONST(CanTp_ConfigType, CANTP_VAR_NOINIT, CANTP_INIT_DATA) CanTp_ConfigDataPtr;
#define CANTP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.hpp"
#endif

#define CANTP_START_SEC_CODE
#include "MemMap.hpp"

#if(CANTP_RXTX_MAINFUNCTION_API != STD_ON)

FUNC(void,  CANTP_CODE)   SwcServiceCanTp_MainFunctionRx(void);

FUNC(void,  CANTP_CODE)   SwcServiceCanTp_MainFunctionTx(void);
#endif

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxInitState(CanTp_RxStatePtrType pTpRxState);

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_TxInitState(CanTp_TxStatePtrType pTpTxState);

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_RxInit(CanTp_RxStatePtrType pTpRxState, CanTp_NotificationType NotifyCode, uint8 DetError, CanTp_ResetControlType ResetRequest);

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxInit(CanTp_TxStatePtrType pTpTxState, CanTp_NotificationType NotifyCode, uint8 DetError);

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_ResetChannels(void);

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_CanIfRxIndicationSF(CanTp_RxStatePtrType pTpRxState, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPdu);

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_CanIfRxIndicationFF(CanTp_RxStatePtrType pTpRxState, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPdu);

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_CanIfRxIndicationCF(CanTp_RxStatePtrType pTpRxState, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPdu);

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_CanIfRxIndicationFC(CanTp_TxStatePtrType pTpTxState, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPdu);

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_CanIfRxIndication(PduIdType SduHdl
   ,                                                          uint8 FrameType
   ,                                                          P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo
   ,                                                          P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo);

#if(CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_CanIfTxConfirmation(CanTp_TxStatePtrType pTpTxState);
#endif

#if(CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_CanIfTxConfirmationFC(CanTp_RxStatePtrType pTpRxState);
#endif

CANTP_LOCAL FUNC(CanTp_TxResultType, CANTP_CODE) CanTp_CanIfTransmitFrame(P2CONST(CanTp_PduTxInfoType, AUTOMATIC, CANTP_APPL_DATA) pPduTxData
   ,                                                                         P2VAR(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pTpData);

CANTP_LOCAL_INLINE FUNC(Std_ReturnType, CANTP_CODE) CanTp_TxStartConnection(PduIdType TxSduSnv
   ,                                                                           PduIdType TxHdl
   ,                                                                           PduLengthType SduLength
   ,                                                                           P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpTxInfoPtr);

#if(CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)

CANTP_LOCAL_INLINE FUNC(uint8, CANTP_CODE) CanTp_TxGetStminTimerFromStminValue(uint8 STminValue);
#endif

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxGetBuffer(CanTp_TxStatePtrType pTpTxState);

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxTransmitFrame(CanTp_TxStatePtrType pTpTxState);

#if(CANTP_TRANSMITFCTOFLOLAYERFCTS == STD_ON)

CANTP_LOCAL_INLINE FUNC(Std_ReturnType, CANTP_CODE) CanTp_LoLayerTransmit(CanTp_DirectionType Direction
   ,                                                                         PduIdType SduHdl
   ,                                                                         PduIdType LoLayerTxPduId
   ,                                                                         P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pTpData);
#endif

#if(CANTP_CANCELTRANSMITFCTOFLOLAYERFCTS == STD_ON)

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_LoLayerCancelTransmit(CanTp_DirectionType Direction
   ,                                                                     PduIdType SduHdl
   ,                                                                     PduIdType LoLayerTxPduId);
#endif

#if(CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_OFF)

CANTP_LOCAL_INLINE FUNC(PduLengthType, CANTP_CODE) CanTp_RxGetBytesPerBlock(CanTp_RxStatePtrType pTpRxState);
#endif

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxGetBufferSF(CanTp_RxStatePtrType pTpRxState);

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxGetBufferFF(CanTp_RxStatePtrType pTpRxState);

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxGetBufferCF(CanTp_RxStatePtrType pTpRxState);

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxGetBufferFCWait(CanTp_RxStatePtrType pTpRxState);

CANTP_LOCAL FUNC(void,  CANTP_CODE) CanTp_RxGetBuffer(CanTp_RxStatePtrType pTpRxState);

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_RxTransmitFrame(CanTp_RxStatePtrType pTpRxState);

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_Util_MemCpy(P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) pDest, P2CONST(uint8, AUTOMATIC, CANTP_APPL_DATA) pSrc, uint16 Count);

#if(CANTP_DEV_ERROR_DETECT == STD_ON)

CANTP_LOCAL_INLINE FUNC(boolean, CANTP_CODE) CanTp_Util_AssertLessEqual(uint32 CurrentValue, uint32 UpperLimit);
#endif

CANTP_LOCAL_INLINE FUNC(boolean, CANTP_CODE) CanTp_Util_CheckConfigValidity(void);

#if(CANTP_PADDING_SUPPORT_REQUIRED == STD_ON)

CANTP_LOCAL_INLINE FUNC(uint8, CANTP_CODE) CanTp_Util_GetPaddingLength(uint8 CurrentLength, boolean PaddingActivation, CanTp_CanType CanType);
#endif

#if(CANTP_GENERIC_CONNECTIONS == STD_ON)

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_Util_RxAssembleSduMetadata(uint8 Addressing
   ,                                                                          P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo
   ,                                                                          P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo
   ,                                                                          P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) pDest
   ,                                                                          P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) pLength);

CANTP_LOCAL_INLINE FUNC(boolean, CANTP_CODE) CanTp_Util_RxSduMetadataFromDataPduMatch(P2CONST(CanTp_RxStateType, AUTOMATIC, CANTP_APPL_DATA) pTpRxState
   ,                                                                                     P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo
   ,                                                                                     P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo);

CANTP_LOCAL_INLINE FUNC(boolean, CANTP_CODE) CanTp_Util_TxSduMetadataFromFcPduMatch(P2CONST(CanTp_TxStateType, AUTOMATIC, CANTP_APPL_DATA) pTpTxState
   ,                                                                                   P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo
   ,                                                                                   P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo);

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_Util_RxExtractSduMetadataInfo(CanTp_RxStatePtrType pTpRxState
   ,                                                                             P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo
   ,                                                                             P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo);

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_Util_TxExtractSduMetadataInfo(CanTp_TxStatePtrType pTpTxState
   ,                                                                             P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpTxInfoPtr);
#endif

#if((CANTP_RX_HAS_EXTENDED_ADDRESSING == STD_ON) || (CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON) || (CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON))
#if((CANTP_GENERIC_CONNECTIONS == STD_ON) && ((CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON) || (CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON)))
CANTP_LOCAL_INLINE FUNC(uint8, CANTP_CODE) CanTp_Util_RxGetFCInPayloadAddressInfo(P2CONST(CanTp_RxStateType, AUTOMATIC, CANTP_APPL_DATA) pTpRxState);
#else
#define CanTp_Util_RxGetFCInPayloadAddressInfo(pTpRxState)    CanTp_RxCfg_GetTxFcAddress((pTpRxState)->RxHdl)
#endif
#endif

#if((CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON))
#if(CANTP_GENERIC_CONNECTIONS == STD_ON)
CANTP_LOCAL_INLINE FUNC(uint8, CANTP_CODE) CanTp_Util_TxGetInPayloadAddressInfo(P2CONST(CanTp_TxStateType, AUTOMATIC, CANTP_APPL_DATA) pTpTxState);
#else
#define CanTp_Util_TxGetInPayloadAddressInfo(pTpTxState)    CanTp_TxCfg_GetTxAddress((pTpTxState)->TxHdl)
#endif
#endif

#if(CANTP_RX_HAS_HALF_DUPLEX == STD_ON)

CANTP_LOCAL FUNC(Std_ReturnType, CANTP_CODE) CanTp_RxCheckChannelMode(PduIdType RxHdl);
#endif

#if(CANTP_TX_HAS_HALF_DUPLEX == STD_ON)

CANTP_LOCAL FUNC(Std_ReturnType, CANTP_CODE) CanTp_TxCheckChannelMode(PduIdType TxHdl);
#endif

#if((CANTP_SUPPORT_STANDARD_ADDRESSING == STD_ON) || (CANTP_SUPPORT_NORMALFIXED_ADDRESSING == STD_ON) || CANTP_GENERIC_CONNECTIONS == STD_ON)

CANTP_LOCAL_INLINE FUNC(PduIdType, CANTP_CODE) CanTp_Cfg_GetSduHdlByRxPduOnly (PduIdType RxPduId, uint8 FrameType);
#endif

#if((CANTP_SUPPORT_EXTENDED_ADDRESSING == STD_ON) || (CANTP_SUPPORT_MIXED11_ADDRESSING == STD_ON) || (CANTP_SUPPORT_MIXED29_ADDRESSING == STD_ON))

CANTP_LOCAL_INLINE FUNC(PduIdType, CANTP_CODE) CanTp_Cfg_GetSduHdlByRxPduAddress (PduIdType RxPduId, uint8 FrameType, uint8 Address);
#endif

CANTP_LOCAL FUNC(CanTp_RxStatePtrType, CANTP_CODE) CanTp_RxGetFreeChannelPtr(PduIdType RxHdl
   ,                                                                            P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo
   ,                                                                            P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo);

CANTP_LOCAL FUNC(CanTp_RxStatePtrType, CANTP_CODE) CanTp_RxGetActiveChannelPtr(PduIdType RxHdl);

CANTP_LOCAL FUNC(CanTp_TxStatePtrType, CANTP_CODE) CanTp_TxGetFreeChannelPtr(PduIdType TxHdl
   ,                                                                            P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpTxInfoPtr);

CANTP_LOCAL FUNC(CanTp_TxStatePtrType, CANTP_CODE) CanTp_TxGetActiveChannelPtr(PduIdType TxHdl);

#if(CANTP_TRANSMIT_QUEUE == STD_ON)

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxQueueProcess(PduIdType TxConfPduId);

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxQueueCancel(PduIdType SduHdl, CanTp_DirectionType Direction);
#endif

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_Util_MemCpy(P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) pDest
   ,                                                           P2CONST(uint8, AUTOMATIC, CANTP_APPL_DATA) pSrc
   ,                                                           uint16 Count){
  uint16_least i;

  for(i = 0; i < Count; i++){
    pDest[i] = pSrc[i];
  }
}

#if(CANTP_DEV_ERROR_DETECT == STD_ON)

CANTP_LOCAL_INLINE FUNC(boolean, CANTP_CODE) CanTp_Util_AssertLessEqual (uint32 CurrentValue, uint32 UpperLimit){
  boolean lResult;

  if(CurrentValue <= UpperLimit){
    lResult = TRUE;
  }
  else{
    lResult = FALSE;
    CanTp_DetReportError(CANTP_SID_INIT, CANTP_E_PARAM_CONFIG)
  }
  return lResult;
}
#endif

CANTP_LOCAL_INLINE FUNC(boolean, CANTP_CODE) CanTp_Util_CheckConfigValidity(void){
  boolean lResult = TRUE;

#if(CANTP_DEV_ERROR_DETECT == STD_ON)
  boolean lTmp;
  PduIdType lSduId;
  PduIdType lSduHdl;

#if(CANTP_LOLAYERFCTS == STD_ON)
  CanTp_LoLayerFctsIterType lLoLayerIdx;
#endif

#if(CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)

  for(lSduId = 0; lSduId < CanTp_Cfg_GetNumRxSduIds(); lSduId++){
    if(CanTp_RxSduSnvIsAvailable(lSduId)){
      lSduHdl = CanTp_RxGetSduHdlBySduId(lSduId);

      lTmp = CanTp_Util_AssertLessEqual(CanTp_RxCfg_GetMaxPayload(lSduHdl), CANTP_MAX_PAYLOAD_LENGTH);
      if(lTmp == FALSE)
      {
        lResult = FALSE;
      }

      if(CanTp_RxCfg_GetTAType(lSduHdl) == CANTP_TATYPE_PHYSICAL)
      {
        lTmp = CanTp_Util_AssertLessEqual(CanTp_RxCfg_GetTxFcConfPduId(lSduHdl), (CanTp_Cfg_GetNumTxConfPdus() - (uint32)1));
        if(lTmp == FALSE)
        {
          lResult = FALSE;
        }
      }
    }

  }
#endif

#if(CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)

  for(lSduId = 0; lSduId < CanTp_Cfg_GetNumTxSduIds(); lSduId++){
    if(CanTp_TxSduSnvIsAvailable(lSduId)){
      lSduHdl = CanTp_TxGetSduHdlBySduId(lSduId);

      lTmp = CanTp_Util_AssertLessEqual(CanTp_TxCfg_GetMaxPayload(lSduHdl), CANTP_MAX_PAYLOAD_LENGTH);
      if(lTmp == FALSE)
      {
        lResult = FALSE;
      }

      lTmp = CanTp_Util_AssertLessEqual(CanTp_TxCfg_GetTxConfPduId(lSduHdl), (CanTp_Cfg_GetNumTxConfPdus() - (uint32)1));
      if(lTmp == FALSE)
      {
        lResult = FALSE;
      }

#if(CANTP_SUPPORT_MULTIPLE_ADDRESSING == STD_ON)
      if(CanTp_TxGetAdrOffset(lSduHdl) == 0u)
      {
        lTmp = CanTp_Util_AssertLessEqual((CanTp_TxCfg_GetMaxPayload(lSduHdl) + (uint32)1), CANTP_MAX_FRAME_LENGTH);
        if(lTmp == FALSE)
        {
          lResult = FALSE;
        }
      }
      else
      {
        lTmp = CanTp_Util_AssertLessEqual((CanTp_TxCfg_GetMaxPayload(lSduHdl) + (uint32)2), CANTP_MAX_FRAME_LENGTH);
        if(lTmp == FALSE)
        {
          lResult = FALSE;
        }
      }
#else
#if((CANTP_SUPPORT_STANDARD_ADDRESSING == STD_ON) || (CANTP_SUPPORT_NORMALFIXED_ADDRESSING == STD_ON))
      lTmp = CanTp_Util_AssertLessEqual((CanTp_TxCfg_GetMaxPayload(lSduHdl) + (uint32)1), CANTP_MAX_FRAME_LENGTH);
      if(lTmp == FALSE)
      {
        lResult = FALSE;
      }
#else
      lTmp = CanTp_Util_AssertLessEqual((CanTp_TxCfg_GetMaxPayload(lSduHdl) + (uint32)2), CANTP_MAX_FRAME_LENGTH);
      if(lTmp == FALSE)
      {
        lResult = FALSE;
      }
#endif
#endif

    }

  }
#endif

#if(CANTP_CONSTANT_BS == STD_ON)
  lTmp = CanTp_Util_AssertLessEqual(CanTp_GetSizeOfRxSduCfg(), CanTp_GetSizeOfCalcBS());
  if(lTmp == FALSE){
    lResult = FALSE;
  }
#endif
#if(CANTP_ENABLE_CHANGE_PARAM == STD_ON)
  lTmp = CanTp_Util_AssertLessEqual(CanTp_GetSizeOfRxSduCfg(), CanTp_GetSizeOfDynFCParameters());
  if(lTmp == FALSE){
    lResult = FALSE;
  }
#endif
#if(CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
  lTmp = CanTp_Util_AssertLessEqual(CanTp_GetSizeOfRxSduCfg(), CanTp_GetSizeOfRxChannelMap());
  if(lTmp == FALSE){
    lResult = FALSE;
  }
#else
  lTmp = CanTp_Util_AssertLessEqual(CanTp_GetSizeOfRxSduCfg(), CanTp_GetSizeOfRxState());
  if(lTmp == FALSE){
    lResult = FALSE;
  }
#endif

#if(CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
  lTmp = CanTp_Util_AssertLessEqual(CanTp_GetSizeOfTxSduCfg(), CanTp_GetSizeOfTxChannelMap());
  if(lTmp == FALSE){
    lResult = FALSE;
  }
#else
  lTmp = CanTp_Util_AssertLessEqual(CanTp_GetSizeOfTxSduCfg(), CanTp_GetSizeOfTxState());
  if(lTmp == FALSE){
    lResult = FALSE;
  }
#endif

#if(CANTP_TRANSMIT_QUEUE == STD_ON)
  lTmp = CanTp_Util_AssertLessEqual(CanTp_GetSizeOfTxSemaphores(), CanTp_GetSizeOfTxQueue());
  if(lTmp == FALSE){
    lResult = FALSE;
  }
#endif

#if(CANTP_LOLAYERFCTS == STD_ON)
  for(lLoLayerIdx = 0; lLoLayerIdx < CanTp_GetSizeOfLoLayerFcts(); lLoLayerIdx++){
    if(CanTp_GetTransmitFctOfLoLayerFcts(lLoLayerIdx) == NULL_PTR){
      CanTp_DetReportError(CANTP_SID_INIT, CANTP_E_PARAM_CONFIG)
      lResult = FALSE;
    }
  }
#endif

#endif

#if((CANTP_GENERIC_CONNECTIONS == STD_ON) && (CANTP_MIXED29_ADDRESSING == STD_ON) && (CANTP_MAX_SDU_METADATA_LENGTH != 3))
# error "CANTP_MAX_SDU_METADATA_LENGTH must be 3 if generic connections and mixed29 addressing are enabled."
#elif((CANTP_GENERIC_CONNECTIONS == STD_ON) && (CANTP_NORMALFIXED_ADDRESSING == STD_ON) && (CANTP_MAX_SDU_METADATA_LENGTH < 2))
# error "CANTP_MAX_SDU_METADATA_LENGTH must be at least 2 if generic connections and normal fixed addressing are enabled."
#elif((CANTP_GENERIC_CONNECTIONS == STD_ON) && ((CANTP_EXTENDED_ADDRESSING == STD_ON) || (CANTP_MIXED11_ADDRESSING == STD_ON)) && (CANTP_MAX_SDU_METADATA_LENGTH < 1))
# error "CANTP_MAX_SDU_METADATA_LENGTH must be at least 1 if generic connections and extended/mixed11 addressing are enabled."
#endif

#if((CANTP_GENERIC_CONNECTIONS == STD_ON) && ((CANTP_MIXED29_ADDRESSING == STD_ON) || (CANTP_NORMALFIXED_ADDRESSING == STD_ON)) && (CANTP_MAX_PDU_METADATA_LENGTH != 2))
# error "CANTP_MAX_PDU_METADATA_LENGTH must be 2 if generic connections and mixed29/normal fixed addressing are enabled."
#endif

  return lResult;
}

#if(CANTP_PADDING_SUPPORT_REQUIRED == STD_ON)

CANTP_LOCAL_INLINE FUNC(uint8, CANTP_CODE) CanTp_Util_GetPaddingLength(uint8 CurrentLength, boolean PaddingActivation, CanTp_CanType CanType){
  uint8 lPaddedLength;

  lPaddedLength = 0;

  if(CurrentLength <= CANTP_CAN20_FRAME_LENGTH){
    if(PaddingActivation == FALSE){
      lPaddedLength = CurrentLength;
    }
    else{
      lPaddedLength = CANTP_CAN20_FRAME_LENGTH;
    }
  }
#if(CANTP_SUPPORT_CANFD == STD_ON)
  else{
    if(CanType == CANTP_CANTYPE_CANFD){
      if(CurrentLength <= 24u)
      {
        lPaddedLength = (uint8)(((uint8)(CurrentLength - 1u) & 0xFCu) + 0x04u);
      }
      else if(CurrentLength <= 64u)
      {
        lPaddedLength = (uint8)(((uint8)(CurrentLength - 1u) & 0xF0u) + 0x10u);
      }
      else
      {
      }
    }

  }
#else
  CANTP_DUMMY_STATEMENT(CanType);
#endif

  return lPaddedLength;
}
#endif

#if(CANTP_GENERIC_CONNECTIONS == STD_ON)

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_Util_RxAssembleSduMetadata(uint8 Addressing
   ,                                                                          P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo
   ,                                                                          P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo
   ,                                                                          P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) pDest
   ,                                                                          P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) pLength){
  CANTP_DUMMY_STATEMENT(pPayloadInfo);
  CANTP_DUMMY_STATEMENT(pMetadataInfo);

  switch(Addressing){
#if((CANTP_RX_HAS_EXTENDED_ADDRESSING == STD_ON) || (CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON))
    case CANTP_ADDRESS_FORMAT_EXTENDED:
    case CANTP_ADDRESS_FORMAT_MIXED11:
      pDest[0] = pPayloadInfo->SduDataPtr[0];
      *pLength = 1;
      break;
#endif

#if(CANTP_RX_HAS_NORMALFIXED_ADDRESSING == STD_ON)
    case CANTP_ADDRESS_FORMAT_NORMALFIXED:
      pDest[0] = pMetadataInfo->SduDataPtr[0];
      pDest[1] = pMetadataInfo->SduDataPtr[1];
      *pLength = 2;
      break;
#endif

#if(CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON)
    case CANTP_ADDRESS_FORMAT_MIXED29:
      pDest[0] = pMetadataInfo->SduDataPtr[0];
      pDest[1] = pMetadataInfo->SduDataPtr[1];
      pDest[2] = pPayloadInfo->SduDataPtr[0];
      *pLength = 3;
      break;
#endif

    default:
      break;
  }
}

CANTP_LOCAL_INLINE FUNC(boolean, CANTP_CODE) CanTp_Util_RxSduMetadataFromDataPduMatch(P2CONST(CanTp_RxStateType, AUTOMATIC, CANTP_APPL_DATA) pTpRxState
   ,                                                                                     P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo
   ,                                                                                     P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo){
  boolean result = TRUE;
  uint8 lSduMetadataLength;
  uint8 lSduMetadata[CANTP_MAX_SDU_METADATA_LENGTH];
  uint8_least i;

  CanTp_Util_RxAssembleSduMetadata(CanTp_RxCfg_GetAddressingFormat(pTpRxState->RxHdl), pPayloadInfo, pMetadataInfo
   ,                                  lSduMetadata, &lSduMetadataLength);

  for(i = 0; i < pTpRxState->SduMetadataLength; i++){
    if(pTpRxState->SduMetadata[i] != lSduMetadata[i]){
      result = FALSE;
      break;
    }
  }

  return result;
}

CANTP_LOCAL_INLINE FUNC(boolean, CANTP_CODE) CanTp_Util_TxSduMetadataFromFcPduMatch(P2CONST(CanTp_TxStateType, AUTOMATIC, CANTP_APPL_DATA) pTpTxState
   ,                                                                                   P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo
   ,                                                                                   P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo){
  boolean result = TRUE;
  CANTP_DUMMY_STATEMENT(pPayloadInfo);
  CANTP_DUMMY_STATEMENT(pMetadataInfo);

  if(pTpTxState->SduMetadataLength != 0u){
#if(CANTP_TX_HAS_NORMALFIXED_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON)
    uint8_least i;
    uint8 lSduMetadata[CANTP_MAX_SDU_METADATA_LENGTH];
#endif

    switch(CanTp_TxCfg_GetAddressingFormat(pTpTxState->TxHdl)){
#if(CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON)
      case CANTP_ADDRESS_FORMAT_EXTENDED:
        if(pPayloadInfo->SduDataPtr[0] != CanTp_TxCfg_GetRxFcAddress(pTpTxState->TxHdl))
        {
          result = FALSE;
        }
        break;
#endif

#if(CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON)
      case CANTP_ADDRESS_FORMAT_MIXED11:
        if(pPayloadInfo->SduDataPtr[0] != pTpTxState->SduMetadata[pTpTxState->SduMetadataLength - 1u])
        {
          result = FALSE;
        }
        break;
#endif

#if(CANTP_TX_HAS_NORMALFIXED_ADDRESSING == STD_ON)
      case CANTP_ADDRESS_FORMAT_NORMALFIXED:
        lSduMetadata[0] = pMetadataInfo->SduDataPtr[1];
        lSduMetadata[1] = pMetadataInfo->SduDataPtr[0];

        for(i = 0; i < pTpTxState->SduMetadataLength; i++)
        {
          if(pTpTxState->SduMetadata[i] != lSduMetadata[i])
          {
            result = FALSE;
            break;
          }
        }

        break;
#endif

#if(CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON)
      case CANTP_ADDRESS_FORMAT_MIXED29:
        lSduMetadata[0] = pMetadataInfo->SduDataPtr[1];
        lSduMetadata[1] = pMetadataInfo->SduDataPtr[0];
        lSduMetadata[2] = pPayloadInfo->SduDataPtr[0];

        for(i = 0; i < pTpTxState->SduMetadataLength; i++)
        {
          if(pTpTxState->SduMetadata[i] != lSduMetadata[i])
          {
            result = FALSE;
            break;
          }
        }
        break;
#endif

      default:
        break;
    }
  }
  return result;
}

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_Util_RxExtractSduMetadataInfo(CanTp_RxStatePtrType pTpRxState
   ,  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo
   ,  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo){
  CANTP_DUMMY_STATEMENT(pPayloadInfo);

  if(CanTp_RxCfg_IsGenericConnection(pTpRxState->RxHdl)) {
    CanTp_Util_RxAssembleSduMetadata(CanTp_RxCfg_GetAddressingFormat(pTpRxState->RxHdl), pPayloadInfo, pMetadataInfo
   ,     pTpRxState->SduMetadata, &pTpRxState->SduMetadataLength);
  }

#if(CANTP_MAX_PDU_METADATA_LENGTH != 0)
  if(pMetadataInfo->SduLength == CANTP_MAX_PDU_METADATA_LENGTH){
    pTpRxState->FcPduMetadata[0] = pMetadataInfo->SduDataPtr[1];
    pTpRxState->FcPduMetadata[1] = pMetadataInfo->SduDataPtr[0];
    pTpRxState->FcPduMetadataLength = CANTP_MAX_PDU_METADATA_LENGTH;
  }
  else{
    pTpRxState->FcPduMetadataLength = 0;
  }
#endif
}

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_Util_TxExtractSduMetadataInfo(CanTp_TxStatePtrType pTpTxState
   ,                                                                             P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpTxInfoPtr){
  if(CanTp_TxCfg_GetSduMetadataLength(pTpTxState->TxHdl) != 0u){
    pTpTxState->SduMetadataLength = CanTp_TxCfg_GetSduMetadataLength(pTpTxState->TxHdl);
    CanTp_Util_MemCpy(pTpTxState->SduMetadata, CanTpTxInfoPtr->SduDataPtr, pTpTxState->SduMetadataLength);

#if(CANTP_MAX_PDU_METADATA_LENGTH != 0)
    switch(CanTp_TxCfg_GetAddressingFormat(pTpTxState->TxHdl)){
#if((CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON))
      case CANTP_ADDRESS_FORMAT_EXTENDED:
      case CANTP_ADDRESS_FORMAT_MIXED11:
        pTpTxState->DataPduMetadataLength = 0;
        break;
#endif

#if(CANTP_TX_HAS_NORMALFIXED_ADDRESSING)
      case CANTP_ADDRESS_FORMAT_NORMALFIXED:
#endif
#if(CANTP_TX_HAS_MIXED29_ADDRESSING)
      case CANTP_ADDRESS_FORMAT_MIXED29:
#endif
        pTpTxState->DataPduMetadata[0] = pTpTxState->SduMetadata[0];
        pTpTxState->DataPduMetadata[1] = pTpTxState->SduMetadata[1];
        pTpTxState->DataPduMetadataLength = 2;
        break;

      default:
        break;
    }
#endif
  }
}
#endif

#if((CANTP_GENERIC_CONNECTIONS == STD_ON) && ((CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON) || (CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON)))

CANTP_LOCAL_INLINE FUNC(uint8, CANTP_CODE) CanTp_Util_RxGetFCInPayloadAddressInfo(P2CONST(CanTp_RxStateType, AUTOMATIC, CANTP_APPL_DATA) pTpRxState){
  uint8 result;

  if((CanTp_RxCfg_IsGenericConnection(pTpRxState->RxHdl))
#if(CANTP_RX_HAS_EXTENDED_ADDRESSING)
      && (CanTp_RxCfg_GetAddressingFormat(pTpRxState->RxHdl) != CANTP_ADDRESS_FORMAT_EXTENDED)
#endif
     ){
    result = pTpRxState->SduMetadata[pTpRxState->SduMetadataLength - 1u];
  }
  else{
    result = CanTp_RxCfg_GetTxFcAddress(pTpRxState->RxHdl);
  }

  return result;
}
#endif

#if((CANTP_GENERIC_CONNECTIONS == STD_ON) && \
     ((CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON)))

CANTP_LOCAL_INLINE FUNC(uint8, CANTP_CODE) CanTp_Util_TxGetInPayloadAddressInfo(P2CONST(CanTp_TxStateType, AUTOMATIC, CANTP_APPL_DATA) pTpTxState){
  uint8 result;

  if(CanTp_TxCfg_GetSduMetadataLength(pTpTxState->TxHdl) != 0u){
    result = pTpTxState->SduMetadata[pTpTxState->SduMetadataLength - 1u];
  }
  else{
    result = CanTp_TxCfg_GetTxAddress(pTpTxState->TxHdl);
  }

  return result;
}
#endif

#if(CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)

CANTP_LOCAL_INLINE FUNC(uint8, CANTP_CODE) CanTp_TxGetStminTimerFromStminValue(uint8 STminValue){
  uint8  lTaskCycles = 0;
  uint8  lSTminTemp  = STminValue;

  if(STminValue > CANTP_STMIN_MILLISEC_MAX){
    if((STminValue >= CANTP_STMIN_MICROSEC_MIN) && (STminValue <= CANTP_STMIN_MICROSEC_MAX)){
      lTaskCycles = 1;
      lSTminTemp  = 0;
    }
    else{
      lSTminTemp = CANTP_STMIN_MILLISEC_MAX;

    }
  }

  if(lSTminTemp != 0u){
    lTaskCycles = (uint8)(((lSTminTemp + (CanTp_Cfg_GetTaskCycle() - 1u)) / CanTp_Cfg_GetTaskCycle()) + 1u);
  }

  return lTaskCycles;
}
#endif

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_CanIfRxIndicationSF(CanTp_RxStatePtrType pTpRxState
   ,                                                                   P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPdu){
  uint8                   lAddressingOffset;
  uint8                   lPayloadOffset;
  uint8                   lMinPayloadLength;
  uint8                   lMaxPayloadLength;
  PduLengthType           lReceivedDataLength;

  lAddressingOffset = CanTp_RxGetAdrOffset(pTpRxState->RxHdl);

  lReceivedDataLength = ((PduLengthType)pPdu->SduDataPtr[lAddressingOffset] & CANTP_MASK_SF_LENGTH);

  lPayloadOffset    = (uint8)(lAddressingOffset + CANTP_PCI_LENGTH_SF);
  lMinPayloadLength = 1;
  lMaxPayloadLength = CanTp_RxCfg_GetMaxPayloadSF(pTpRxState->RxHdl);

#if(CANTP_RX_HAS_CANFD == STD_ON)

  if(pPdu->SduLength > CANTP_CAN20_FRAME_LENGTH){
    if(lReceivedDataLength == 0u){
      lReceivedDataLength = (PduLengthType)(pPdu->SduDataPtr[lAddressingOffset + 1u]);
      lPayloadOffset      = (uint8)(lAddressingOffset + CANTP_PCI_LENGTH_LSF);
      lMinPayloadLength   = (uint8)(CanTp_RxCfg_GetMaxPayloadSF(pTpRxState->RxHdl) + 1u);
      lMaxPayloadLength   = (uint8)CanTp_RxCfg_GetMaxPayloadLSF(pTpRxState->RxHdl);
    }
    else{
      lMaxPayloadLength = 0u;
    }
  }

#endif

  if( (lReceivedDataLength >= lMinPayloadLength) &&
       (lReceivedDataLength <= lMaxPayloadLength) &&
       ((pPdu->SduLength)   >= (PduLengthType)(lPayloadOffset +  lReceivedDataLength)) ){
    if(pTpRxState->ChannelState != CANTP_RXSTATE_IDLE){
      CanTp_RxInit(pTpRxState, CANTP_NOTIFY_UNEXP_PDU, CANTP_E_RX_RESTART, CANTP_RESET_BUT_KEEP_MAPPING);
    }

    pTpRxState->FrameType  = CANTP_FRAME_SF;
    pTpRxState->DataLength = lReceivedDataLength;
    pTpRxState->PayloadLength = (uint8)pTpRxState->DataLength;
    CanTp_Util_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(&pTpRxState->Payload[0])
   ,                     (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(&pPdu->SduDataPtr[lPayloadOffset])
   ,                     (pTpRxState->PayloadLength) );

    CanTp_ApplRxSFIndication(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl), pPdu)

    pTpRxState->ProvidedBufferSize = 0;

#if(CANTP_GENERIC_CONNECTIONS == STD_ON)
    if(CanTp_RxCfg_PassSduMetadata(pTpRxState->RxHdl)){
      PduInfoType lPduInfo;
      lPduInfo.SduDataPtr = pTpRxState->SduMetadata;
      lPduInfo.SduLength  = pTpRxState->SduMetadataLength;

      pTpRxState->BufferState = CanTp_PduRStartOfReception(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl)
   ,                                                          &lPduInfo
   ,                                                          pTpRxState->DataLength
   ,                                                          &(pTpRxState->ProvidedBufferSize));
    }
    else
#endif
    {
      pTpRxState->BufferState = CanTp_PduRStartOfReception(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl)
   ,                                                          (PduInfoType*)NULL_PTR
   ,                                                          pTpRxState->DataLength
   ,                                                          &(pTpRxState->ProvidedBufferSize));
    }

    switch(pTpRxState->BufferState){
      case CANTP_BUFREQ_OK:
      case CANTP_BUFREQ_E_BUSY:

        pTpRxState->Timer        = CanTp_RxCfg_GetNBr(pTpRxState->RxHdl);
        pTpRxState->ChannelState = CANTP_RXSTATE_WAIT_BUFFER_SF;

#if(CANTP_ONLY_NOTIFY_INFORMED_APPL == STD_ON)

        pTpRxState->ApplState = (uint8)CANTP_APPL_INFORMED;
#endif
        CanTp_RxGetBuffer_ISR(pTpRxState)
        break;

      case CANTP_BUFREQ_E_NOT_OK:
      case CANTP_BUFREQ_E_OVFL:
      default:

        CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);
        break;
    }
  }
  else{
    CanTp_DetReportError(CANTP_SID_RXINDICATION, CANTP_E_INVALID_RX_LENGTH)
    if(pTpRxState->ChannelState == CANTP_RXSTATE_IDLE){
      CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NORESULT, CANTP_E_NO_ERROR, CANTP_RESET_ALL);
    }

  }
}

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_CanIfRxIndicationFF(CanTp_RxStatePtrType pTpRxState
   ,                                                                   P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPdu){
#if(CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)

  uint8                   lAddressingOffset;
  uint8                   lPayloadOffset;
  uint8                   lMaxPayloadLen;
  uint16                  lDataLengthLowerLimit;
  PduLengthType           lReceivedDataLength;

  lAddressingOffset = CanTp_RxGetAdrOffset(pTpRxState->RxHdl);

#if(CANTP_RX_HAS_TATYPE_FUNCTIONAL == STD_ON)
  if(CANTP_TATYPE_FUNCTIONAL == CanTp_RxCfg_GetTAType(pTpRxState->RxHdl)){
    CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NORESULT, CANTP_E_INVALID_TATYPE, CANTP_RESET_ALL);
  }

  else
#endif
  {
    lReceivedDataLength = CanTp_Util_Make16Bit( (uint8)(pPdu->SduDataPtr[lAddressingOffset] & CANTP_MASK_FF_LENGTH)
   ,                                               (uint8)(pPdu->SduDataPtr[lAddressingOffset + 1u]) );

#if(CANTP_SUPPORT_LONG_FF == STD_ON)

    if(lReceivedDataLength == 0u){
#if(CANTP_SIZEOF_PDULENGTHTYPE < 4)

      if((pPdu->SduDataPtr[lAddressingOffset + 2u] == 0u) &&
          (pPdu->SduDataPtr[lAddressingOffset + 3u] == 0u))
      {
        lReceivedDataLength = (PduLengthType)CanTp_Util_Make16Bit((uint8)(pPdu->SduDataPtr[lAddressingOffset + 4u])
   ,                                                                 (uint8)(pPdu->SduDataPtr[lAddressingOffset + 5u]));
      }
      else
      {
        lReceivedDataLength = 0;
      }
#else

      lReceivedDataLength = (PduLengthType)CanTp_Util_Make32Bit((uint8)(pPdu->SduDataPtr[lAddressingOffset + 2u])
   ,                                                               (uint8)(pPdu->SduDataPtr[lAddressingOffset + 3u])
   ,                                                               (uint8)(pPdu->SduDataPtr[lAddressingOffset + 4u])
   ,                                                               (uint8)(pPdu->SduDataPtr[lAddressingOffset + 5u]));
#endif

      lDataLengthLowerLimit = CANTP_FF_DL_12BIT;
      lMaxPayloadLen        = CanTp_RxCfg_GetMaxPayloadLFF(pTpRxState->RxHdl);
      lPayloadOffset        = (uint8) (lAddressingOffset + CANTP_PCI_LENGTH_LFF);
    }
    else
#endif
    {
      lDataLengthLowerLimit = (uint16)(CanTp_RxCfg_GetMaxSFDataLength(pTpRxState->RxHdl, pPdu->SduLength));
      lMaxPayloadLen        = CanTp_RxCfg_GetMaxPayloadFF(pTpRxState->RxHdl);
      lPayloadOffset        = (uint8) (lAddressingOffset + CANTP_PCI_LENGTH_FF);
    }

    if((lReceivedDataLength  > lDataLengthLowerLimit) &&
        (pPdu->SduLength     <= ((PduLengthType)lPayloadOffset + lMaxPayloadLen)) &&
        (pPdu->SduLength     >= CANTP_CAN20_FRAME_LENGTH)){
      if(pTpRxState->ChannelState != CANTP_RXSTATE_IDLE)
      {
        CanTp_RxInit(pTpRxState, CANTP_NOTIFY_UNEXP_PDU, CANTP_E_RX_RESTART, CANTP_RESET_BUT_KEEP_MAPPING);
      }

      pTpRxState->DataLength = lReceivedDataLength;
      pTpRxState->FrameType  = CANTP_FRAME_FF;
      pTpRxState->ExpectedSN = CANTP_SN_FIRST_CF;
      pTpRxState->DataIndex  = 0;
      pTpRxState->WFTCounter = CanTp_RxCfg_GetWFTmax(pTpRxState->RxHdl);

      pTpRxState->PayloadLength = (uint8)(pPdu->SduLength - lPayloadOffset);
      pTpRxState->InitalDLC     = (uint8)pPdu->SduLength;
      CanTp_Util_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) (&pTpRxState->Payload[0])
   ,                       (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) (&pPdu->SduDataPtr[lPayloadOffset])
   ,                       (pTpRxState->PayloadLength) );

      CanTp_ApplRxFFIndication(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl), pPdu)

      pTpRxState->ProvidedBufferSize = 0;

#if(CANTP_GENERIC_CONNECTIONS == STD_ON)
      if(CanTp_RxCfg_PassSduMetadata(pTpRxState->RxHdl))
      {
        PduInfoType lPduInfo;
        lPduInfo.SduDataPtr = pTpRxState->SduMetadata;
        lPduInfo.SduLength  = pTpRxState->SduMetadataLength;

        pTpRxState->BufferState = CanTp_PduRStartOfReception(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl)
   ,                                                            &lPduInfo
   ,                                                            pTpRxState->DataLength
   ,                                                            &(pTpRxState->ProvidedBufferSize));
      }
    else
#endif
      {
        pTpRxState->BufferState = CanTp_PduRStartOfReception(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl)
   ,                                                            (PduInfoType*)NULL_PTR
   ,                                                            pTpRxState->DataLength
   ,                                                            &(pTpRxState->ProvidedBufferSize));
      }

      switch(pTpRxState->BufferState)
      {
        case CANTP_BUFREQ_OK:

          pTpRxState->Timer         = CanTp_RxCfg_GetNBr(pTpRxState->RxHdl);
          pTpRxState->ChannelState  = CANTP_RXSTATE_WAIT_BUFFER_FF;

#if(CANTP_ONLY_NOTIFY_INFORMED_APPL == STD_ON)

          pTpRxState->ApplState     = (uint8)CANTP_APPL_INFORMED;
#endif
#if(CANTP_CONSTANT_BS == STD_ON)

          CanTp_Data_CalcBS(pTpRxState->RxHdl) = 0;
#endif
          CanTp_RxGetBuffer_ISR(pTpRxState)
          break;

        case CANTP_BUFREQ_E_BUSY:

          pTpRxState->Timer         = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);
          pTpRxState->ChannelState  = CANTP_RXSTATE_TRANSMIT_FC_WT;
#if(CANTP_ONLY_NOTIFY_INFORMED_APPL == STD_ON)

          pTpRxState->ApplState     = (uint8)CANTP_APPL_INFORMED;
#endif
          CanTp_RxTransmitFrame_ISR(pTpRxState)
          break;

        case CANTP_BUFREQ_E_OVFL:

          pTpRxState->Timer        = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);
          pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_OVFL;
          CanTp_RxTransmitFrame_ISR(pTpRxState)
          break;

        case CANTP_BUFREQ_E_NOT_OK:
        default:

          CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);
          break;
      }
    }

    else{
      CanTp_DetReportError(CANTP_SID_RXINDICATION, CANTP_E_INVALID_RX_LENGTH)
      if(pTpRxState->ChannelState == CANTP_RXSTATE_IDLE)
      {
        CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NORESULT, CANTP_E_NO_ERROR, CANTP_RESET_ALL);
      }

    }
  }

#else
CANTP_DUMMY_STATEMENT(pTpRxState);
CANTP_DUMMY_STATEMENT(pPdu);
#endif
}

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_CanIfRxIndicationCF(CanTp_RxStatePtrType pTpRxState
   ,                                                                   P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPdu){
#if(CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)

  uint8                   lAddressingOffset;
  uint8                   lPayloadOffset;
  uint8                   lSNinFrame;

  lAddressingOffset = CanTp_RxGetAdrOffset(pTpRxState->RxHdl);

  if(pTpRxState->ChannelState == CANTP_RXSTATE_WAIT_TXCONFFC_CTS){
#if(CANTP_TRANSMIT_QUEUE == STD_ON)
    CanTp_TxQueueCancel(pTpRxState->RxHdl, CANTP_DIR_RX);
#else
    CanTp_Data_TxSemaphore( CanTp_RxCfg_GetTxFcConfPduId(pTpRxState->RxHdl) ).Handle    = CANTP_INVALID_HDL;
    CanTp_Data_TxSemaphore( CanTp_RxCfg_GetTxFcConfPduId(pTpRxState->RxHdl) ).Direction = CANTP_DIR_NONE;
    CanTp_CanIfCancelTransmit(CANTP_DIR_RX, pTpRxState->RxHdl, CanTp_RxCfg_GetLoLayerTxFcPduId(pTpRxState->RxHdl));
#endif
    CanTp_CanIfTxConfirmationFC(pTpRxState);
  }

  if(pTpRxState->ChannelState == CANTP_RXSTATE_WAIT_CF){
    uint8 lErrorId = CANTP_E_INVALID_RX_LENGTH;

    pTpRxState->FrameType     = CANTP_FRAME_CF;
    lSNinFrame                = (uint8)(pPdu->SduDataPtr[lAddressingOffset] & CANTP_PCI_SN_MASK);

    lPayloadOffset            = (uint8)(lAddressingOffset + CANTP_PCI_LENGTH_CF);
    pTpRxState->PayloadLength = (uint8)(pTpRxState->InitalDLC - lPayloadOffset);

    if(pTpRxState->PayloadLength <= (pTpRxState->DataLength - pTpRxState->DataIndex)){
      if(pPdu->SduLength == pTpRxState->InitalDLC)
      {
        lErrorId = CANTP_E_NO_ERROR;
      }
    }
    else{
      pTpRxState->PayloadLength = (uint8)(pTpRxState->DataLength - pTpRxState->DataIndex);

      if(pPdu->SduLength >= ((PduLengthType)pTpRxState->PayloadLength + lPayloadOffset))
      {
        lErrorId = CANTP_E_NO_ERROR;
      }
    }

    if(lErrorId != CANTP_E_NO_ERROR){
      CanTp_DetReportError(CANTP_SID_RXINDICATION, lErrorId)
    }

    else if(lSNinFrame != (uint8)(pTpRxState->ExpectedSN)){
#if(CANTP_IGNORE_CF_WITH_WRONG_SN != STD_ON)
      CanTp_RxInit(pTpRxState, CANTP_NOTIFY_WRONG_SN, CANTP_E_RX_INVALID_SN, CANTP_RESET_ALL);
#endif
    }
    else{
      pTpRxState->ExpectedSN = (uint8)((pTpRxState->ExpectedSN + 1u) & CANTP_PCI_SN_MASK);
      CanTp_ApplRxCFIndication(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl), pPdu)

      CanTp_Util_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) (&pTpRxState->Payload[0])
   ,                       (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) (&pPdu->SduDataPtr[lPayloadOffset])
   ,                       (pTpRxState->PayloadLength) );

#if(CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_ON)

      pTpRxState->BufferState = CANTP_BUFREQ_OK;
#else
      if(pTpRxState->ProvidedBufferSize >= pTpRxState->PayloadLength)
      {
        pTpRxState->BufferState = CANTP_BUFREQ_OK;
      }
      else
      {
        pTpRxState->BufferState = CANTP_BUFREQ_E_BUSY;
      }
#endif

      pTpRxState->Timer        = CanTp_RxCfg_GetNCr(pTpRxState->RxHdl);
      pTpRxState->ChannelState = CANTP_RXSTATE_WAIT_BUFFER_CF;
      CanTp_RxGetBuffer_ISR(pTpRxState)
    }
  }

#else
CANTP_DUMMY_STATEMENT(pTpRxState);
CANTP_DUMMY_STATEMENT(pPdu);
#endif
}

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_CanIfRxIndicationFC(CanTp_TxStatePtrType pTpTxState
   ,                                                                   P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPdu){
  uint8 lAddressingOffset = CanTp_TxGetAdrOffset(pTpTxState->TxHdl);

  if(  (pTpTxState->ChannelState == CANTP_TXSTATE_WAIT_TXCONF_FF ) ||
       ((pTpTxState->ChannelState == CANTP_TXSTATE_WAIT_TXCONF_CF) && (pTpTxState->BlocksizeCounter == 1u)) ){
    pTpTxState->FCLength = CANTP_PCI_LENGTH_FC + lAddressingOffset;
    CanTp_Util_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) (pTpTxState->FCData)
   ,                     (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) (pPdu->SduDataPtr)
   ,                     (pTpTxState->FCLength) );

  }
  else{
    if(pTpTxState->ChannelState == CANTP_TXSTATE_WAIT_FC){
      if(pPdu->SduLength >= ((PduLengthType)CANTP_PCI_LENGTH_FC + lAddressingOffset))
      {
        switch(pPdu->SduDataPtr[lAddressingOffset] & CANTP_MASK_FS)
        {
          case CANTP_FLOWSTATUS_CTS:
#if(CANTP_USE_ONLY_FIRST_FC == STD_ON)

            if(pTpTxState->FirstFCReceived == TRUE)
            {
              pTpTxState->BlocksizeCounter = pTpTxState->BS;

            }
            else
#endif
            {
#if(CANTP_MODIFIED_RES_STMIN_HANDLING == STD_ON)

              uint8 lTempSTmin;
              lTempSTmin = pPdu->SduDataPtr[lAddressingOffset + CANTP_FRAME_OFFSET_FC_STMIN];

              if( ((lTempSTmin > CANTP_STMIN_MILLISEC_MAX) && (lTempSTmin < CANTP_STMIN_MICROSEC_MIN)) ||
                    (lTempSTmin > CANTP_STMIN_MICROSEC_MAX) )
              {
#if(CANTP_REJECT_FC_WITH_RES_STMIN == STD_ON)

                CanTp_TxInit(pTpTxState, CANTP_NOTIFY_NOT_OK, CANTP_E_TX_RES_STMIN);
#endif
                break;
              }
#endif

              pTpTxState->STmin            = pPdu->SduDataPtr[lAddressingOffset + CANTP_FRAME_OFFSET_FC_STMIN];
              pTpTxState->BlocksizeCounter = pPdu->SduDataPtr[lAddressingOffset + CANTP_FRAME_OFFSET_FC_BS];
#if(CANTP_USE_ONLY_FIRST_FC == STD_ON)
              pTpTxState->BS               = pPdu->SduDataPtr[lAddressingOffset + CANTP_FRAME_OFFSET_FC_BS];
              pTpTxState->FirstFCReceived  = TRUE;
#endif
            }

            pTpTxState->Timer           = CanTp_TxCfg_GetNCs(pTpTxState->TxHdl);
            pTpTxState->ChannelState    = CANTP_TXSTATE_WAIT_BUFFER_CF;
            CanTp_TxGetBuffer_ISR(pTpTxState)
            break;

          case CANTP_FLOWSTATUS_WT:

            pTpTxState->Timer = CanTp_TxCfg_GetNBs(pTpTxState->TxHdl);
            break;

#if(CANTP_IGNORE_FC_OVFL_INVALID_FS == STD_ON)
          case CANTP_FLOWSTATUS_OVFL:
          default:

            break;
#else
          case CANTP_FLOWSTATUS_OVFL:

            CanTp_TxInit(pTpTxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_TX_FC_OVFL);
            break;

          default:

            CanTp_TxInit(pTpTxState, CANTP_NOTIFY_INVALID_FS, CANTP_E_TX_INVALID_FS);
            break;
#endif
        }
      }

      else
      {
        CanTp_DetReportError(CANTP_SID_RXINDICATION, CANTP_E_INVALID_RX_LENGTH)
      }
    }

  }
}

CANTP_LOCAL_INLINE FUNC(Std_ReturnType, CANTP_CODE) CanTp_TxStartConnection(PduIdType TxSduSnv
   ,                                                                           PduIdType TxHdl
   ,                                                                           PduLengthType SduLength
   ,                                                                           P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpTxInfoPtr){
  CanTp_TxStatePtrType pTpTxState;
  Std_ReturnType       lReturnValue;

  lReturnValue = E_NOT_OK;
  CANTP_DUMMY_STATEMENT(TxSduSnv);

  pTpTxState = CanTp_TxGetFreeChannelPtr(TxHdl, CanTpTxInfoPtr);

  if(pTpTxState != NULL_PTR){
    lReturnValue = E_OK;
#if(CANTP_STMIN_BY_APPL == STD_ON)
    pTpTxState->TxSduSnv = TxSduSnv;
#endif

    if(SduLength > CanTp_TxCfg_GetMaxSFDataLength(TxHdl)){
      pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_BUFFER_FF;

#if(CANTP_TX_HAS_TATYPE_FUNCTIONAL == STD_ON)
      if(CanTp_TxCfg_GetTAType(TxHdl) == CANTP_TATYPE_FUNCTIONAL)
      {
        CanTp_TxInit(pTpTxState, CANTP_NOTIFY_UNEXP_PDU, CANTP_E_INVALID_TATYPE);
        lReturnValue = E_NOT_OK;
      }
#endif

    }
    else{
      pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_BUFFER_SF;
    }
  }

  if(lReturnValue == E_OK){
    pTpTxState->DataIndex   = 0;
    pTpTxState->DataLength  = SduLength;
    pTpTxState->Timer       = CanTp_TxCfg_GetNCs(TxHdl);

#if(CANTP_SYNC_TRANSMIT == STD_ON)

    CanTp_TxGetBuffer(pTpTxState);
#else

#endif
  }

  return lReturnValue;
}

#if(CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_OFF)

CANTP_LOCAL_INLINE FUNC(PduLengthType, CANTP_CODE) CanTp_RxGetBytesPerBlock(CanTp_RxStatePtrType pTpRxState){
  PduLengthType           lBytesPerBlock;

  lBytesPerBlock = (PduLengthType)CanTp_RxCfg_GetMaxPayloadCF(pTpRxState->RxHdl);

#if(CANTP_CONSTANT_BS == STD_ON)
  if(pTpRxState->FrameType != CANTP_FRAME_FF){
    lBytesPerBlock = (PduLengthType)(lBytesPerBlock * CanTp_Data_CalcBS(pTpRxState->RxHdl));
  }
#endif

  if(lBytesPerBlock > (pTpRxState->DataLength - pTpRxState->DataIndex)){
    lBytesPerBlock = pTpRxState->DataLength - pTpRxState->DataIndex;
  }

  return lBytesPerBlock;
}
#endif

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxGetBufferSF(CanTp_RxStatePtrType pTpRxState){
  PduInfoType             lPduInfo;

  if((pTpRxState->BufferState == CANTP_BUFREQ_OK) && (pTpRxState->ProvidedBufferSize >= pTpRxState->PayloadLength)){
    lPduInfo.SduLength  = pTpRxState->PayloadLength;
    lPduInfo.SduDataPtr = &pTpRxState->Payload[0];
    pTpRxState->BufferState = CanTp_PduRCopyRxData(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl)
   ,                                                  &lPduInfo
   ,                                                  &pTpRxState->ProvidedBufferSize);

    if(pTpRxState->BufferState == CANTP_BUFREQ_OK){
      CanTp_RxInit(pTpRxState, CANTP_NOTIFY_OK, CANTP_E_NO_ERROR, CANTP_RESET_ALL);
    }

    else{
      CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);
    }
  }
#if(CANTP_FAULT_TOLERANT_RXBUFFER == STD_ON)

  else if(pTpRxState->BufferState == CANTP_BUFREQ_OK){
    pTpRxState->BufferState = CANTP_BUFREQ_E_BUSY;
  }
#endif

  else if(pTpRxState->BufferState == CANTP_BUFREQ_E_BUSY){
  }

  else{
    CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);
  }
}

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxGetBufferFF(CanTp_RxStatePtrType pTpRxState){
  PduInfoType             lPduInfo;

#if(CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_ON)

  if(pTpRxState->ProvidedBufferSize >= pTpRxState->DataLength)
#else

  if(pTpRxState->ProvidedBufferSize >= pTpRxState->PayloadLength)
#endif
  {
    lPduInfo.SduLength  = pTpRxState->PayloadLength;
    lPduInfo.SduDataPtr = &pTpRxState->Payload[0];
    pTpRxState->BufferState = CanTp_PduRCopyRxData(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl)
   ,                                                  &lPduInfo
   ,                                                  &pTpRxState->ProvidedBufferSize);
  }
  else{
#if(CANTP_FAULT_TOLERANT_RXBUFFER == STD_ON)

    pTpRxState->BufferState = CANTP_BUFREQ_E_BUSY;
#else

    pTpRxState->BufferState = CANTP_BUFREQ_E_NOT_OK;
#endif
  }

  switch(pTpRxState->BufferState){
    case CANTP_BUFREQ_OK:

      pTpRxState->DataIndex = (PduLengthType)(pTpRxState->DataIndex + pTpRxState->PayloadLength);
      pTpRxState->PayloadLength = 0;

#if(CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_ON)

      pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_CTS;
#else
      {
        PduLengthType  lBytesPerBlock;
        lBytesPerBlock = CanTp_RxGetBytesPerBlock(pTpRxState);

        if(pTpRxState->ProvidedBufferSize >= lBytesPerBlock)
        {
          pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_CTS;
        }
        else
        {
          pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_WT;
        }
      }
#endif

      pTpRxState->Timer        = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);
      CanTp_RxTransmitFrame(pTpRxState);
      break;

    case CANTP_BUFREQ_E_BUSY:

      pTpRxState->Timer        = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);
      pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_WT;
      CanTp_RxTransmitFrame(pTpRxState);
      break;

    case CANTP_BUFREQ_E_OVFL:

      pTpRxState->Timer        = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);
      pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_OVFL;
      CanTp_RxTransmitFrame(pTpRxState);
      break;

    case CANTP_BUFREQ_E_NOT_OK:
    default:

      CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);
      break;
  }
}

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxGetBufferCF(CanTp_RxStatePtrType pTpRxState){
  PduInfoType             lPduInfo;

#if(CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_ON)

  lPduInfo.SduLength  = pTpRxState->PayloadLength;
  lPduInfo.SduDataPtr = &(pTpRxState->Payload[0]);
  pTpRxState->BufferState = CanTp_PduRCopyRxData(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl)
   ,                                                &lPduInfo
   ,                                                &pTpRxState->ProvidedBufferSize);
#else

  if(pTpRxState->BufferState == CANTP_BUFREQ_OK){
    if(pTpRxState->ProvidedBufferSize >= pTpRxState->PayloadLength){
      lPduInfo.SduLength  = pTpRxState->PayloadLength;
      lPduInfo.SduDataPtr = &pTpRxState->Payload[0];
      pTpRxState->BufferState = CanTp_PduRCopyRxData(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl)
   ,                                                    &lPduInfo
   ,                                                    &pTpRxState->ProvidedBufferSize);
    }
    else{
      pTpRxState->BufferState = CANTP_BUFREQ_E_NOT_OK;
    }
  }
#endif

  switch(pTpRxState->BufferState){
    case CANTP_BUFREQ_OK:
      pTpRxState->DataIndex = (PduLengthType)(pTpRxState->DataIndex + pTpRxState->PayloadLength);
      pTpRxState->PayloadLength = 0;

      if(pTpRxState->DataIndex >= pTpRxState->DataLength)
      {
        CanTp_RxInit(pTpRxState, CANTP_NOTIFY_OK, CANTP_E_NO_ERROR, CANTP_RESET_ALL);
      }
      else
      {
        pTpRxState->ChannelState = CANTP_RXSTATE_WAIT_CF;

        if(pTpRxState->BlocksizeCounter > 0u)
        {
          pTpRxState->BlocksizeCounter--;
          if(pTpRxState->BlocksizeCounter == 0u)
          {
#if(CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_ON)

            pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_CTS;

            pTpRxState->Timer        = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);
            CanTp_RxTransmitFrame(pTpRxState);
#else
            PduLengthType  lBytesPerBlock;

            lBytesPerBlock = CanTp_RxGetBytesPerBlock(pTpRxState);

            if(pTpRxState->ProvidedBufferSize >= lBytesPerBlock)
            {
              pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_CTS;
            }
            else
            {
              lPduInfo.SduLength = 0;
              pTpRxState->BufferState = (CanTp_BufferStateType)CanTp_PduRCopyRxData(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl)
   ,                                                                                   &lPduInfo
   ,                                                                                   &pTpRxState->ProvidedBufferSize);

              pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_WT;
              if(pTpRxState->BufferState == CANTP_BUFREQ_OK)
              {
                if(pTpRxState->ProvidedBufferSize >= lBytesPerBlock)
                {
                  pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_CTS;
                }

              }
              else
              {
                if(pTpRxState->BufferState != CANTP_BUFREQ_E_BUSY)
                {
                  CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);
                }

              }
            }

            if(pTpRxState->ChannelState != CANTP_RXSTATE_IDLE)
            {
              pTpRxState->Timer = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);
              CanTp_RxTransmitFrame(pTpRxState);
            }

#endif
          }

        }

      }
      break;

    case CANTP_BUFREQ_E_BUSY:
#if(CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_OFF)

      if(pTpRxState->BlocksizeCounter == 1u)
      {
        pTpRxState->Timer        = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);
        pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_WT;
        CanTp_RxTransmitFrame(pTpRxState);
      }
      else
      {
        CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);
      }
      break;
#endif
    case CANTP_BUFREQ_E_OVFL:
    case CANTP_BUFREQ_E_NOT_OK:
    default:

      CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);
      break;
  }
}

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxGetBufferFCWait(CanTp_RxStatePtrType pTpRxState){
  PduInfoType             lPduInfo;

  if((pTpRxState->BufferState == CANTP_BUFREQ_OK) && (pTpRxState->PayloadLength != 0u) ){
#if(CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_ON)
    if(pTpRxState->ProvidedBufferSize >= pTpRxState->DataLength)
#else
    if(pTpRxState->ProvidedBufferSize >= pTpRxState->PayloadLength)
#endif
    {
      lPduInfo.SduLength  = pTpRxState->PayloadLength;
      lPduInfo.SduDataPtr = &pTpRxState->Payload[0];
      pTpRxState->BufferState = CanTp_PduRCopyRxData(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl)
   ,                                                    &lPduInfo
   ,                                                    &pTpRxState->ProvidedBufferSize);
    }
    else{
      pTpRxState->BufferState = CANTP_BUFREQ_E_BUSY;
    }
  }

  switch(pTpRxState->BufferState){
    case CANTP_BUFREQ_OK:

      pTpRxState->DataIndex = (pTpRxState->DataIndex + pTpRxState->PayloadLength);
      pTpRxState->PayloadLength = 0;

#if(CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_ON)

      pTpRxState->Timer        = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);
      pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_CTS;
      CanTp_RxTransmitFrame(pTpRxState);
#else

      if(pTpRxState->DataIndex >= pTpRxState->DataLength)
      {
        CanTp_RxInit(pTpRxState, CANTP_NOTIFY_OK, CANTP_E_NO_ERROR, CANTP_RESET_ALL);
      }
      else
      {
        PduLengthType  lBytesPerBlock;

        lBytesPerBlock = CanTp_RxGetBytesPerBlock(pTpRxState);

        if(pTpRxState->ProvidedBufferSize >= lBytesPerBlock)
        {
          pTpRxState->Timer        = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);
          pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_CTS;
          CanTp_RxTransmitFrame(pTpRxState);
        }
        else
        {
          pTpRxState->BufferState = CANTP_BUFREQ_E_BUSY;
        }
      }
#endif
      break;

    case CANTP_BUFREQ_E_BUSY:

      break;

    default:

      CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);
      break;
  }
}

#if((CANTP_SUPPORT_STANDARD_ADDRESSING == STD_ON) || (CANTP_SUPPORT_NORMALFIXED_ADDRESSING == STD_ON) || (CANTP_GENERIC_CONNECTIONS == STD_ON))

CANTP_LOCAL_INLINE FUNC(PduIdType, CANTP_CODE) CanTp_Cfg_GetSduHdlByRxPduOnly (PduIdType RxPduId, uint8 FrameType){
  PduIdType lSduHdl = CANTP_INVALID_HDL;

  CANTP_DUMMY_STATEMENT(RxPduId);

  if( (FrameType == CANTP_PCI_TYPE_FC) && (CanTp_CanIfRxPduHasTxSduRef(RxPduId)) ){
    lSduHdl = (PduIdType)CanTp_GetTxSduCfgInd(CanTp_GetTxSduCfgIndStartIdxOfRxPduMap(RxPduId));
  }
#if(CANTP_RXSDUCFGIND == STD_ON)
  else if( (FrameType != CANTP_PCI_TYPE_FC) && (CanTp_CanIfRxPduHasRxSduRef(RxPduId)) ){
    lSduHdl = (PduIdType)CanTp_GetRxSduCfgInd(CanTp_GetRxSduCfgIndStartIdxOfRxPduMap(RxPduId));
  }
#endif
  else{
  }

  return lSduHdl;
}
#endif

#if((CANTP_SUPPORT_EXTENDED_ADDRESSING == STD_ON) || (CANTP_SUPPORT_MIXED11_ADDRESSING == STD_ON) || (CANTP_SUPPORT_MIXED29_ADDRESSING == STD_ON))

CANTP_LOCAL_INLINE FUNC(PduIdType, CANTP_CODE) CanTp_Cfg_GetSduHdlByRxPduAddress (PduIdType RxPduId, uint8 FrameType, uint8 Address){
  PduIdType lSduCurrentHdl;
  PduIdType lSduReturnHdl = CANTP_INVALID_HDL;

  CANTP_DUMMY_STATEMENT(RxPduId);

  if(FrameType == CANTP_PCI_TYPE_FC){
#if(CANTP_TXSDUCFGIND == STD_ON)
    CanTp_TxSduCfgIndIterType lTxduIndirectionIndex;

    for(lTxduIndirectionIndex = (PduIdType)CanTp_GetTxSduCfgIndStartIdxOfRxPduMap(RxPduId);
         lTxduIndirectionIndex < (PduIdType)CanTp_GetTxSduCfgIndEndIdxOfRxPduMap(RxPduId);
         lTxduIndirectionIndex++){
      lSduCurrentHdl = (PduIdType)CanTp_GetTxSduCfgInd(lTxduIndirectionIndex);

      if(CanTp_TxCfg_GetRxFcAddress(lSduCurrentHdl) == Address)
      {
        lSduReturnHdl = lSduCurrentHdl;
        break;
      }
    }
#endif
  }
  else{
#if(CANTP_RXSDUCFGIND == STD_ON)
    CanTp_RxSduCfgIndIterType lRxduIndirectionIndex;

    for(lRxduIndirectionIndex = (PduIdType)CanTp_GetRxSduCfgIndStartIdxOfRxPduMap(RxPduId);
         lRxduIndirectionIndex < (PduIdType)CanTp_GetRxSduCfgIndEndIdxOfRxPduMap(RxPduId);
         lRxduIndirectionIndex++){
      lSduCurrentHdl = (PduIdType)CanTp_GetRxSduCfgInd(lRxduIndirectionIndex);

      if(CanTp_RxCfg_GetRxAddress(lSduCurrentHdl) == Address)
      {
        lSduReturnHdl = lSduCurrentHdl;
        break;
      }
    }
#endif
  }

  return lSduReturnHdl;
}
#endif

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxInitState(CanTp_RxStatePtrType pTpRxState){
  pTpRxState->RxHdl                = CANTP_INVALID_HDL;
  pTpRxState->FrameType            = CANTP_FRAME_INVALID;
  pTpRxState->ChannelState         = CANTP_RXSTATE_IDLE;
  pTpRxState->Timer                = 0;
  pTpRxState->DataLength           = 0;
  pTpRxState->DataIndex            = 0;
  pTpRxState->ProvidedBufferSize   = 0;
  pTpRxState->WFTCounter           = 0;
  pTpRxState->BufferState          = CANTP_BUFREQ_OK;
  pTpRxState->BlocksizeCounter     = 0;
  pTpRxState->PayloadLength        = 0;
  pTpRxState->InitalDLC            = 0;
  pTpRxState->ExpectedSN           = 0;
#if(( CANTP_ONLY_NOTIFY_INFORMED_APPL == STD_ON ) || ( CANTP_RC == STD_ON ))
  pTpRxState->ApplState            = CANTP_APPL_NOT_INFORMED;
#endif
#if(CANTP_GENERIC_CONNECTIONS == STD_ON)
  pTpRxState->SduMetadataLength    = 0;
#if(CANTP_MAX_PDU_METADATA_LENGTH != 0)
  pTpRxState->FcPduMetadataLength  = 0;
#endif
#endif

}

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_TxInitState(CanTp_TxStatePtrType pTpTxState){
  pTpTxState->TxHdl             = CANTP_INVALID_HDL;
#if(CANTP_STMIN_BY_APPL == STD_ON)
  pTpTxState->TxSduSnv          = CanTp_Cfg_GetNumTxSduIds();
#endif
  pTpTxState->ChannelState          = CANTP_TXSTATE_IDLE;
  pTpTxState->Timer                 = 0;
  pTpTxState->DataLength            = 0;
  pTpTxState->DataIndex             = 0;
  pTpTxState->BufferState           = CANTP_BUFREQ_OK;
  pTpTxState->BlocksizeCounter      = 0;
  pTpTxState->STmin                 = 0;
  pTpTxState->STminTimer            = 0;
  pTpTxState->PayloadLength         = 0;
  pTpTxState->SeqNumber             = 0;
#if(CANTP_USE_ONLY_FIRST_FC == STD_ON)
  pTpTxState->BS                    = 0;
  pTpTxState->FirstFCReceived       = FALSE;
#endif
  pTpTxState->FCLength              = 0;
#if(CANTP_GENERIC_CONNECTIONS == STD_ON)
  pTpTxState->SduMetadataLength     = 0;
#if(CANTP_MAX_PDU_METADATA_LENGTH != 0)
  pTpTxState->DataPduMetadataLength = 0;
#endif
#endif
}

CANTP_LOCAL_INLINE FUNC(CanTp_RxStatePtrType, CANTP_CODE) CanTp_RxGetFreeChannelPtr(PduIdType RxHdl
   ,                                                                                   P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo
   ,                                                                                   P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo){
  CanTp_RxStatePtrType pTpRxState = (CanTp_RxStatePtrType)NULL_PTR;

  if(CanTp_RxChannelIsIdle(RxHdl)){
#if(CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
    PduIdType            lChannelHdl;

    for(lChannelHdl = 0; lChannelHdl < CanTp_Cfg_GetNumRxChannels(); lChannelHdl++){
      if(CanTp_Data_RxState(lChannelHdl).ChannelState == CANTP_RXSTATE_IDLE)
      {
        CanTp_NumRxChannelsAvail--;
        CanTp_Data_RxChannelMap(RxHdl) = lChannelHdl;
        pTpRxState = &CanTp_Data_RxState(lChannelHdl);
        pTpRxState->RxHdl = RxHdl;

        break;
      }
    }
#else

    pTpRxState = &CanTp_Data_RxState(RxHdl);
    pTpRxState->RxHdl = RxHdl;
#endif
  }

#if(CANTP_GENERIC_CONNECTIONS == STD_ON)
  if(pTpRxState != NULL_PTR){
    CanTp_Util_RxExtractSduMetadataInfo(pTpRxState, pPayloadInfo, pMetadataInfo);
  }
#else
  CANTP_DUMMY_STATEMENT(pPayloadInfo);
  CANTP_DUMMY_STATEMENT(pMetadataInfo);
#endif

  return pTpRxState;
}

CANTP_LOCAL_INLINE FUNC(CanTp_RxStatePtrType, CANTP_CODE) CanTp_RxGetActiveChannelPtr(PduIdType RxHdl){
  CanTp_RxStatePtrType pTpRxState = (CanTp_RxStatePtrType)NULL_PTR;

  if(!CanTp_RxChannelIsIdle(RxHdl)){
    pTpRxState = CanTp_RxGetChannelPtr(RxHdl);
  }

  return pTpRxState;
}

CANTP_LOCAL_INLINE FUNC(CanTp_TxStatePtrType, CANTP_CODE) CanTp_TxGetFreeChannelPtr(PduIdType TxHdl
   ,  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpTxInfoPtr){
  CanTp_TxStatePtrType pTpTxState = (CanTp_TxStatePtrType)NULL_PTR;

  if(CanTp_TxChannelIsIdle(TxHdl)){
#if(CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
    PduIdType            lChannelHdl;

    for(lChannelHdl = 0; lChannelHdl < CanTp_Cfg_GetNumTxChannels(); lChannelHdl++){
      if(CanTp_Data_TxState(lChannelHdl).ChannelState == CANTP_TXSTATE_IDLE)
      {
        CanTp_NumTxChannelsAvail--;
        CanTp_Data_TxChannelMap(TxHdl) = lChannelHdl;
        pTpTxState = &CanTp_Data_TxState(lChannelHdl);
        pTpTxState->TxHdl = TxHdl;
        break;
      }
    }
#else

    pTpTxState = &CanTp_Data_TxState(TxHdl);
    pTpTxState->TxHdl = TxHdl;
#endif
  }

#if(CANTP_GENERIC_CONNECTIONS == STD_ON)
  if(pTpTxState != NULL_PTR){
    CanTp_Util_TxExtractSduMetadataInfo(pTpTxState, CanTpTxInfoPtr);
  }
#else
  CANTP_DUMMY_STATEMENT(CanTpTxInfoPtr);
#endif

  return pTpTxState;
}

CANTP_LOCAL_INLINE FUNC(CanTp_TxStatePtrType, CANTP_CODE) CanTp_TxGetActiveChannelPtr(PduIdType TxHdl){
  CanTp_TxStatePtrType pTpTxState = (CanTp_TxStatePtrType)NULL_PTR;

  if(!CanTp_TxChannelIsIdle(TxHdl)){
    pTpTxState = CanTp_TxGetChannelPtr(TxHdl);
  }

  return pTpTxState;
}

#if(CANTP_TRANSMITFCTOFLOLAYERFCTS == STD_ON)

CANTP_LOCAL_INLINE FUNC(Std_ReturnType, CANTP_CODE) CanTp_LoLayerTransmit(CanTp_DirectionType Direction
   ,                                                                         PduIdType SduHdl
   ,                                                                         PduIdType LoLayerTxPduId
   ,                                                                         P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pTpData){
  uint8 lLoLayerIdx;
  Std_ReturnType lResult;

  if(Direction == CANTP_DIR_TX){
    lLoLayerIdx = CanTp_TxCfg_GetLoLayerIdx(SduHdl);
  }
  else{
    lLoLayerIdx = CanTp_RxCfg_GetLoLayerIdx(SduHdl);
  }

  lResult = CanTp_GetTransmitFctOfLoLayerFcts(lLoLayerIdx)(LoLayerTxPduId, pTpData);

  return lResult;
}
#endif

#if(CANTP_CANCELTRANSMITFCTOFLOLAYERFCTS == STD_ON)

CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_LoLayerCancelTransmit(CanTp_DirectionType Direction, PduIdType SduHdl, PduIdType LoLayerTxPduId){
  uint8 lLoLayerIdx;

  if(Direction == CANTP_DIR_TX){
    lLoLayerIdx = CanTp_TxCfg_GetLoLayerIdx(SduHdl);
  }
  else{
    lLoLayerIdx = CanTp_RxCfg_GetLoLayerIdx(SduHdl);
  }

  if(CanTp_GetCancelTransmitFctOfLoLayerFcts(lLoLayerIdx) != NULL_PTR){
    (void)CanTp_GetCancelTransmitFctOfLoLayerFcts(lLoLayerIdx)(LoLayerTxPduId);
  }
}
#endif

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_CanIfRxIndication(PduIdType  SduHdl
   ,                                                          uint8      FrameType
   ,                                                          P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo
   ,                                                          P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo){
  CANTP_DUMMY_STATEMENT(SduHdl);
  CANTP_DUMMY_STATEMENT(pMetadataInfo);

  if(CANTP_PCI_TYPE_FC != FrameType){
#if(CANTP_PADDING_SUPPORT_REQUIRED == STD_ON)
    uint8 lPaddingLength;

    lPaddingLength = CanTp_Util_GetPaddingLength((uint8)pPayloadInfo->SduLength, CanTp_RxCfg_HasPaddingActivation(SduHdl), CanTp_RxCfg_GetCanType(SduHdl));
    if(pPayloadInfo->SduLength != lPaddingLength){
      CanTp_DetReportError(CANTP_SID_RXINDICATION, CANTP_E_PARAM_CONFIG)
    }
    else
#endif
    {
      CanTp_EnterCritical();

#if(CANTP_RX_HAS_HALF_DUPLEX == STD_ON)
      if(CanTp_RxCheckChannelMode(SduHdl) == E_OK)
#endif
      {
        {
          CanTp_RxStatePtrType pTpRxState;
          pTpRxState = CanTp_RxGetActiveChannelPtr(SduHdl);

          if(pTpRxState == NULL_PTR)
          {
            if((FrameType == CANTP_PCI_TYPE_SF) || (FrameType == CANTP_PCI_TYPE_FF))
            {
              pTpRxState = CanTp_RxGetFreeChannelPtr(SduHdl, pPayloadInfo, pMetadataInfo);
            }

          }

          if(pTpRxState != NULL_PTR)
          {
#if(CANTP_GENERIC_CONNECTIONS == STD_ON)
            if(CanTp_Util_RxSduMetadataFromDataPduMatch(pTpRxState, pPayloadInfo, pMetadataInfo) == TRUE)
#endif
            {
              switch(FrameType)
              {
                case CANTP_PCI_TYPE_SF:
#if(CANTP_GENERIC_CONNECTIONS == STD_ON)
                  if((!CanTp_RxCfg_IsGenericConnection(pTpRxState->RxHdl)) ||
                      (pTpRxState->ChannelState == CANTP_RXSTATE_IDLE))
#endif
                  {
                    CanTp_CanIfRxIndicationSF(pTpRxState, pPayloadInfo);
                  }
                  break;
                case CANTP_PCI_TYPE_FF:
#if(CANTP_GENERIC_CONNECTIONS == STD_ON)
                  if((!CanTp_RxCfg_IsGenericConnection(pTpRxState->RxHdl)) ||
                      (pTpRxState->ChannelState == CANTP_RXSTATE_IDLE))
#endif
                  {
                    CanTp_CanIfRxIndicationFF(pTpRxState, pPayloadInfo);
                  }
                  break;

                case CANTP_PCI_TYPE_CF:
                  CanTp_CanIfRxIndicationCF(pTpRxState, pPayloadInfo);
                  break;

                default:

                  break;
              }
            }
          }

        }
      }

      CanTp_LeaveCritical();
    }
  }

  else{
#if(CANTP_PADDING_SUPPORT_REQUIRED == STD_ON)
    uint8  lPaddingLength;

    lPaddingLength = CanTp_Util_GetPaddingLength((uint8)pPayloadInfo->SduLength, CanTp_TxCfg_HasPaddingActivation(SduHdl), CanTp_TxCfg_GetCanType(SduHdl));
    if(pPayloadInfo->SduLength != lPaddingLength ){
      CanTp_DetReportError(CANTP_SID_RXINDICATION, CANTP_E_PARAM_CONFIG)
    }
    else
#endif
    {
      CanTp_TxStatePtrType pTpTxState;

      CanTp_EnterCritical();

      pTpTxState = CanTp_TxGetActiveChannelPtr(SduHdl);
      if(pTpTxState != NULL_PTR)
      {
#if(CANTP_GENERIC_CONNECTIONS == STD_ON)
        if(CanTp_Util_TxSduMetadataFromFcPduMatch(pTpTxState, pPayloadInfo, pMetadataInfo) == TRUE)
#endif
        {
          CanTp_CanIfRxIndicationFC(pTpTxState, pPayloadInfo);
        }
      }

      CanTp_LeaveCritical();
    }
  }
}

#if(CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_CanIfTxConfirmation(CanTp_TxStatePtrType pTpTxState){
  switch(pTpTxState->ChannelState){
    case CANTP_TXSTATE_WAIT_TXCONF_SF:

      CanTp_TxInit(pTpTxState, CANTP_NOTIFY_OK, CANTP_E_NO_ERROR);
      break;

    case CANTP_TXSTATE_WAIT_TXCONF_FF:

#if(CANTP_USE_ONLY_FIRST_FC == STD_ON)
      pTpTxState->FirstFCReceived = FALSE;
#endif
      pTpTxState->Timer        = CanTp_TxCfg_GetNBs(pTpTxState->TxHdl);
      pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_FC;
      break;

    case CANTP_TXSTATE_WAIT_TXCONF_CF:
      if(pTpTxState->DataIndex < pTpTxState->DataLength)
      {
        pTpTxState->SeqNumber  = (uint8)((pTpTxState->SeqNumber + 1u) & CANTP_PCI_SN_MASK);

        if(pTpTxState->BlocksizeCounter != 0u)
        {
          pTpTxState->BlocksizeCounter--;
          if(pTpTxState->BlocksizeCounter == 0u)
          {
            pTpTxState->Timer        = CanTp_TxCfg_GetNBs(pTpTxState->TxHdl);
            pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_FC;
          }
        }

        if(pTpTxState->ChannelState != CANTP_TXSTATE_WAIT_FC)
        {
          pTpTxState->Timer        = CanTp_TxCfg_GetNCs(pTpTxState->TxHdl);
          {
#if(CANTP_STMIN_BY_APPL == STD_ON)
            boolean lSeparationTimeByAppl;

            pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_STMIN_APPL;

            CanTp_LeaveCritical();
            lSeparationTimeByAppl = CanTp_ApplStartSeparationTime(pTpTxState->TxSduSnv, pTpTxState->STmin);
            CanTp_EnterCritical();

            if( (lSeparationTimeByAppl    == FALSE) &&
                 (pTpTxState->ChannelState == CANTP_TXSTATE_WAIT_STMIN_APPL) )
#endif
            {
              if(pTpTxState->STmin == 0u)
              {
                pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_BUFFER_CF;
                CanTp_TxGetBuffer_ISR(pTpTxState)
              }
              else
              {
                pTpTxState->STminTimer   = CanTp_TxGetStminTimerFromStminValue(pTpTxState->STmin);
                pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_STMIN_INTERN;
              }
            }

          }

        }

      }

      else
      {
        CanTp_TxInit(pTpTxState, CANTP_NOTIFY_OK, CANTP_E_NO_ERROR);
      }
      break;

    default:
      CanTp_DetReportError(CANTP_SID_TXCONFIRMATION, CANTP_E_INVALID_TX_STATE)
      break;
  }

  if(pTpTxState->FCLength != 0u){
    PduInfoType PduInfo;

    PduInfo.SduDataPtr   = pTpTxState->FCData;
    PduInfo.SduLength    = pTpTxState->FCLength;
    pTpTxState->FCLength = 0;
    CanTp_CanIfRxIndicationFC(pTpTxState, &PduInfo);
  }
}
#endif

#if(CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_CanIfTxConfirmationFC(CanTp_RxStatePtrType pTpRxState){
  switch(pTpRxState->ChannelState){
    case CANTP_RXSTATE_WAIT_TXCONFFC_CTS:

      pTpRxState->WFTCounter   = CanTp_RxCfg_GetWFTmax(pTpRxState->RxHdl);
      pTpRxState->Timer        = CanTp_RxCfg_GetNCr(pTpRxState->RxHdl);
      pTpRxState->ChannelState = CANTP_RXSTATE_WAIT_CF;
      break;

    case CANTP_RXSTATE_WAIT_TXCONFFC_WT:

      CanTp_DetAssert((pTpRxState->WFTCounter >= 1u), CANTP_SID_TXCONFIRMATION, (CANTP_E_PARAM_CONFIG))
      pTpRxState->WFTCounter--;
      pTpRxState->BufferState  = CANTP_BUFREQ_E_BUSY;
      pTpRxState->Timer        = CanTp_RxCfg_GetNBr(pTpRxState->RxHdl);
      pTpRxState->ChannelState = CANTP_RXSTATE_WAIT_NEXT_FCWAIT;
      break;

    case CANTP_RXSTATE_WAIT_TXCONFFC_OVFL:

      CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);
      break;

    default:
      CanTp_DetReportError(CANTP_SID_TXCONFIRMATION, CANTP_E_INVALID_RX_STATE)
      break;
  }
}
#endif

CANTP_LOCAL FUNC(CanTp_TxResultType, CANTP_CODE) CanTp_CanIfTransmitFrame(P2CONST(CanTp_PduTxInfoType, AUTOMATIC, CANTP_APPL_DATA) pPduTxData
   ,                                                                         P2VAR(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pTpData){
  CanTp_TxResultType  lCanIfResult;

#if(CANTP_PADDING_SUPPORT_REQUIRED == STD_ON)

#if(CANTP_HAVE_PADDING_BYTE == STD_ON)
  while( pTpData->SduLength < (PduLengthType)pPduTxData->PaddingLength ){
    pTpData->SduDataPtr[pTpData->SduLength] = CANTP_PADDING_PATTERN;
    pTpData->SduLength++;
  }
#else

  pTpData->SduLength = (PduLengthType)pPduTxData->PaddingLength;
#endif
#endif

#if(CANTP_MAX_PDU_METADATA_LENGTH != 0)
  if(pPduTxData->PduMetadataLength != 0u){
    CanTp_Util_MemCpy(&pTpData->SduDataPtr[pTpData->SduLength]
   ,                     pPduTxData->PduMetadata
   ,                     pPduTxData->PduMetadataLength);
    pTpData->SduLength += pPduTxData->PduMetadataLength;
  }
#endif

  if(CanTp_Data_TxSemaphore(pPduTxData->TxConfPduId).Handle == CANTP_INVALID_HDL){
    lCanIfResult = CanTp_CanIfTransmit(pPduTxData->SduDirection, pPduTxData->SduHdl, pPduTxData->TxPduId, pTpData);

    if(lCanIfResult == CANTP_TX_OK){
      CanTp_Data_TxSemaphore(pPduTxData->TxConfPduId).Direction = pPduTxData->SduDirection;
      CanTp_Data_TxSemaphore(pPduTxData->TxConfPduId).Handle    = pPduTxData->SduHdl;

      CanTp_ApplFrameTransmission(pPduTxData->TxPduId, pTpData)
    }

  }

  else{
    lCanIfResult = CANTP_TX_BUSY;

#if(CANTP_TRANSMIT_QUEUE == STD_ON)

    if(!CanTp_TxQueueIsFull(pPduTxData->TxConfPduId)){
      CanTp_TxQueueEntryWritePos(pPduTxData->TxConfPduId).PduId = pPduTxData->TxPduId;
      CanTp_TxQueueEntryWritePos(pPduTxData->TxConfPduId).SduHandle = pPduTxData->SduHdl;
      CanTp_TxQueueEntryWritePos(pPduTxData->TxConfPduId).SduDirection = pPduTxData->SduDirection;
      CanTp_TxQueueEntryWritePos(pPduTxData->TxConfPduId).SduLength = pTpData->SduLength;
      CanTp_Util_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(CanTp_TxQueueEntryWritePos(pPduTxData->TxConfPduId).SduData)
   ,                       (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(pTpData->SduDataPtr), (uint16)pTpData->SduLength);

      CanTp_Data_TxQueue(pPduTxData->TxConfPduId).WritePos = (uint8)((CanTp_Data_TxQueue(pPduTxData->TxConfPduId).WritePos + 1u) & CANTP_TX_QUEUE_MASK);
      lCanIfResult = CANTP_TX_OK;
    }

#endif
  }

  return lCanIfResult;
}

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_RxInit(CanTp_RxStatePtrType pTpRxState, CanTp_NotificationType NotifyCode, uint8 DetError, CanTp_ResetControlType ResetRequest){
#if(CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)

  uint8  lIndicationPduR = 0;
  PduIdType lRxHdl = pTpRxState->RxHdl;

#if(CANTP_GENERIC_CONNECTIONS == STD_ON)
  uint8 lSduMetadataLength   = pTpRxState->SduMetadataLength;
#if(CANTP_MAX_PDU_METADATA_LENGTH != 0)
  uint8 lFcPduMetadataLength = pTpRxState->FcPduMetadataLength;
#endif
#endif

  if((pTpRxState->ChannelState & CANTP_RXSTATE_WAIT_TXCONFFC_ANY) == CANTP_RXSTATE_WAIT_TXCONFFC_ANY){
#if(CANTP_TRANSMIT_QUEUE == STD_ON)
    CanTp_TxQueueCancel(lRxHdl, CANTP_DIR_RX);
#else

    CanTp_Data_TxSemaphore( CanTp_RxCfg_GetTxFcConfPduId(lRxHdl) ).Handle    = CANTP_INVALID_HDL;
    CanTp_Data_TxSemaphore( CanTp_RxCfg_GetTxFcConfPduId(lRxHdl) ).Direction = CANTP_DIR_NONE;
    CanTp_CanIfCancelTransmit(CANTP_DIR_RX, lRxHdl, CanTp_RxCfg_GetLoLayerTxFcPduId(lRxHdl));
#endif
  }

  if(NotifyCode != CANTP_NOTIFY_NORESULT){
#if(CANTP_ONLY_NOTIFY_INFORMED_APPL == STD_ON)
    if(pTpRxState->ApplState == CANTP_APPL_INFORMED)
#endif
    {
      lIndicationPduR = 1;
    }
  }

  CanTp_RxInitState(pTpRxState);

  if(ResetRequest == CANTP_RESET_BUT_KEEP_MAPPING){
    pTpRxState->RxHdl = lRxHdl;

#if(CANTP_GENERIC_CONNECTIONS == STD_ON)
    pTpRxState->SduMetadataLength   = lSduMetadataLength;
#if(CANTP_MAX_PDU_METADATA_LENGTH != 0)
    pTpRxState->FcPduMetadataLength = lFcPduMetadataLength;
#endif
#endif

  }
#if(CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
  else{
    CanTp_Data_RxChannelMap(lRxHdl) = CANTP_INVALID_HDL;
    CanTp_NumRxChannelsAvail++;
  }
#endif

  if(lIndicationPduR != 0u){
    CanTp_PduRRxIndication(CanTp_RxCfg_GetPduRRxSduId(lRxHdl), NotifyCode);
  }

  if(DetError != CANTP_E_NO_ERROR){
    CanTp_DetReportError(CANTP_SID_RXINIT, DetError)
  }

#else
CANTP_DUMMY_STATEMENT(pTpRxState);
CANTP_DUMMY_STATEMENT(NotifyCode);
CANTP_DUMMY_STATEMENT(DetError);
CANTP_DUMMY_STATEMENT(ResetRequest);
#endif
}

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxInit(CanTp_TxStatePtrType pTpTxState, CanTp_NotificationType NotifyCode, uint8 DetError){
#if(CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)

  PduIdType lTxHdl = pTpTxState->TxHdl;
  CANTP_DUMMY_STATEMENT(lTxHdl);

  if((pTpTxState->ChannelState & CANTP_TXSTATE_WAIT_TXCONF_ANY) == CANTP_TXSTATE_WAIT_TXCONF_ANY){
#if(CANTP_TRANSMIT_QUEUE == STD_ON)

    CanTp_TxQueueCancel(lTxHdl, CANTP_DIR_TX);
#else

    CanTp_Data_TxSemaphore( CanTp_TxCfg_GetTxConfPduId(lTxHdl) ).Handle = CANTP_INVALID_HDL;
    CanTp_Data_TxSemaphore( CanTp_TxCfg_GetTxConfPduId(lTxHdl) ).Direction = CANTP_DIR_NONE;
    CanTp_CanIfCancelTransmit(CANTP_DIR_TX, lTxHdl, CanTp_TxCfg_GetLoLayerTxPduId(lTxHdl));
#endif
  }

  CanTp_TxInitState(pTpTxState);
#if(CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
  CanTp_Data_TxChannelMap(lTxHdl) = CANTP_INVALID_HDL;
  CanTp_NumTxChannelsAvail++;
#endif

  CanTp_PduRTxConfirmation(CanTp_TxCfg_GetPduRTxSduId(lTxHdl), NotifyCode);

  if(DetError != CANTP_E_NO_ERROR){
    CanTp_DetReportError(CANTP_SID_TXINIT, DetError)
  }

#else
  CANTP_DUMMY_STATEMENT(pTpTxState);
  CANTP_DUMMY_STATEMENT(NotifyCode);
  CANTP_DUMMY_STATEMENT(DetError);
#endif
}

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_ResetChannels(void){
  {
    PduIdType  lSduHdl;

    for(lSduHdl = 0; lSduHdl < CanTp_Cfg_GetNumRxHdls(); lSduHdl++){
#if(CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)

      CanTp_Data_RxChannelMap(lSduHdl) = CANTP_INVALID_HDL;
#endif

#if(CANTP_ENABLE_CHANGE_PARAM == STD_ON)

      CanTp_Data_DynFcParam(lSduHdl).BS    = CanTp_RxCfg_GetBS(lSduHdl);
      CanTp_Data_DynFcParam(lSduHdl).STmin = CanTp_RxCfg_GetSTmin(lSduHdl);
#endif
    }

#if(CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)

    for(lSduHdl = 0; lSduHdl < CanTp_Cfg_GetNumTxHdls(); lSduHdl++){
      CanTp_Data_TxChannelMap(lSduHdl) = CANTP_INVALID_HDL;
    }
#endif
  }

  {
    PduIdType  lChannelHdl;

    for(lChannelHdl = 0; lChannelHdl < CanTp_Cfg_GetNumRxChannels(); lChannelHdl++){
      CanTp_RxInitState(&CanTp_Data_RxState(lChannelHdl));
    }

    for(lChannelHdl = 0; lChannelHdl < CanTp_Cfg_GetNumTxChannels(); lChannelHdl++){
      CanTp_TxInitState(&CanTp_Data_TxState(lChannelHdl));
    }
  }

#if(CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)

  CanTp_NumRxChannelsAvail = CanTp_Cfg_GetNumRxChannels();
  CanTp_NumTxChannelsAvail = CanTp_Cfg_GetNumTxChannels();
#endif

  {
    PduIdType  lTxConfHdl;

    for(lTxConfHdl = 0; lTxConfHdl < CanTp_Cfg_GetNumTxConfPdus(); lTxConfHdl++){
      CanTp_Data_TxSemaphore(lTxConfHdl).Handle     = CANTP_INVALID_HDL;
      CanTp_Data_TxSemaphore(lTxConfHdl).Direction  = CANTP_DIR_NONE;

#if(CANTP_TRANSMIT_QUEUE == STD_ON)
      {
        uint8 lQueueCntr;

        CanTp_Data_TxQueue(lTxConfHdl).ReadPos = 0;
        CanTp_Data_TxQueue(lTxConfHdl).WritePos = 0;

        for(lQueueCntr = 0; lQueueCntr < CANTP_TX_QUEUE_SIZE; lQueueCntr++)
        {
          CanTp_Data_TxQueue(lTxConfHdl).Entries[lQueueCntr].SduHandle = CANTP_INVALID_HDL;
        }
      }
#endif
    }
  }
}

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_RxGetBuffer(CanTp_RxStatePtrType pTpRxState){
  PduInfoType             lPduInfo;

  if(pTpRxState->BufferState == CANTP_BUFREQ_E_BUSY){
    lPduInfo.SduLength = 0;
    pTpRxState->BufferState = (CanTp_BufferStateType)CanTp_PduRCopyRxData(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl)
   ,                                                                          &lPduInfo
   ,                                                                          &pTpRxState->ProvidedBufferSize);
  }

  switch(pTpRxState->ChannelState){
    case CANTP_RXSTATE_WAIT_BUFFER_SF:

      CanTp_RxGetBufferSF(pTpRxState);
      break;

    case CANTP_RXSTATE_WAIT_BUFFER_FF:

      CanTp_RxGetBufferFF(pTpRxState);
      break;

    case CANTP_RXSTATE_WAIT_BUFFER_CF:

      CanTp_RxGetBufferCF(pTpRxState);
      break;

    case CANTP_RXSTATE_WAIT_NEXT_FCWAIT:

      CanTp_RxGetBufferFCWait(pTpRxState);
      break;

    default:

      CanTp_DetReportError(CANTP_SID_RXGETBUFFER, CANTP_E_INVALID_RX_STATE)
      break;
  }
}

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxGetBuffer(CanTp_TxStatePtrType pTpTxState){
#if(CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)

  PduInfoType               lPduInfo;
  CanTp_TxChannelStateType  lNewChannelState;
  PduLengthType             lRemainingBufferSize;

  switch(pTpTxState->ChannelState){
    case CANTP_TXSTATE_WAIT_BUFFER_SF:

      pTpTxState->PayloadLength = (uint8)pTpTxState->DataLength;
      lNewChannelState = CANTP_TXSTATE_TRANSMIT_SF;
      break;

    case CANTP_TXSTATE_WAIT_BUFFER_FF:

#if(CANTP_SUPPORT_LONG_FF == STD_ON)
      if(pTpTxState->DataLength > CANTP_FF_DL_12BIT)
      {
        pTpTxState->PayloadLength = CanTp_TxCfg_GetMaxPayloadLFF(pTpTxState->TxHdl);
      }
      else
#endif
      {
        pTpTxState->PayloadLength = CanTp_TxCfg_GetMaxPayloadFF(pTpTxState->TxHdl);
      }
      lNewChannelState = CANTP_TXSTATE_TRANSMIT_FF;
      break;

    case CANTP_TXSTATE_WAIT_BUFFER_CF:

      pTpTxState->PayloadLength = CanTp_TxCfg_GetMaxPayloadCF(pTpTxState->TxHdl);
      lNewChannelState = CANTP_TXSTATE_TRANSMIT_CF;

      if((pTpTxState->DataIndex + pTpTxState->PayloadLength) > pTpTxState->DataLength)
      {
        pTpTxState->PayloadLength = (uint8)(pTpTxState->DataLength - pTpTxState->DataIndex);
      }
      break;

    default:

      CanTp_DetReportError(CANTP_SID_TXGETBUFFER, CANTP_E_INVALID_TX_STATE)
      return;
  }

  lPduInfo.SduDataPtr = &pTpTxState->Payload[0];
  lPduInfo.SduLength  =  pTpTxState->PayloadLength;
  pTpTxState->BufferState = CanTp_PduRCopyTxData(CanTp_TxCfg_GetPduRTxSduId(pTpTxState->TxHdl)
   ,                                                 &lPduInfo
   ,                                                 (RetryInfoType*)NULL_PTR
   ,                                                 &lRemainingBufferSize);

  if(pTpTxState->BufferState == CANTP_BUFREQ_OK){
    pTpTxState->Timer        = CanTp_TxCfg_GetNAs(pTpTxState->TxHdl);
    pTpTxState->ChannelState = lNewChannelState;
    CanTp_TxTransmitFrame(pTpTxState);
  }
  else{
    if(pTpTxState->BufferState != CANTP_BUFREQ_E_BUSY){
      CanTp_TxInit(pTpTxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_TX_BUFFER);
    }

  }

#else
  CANTP_DUMMY_STATEMENT(pTpTxState);
#endif
}

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_RxTransmitFrame(CanTp_RxStatePtrType pTpRxState){
#if(CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)

  CanTp_TxResultType      lTxResult;
  PduInfoType             lFCFrameData;
  uint8                   lFCBuffer[CANTP_FRAME_FC_MAX_LENGTH + CANTP_MAX_PDU_METADATA_LENGTH];
  uint8                   lBlockSizeValue;
  boolean                 lTransmitFC;

  lTransmitFC = TRUE;
  lFCFrameData.SduDataPtr = lFCBuffer;
  lFCFrameData.SduLength  = 0;

#if(CANTP_RX_CHECK_ADDRESSING_FORMAT == STD_ON)
  if(CanTp_RxGetAdrOffset(pTpRxState->RxHdl) != 0u)
#endif
#if((CANTP_RX_HAS_EXTENDED_ADDRESSING == STD_ON) || (CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON) || (CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON))
  {
    lFCFrameData.SduDataPtr[0] = CanTp_Util_RxGetFCInPayloadAddressInfo(pTpRxState);
    lFCFrameData.SduLength++;
  }
#endif

  lBlockSizeValue = CanTp_RxGetCurrentBS(pTpRxState->RxHdl);

  switch(pTpRxState->ChannelState){
    case CANTP_RXSTATE_TRANSMIT_FC_CTS:

      if(lBlockSizeValue != 0u)
      {
#if(CANTP_CONSTANT_BS == STD_ON)
        if(CanTp_Data_CalcBS(pTpRxState->RxHdl) != 0u)
        {
          lBlockSizeValue = CanTp_Data_CalcBS(pTpRxState->RxHdl);
        }
        else
#endif
        {
          uint16 lBytesPerBlock;

          lBytesPerBlock = ((uint16)lBlockSizeValue) * CanTp_RxCfg_GetMaxPayloadCF(pTpRxState->RxHdl);
          if( (pTpRxState->ProvidedBufferSize < lBytesPerBlock) &&
               (pTpRxState->ProvidedBufferSize < (pTpRxState->DataLength - pTpRxState->DataIndex)) )
          {
            lBlockSizeValue = (uint8)(pTpRxState->ProvidedBufferSize / CanTp_RxCfg_GetMaxPayloadCF(pTpRxState->RxHdl));

            CanTp_DetAssert(lBlockSizeValue >= 1u, CANTP_SID_RXTRANSMITFRAME, CANTP_E_INVALID_RX_BUFFER)
          }

#if(CANTP_CONSTANT_BS == STD_ON)

          CanTp_Data_CalcBS(pTpRxState->RxHdl) = lBlockSizeValue;
#endif
        }
      }

      lFCFrameData.SduDataPtr[lFCFrameData.SduLength] = CANTP_PCI_TYPE_FC;

      pTpRxState->BlocksizeCounter = lBlockSizeValue;
      break;

    case CANTP_RXSTATE_TRANSMIT_FC_WT:

      if(pTpRxState->WFTCounter > 0u )
      {
        lFCFrameData.SduDataPtr[lFCFrameData.SduLength] = (CANTP_PCI_TYPE_FC | CANTP_FLOWSTATUS_WT);
      }
      else
      {
        lTransmitFC = FALSE;
        CanTp_RxInit(pTpRxState, CANTP_NOTIFY_WFT_OVERRUN, CANTP_E_RX_WFTMAX, CANTP_RESET_ALL);
      }
      break;

    case CANTP_RXSTATE_TRANSMIT_FC_OVFL:

      lFCFrameData.SduDataPtr[lFCFrameData.SduLength] = (CANTP_PCI_TYPE_FC | CANTP_FLOWSTATUS_OVFL);
      break;

    default:
      CanTp_DetReportError(CANTP_SID_RXTRANSMITFRAME, CANTP_E_INVALID_RX_STATE)
      lTransmitFC = FALSE;
      break;
  }

  if(lTransmitFC == TRUE){
    CanTp_PduTxInfoType  lPduTxInfo;

    lFCFrameData.SduDataPtr[lFCFrameData.SduLength + CANTP_FRAME_OFFSET_FC_BS ]   = lBlockSizeValue;
    lFCFrameData.SduDataPtr[lFCFrameData.SduLength + CANTP_FRAME_OFFSET_FC_STMIN] = CanTp_RxGetCurrentSTmin(pTpRxState->RxHdl);
    lFCFrameData.SduLength += CANTP_PCI_LENGTH_FC;

    lPduTxInfo.SduDirection  = CANTP_DIR_RX;
    lPduTxInfo.SduHdl        = pTpRxState->RxHdl;
    lPduTxInfo.TxPduId       = CanTp_RxCfg_GetLoLayerTxFcPduId(pTpRxState->RxHdl);
    lPduTxInfo.TxConfPduId   = CanTp_RxCfg_GetTxFcConfPduId(pTpRxState->RxHdl);

#if(CANTP_PADDING_SUPPORT_REQUIRED == STD_ON)
    lPduTxInfo.PaddingLength = CanTp_Util_GetPaddingLength((uint8)lFCFrameData.SduLength, CanTp_RxCfg_HasPaddingActivation(pTpRxState->RxHdl), CanTp_RxCfg_GetCanType(pTpRxState->RxHdl));
#endif

#if(CANTP_MAX_PDU_METADATA_LENGTH != 0)
    lPduTxInfo.PduMetadata = pTpRxState->FcPduMetadata;
    lPduTxInfo.PduMetadataLength = pTpRxState->FcPduMetadataLength;
#endif

    lTxResult = CanTp_CanIfTransmitFrame(&lPduTxInfo, &lFCFrameData);

    if(lTxResult == CANTP_TX_OK){
      pTpRxState->ChannelState = (CanTp_RxChannelStateType)((pTpRxState->ChannelState  & CANTP_RXSTATE_TRANSMIT_FC_ANY_MASK)
                                                            | CANTP_RXSTATE_WAIT_TXCONFFC_ANY);
    }
    else{
      if(lTxResult == CANTP_TX_NOT_OK)
      {
        CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NOT_OK, CANTP_E_RX_TRANSMIT_ERROR, CANTP_RESET_ALL);
      }

    }
  }

#else
  CANTP_DUMMY_STATEMENT(pTpRxState);
#endif
}

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxTransmitFrame(CanTp_TxStatePtrType pTpTxState){
  PduInfoType             lTxFrameData;
  uint8                   lTxFrameDataBuffer[CANTP_MAX_FRAME_LENGTH + CANTP_MAX_PDU_METADATA_LENGTH];
  CanTp_PduTxInfoType     lPduTxInfo;
  Std_ReturnType          lTxResult;

  lTxFrameData.SduDataPtr = lTxFrameDataBuffer;
  lTxFrameData.SduLength  = 0;

#if(CANTP_TX_CHECK_ADDRESSING_FORMAT == STD_ON)
  if(CanTp_TxGetAdrOffset(pTpTxState->TxHdl) != 0u)
#endif
#if((CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON))
  {
    lTxFrameData.SduDataPtr[0] = CanTp_Util_TxGetInPayloadAddressInfo(pTpTxState);
    lTxFrameData.SduLength++;
  }
#endif

  switch(pTpTxState->ChannelState){
    case CANTP_TXSTATE_TRANSMIT_SF:
      lTxFrameData.SduDataPtr[lTxFrameData.SduLength]  = CANTP_PCI_TYPE_SF;

#if(CANTP_TX_HAS_CANFD == STD_ON)
      if((CANTP_PCI_LENGTH_SF + lTxFrameData.SduLength + pTpTxState->PayloadLength) > CANTP_CAN20_FRAME_LENGTH)
      {
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 1u] = (uint8)(pTpTxState->DataLength);
        lTxFrameData.SduLength += CANTP_PCI_LENGTH_LSF;
      }
      else
#endif
      {
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength] |= (uint8)((pTpTxState->DataLength) & CANTP_MASK_SF_LENGTH);
        lTxFrameData.SduLength += CANTP_PCI_LENGTH_SF;
      }
      break;

    case CANTP_TXSTATE_TRANSMIT_FF:
      lTxFrameData.SduDataPtr[lTxFrameData.SduLength]  = CANTP_PCI_TYPE_FF;

#if(CANTP_SUPPORT_LONG_FF == STD_ON)
      if(pTpTxState->DataLength > CANTP_FF_DL_12BIT)
      {
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 1u] = 0;
#if(CANTP_SIZEOF_PDULENGTHTYPE < 4)

        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 2u] = 0;
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 3u] = 0;
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 4u] = CanTp_Util_GetHiByte(pTpTxState->DataLength);
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 5u] = CanTp_Util_GetLoByte(pTpTxState->DataLength);
#else

        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 2u] = CanTp_Util_GetHiHiByte(pTpTxState->DataLength);
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 3u] = CanTp_Util_GetHiLoByte(pTpTxState->DataLength);
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 4u] = CanTp_Util_GetLoHiByte(pTpTxState->DataLength);
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 5u] = CanTp_Util_GetLoLoByte(pTpTxState->DataLength);
#endif
        lTxFrameData.SduLength += CANTP_PCI_LENGTH_LFF;
      }
      else
#endif
      {
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength]     |= (uint8)(CanTp_Util_GetHiByte(pTpTxState->DataLength) & CANTP_MASK_FF_LENGTH);
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 1u]  = (uint8)(CanTp_Util_GetLoByte(pTpTxState->DataLength));
        lTxFrameData.SduLength += CANTP_PCI_LENGTH_FF;
      }

      pTpTxState->SeqNumber        = CANTP_SN_FIRST_CF;
      pTpTxState->BlocksizeCounter = 0;
      pTpTxState->DataIndex        = 0;
      break;

    case CANTP_TXSTATE_TRANSMIT_CF:
      lTxFrameData.SduDataPtr[lTxFrameData.SduLength]  = CANTP_PCI_TYPE_CF;
      lTxFrameData.SduDataPtr[lTxFrameData.SduLength] |= (uint8) (pTpTxState->SeqNumber);
      lTxFrameData.SduLength += CANTP_PCI_LENGTH_CF;
      break;

    default:
      CanTp_DetReportError(CANTP_SID_TXTRANSMITFRAME, CANTP_E_INVALID_TX_STATE)
      return;
  }

  CanTp_Util_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(&lTxFrameData.SduDataPtr[lTxFrameData.SduLength])
   ,                   (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(pTpTxState->Payload)
   ,                   pTpTxState->PayloadLength);
  lTxFrameData.SduLength += pTpTxState->PayloadLength;

  lPduTxInfo.SduDirection  = CANTP_DIR_TX;
  lPduTxInfo.SduHdl        = pTpTxState->TxHdl;
  lPduTxInfo.TxPduId       = CanTp_TxCfg_GetLoLayerTxPduId(pTpTxState->TxHdl);
  lPduTxInfo.TxConfPduId   = CanTp_TxCfg_GetTxConfPduId(pTpTxState->TxHdl);

#if(CANTP_PADDING_SUPPORT_REQUIRED == STD_ON)
  lPduTxInfo.PaddingLength = CanTp_Util_GetPaddingLength((uint8)lTxFrameData.SduLength
   ,                                                        CanTp_TxCfg_HasPaddingActivation(pTpTxState->TxHdl)
   ,                                                        CanTp_TxCfg_GetCanType(pTpTxState->TxHdl));
#endif

#if(CANTP_MAX_PDU_METADATA_LENGTH != 0)
  lPduTxInfo.PduMetadata = pTpTxState->DataPduMetadata;
  lPduTxInfo.PduMetadataLength = pTpTxState->DataPduMetadataLength;
#endif

  lTxResult = CanTp_CanIfTransmitFrame(&lPduTxInfo, &lTxFrameData);

  if(lTxResult == CANTP_TX_OK){
    pTpTxState->ChannelState = (CanTp_TxChannelStateType)((pTpTxState->ChannelState  & CANTP_TXSTATE_TRANSMIT_ANY_MASK)
                                                          | CANTP_TXSTATE_WAIT_TXCONF_ANY);
    pTpTxState->DataIndex = pTpTxState->DataIndex + pTpTxState->PayloadLength;
  }
  else{
    if(lTxResult == CANTP_TX_NOT_OK){
      CanTp_TxInit(pTpTxState, CANTP_NOTIFY_NOT_OK, CANTP_E_TX_TRANSMIT_ERROR);
    }

  }
}

#if(CANTP_RX_HAS_HALF_DUPLEX == STD_ON)

CANTP_LOCAL FUNC(Std_ReturnType, CANTP_CODE) CanTp_RxCheckChannelMode(PduIdType RxHdl){
  Std_ReturnType  lResult;
  CANTP_DUMMY_STATEMENT(RxHdl);

  if(!CanTp_RxSdu2TxSduRefIsAvailable(RxHdl)){
    lResult = E_OK;
  }
#if(CANTP_RX_CHECK_HALF_DUPLEX == STD_ON)
  else if(CANTP_MODE_FULL_DUPLEX == CanTp_RxCfg_GetChannelMode(RxHdl)){
    lResult = E_OK;
  }
#endif
  else if(CanTp_TxChannelIsIdle(CanTp_RxCfg_GetTxSduHdl(RxHdl))){
    lResult = E_OK;
  }
  else{
    lResult = E_NOT_OK;
  }
  return lResult;
}
#endif

#if(CANTP_TX_HAS_HALF_DUPLEX == STD_ON)

CANTP_LOCAL FUNC(Std_ReturnType, CANTP_CODE) CanTp_TxCheckChannelMode(PduIdType TxHdl){
  Std_ReturnType  lResult;
  CANTP_DUMMY_STATEMENT(TxHdl);

  if(!CanTp_TxSdu2RxSduRefIsAvailable(TxHdl)){
    lResult = E_OK;
  }
#if(CANTP_TX_CHECK_HALF_DUPLEX == STD_ON)
  else if(CANTP_MODE_FULL_DUPLEX == CanTp_TxCfg_GetChannelMode(TxHdl)){
    lResult = E_OK;
  }
#endif
  else if(CanTp_RxChannelIsIdle(CanTp_TxCfg_GetRxSduHdl(TxHdl)) == TRUE){
    lResult = E_OK;
  }
  else{
    lResult = E_NOT_OK;
  }
  return lResult;
}
#endif

#if(CANTP_TRANSMIT_QUEUE == STD_ON)

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxQueueProcess(PduIdType TxConfPduId){
  PduInfoType          lPduInfo;
  PduIdType            lQueuedHandle;
  PduIdType            lQueuedPduId;
  CanTp_DirectionType  lQueuedDirection;
  CanTp_TxResultType   lCanIfResult;

  if(CanTp_TxQueueEntryReadPos(TxConfPduId).SduHandle != CANTP_INVALID_HDL){
    if(CanTp_Data_TxSemaphore(TxConfPduId).Handle == CANTP_INVALID_HDL){
      lPduInfo.SduLength  = CanTp_TxQueueEntryReadPos(TxConfPduId).SduLength;
      lPduInfo.SduDataPtr = CanTp_TxQueueEntryReadPos(TxConfPduId).SduData;
      lQueuedPduId        = CanTp_TxQueueEntryReadPos(TxConfPduId).PduId;
      lQueuedHandle       = CanTp_TxQueueEntryReadPos(TxConfPduId).SduHandle;
      lQueuedDirection    = CanTp_TxQueueEntryReadPos(TxConfPduId).SduDirection;

      lCanIfResult = CanTp_CanIfTransmit(lQueuedDirection, lQueuedHandle, lQueuedPduId, &lPduInfo);

      CanTp_TxQueueEntryReadPos(TxConfPduId).SduHandle = CANTP_INVALID_HDL;
      CanTp_Data_TxQueue(TxConfPduId).ReadPos = (uint8)((CanTp_Data_TxQueue(TxConfPduId).ReadPos + 1u) & CANTP_TX_QUEUE_MASK);

      if(lCanIfResult == CANTP_TX_OK)
      {
        CanTp_Data_TxSemaphore(TxConfPduId).Handle    = lQueuedHandle;
        CanTp_Data_TxSemaphore(TxConfPduId).Direction = lQueuedDirection;

        CanTp_ApplFrameTransmission(lQueuedPduId, &lPduInfo)
      }
      else
      {
        if(lQueuedDirection == CANTP_DIR_TX)
        {
          CanTp_TxInit(CanTp_TxGetChannelPtr(lQueuedHandle), CANTP_NOTIFY_NOT_OK, CANTP_E_TX_TRANSMIT_ERROR);
        }
        else
        {
          CanTp_RxInit(CanTp_RxGetChannelPtr(lQueuedHandle), CANTP_NOTIFY_NOT_OK, CANTP_E_RX_TRANSMIT_ERROR, CANTP_RESET_ALL);
        }
      }
    }

  }

  else{
    CanTp_Data_TxQueue(TxConfPduId).ReadPos = (uint8)((CanTp_Data_TxQueue(TxConfPduId).ReadPos + 1u) & CANTP_TX_QUEUE_MASK);
  }
}

CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxQueueCancel(PduIdType SduHdl, CanTp_DirectionType Direction){
  PduIdType  lTxConfPduId;
  uint8      lQueueCntr;

  if(Direction == CANTP_DIR_TX){
    lTxConfPduId = CanTp_TxCfg_GetTxConfPduId(SduHdl);
  }
  else{
    lTxConfPduId = CanTp_RxCfg_GetTxFcConfPduId(SduHdl);
  }

  if((CanTp_Data_TxSemaphore(lTxConfPduId).Handle == SduHdl) &&
      (CanTp_Data_TxSemaphore(lTxConfPduId).Direction == Direction)){
    CanTp_Data_TxSemaphore(lTxConfPduId).Handle    = CANTP_INVALID_HDL;
    CanTp_Data_TxSemaphore(lTxConfPduId).Direction = CANTP_DIR_NONE;

#if(CANTP_LOLAYER_TC == STD_ON)
    if(Direction == CANTP_DIR_TX){
      CanTp_CanIfCancelTransmit(CANTP_DIR_TX, SduHdl, CanTp_TxCfg_GetLoLayerTxPduId(SduHdl));
    }
    else{
      CanTp_CanIfCancelTransmit(CANTP_DIR_RX, SduHdl, CanTp_RxCfg_GetLoLayerTxFcPduId(SduHdl));
    }
#endif

    if(!CanTp_TxQueueIsEmpty(lTxConfPduId)){
      CanTp_TxQueueProcess(lTxConfPduId);
    }
  }
  else{
    lQueueCntr = CanTp_Data_TxQueue(lTxConfPduId).ReadPos;
    while(lQueueCntr != CanTp_Data_TxQueue(lTxConfPduId).WritePos){
      if((CanTp_Data_TxQueue(lTxConfPduId).Entries[lQueueCntr].SduHandle == SduHdl) &&
          (CanTp_Data_TxQueue(lTxConfPduId).Entries[lQueueCntr].SduDirection == Direction))
      {
        CanTp_Data_TxQueue(lTxConfPduId).Entries[lQueueCntr].SduHandle = CANTP_INVALID_HDL;
        break;
      }

      lQueueCntr = (uint8)((lQueueCntr + 1u) & CANTP_TX_QUEUE_MASK);
    }
  }
}
#endif

FUNC(void, CANTP_CODE) SwcServiceCanTp_InitFunction(P2CONST(CanTp_ConfigType, AUTOMATIC, CANTP_INIT_DATA) CfgPtr){
#if(CANTP_USE_INIT_POINTER == STD_ON)
  uint8  lErrorId = CANTP_E_NO_ERROR;

  CanTp_Data_CfgPtr() = CfgPtr;

  if(CfgPtr == NULL_PTR){
    lErrorId = CANTP_E_PARAM_POINTER;
    CanTp_EcuMReportBswError(ECUM_BSWERROR_NULLPTR)
  }
#if(CANTP_CONFIGURATION_VARIANT == CANTP_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)

  else if(CANTP_GENERATOR_COMPATIBILITY_VERSION != CfgPtr->CompatibilityVersionOfPBConfig){
    CanTp_EcuMReportBswError(ECUM_BSWERROR_COMPATIBILITYVERSION)
  }

  else if(CANTP_FINAL_MAGIC_NUMBER != CfgPtr->FinalMagicNumberOfPBConfig){
    CanTp_EcuMReportBswError(ECUM_BSWERROR_MAGICNUMBER)
  }
#endif
  else
#endif
  {
    if(CanTp_Util_CheckConfigValidity() == TRUE){
      CanTp_ResetChannels();
      CanTp_Data_InitState() = CANTP_STATUS_INITIALIZED;
    }

  }

#if(CANTP_USE_INIT_POINTER == STD_ON)
#if(CANTP_DEV_ERROR_REPORT == STD_ON)
  if(lErrorId != CANTP_E_NO_ERROR){
    CanTp_DetReportError(CANTP_SID_INIT, lErrorId)
  }
#else

  CANTP_DUMMY_STATEMENT(lErrorId);
#endif
#else
  CANTP_DUMMY_STATEMENT(CfgPtr);
#endif
}

FUNC(void, CANTP_CODE) SwcServiceCanTp_InitFunctionMemory(void){
  CanTp_Data_InitState() = CANTP_STATUS_NOT_INITIALIZED;
}

FUNC(void, CANTP_CODE) SwcServiceCanTp_Shutdown(void){
  uint8  lErrorId = CANTP_E_NO_ERROR;

  if(CanTp_Data_InitState() != CANTP_STATUS_INITIALIZED){
    lErrorId = CANTP_E_UNINIT;
  }
  else{
    CanTp_ResetChannels();
    CanTp_Data_InitState() = CANTP_STATUS_SHUTDOWN;
  }

#if(CANTP_DEV_ERROR_REPORT == STD_ON)
  if(lErrorId != CANTP_E_NO_ERROR){
    CanTp_DetReportError(CANTP_SID_SHUTDOWN, lErrorId)
  }
#else
  CANTP_DUMMY_STATEMENT(lErrorId);
#endif
}

#if(CANTP_VERSION_INFO_API == STD_ON)

FUNC(void, CANTP_CODE) SwcServiceCanTp_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CANTP_APPL_DATA) versioninfo){
  uint8  lErrorId = CANTP_E_NO_ERROR;

#if(CANTP_DEV_ERROR_DETECT == STD_ON)

  if(versioninfo == NULL_PTR){
    lErrorId = CANTP_E_PARAM_POINTER;
  }
  else
#endif
  {
    versioninfo->vendorID         = CANTP_VENDOR_ID;
    versioninfo->moduleID         = CANTP_MODULE_ID;

    versioninfo->sw_major_version = CANTP_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = CANTP_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = CANTP_SW_PATCH_VERSION;
  }

#if(CANTP_DEV_ERROR_REPORT == STD_ON)
  if(lErrorId != CANTP_E_NO_ERROR){
    CanTp_DetReportError(CANTP_SID_GETVERSIONINFO, lErrorId)
  }
#else
  CANTP_DUMMY_STATEMENT(lErrorId);
#endif
}
#endif

FUNC(void, CANTP_CODE) SwcServiceCanTp_MainFunction(void){
  SwcServiceCanTp_MainFunctionRx();
  SwcServiceCanTp_MainFunctionTx();
}

FUNC(void,  CANTP_CODE)   SwcServiceCanTp_MainFunctionRx(void){
  PduIdType            lRxChannelHdl;
  CanTp_RxStatePtrType pTpRxState;

  if(CanTp_Data_InitState() == CANTP_STATUS_INITIALIZED){
    for(lRxChannelHdl = 0; lRxChannelHdl < CanTp_Cfg_GetNumRxChannels(); lRxChannelHdl++){
      pTpRxState = &CanTp_Data_RxState(lRxChannelHdl);

      if(pTpRxState->RxHdl != CANTP_INVALID_HDL)
      {
        CanTp_EnterCritical();

        if(pTpRxState->RxHdl != CANTP_INVALID_HDL)
        {
          pTpRxState->Timer--;

          if(pTpRxState->Timer == 0u)
          {
            switch(pTpRxState->ChannelState)
            {
              case CANTP_RXSTATE_WAIT_CF:
                CanTp_RxInit(pTpRxState, CANTP_NOTIFY_TIMEOUT_C, CANTP_E_RX_TIMEOUT_CR, CANTP_RESET_ALL);
                break;

              case CANTP_RXSTATE_TRANSMIT_FC_CTS:
              case CANTP_RXSTATE_TRANSMIT_FC_WT:
              case CANTP_RXSTATE_WAIT_TXCONFFC_CTS:
              case CANTP_RXSTATE_WAIT_TXCONFFC_WT:
                CanTp_RxInit(pTpRxState, CANTP_NOTIFY_TIMEOUT_A, CANTP_E_RX_TIMEOUT_AR, CANTP_RESET_ALL);
                break;

              case CANTP_RXSTATE_TRANSMIT_FC_OVFL:
              case CANTP_RXSTATE_WAIT_TXCONFFC_OVFL:

                CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);
                break;

              case CANTP_RXSTATE_WAIT_BUFFER_SF:
              case CANTP_RXSTATE_WAIT_BUFFER_FF:
              case CANTP_RXSTATE_WAIT_BUFFER_CF:

                CanTp_RxGetBuffer(pTpRxState);

                if(pTpRxState->BufferState == CANTP_BUFREQ_E_BUSY)
                {
                  CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);
                }
                break;

              case CANTP_RXSTATE_WAIT_NEXT_FCWAIT:

                pTpRxState->Timer        = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);
                pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_WT;
                CanTp_RxTransmitFrame(pTpRxState);
                break;

              default:
                CanTp_DetReportError(CANTP_SID_MAINFUNCTIONRX, CANTP_E_INVALID_RX_STATE)
                break;
            }
          }

          else
          {
#if(CANTP_TRANSMIT_QUEUE == STD_ON)

            if( (CanTp_RxCfg_GetTxFcConfPduId(pTpRxState->RxHdl) != CANTP_INVALID_HDL) &&
                 (!CanTp_TxQueueIsEmpty(CanTp_RxCfg_GetTxFcConfPduId(pTpRxState->RxHdl))) )
            {
              CanTp_TxQueueProcess(CanTp_RxCfg_GetTxFcConfPduId(pTpRxState->RxHdl));
            }
#endif

            if( ((pTpRxState->ChannelState & CANTP_RXSTATE_WAIT_BUFFER_ANY) == CANTP_RXSTATE_WAIT_BUFFER_ANY) ||
                  (pTpRxState->ChannelState == CANTP_RXSTATE_WAIT_NEXT_FCWAIT) )
            {
              CanTp_RxGetBuffer(pTpRxState);
            }

            if((pTpRxState->ChannelState & CANTP_RXSTATE_TRANSMIT_FC_ANY) == CANTP_RXSTATE_TRANSMIT_FC_ANY)
            {
              CanTp_RxTransmitFrame(pTpRxState);
            }
          }
        }

        CanTp_LeaveCritical();
      }

    }

  }

}

FUNC(void, CANTP_CODE) SwcServiceCanTp_MainFunctionTx(void){
  PduIdType            lTxChannelHdl;
  CanTp_TxStatePtrType pTpTxState;

  if(CanTp_Data_InitState() == CANTP_STATUS_INITIALIZED){
    for(lTxChannelHdl = 0; lTxChannelHdl < CanTp_Cfg_GetNumTxChannels(); lTxChannelHdl++){
      pTpTxState = &CanTp_Data_TxState(lTxChannelHdl);

      if(pTpTxState->TxHdl != CANTP_INVALID_HDL)
      {
        CanTp_EnterCritical();

        if(pTpTxState->TxHdl != CANTP_INVALID_HDL)
        {
          if(pTpTxState->STminTimer > 0u)
          {
            pTpTxState->STminTimer--;

            if(pTpTxState->STminTimer == 0u)
            {
              pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_BUFFER_CF;

            }
          }

          pTpTxState->Timer--;
          if(pTpTxState->Timer == 0u)
          {
            switch(pTpTxState->ChannelState)
            {
              case CANTP_TXSTATE_WAIT_FC:
                CanTp_TxInit(pTpTxState, CANTP_NOTIFY_TIMEOUT_B, CANTP_E_TX_TIMEOUT_BS);
                break;

#if(CANTP_STMIN_BY_APPL == STD_ON)
              case CANTP_TXSTATE_WAIT_STMIN_APPL:
#endif
              case CANTP_TXSTATE_WAIT_STMIN_INTERN:

                pTpTxState->STminTimer   = 0;
                pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_BUFFER_CF;

              case CANTP_TXSTATE_WAIT_BUFFER_SF:
              case CANTP_TXSTATE_WAIT_BUFFER_FF:
              case CANTP_TXSTATE_WAIT_BUFFER_CF:

                CanTp_TxGetBuffer(pTpTxState);

                if(pTpTxState->BufferState == CANTP_BUFREQ_E_BUSY)
                {
                  CanTp_TxInit(pTpTxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_TX_TIMEOUT_CS);
                }
                break;

              case CANTP_TXSTATE_TRANSMIT_SF:
              case CANTP_TXSTATE_TRANSMIT_FF:
              case CANTP_TXSTATE_TRANSMIT_CF:
              case CANTP_TXSTATE_WAIT_TXCONF_SF:
              case CANTP_TXSTATE_WAIT_TXCONF_FF:
              case CANTP_TXSTATE_WAIT_TXCONF_CF:
                CanTp_TxInit(pTpTxState, CANTP_NOTIFY_TIMEOUT_A, CANTP_E_TX_TIMEOUT_AS);
                break;

              default:
                CanTp_DetReportError(CANTP_SID_MAINFUNCTIONTX, CANTP_E_INVALID_TX_STATE)
                break;
            }
          }

          else
          {
#if(CANTP_TRANSMIT_QUEUE == STD_ON)

            if(!CanTp_TxQueueIsEmpty(CanTp_TxCfg_GetTxConfPduId(pTpTxState->TxHdl)))
            {
              CanTp_TxQueueProcess(CanTp_TxCfg_GetTxConfPduId(pTpTxState->TxHdl));
            }
#endif

            if((pTpTxState->ChannelState & CANTP_TXSTATE_WAIT_BUFFER_ANY) == CANTP_TXSTATE_WAIT_BUFFER_ANY)
            {
              CanTp_TxGetBuffer(pTpTxState);
            }

            if((pTpTxState->ChannelState & CANTP_TXSTATE_TRANSMIT_ANY) == CANTP_TXSTATE_TRANSMIT_ANY)
            {
              CanTp_TxTransmitFrame(pTpTxState);
            }
          }
        }

        CanTp_LeaveCritical();
      }

    }

  }

}

FUNC(Std_ReturnType, CANTP_CODE) SwcServiceCanTp_Transmit(PduIdType CanTpTxSduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpTxInfoPtr){
  uint8           lErrorId     = CANTP_E_NO_ERROR;
  Std_ReturnType  lReturnValue = E_NOT_OK;

  CANTP_DUMMY_STATEMENT(CanTpTxSduId);

  if(CanTp_Data_InitState() != CANTP_STATUS_INITIALIZED){
    lErrorId = CANTP_E_UNINIT;
  }
#if(CANTP_DEV_ERROR_DETECT == STD_ON)
  else if(CanTpTxSduId >= CanTp_Cfg_GetNumTxSduIds()){
    lErrorId = CANTP_E_INVALID_TX_ID;
  }
  else if(CanTpTxInfoPtr == NULL_PTR){
    lErrorId = CANTP_E_PARAM_POINTER;
  }
#if(CANTP_SUPPORT_LONG_FF != STD_ON)

  else if(CanTpTxInfoPtr->SduLength > CANTP_FF_DL_12BIT){
    lErrorId = CANTP_E_INVALID_TX_LENGTH;
  }
#endif
#if(CANTP_CONFIGURATION_VARIANT != CANTP_CONFIGURATION_VARIANT_PRECOMPILE)

  else if(!CanTp_TxSduSnvIsAvailable(CanTpTxSduId)){
    lErrorId = CANTP_E_INVALID_TX_ID;
  }
#endif
#endif
  else{
    CONST(PduIdType, AUTOMATIC) lTxSduHdl = CanTp_TxGetSduHdlBySduId(CanTpTxSduId);

    if(CanTpTxInfoPtr->SduLength > 0u){
      CanTp_EnterCritical();

#if(CANTP_TX_HAS_HALF_DUPLEX == STD_ON)
      if(CanTp_TxCheckChannelMode(lTxSduHdl) == E_OK)
#endif
      {
        lReturnValue = CanTp_TxStartConnection(CanTpTxSduId, lTxSduHdl, CanTpTxInfoPtr->SduLength, CanTpTxInfoPtr);
      }

      CanTp_LeaveCritical();
    }

  }

#if(CANTP_DEV_ERROR_REPORT == STD_ON)
  if(lErrorId != CANTP_E_NO_ERROR){
    CanTp_DetReportError(CANTP_SID_TRANSMIT, lErrorId)
  }
#else
  CANTP_DUMMY_STATEMENT(lErrorId);
#endif

  return lReturnValue;
}

FUNC(void, CANTP_CODE) CanTp_RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) PduInfoPtr){
  uint8 lErrorId = CANTP_E_NO_ERROR;

  if(CanTp_Data_InitState() != CANTP_STATUS_INITIALIZED){
    lErrorId = CANTP_E_UNINIT;
  }
#if(CANTP_DEV_ERROR_DETECT == STD_ON)
  else if(RxPduId >= CanTp_Cfg_GetNumRxPdus()){
    lErrorId = CANTP_E_INVALID_RX_ID;
  }
  else if(PduInfoPtr == NULL_PTR){
    lErrorId = CANTP_E_PARAM_POINTER;
  }
  else if(PduInfoPtr->SduDataPtr == NULL_PTR){
    lErrorId = CANTP_E_PARAM_POINTER;
  }
#endif
  else{
    PduIdType                  lSduHdl;
    uint8                      lReceivedFrameType;

#if(CANTP_SUPPORT_MULTIPLE_ADDRESSING == STD_ON)

    lSduHdl            = CANTP_INVALID_HDL;
    lReceivedFrameType = CANTP_PCI_TYPE_INVALID;

    switch(CanTp_Cfg_GetAddressingTypeByRxPdu(RxPduId)){
      case CANTP_ADDRESS_FORMAT_STANDARD:
      case CANTP_ADDRESS_FORMAT_NORMALFIXED:
        lReceivedFrameType = (uint8)(PduInfoPtr->SduDataPtr[0] & CANTP_PCI_TYPE_MASK);

        lSduHdl = CanTp_Cfg_GetSduHdlByRxPduOnly(RxPduId, lReceivedFrameType);
        break;

      case CANTP_ADDRESS_FORMAT_EXTENDED:
      case CANTP_ADDRESS_FORMAT_MIXED11:
      case CANTP_ADDRESS_FORMAT_MIXED29:
        lReceivedFrameType = (uint8)(PduInfoPtr->SduDataPtr[1] & CANTP_PCI_TYPE_MASK);

#if(CANTP_GENERIC_CONNECTIONS == STD_ON)
        if(CanTp_Cfg_IsGenericConnectionByRxPdu(RxPduId))
        {
          lSduHdl = CanTp_Cfg_GetSduHdlByRxPduOnly(RxPduId, lReceivedFrameType);
        }
        else
#endif
        {
          lSduHdl = CanTp_Cfg_GetSduHdlByRxPduAddress(RxPduId, lReceivedFrameType, PduInfoPtr->SduDataPtr[0]);
        }
        break;

      default:

        break;
    }
#else
#if((CANTP_SUPPORT_STANDARD_ADDRESSING == STD_ON) || (CANTP_SUPPORT_NORMALFIXED_ADDRESSING == STD_ON))
    lReceivedFrameType = (uint8)(PduInfoPtr->SduDataPtr[0] & CANTP_PCI_TYPE_MASK);
    lSduHdl = CanTp_Cfg_GetSduHdlByRxPduOnly(RxPduId, lReceivedFrameType);
#else
    lReceivedFrameType = (uint8)(PduInfoPtr->SduDataPtr[1] & CANTP_PCI_TYPE_MASK);
#if(CANTP_GENERIC_CONNECTIONS == STD_ON)
    if(CanTp_Cfg_IsGenericConnectionByRxPdu(RxPduId)){
      lSduHdl = CanTp_Cfg_GetSduHdlByRxPduOnly(RxPduId, lReceivedFrameType);
    }
    else
#endif
    {
      lSduHdl = CanTp_Cfg_GetSduHdlByRxPduAddress(RxPduId, lReceivedFrameType, PduInfoPtr->SduDataPtr[0]);
    }
#endif
#endif

#if((CANTP_DCM_REQUEST_DETECT == STD_ON) && (CANTP_MIXED11_ADDRESSING == STD_ON))
#if(CANTP_SUPPORT_MULTIPLE_ADDRESSING == STD_ON)
    if((CanTp_Cfg_GetAddressingTypeByRxPdu(RxPduId) == CANTP_ADDRESS_FORMAT_MIXED11) &&
        ((lReceivedFrameType == CANTP_PCI_TYPE_SF) || (lReceivedFrameType == CANTP_PCI_TYPE_FF)))
#else
    if((lReceivedFrameType == CANTP_PCI_TYPE_SF) || (lReceivedFrameType == CANTP_PCI_TYPE_FF))
#endif
    {
      CanTp_DcmForwardNAE(RxPduId, PduInfoPtr->SduDataPtr[0]);
    }
#endif

    if(lSduHdl != CANTP_INVALID_HDL){
      PduInfoType lPayloadInfo;
      PduInfoType lMetadataInfo;

      lPayloadInfo.SduDataPtr = PduInfoPtr->SduDataPtr;
      lMetadataInfo.SduLength = CanTp_Cfg_GetPduMetadataLengthByRxPdu(RxPduId);

#if(CANTP_MAX_PDU_METADATA_LENGTH != 0)
      if(CanTp_Cfg_GetPduMetadataLengthByRxPdu(RxPduId) != 0u)
      {
        lPayloadInfo.SduLength = PduInfoPtr->SduLength - CanTp_Cfg_GetPduMetadataLengthByRxPdu(RxPduId);
        lMetadataInfo.SduDataPtr = &PduInfoPtr->SduDataPtr[PduInfoPtr->SduLength - CanTp_Cfg_GetPduMetadataLengthByRxPdu(RxPduId)];
      }
      else
#endif
      {
        lPayloadInfo.SduLength = PduInfoPtr->SduLength;
        lMetadataInfo.SduDataPtr = PduInfoPtr->SduDataPtr;
      }

      CanTp_CanIfRxIndication(lSduHdl, lReceivedFrameType, &lPayloadInfo, &lMetadataInfo);
    }
#if((CANTP_CONFIGURATION_VARIANT == CANTP_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE) || (CANTP_POSTBUILD_VARIANT_SUPPORT == STD_ON))

    else if((!CanTp_CanIfRxPduHasTxSduRef(RxPduId)) && (!CanTp_CanIfRxPduHasRxSduRef(RxPduId))){
      lErrorId = CANTP_E_INVALID_RX_ID;
    }
    else{
    }
#endif
  }

#if(CANTP_DEV_ERROR_REPORT == STD_ON)
  if(lErrorId != CANTP_E_NO_ERROR){
    CanTp_DetReportError(CANTP_SID_RXINDICATION, lErrorId)
  }
#else
  CANTP_DUMMY_STATEMENT(lErrorId);
#endif
}

FUNC(void, CANTP_CODE) CanTp_TxConfirmation(PduIdType TxPduId){
  uint8 lErrorId = CANTP_E_NO_ERROR;

#if(CANTP_DEV_ERROR_DETECT == STD_ON)
  if(CanTp_Data_InitState() != CANTP_STATUS_INITIALIZED){
    lErrorId = CANTP_E_UNINIT;
  }
  else if(TxPduId >= CanTp_Cfg_GetNumTxConfPdus()){
    lErrorId = CANTP_E_INVALID_TX_ID;
  }
  else
#endif
  {
    PduIdType            lSduHdl;
    CanTp_DirectionType  lSduDir;

    CanTp_EnterCritical();

    lSduHdl = CanTp_Data_TxSemaphore(TxPduId).Handle;
    lSduDir = CanTp_Data_TxSemaphore(TxPduId).Direction;

    CanTp_Data_TxSemaphore(TxPduId).Handle    = CANTP_INVALID_HDL;
    CanTp_Data_TxSemaphore(TxPduId).Direction = CANTP_DIR_NONE;

#if(CANTP_TRANSMIT_QUEUE == STD_ON)

    if(!CanTp_TxQueueIsEmpty(TxPduId)){
      CanTp_TxQueueProcess(TxPduId);
    }
#endif

    CanTp_LeaveCritical();

    if(lSduHdl != CANTP_INVALID_HDL){
      if(lSduDir == CANTP_DIR_TX)
      {
#if(CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)

        if(CanTp_TxCfg_GetTxConfPduId(lSduHdl) == TxPduId)
        {
          CanTp_TxStatePtrType pTpTxState;
          CanTp_EnterCritical();

          pTpTxState = CanTp_TxGetActiveChannelPtr(lSduHdl);
          if(pTpTxState != NULL_PTR)
          {
            CanTp_ApplFrameTxConfirmation(CanTp_TxCfg_GetLoLayerTxPduId(lSduHdl))
            CanTp_CanIfTxConfirmation(pTpTxState);
          }

          CanTp_LeaveCritical();
        }

#endif
      }

      else
      {
#if(CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)

        if(CanTp_RxCfg_GetTxFcConfPduId(lSduHdl) == TxPduId)
        {
          CanTp_RxStatePtrType pTpRxState;

          CanTp_EnterCritical();

          pTpRxState = CanTp_RxGetActiveChannelPtr(lSduHdl);
          if(pTpRxState != NULL_PTR)
          {
            CanTp_ApplFrameTxConfirmation(CanTp_RxCfg_GetLoLayerTxFcPduId(lSduHdl))
            CanTp_CanIfTxConfirmationFC(pTpRxState);
          }

          CanTp_LeaveCritical();
        }

#endif
      }
    }

  }

#if(CANTP_DEV_ERROR_REPORT == STD_ON)
  if(lErrorId != CANTP_E_NO_ERROR){
    CanTp_DetReportError(CANTP_SID_TXCONFIRMATION, lErrorId)
  }
#else
  CANTP_DUMMY_STATEMENT(lErrorId);
#endif
}

#if(CANTP_ENABLE_CHANGE_PARAM == STD_ON)

FUNC(Std_ReturnType, CANTP_CODE) CanTp_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value){
  Std_ReturnType  lReturnValue = E_NOT_OK;
  uint8           lErrorId     = CANTP_E_NO_ERROR;

  CANTP_DUMMY_STATEMENT(id);

#if(CANTP_DEV_ERROR_DETECT == STD_ON)
  if(CanTp_Data_InitState() != CANTP_STATUS_INITIALIZED){
    lErrorId = CANTP_E_UNINIT;
  }
  else if(id >= CanTp_Cfg_GetNumRxSduIds()){
    lErrorId = CANTP_E_INVALID_RX_ID;
  }
  else if((parameter != TP_STMIN) && (parameter != TP_BS)){
    lErrorId = CANTP_E_PARAM_ID;
  }
#if(CANTP_CONFIGURATION_VARIANT != CANTP_CONFIGURATION_VARIANT_PRECOMPILE)

  else if(!CanTp_RxSduSnvIsAvailable(id)){
    lErrorId = CANTP_E_INVALID_RX_ID;
  }
#endif
  else
#endif
  {
    CONST(PduIdType, AUTOMATIC) lRxSduHdl = CanTp_RxGetSduHdlBySduId(id);

    CanTp_EnterCritical();

    if(CanTp_RxChannelIsIdle(lRxSduHdl) == TRUE){
      if(parameter == TP_STMIN)
      {
        if( ((value > CANTP_STMIN_MILLISEC_MAX) && (value < CANTP_STMIN_MICROSEC_MIN)) ||
              (value > CANTP_STMIN_MICROSEC_MAX) )
        {
          lErrorId = CANTP_E_PARAM_ID;
        }
        else
        {
          CanTp_Data_DynFcParam(lRxSduHdl).STmin = (uint8)value;
          lReturnValue = E_OK;
        }
      }

      else
      {
        CanTp_Data_DynFcParam(lRxSduHdl).BS = (uint8)value;
        lReturnValue = E_OK;
      }
    }

    CanTp_LeaveCritical();
  }

#if(CANTP_DEV_ERROR_REPORT == STD_ON)
  if(lErrorId != CANTP_E_NO_ERROR){
    CanTp_DetReportError(CANTP_SID_CHANGEPARAMETER, lErrorId)
  }
#else
  CANTP_DUMMY_STATEMENT(lErrorId);
#endif

  return lReturnValue;
}
#endif

#if(CANTP_ENABLE_READ_PARAM == STD_ON)

FUNC(Std_ReturnType, CANTP_CODE) CanTp_ReadParameter(PduIdType id, TPParameterType parameter, uint16* value){
  Std_ReturnType  lReturnValue;
  uint8           lErrorId = CANTP_E_NO_ERROR;

  CANTP_DUMMY_STATEMENT(id);

#if(CANTP_DEV_ERROR_DETECT == STD_ON)

  lReturnValue = E_NOT_OK;

  if(CanTp_Data_InitState() != CANTP_STATUS_INITIALIZED){
    lErrorId = CANTP_E_UNINIT;
  }
  else if(id >= CanTp_Cfg_GetNumRxSduIds()){
    lErrorId = CANTP_E_INVALID_RX_ID;
  }
  else if((parameter != TP_STMIN) && (parameter != TP_BS)){
    lErrorId = CANTP_E_PARAM_ID;
  }
  else if(value == NULL_PTR){
    lErrorId = CANTP_E_PARAM_POINTER;
  }
#if(CANTP_CONFIGURATION_VARIANT != CANTP_CONFIGURATION_VARIANT_PRECOMPILE)

  else if(!CanTp_RxSduSnvIsAvailable(id)){
    lErrorId = CANTP_E_INVALID_RX_ID;
  }
#endif
  else
#endif
  {
    CONST(PduIdType, AUTOMATIC) lRxSduHdl = CanTp_RxGetSduHdlBySduId(id);

    lReturnValue = E_OK;

    if(parameter == TP_STMIN){
      *value = CanTp_RxGetCurrentSTmin(lRxSduHdl);
    }
    else{
      *value = CanTp_RxGetCurrentBS(lRxSduHdl);
    }
  }

#if(CANTP_DEV_ERROR_REPORT == STD_ON)
  if(lErrorId != CANTP_E_NO_ERROR){
    CanTp_DetReportError(CANTP_SID_READPARAMETER, lErrorId)
  }
#else
  CANTP_DUMMY_STATEMENT(lErrorId);
#endif

  return lReturnValue;
}
#endif

#if(CANTP_TC == STD_ON)

FUNC(Std_ReturnType, CANTP_CODE) SwcServiceCanTp_CancelTransmit(PduIdType CanTpTxSduId){
  Std_ReturnType   lReturnValue = E_NOT_OK;
  uint8            lErrorId     = CANTP_E_NO_ERROR;

  CANTP_DUMMY_STATEMENT(CanTpTxSduId);

#if(CANTP_DEV_ERROR_DETECT == STD_ON)
  if(CanTp_Data_InitState() != CANTP_STATUS_INITIALIZED){
    lErrorId = CANTP_E_UNINIT;
  }
  else if(CanTpTxSduId >= CanTp_Cfg_GetNumTxSduIds()){
    lErrorId = CANTP_E_INVALID_TX_ID;
  }
#if(CANTP_CONFIGURATION_VARIANT != CANTP_CONFIGURATION_VARIANT_PRECOMPILE)

  else if(!CanTp_TxSduSnvIsAvailable(CanTpTxSduId)){
    lErrorId = CANTP_E_INVALID_TX_ID;
  }
#endif
  else
#endif
  {
    CanTp_TxStatePtrType pTpTxState;

    CONST(PduIdType, AUTOMATIC) lTxSduHdl = CanTp_TxGetSduHdlBySduId(CanTpTxSduId);

    if(CanTp_TxCfg_HasTxCancel(lTxSduHdl)){
      CanTp_EnterCritical();

      pTpTxState = CanTp_TxGetActiveChannelPtr(lTxSduHdl);
      if(pTpTxState != NULL_PTR)
      {
        if(pTpTxState->DataLength > CanTp_TxCfg_GetMaxSFDataLength(lTxSduHdl))
        {
          if(pTpTxState->DataIndex < pTpTxState->DataLength)
          {
            CanTp_TxInit(pTpTxState, CANTP_NOTIFY_CANCEL_OK, CANTP_E_NO_ERROR);
            lReturnValue = E_OK;
          }

        }

      }
      else
      {
        lErrorId = CANTP_E_OPER_NOT_SUPPORTED;
      }

      CanTp_LeaveCritical();
    }

  }

#if(CANTP_DEV_ERROR_REPORT == STD_ON)
  if(lErrorId != CANTP_E_NO_ERROR){
    CanTp_DetReportError(CANTP_SID_CANCELTRANSMIT, lErrorId)
  }
#else
  CANTP_DUMMY_STATEMENT(lErrorId);
#endif

  return lReturnValue;
}
#endif

#if(CANTP_RC == STD_ON)

FUNC(Std_ReturnType, CANTP_CODE) SwcServiceCanTp_CancelReceive(PduIdType CanTpRxSduId){
  Std_ReturnType lReturnValue = E_NOT_OK;
  uint8          lErrorId     = CANTP_E_NO_ERROR;

  CANTP_DUMMY_STATEMENT(CanTpRxSduId);

#if(CANTP_DEV_ERROR_DETECT == STD_ON)
  if(CanTp_Data_InitState() != CANTP_STATUS_INITIALIZED){
    lErrorId = CANTP_E_UNINIT;
  }
  else if(CanTpRxSduId >= CanTp_Cfg_GetNumRxSduIds()){
    lErrorId = CANTP_E_INVALID_RX_ID;
  }
#if(CANTP_CONFIGURATION_VARIANT != CANTP_CONFIGURATION_VARIANT_PRECOMPILE)

  else if(!CanTp_RxSduSnvIsAvailable(CanTpRxSduId)){
    lErrorId = CANTP_E_INVALID_RX_ID;
  }
#endif
  else
#endif
  {
    CanTp_RxStatePtrType pTpRxState;

    CONST(PduIdType, AUTOMATIC) lRxSduHdl = CanTp_RxGetSduHdlBySduId(CanTpRxSduId);

    CanTp_EnterCritical();

    pTpRxState = CanTp_RxGetActiveChannelPtr(lRxSduHdl);
    if(pTpRxState != NULL_PTR){
      if(pTpRxState->FrameType != CANTP_FRAME_SF)
      {
        if((pTpRxState->DataIndex + pTpRxState->PayloadLength) < pTpRxState->DataLength)
        {
          CanTp_RxInit(pTpRxState, CANTP_NOTIFY_CANCEL_OK, CANTP_E_NO_ERROR, CANTP_RESET_ALL);
          lReturnValue = E_OK;
        }

      }

    }
    else{
      lErrorId = CANTP_E_OPER_NOT_SUPPORTED;
    }

    CanTp_LeaveCritical();
  }

#if(CANTP_DEV_ERROR_REPORT == STD_ON)
  if(lErrorId != CANTP_E_NO_ERROR){
    CanTp_DetReportError(CANTP_SID_CANCELRECEIVE, lErrorId)
  }
#else
  CANTP_DUMMY_STATEMENT(lErrorId);
#endif

  return lReturnValue;
}
#endif

#if(CANTP_STMIN_BY_APPL == STD_ON)

FUNC(void, CANTP_CODE) CanTp_StopSeparationTime(PduIdType CanTpTxSduId){
  uint8          lErrorId;

  CANTP_DUMMY_STATEMENT(CanTpTxSduId);

#if(CANTP_DEV_ERROR_DETECT == STD_ON)
  if(CanTp_Data_InitState() != CANTP_STATUS_INITIALIZED){
    lErrorId = CANTP_E_UNINIT;
  }
  else if(CanTpTxSduId >= CanTp_Cfg_GetNumTxSduIds()){
    lErrorId = CANTP_E_INVALID_TX_ID;
  }
#if(CANTP_CONFIGURATION_VARIANT != CANTP_CONFIGURATION_VARIANT_PRECOMPILE)

  else if(!CanTp_TxSduSnvIsAvailable(CanTpTxSduId)){
    lErrorId = CANTP_E_INVALID_TX_ID;
  }
#endif
  else
#endif
  {
    CanTp_TxStatePtrType pTpTxState;

    CONST(PduIdType, AUTOMATIC) lTxSduHdl = CanTp_TxGetSduHdlBySduId(CanTpTxSduId);

    lErrorId = CANTP_E_INVALID_TX_STATE;

    CanTp_EnterCritical();

    pTpTxState = CanTp_TxGetActiveChannelPtr(lTxSduHdl);
    if(pTpTxState != NULL_PTR){
      if(pTpTxState->ChannelState == CANTP_TXSTATE_WAIT_STMIN_APPL)
      {
        lErrorId = CANTP_E_NO_ERROR;

        pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_BUFFER_CF;
        CanTp_TxGetBuffer(pTpTxState);
      }

    }

    CanTp_LeaveCritical();
  }

#if(CANTP_DEV_ERROR_REPORT == STD_ON)
  if(lErrorId != CANTP_E_NO_ERROR){
    CanTp_DetReportError(CANTP_SID_STOPSEPARATIONTIME, lErrorId)
  }
#else
  CANTP_DUMMY_STATEMENT(lErrorId);
#endif

}
#endif

#define CANTP_STOP_SEC_CODE
#include "MemMap.hpp"

#ifdef __cplusplus
}
#endif
