#if !defined (CANTP_H)
#define CANTP_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "Types_SwcServiceCanTp.hpp"
#include "CfgSwcServiceCanTp.hpp"
#include "SwcServiceCanTp_Lcfg.hpp"
#include "PbCfgSwcServiceCanTp.hpp"

#define CANTP_VENDOR_ID                          (1u)
#define CANTP_MODULE_ID                          (0x23u)
#define CANTP_AR_RELEASE_MAJOR_VERSION          (4u)
#define CANTP_AR_RELEASE_MINOR_VERSION          (0u)
#define CANTP_AR_RELEASE_REVISION_VERSION       (3u)
#define CANTP_SW_MAJOR_VERSION                  (3u)
#define CANTP_SW_MINOR_VERSION                  (5u)
#define CANTP_SW_PATCH_VERSION                  (0u)
#define CANTP_INSTANCE_ID_DET                   (0x00u)
#define CANTP_SID_INIT                           (0x01u)
#define CANTP_SID_SHUTDOWN                       (0x02u)
#define CANTP_SID_TRANSMIT                       (0x03u)
#define CANTP_SID_RXINDICATION                   (0x04u)
#define CANTP_SID_TXCONFIRMATION                 (0x05u)
#define CANTP_SID_MAINFUNCTION                   (0x06u)
#define CANTP_SID_GETVERSIONINFO                 (0x07u)
#define CANTP_SID_CANCELTRANSMIT                 (0x08u)
#define CANTP_SID_CANCELRECEIVE                  (0x09u)
#define CANTP_SID_CHANGEPARAMETER                (0x0Au)
#define CANTP_SID_READPARAMETER                  (0x0Bu)
#define CANTP_SID_MAINFUNCTIONRX                 (0x20u)
#define CANTP_SID_MAINFUNCTIONTX                 (0x21u)
#define CANTP_SID_RXGETBUFFER                    (0x30u)
#define CANTP_SID_TXGETBUFFER                    (0x31u)
#define CANTP_SID_RXTRANSMITFRAME                (0x32u)
#define CANTP_SID_TXTRANSMITFRAME                (0x33u)
#define CANTP_SID_RXINIT                         (0x34u)
#define CANTP_SID_TXINIT                         (0x35u)
#define CANTP_SID_STOPSEPARATIONTIME             (0x36u)
#define CANTP_E_PARAM_CONFIG                     (0x01u)
#define CANTP_E_PARAM_ID                         (0x02u)
#define CANTP_E_PARAM_POINTER                    (0x03u)
#define CANTP_E_UNINIT                           (0x20u)
#define CANTP_E_INVALID_TX_ID                    (0x30u)
#define CANTP_E_INVALID_RX_ID                    (0x40u)
#define CANTP_E_INVALID_TX_BUFFER                (0x50u)
#define CANTP_E_INVALID_RX_BUFFER                (0x60u)
#define CANTP_E_INVALID_TX_LENGTH                (0x70u)
#define CANTP_E_INVALID_RX_LENGTH                (0x80u)
#define CANTP_E_INVALID_TATYPE                   (0x90u)
#define CANTP_E_OPER_NOT_SUPPORTED               (0xA0u)
#define CANTP_E_COM                              (0xB0u)
#define CANTP_E_INVALID_RX_STATE                 (0xB1u)
#define CANTP_E_INVALID_TX_STATE                 (0xB2u)
#define CANTP_E_INVALID_FRAME_TYPE               (0xB3u)
#define CANTP_E_RX_COM                           (0xC0u)
#define CANTP_E_RX_TIMEOUT_AR                    (0xC1u)
#define CANTP_E_RX_TIMEOUT_BR                    (0xC2u)
#define CANTP_E_RX_TIMEOUT_CR                    (0xC3u)
#define CANTP_E_RX_INVALID_SN                    (0xC4u)
#define CANTP_E_RX_WFTMAX                        (0xC5u)
#define CANTP_E_RX_RESTART                       (0xC6u)
#define CANTP_E_RX_TRANSMIT_ERROR                (0xC7u)
#define CANTP_E_TX_COM                           (0xD0u)
#define CANTP_E_TX_TIMEOUT_AS                    (0xD1u)
#define CANTP_E_TX_TIMEOUT_BS                    (0xD2u)
#define CANTP_E_TX_TIMEOUT_CS                    (0xD3u)
#define CANTP_E_TX_FC_OVFL                       (0xD4u)
#define CANTP_E_TX_INVALID_FS                    (0xD5u)
#define CANTP_E_TX_RES_STMIN                     (0xD6u)
#define CANTP_E_TX_TRANSMIT_ERROR                (0xD7u)
#define CANTP_E_NO_ERROR                         (0xFFu)
#define CANTP_OFF                                (0x00u)
#define CANTP_ON                                 (0x01u)

#if(!defined (CANTP_APPL_RX_SF_INDICATION))
#define CANTP_APPL_RX_SF_INDICATION             STD_OFF
#endif

#if(!defined (CANTP_APPL_RX_FF_INDICATION))
#define CANTP_APPL_RX_FF_INDICATION             STD_OFF
#endif

#if(!defined (CANTP_APPL_RX_CF_INDICATION))
#define CANTP_APPL_RX_CF_INDICATION             STD_OFF
#endif

#if(!defined (CANTP_APPL_FRAME_TRANSMISSION))
#define CANTP_APPL_FRAME_TRANSMISSION           STD_OFF
#endif

#if(!defined (CANTP_APPL_FRAME_CONFIRMATION))
#define CANTP_APPL_FRAME_CONFIRMATION           STD_OFF
#endif

#if !defined (CANTP_TX_FC_FROM_ISR)
#define CANTP_TX_FC_FROM_ISR                    STD_ON
#endif

#if !defined (CANTP_RX_GET_BUFFER_FROM_ISR)
#define CANTP_RX_GET_BUFFER_FROM_ISR            STD_ON
#endif

#if !defined (CANTP_TX_GET_BUFFER_FROM_ISR)
#define CANTP_TX_GET_BUFFER_FROM_ISR            STD_ON
#endif

#if !defined (CANTP_FAULT_TOLERANT_RXBUFFER)
#define CANTP_FAULT_TOLERANT_RXBUFFER           STD_OFF
#endif

#if !defined (CANTP_IGNORE_FC_WITH_RES_STMIN)
#define CANTP_IGNORE_FC_WITH_RES_STMIN          STD_OFF
#endif

#if !defined (CANTP_IGNORE_CF_WITH_WRONG_SN)
#define CANTP_IGNORE_CF_WITH_WRONG_SN           STD_OFF
#endif

#if !defined (CANTP_IGNORE_FC_OVFL_INVALID_FS)
#define CANTP_IGNORE_FC_OVFL_INVALID_FS         STD_OFF
#endif

#define CANTP_START_SEC_CODE
#include "MemMap.hpp"

FUNC(void, CANTP_CODE) SwcServiceCanTp_InitFunction(P2CONST(CanTp_ConfigType, AUTOMATIC, CANTP_INIT_DATA) CfgPtr);
FUNC(void, CANTP_CODE) SwcServiceCanTp_InitFunctionMemory(void);
FUNC(void, CANTP_CODE) SwcServiceCanTp_Shutdown(void);
FUNC(Std_ReturnType, CANTP_CODE) SwcServiceCanTp_Transmit(PduIdType CanTpTxSduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpTxInfoPtr);

#if(CANTP_RXTX_MAINFUNCTION_API == STD_ON)
FUNC(void, CANTP_CODE) SwcServiceCanTp_MainFunction(void);
#endif

#if(CANTP_VERSION_INFO_API == STD_ON)
FUNC(void, CANTP_CODE) SwcServiceCanTp_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CANTP_APPL_DATA) versioninfo);
#endif

#if(CANTP_ENABLE_CHANGE_PARAM == STD_ON)
FUNC(Std_ReturnType, CANTP_CODE) CanTp_ChangeParameter(PduIdType id, TPParameterType parameter, uint16  value);
#endif

#if(CANTP_ENABLE_READ_PARAM == STD_ON)
FUNC(Std_ReturnType, CANTP_CODE) CanTp_ReadParameter(PduIdType id, TPParameterType parameter, uint16* value);
#endif

#if(CANTP_TC == STD_ON)
FUNC(Std_ReturnType, CANTP_CODE) SwcServiceCanTp_CancelTransmit(PduIdType CanTpTxSduId);
#endif

#if(CANTP_RC == STD_ON)
FUNC(Std_ReturnType, CANTP_CODE) SwcServiceCanTp_CancelReceive(PduIdType CanTpRxSduId);
#endif

#define CANTP_STOP_SEC_CODE
#include "MemMap.hpp"

#ifdef __cplusplus
}
#endif
#endif

