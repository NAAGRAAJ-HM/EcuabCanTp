#if !defined (CANTP_TYPES_H)
#define CANTP_TYPES_H

#include "Types_SwcServiceCom.hpp"
#include "CfgSwcServiceCanTp.hpp"

#if defined (MSR_PDUR_API_AR_VERSION)

# undef  CANTP_PDUR_API_AR_VERSION
#define CANTP_PDUR_API_AR_VERSION        MSR_PDUR_API_AR_VERSION
#endif

#if defined (CANTP_PDUR_API_AR_VERSION)
#if   (CANTP_PDUR_API_AR_VERSION == 0x403)
#define CANTP_PDUR_API_403_ENABLED             STD_ON
#define CANTP_PDUR_API_412_ENABLED             STD_OFF
# elif(CANTP_PDUR_API_AR_VERSION == 0x412)
#define CANTP_PDUR_API_403_ENABLED             STD_OFF
#define CANTP_PDUR_API_412_ENABLED             STD_ON
#else
#error "Not supported PduR version! No PduR BSWMD file in your MSR project?"
#endif
#else
# error "Missing CANTP_PDUR_API_AR_VERSION! Mixing new BSW with old generation tool?"
#endif

#if !defined (CANTP_TX_QUEUE_SIZE)
#define CANTP_TX_QUEUE_SIZE                     4u
#else
#if((CANTP_TX_QUEUE_SIZE & (CANTP_TX_QUEUE_SIZE - 1)) != 0)

#error "CANTP_TX_QUEUE_SIZE must be a power of 2 (2, 4, 8, 16...)"
#endif
#endif

typedef uint8                                    CanTp_FrameType;
#define CANTP_FRAME_SF                           (0x00u)
#define CANTP_FRAME_FF                           (0x01u)
#define CANTP_FRAME_CF                           (0x02u)
#define CANTP_FRAME_FC                           (0x03u)
#define CANTP_FRAME_INVALID                      (0x04u)

typedef uint8                                    SwcServiceCanTp_InitFunctionStatusType;
#define CANTP_STATUS_NOT_INITIALIZED             CANTP_OFF
#define CANTP_STATUS_INITIALIZED                 CANTP_ON
#define CANTP_STATUS_SHUTDOWN                    CANTP_STATUS_NOT_INITIALIZED

typedef uint8                                    CanTp_TxChannelStateType;
#define CANTP_TXSTATE_IDLE                       (0x00u)
#define CANTP_TXSTATE_WAIT_FC                    (0x01u)
#define CANTP_TXSTATE_WAIT_STMIN_INTERN          (0x02u)
#define CANTP_TXSTATE_WAIT_STMIN_APPL            (0x03u)
#define CANTP_TXSTATE_TRANSMIT_ANY               (0x10u)
#define CANTP_TXSTATE_TRANSMIT_ANY_MASK          (0xEFu)
#define CANTP_TXSTATE_TRANSMIT_SF                (0x11u)
#define CANTP_TXSTATE_TRANSMIT_FF                (0x12u)
#define CANTP_TXSTATE_TRANSMIT_CF                (0x13u)
#define CANTP_TXSTATE_WAIT_TXCONF_ANY            (0x20u)
#define CANTP_TXSTATE_WAIT_TXCONF_SF             (0x21u)
#define CANTP_TXSTATE_WAIT_TXCONF_FF             (0x22u)
#define CANTP_TXSTATE_WAIT_TXCONF_CF             (0x23u)
#define CANTP_TXSTATE_WAIT_BUFFER_ANY            (0x40u)
#define CANTP_TXSTATE_WAIT_BUFFER_SF             (0x41u)
#define CANTP_TXSTATE_WAIT_BUFFER_FF             (0x42u)
#define CANTP_TXSTATE_WAIT_BUFFER_CF             (0x43u)

typedef uint8                                    CanTp_RxChannelStateType;
#define CANTP_RXSTATE_IDLE                       (0x00u)
#define CANTP_RXSTATE_WAIT_CF                    (0x01u)
#define CANTP_RXSTATE_WAIT_NEXT_FCWAIT           (0x02u)
#define CANTP_RXSTATE_TRANSMIT_FC_ANY            (0x10u)
#define CANTP_RXSTATE_TRANSMIT_FC_ANY_MASK       (0xEFu)
#define CANTP_RXSTATE_TRANSMIT_FC_CTS            (0x11u)
#define CANTP_RXSTATE_TRANSMIT_FC_WT             (0x12u)
#define CANTP_RXSTATE_TRANSMIT_FC_OVFL           (0x13u)
#define CANTP_RXSTATE_WAIT_TXCONFFC_ANY          (0x20u)
#define CANTP_RXSTATE_WAIT_TXCONFFC_CTS          (0x21u)
#define CANTP_RXSTATE_WAIT_TXCONFFC_WT           (0x22u)
#define CANTP_RXSTATE_WAIT_TXCONFFC_OVFL         (0x23u)
#define CANTP_RXSTATE_WAIT_BUFFER_ANY            (0x40u)
#define CANTP_RXSTATE_WAIT_BUFFER_SF             (0x41u)
#define CANTP_RXSTATE_WAIT_BUFFER_FF             (0x42u)
#define CANTP_RXSTATE_WAIT_BUFFER_CF             (0x43u)

typedef uint8                                    CanTp_DirectionType;
#define CANTP_DIR_NONE                           (CanTp_DirectionType)(0x01u)
#define CANTP_DIR_TX                             (CanTp_DirectionType)(0x02u)
#define CANTP_DIR_RX                             (CanTp_DirectionType)(0x03u)

#if(CANTP_PDUR_API_403_ENABLED == STD_ON)
typedef  NotifResultType                         CanTp_NotificationType;
#define CANTP_NOTIFY_OK                         (NotifResultType)NTFRSLT_OK
#define CANTP_NOTIFY_NOT_OK                     (NotifResultType)NTFRSLT_E_NOT_OK
#define CANTP_NOTIFY_TIMEOUT_A                  (NotifResultType)NTFRSLT_E_TIMEOUT_A
#define CANTP_NOTIFY_TIMEOUT_B                  (NotifResultType)NTFRSLT_E_TIMEOUT_BS
#define CANTP_NOTIFY_TIMEOUT_C                  (NotifResultType)NTFRSLT_E_TIMEOUT_CR
#define CANTP_NOTIFY_WRONG_SN                   (NotifResultType)NTFRSLT_E_WRONG_SN
#define CANTP_NOTIFY_INVALID_FS                 (NotifResultType)NTFRSLT_E_INVALID_FS
#define CANTP_NOTIFY_UNEXP_PDU                  (NotifResultType)NTFRSLT_E_UNEXP_PDU
#define CANTP_NOTIFY_WFT_OVERRUN                (NotifResultType)NTFRSLT_E_WFT_OVRN
#define CANTP_NOTIFY_NO_BUFFER                  (NotifResultType)NTFRSLT_E_NO_BUFFER
#define CANTP_NOTIFY_CANCEL_OK                  (NotifResultType)NTFRSLT_E_CANCELATION_OK
#define CANTP_NOTIFY_CANCEL_NOT_OK              (NotifResultType)NTFRSLT_E_CANCELATION_NOT_OK
#define CANTP_NOTIFY_NORESULT                   (NotifResultType)(0x80u)
#else
typedef  Std_ReturnType                          CanTp_NotificationType;
#define CANTP_NOTIFY_OK                         (Std_ReturnType)E_OK
#define CANTP_NOTIFY_NOT_OK                     (Std_ReturnType)E_NOT_OK
#define CANTP_NOTIFY_TIMEOUT_A                  (Std_ReturnType)E_NOT_OK
#define CANTP_NOTIFY_TIMEOUT_B                  (Std_ReturnType)E_NOT_OK
#define CANTP_NOTIFY_TIMEOUT_C                  (Std_ReturnType)E_NOT_OK
#define CANTP_NOTIFY_WRONG_SN                   (Std_ReturnType)E_NOT_OK
#define CANTP_NOTIFY_INVALID_FS                 (Std_ReturnType)E_NOT_OK
#define CANTP_NOTIFY_UNEXP_PDU                  (Std_ReturnType)E_NOT_OK
#define CANTP_NOTIFY_WFT_OVERRUN                (Std_ReturnType)E_NOT_OK
#define CANTP_NOTIFY_NO_BUFFER                  (Std_ReturnType)E_NOT_OK
#define CANTP_NOTIFY_CANCEL_OK                  (Std_ReturnType)E_NOT_OK
#define CANTP_NOTIFY_CANCEL_NOT_OK              (Std_ReturnType)E_NOT_OK
#define CANTP_NOTIFY_NORESULT                   (Std_ReturnType)(0x80u)
#endif

typedef uint8                                    CanTp_BufferStateType;
#define CANTP_BUFREQ_OK                          (CanTp_BufferStateType)BUFREQ_OK
#define CANTP_BUFREQ_E_NOT_OK                    (CanTp_BufferStateType)BUFREQ_E_NOT_OK
#define CANTP_BUFREQ_E_BUSY                      (CanTp_BufferStateType)BUFREQ_E_BUSY
#define CANTP_BUFREQ_E_OVFL                      (CanTp_BufferStateType)BUFREQ_E_OVFL

typedef unsigned int    CanTp_BitType;
typedef uint16          CanTp_WFTmaxType;
typedef uint16          CanTp_TimerType;
typedef uint8           CanTp_AddressingFormatType;

typedef struct sCanTp_RxStateType{
  CanTp_FrameType                   FrameType;
  volatile CanTp_RxChannelStateType ChannelState;
  CanTp_TimerType                   Timer;
  PduLengthType                     DataLength;
  PduLengthType                     DataIndex;
  PduLengthType                     ProvidedBufferSize;
  PduIdType                         RxHdl;
  CanTp_WFTmaxType                  WFTCounter;
  CanTp_BufferStateType             BufferState;
  uint8                             BlocksizeCounter;
  uint8                             Payload[CANTP_MAX_PAYLOAD_LENGTH];
  uint8                             PayloadLength;
  uint8                             InitalDLC;
  uint8                             ExpectedSN;
#if(( CANTP_ONLY_NOTIFY_INFORMED_APPL == STD_ON ) || ( CANTP_RC == STD_ON ))
  uint8                             ApplState;
#endif
#if(CANTP_GENERIC_CONNECTIONS == STD_ON)
  uint8                             SduMetadata[CANTP_MAX_SDU_METADATA_LENGTH];
  uint8                             SduMetadataLength;
#if(CANTP_MAX_PDU_METADATA_LENGTH != 0)
  uint8                             FcPduMetadata[CANTP_MAX_PDU_METADATA_LENGTH];
  uint8                             FcPduMetadataLength;
#endif
#endif
}CanTp_RxStateType;

typedef struct sCanTp_TxStateType{
  CanTp_TimerType                   Timer;
  PduLengthType                     DataLength;
  PduLengthType                     DataIndex;
  PduIdType                         TxHdl;
#if(CANTP_STMIN_BY_APPL == STD_ON)
  PduIdType                         TxSduSnv;
#endif
  volatile CanTp_TxChannelStateType ChannelState;
  CanTp_BufferStateType             BufferState;
  uint8                             STmin;
  uint8                             STminTimer;
  uint8                             BlocksizeCounter;
#if(CANTP_USE_ONLY_FIRST_FC == STD_ON)
  uint8                             BS;
#endif
  uint8                             Payload[CANTP_MAX_PAYLOAD_LENGTH];
  uint8                             PayloadLength;
  uint8                             SeqNumber;
#if(CANTP_USE_ONLY_FIRST_FC == STD_ON)
  boolean                           FirstFCReceived;
#endif
  uint8                             FCLength;
  uint8                             FCData[4];
#if(CANTP_GENERIC_CONNECTIONS == STD_ON)
  uint8                             SduMetadata[CANTP_MAX_SDU_METADATA_LENGTH];
  uint8                             SduMetadataLength;
#if(CANTP_MAX_PDU_METADATA_LENGTH != 0)
  uint8                             DataPduMetadata[CANTP_MAX_PDU_METADATA_LENGTH];
  uint8                             DataPduMetadataLength;
#endif
#endif
}CanTp_TxStateType;

typedef struct sCanTp_DynFCParameterType{
  uint8                  BS;
  uint8                  STmin;
}CanTp_DynFCParameterType;

typedef struct sTxSemaphoreType{
  PduIdType            Handle;
  CanTp_DirectionType  Direction;
}CanTp_TxSemaphoreType;

typedef struct sTxQueueEntrype
{
  PduIdType              PduId;
  PduIdType              SduHandle;
  CanTp_DirectionType    SduDirection;
  PduLengthType          SduLength;
  uint8                  SduData[CANTP_MAX_FRAME_LENGTH + CANTP_MAX_PDU_METADATA_LENGTH];
}CanTp_TxQueueEntryType;

typedef struct sTxQueueType{
  CanTp_TxQueueEntryType  Entries[CANTP_TX_QUEUE_SIZE];
  uint8                   ReadPos;
  uint8                   WritePos;
}CanTp_TxQueueType;

#endif

