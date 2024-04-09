

#if !defined (CANTP_PRIV_H)
#define CANTP_PRIV_H

#define CANTP_PCI_TYPE_SF                        (0x00u)
#define CANTP_PCI_TYPE_FF                        (0x10u)
#define CANTP_PCI_TYPE_CF                        (0x20u)
#define CANTP_PCI_TYPE_FC                        (0x30u)
#define CANTP_PCI_TYPE_INVALID                   (0xFFu)

#define CANTP_PCI_TYPE_MASK                      (0xF0u)
#define CANTP_PCI_SN_MASK                        (0x0Fu)

#define CANTP_PCI_LENGTH_SF                      1u
#define CANTP_PCI_LENGTH_FF                      2u
#define CANTP_PCI_LENGTH_CF                      1u
#define CANTP_PCI_LENGTH_FC                      3u
#define CANTP_PCI_LENGTH_LSF                     2u
#define CANTP_PCI_LENGTH_LFF                     6u

#define CANTP_CAN20_FRAME_LENGTH                 8u
#define CANTP_FF_DL_12BIT                        4095u
#define CANTP_FF_DL_16BIT                        65535u

#define CANTP_MASK_SF_LENGTH                     (0x0Fu)
#define CANTP_MASK_FF_LENGTH                     (0x0Fu)
#define CANTP_MASK_FRAMETYPE                     (0xF0u)
#define CANTP_MASK_FS                            (0x0Fu)

#define CANTP_FLOWSTATUS_CTS                     (0x00u)
#define CANTP_FLOWSTATUS_WT                      (0x01u)
#define CANTP_FLOWSTATUS_OVFL                    (0x02u)

#define CANTP_STMIN_MILLISEC_MAX                 (0x7Fu)
#define CANTP_STMIN_MICROSEC_MIN                 (0xF1u)
#define CANTP_STMIN_MICROSEC_MAX                 (0xF9u)

#define CANTP_SN_FIRST_CF                        (0x01u)

#define CANTP_APPL_NOT_INFORMED                  (0x00u)
#define CANTP_APPL_INFORMED                      (0x01u)

#define CANTP_FRAME_OFFSET_FC_BS                 1u
#define CANTP_FRAME_OFFSET_FC_STMIN              2u
#if(CANTP_CAN20_PADDING_ACTIVE == STD_OFF)
#define CANTP_FRAME_FC_MAX_LENGTH               4u
#else
#define CANTP_FRAME_FC_MAX_LENGTH               8u
#endif

#if((CANTP_IGNORE_FC_WITH_RES_STMIN == STD_ON) || (CANTP_REJECT_FC_WITH_RES_STMIN == STD_ON))
#define CANTP_MODIFIED_RES_STMIN_HANDLING       STD_ON
#else
#define CANTP_MODIFIED_RES_STMIN_HANDLING       STD_OFF
#endif

#if((CANTP_CAN20_PADDING_ACTIVE == STD_ON) || \
     (CANTP_SUPPORT_CANFD        == STD_ON))

#define CANTP_PADDING_SUPPORT_REQUIRED          STD_ON
#else
#define CANTP_PADDING_SUPPORT_REQUIRED          STD_OFF
#endif

#define CANTP_OPT_ZERO_SDU       0
#define CANTP_OPT_SINGLE_SDU     1
#define CANTP_OPT_MULTI_SDU      2

#if((CANTP_CONFIGURATION_VARIANT == CANTP_CONFIGURATION_VARIANT_PRECOMPILE) && (CANTP_POSTBUILD_VARIANT_SUPPORT == STD_OFF))
#if(CANTP_NUM_RX_SDUS == 0)
#define CANTP_RX_OPTIMIZATION                  CANTP_OPT_ZERO_SDU
#else
#if(CANTP_NUM_RX_SDUS == 1)
#define CANTP_RX_OPTIMIZATION                 CANTP_OPT_SINGLE_SDU
#else
#define CANTP_RX_OPTIMIZATION                 CANTP_OPT_MULTI_SDU
#endif
#endif
#if(CANTP_NUM_TX_SDUS == 0)
#define CANTP_TX_OPTIMIZATION                  CANTP_OPT_ZERO_SDU
#else
#if(CANTP_NUM_TX_SDUS == 1)
#define CANTP_TX_OPTIMIZATION                 CANTP_OPT_SINGLE_SDU
#else
#define CANTP_TX_OPTIMIZATION                 CANTP_OPT_MULTI_SDU
#endif
#endif
#else
#define CANTP_RX_OPTIMIZATION                   CANTP_OPT_MULTI_SDU
#define CANTP_TX_OPTIMIZATION                   CANTP_OPT_MULTI_SDU
#endif

#if((CANTP_EXISTS_HALF_DUPLEX_CHANNELMODEOFRXSDUCFG == STD_ON) && (CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU))
#define CANTP_RX_HAS_HALF_DUPLEX                STD_ON
#else
#define CANTP_RX_HAS_HALF_DUPLEX                STD_OFF
#endif
#if((CANTP_EXISTS_FULL_DUPLEX_CHANNELMODEOFRXSDUCFG == STD_ON) || (CANTP_TX_OPTIMIZATION == CANTP_OPT_ZERO_SDU))
#define CANTP_RX_HAS_FULL_DUPLEX                STD_ON
#else
#define CANTP_RX_HAS_FULL_DUPLEX                STD_OFF
#endif
#if((CANTP_RX_HAS_HALF_DUPLEX == STD_ON) && (CANTP_RX_HAS_FULL_DUPLEX == STD_ON))
#define CANTP_RX_CHECK_HALF_DUPLEX              STD_ON
#else
#define CANTP_RX_CHECK_HALF_DUPLEX              STD_OFF
#endif

#if((CANTP_EXISTS_HALF_DUPLEX_CHANNELMODEOFTXSDUCFG == STD_ON) && (CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU))
#define CANTP_TX_HAS_HALF_DUPLEX                STD_ON
#else
#define CANTP_TX_HAS_HALF_DUPLEX                STD_OFF
#endif
#if((CANTP_EXISTS_FULL_DUPLEX_CHANNELMODEOFTXSDUCFG == STD_ON) || (CANTP_RX_OPTIMIZATION == CANTP_OPT_ZERO_SDU))
#define CANTP_TX_HAS_FULL_DUPLEX                STD_ON
#else
#define CANTP_TX_HAS_FULL_DUPLEX                STD_OFF
#endif
#if((CANTP_TX_HAS_HALF_DUPLEX == STD_ON) && (CANTP_TX_HAS_FULL_DUPLEX == STD_ON))
#define CANTP_TX_CHECK_HALF_DUPLEX              STD_ON
#else
#define CANTP_TX_CHECK_HALF_DUPLEX              STD_OFF
#endif

#define CANTP_RX_HAS_TATYPE_FUNCTIONAL           CANTP_EXISTS_FUNCTIONAL_RXTATYPEOFRXSDUCFG
#define CANTP_TX_HAS_TATYPE_FUNCTIONAL           CANTP_EXISTS_FUNCTIONAL_TXTATYPEOFTXSDUCFG

#if((CANTP_EXISTS_CANFD_CANTYPEOFRXSDUCFG == STD_ON) && (CANTP_SUPPORT_CANFD == STD_ON))
#define CANTP_RX_HAS_CANFD                      STD_ON
#else
#define CANTP_RX_HAS_CANFD                      STD_OFF
#endif
#define CANTP_RX_HAS_CAN20                       CANTP_EXISTS_CAN20_CANTYPEOFRXSDUCFG
#if((CANTP_RX_HAS_CANFD == STD_ON) && (CANTP_RX_HAS_CAN20 == STD_ON))
#define CANTP_RX_CHECK_CANTYPE                  STD_ON
#else
#define CANTP_RX_CHECK_CANTYPE                  STD_OFF
#endif

#if((CANTP_EXISTS_CANFD_CANTYPEOFTXSDUCFG == STD_ON) && (CANTP_SUPPORT_CANFD == STD_ON))
#define CANTP_TX_HAS_CANFD                      STD_ON
#else
#define CANTP_TX_HAS_CANFD                      STD_OFF
#endif
#define CANTP_TX_HAS_CAN20                       CANTP_EXISTS_CAN20_CANTYPEOFTXSDUCFG
#if((CANTP_TX_HAS_CANFD == STD_ON) && (CANTP_TX_HAS_CAN20 == STD_ON))
#define CANTP_TX_CHECK_CANTYPE                  STD_ON
#else
#define CANTP_TX_CHECK_CANTYPE                  STD_OFF
#endif

#if((CANTP_EXISTS_NORMAL_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG == STD_ON) && (CANTP_STANDARD_ADDRESSING == STD_ON))
#define CANTP_RX_HAS_STANDARD_ADDRESSING        STD_ON
#else
#define CANTP_RX_HAS_STANDARD_ADDRESSING        STD_OFF
#endif
#if((CANTP_EXISTS_EXTENDED_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG == STD_ON) && (CANTP_EXTENDED_ADDRESSING == STD_ON))
#define CANTP_RX_HAS_EXTENDED_ADDRESSING        STD_ON
#else
#define CANTP_RX_HAS_EXTENDED_ADDRESSING        STD_OFF
#endif
#if((CANTP_EXISTS_MIXED11_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG  == STD_ON) && (CANTP_MIXED11_ADDRESSING == STD_ON))
#define CANTP_RX_HAS_MIXED11_ADDRESSING         STD_ON
#else
#define CANTP_RX_HAS_MIXED11_ADDRESSING         STD_OFF
#endif
#if((CANTP_EXISTS_MIXED29_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG  == STD_ON) && (CANTP_MIXED29_ADDRESSING == STD_ON))
#define CANTP_RX_HAS_MIXED29_ADDRESSING         STD_ON
#else
#define CANTP_RX_HAS_MIXED29_ADDRESSING         STD_OFF
#endif
#if((CANTP_EXISTS_NORMALFIXED_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG  == STD_ON) && (CANTP_NORMALFIXED_ADDRESSING == STD_ON))
#define CANTP_RX_HAS_NORMALFIXED_ADDRESSING     STD_ON
#else
#define CANTP_RX_HAS_NORMALFIXED_ADDRESSING     STD_OFF
#endif
#if( ((CANTP_RX_HAS_STANDARD_ADDRESSING == STD_ON) && (CANTP_RX_HAS_EXTENDED_ADDRESSING == STD_ON))     || \
      ((CANTP_RX_HAS_STANDARD_ADDRESSING == STD_ON) && (CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON))      || \
      ((CANTP_RX_HAS_STANDARD_ADDRESSING == STD_ON) && (CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON))      || \
      ((CANTP_RX_HAS_STANDARD_ADDRESSING == STD_ON) && (CANTP_RX_HAS_NORMALFIXED_ADDRESSING == STD_ON))  || \
      ((CANTP_RX_HAS_EXTENDED_ADDRESSING == STD_ON) && (CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON))      || \
      ((CANTP_RX_HAS_EXTENDED_ADDRESSING == STD_ON) && (CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON))      || \
      ((CANTP_RX_HAS_EXTENDED_ADDRESSING == STD_ON) && (CANTP_RX_HAS_NORMALFIXED_ADDRESSING == STD_ON))  || \
      ((CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON)  && (CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON))      || \
      ((CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON)  && (CANTP_RX_HAS_NORMALFIXED_ADDRESSING == STD_ON))  || \
      ((CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON)  && (CANTP_RX_HAS_NORMALFIXED_ADDRESSING == STD_ON)) )
#define CANTP_RX_CHECK_ADDRESSING_FORMAT         STD_ON
#else
#define CANTP_RX_CHECK_ADDRESSING_FORMAT         STD_OFF
#endif

#if((CANTP_EXISTS_NORMAL_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG == STD_ON) && (CANTP_STANDARD_ADDRESSING == STD_ON))
#define CANTP_TX_HAS_STANDARD_ADDRESSING        STD_ON
#else
#define CANTP_TX_HAS_STANDARD_ADDRESSING        STD_OFF
#endif
#if((CANTP_EXISTS_EXTENDED_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG == STD_ON) && (CANTP_EXTENDED_ADDRESSING == STD_ON))
#define CANTP_TX_HAS_EXTENDED_ADDRESSING        STD_ON
#else
#define CANTP_TX_HAS_EXTENDED_ADDRESSING        STD_OFF
#endif
#if((CANTP_EXISTS_MIXED11_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG  == STD_ON) && (CANTP_MIXED11_ADDRESSING == STD_ON))
#define CANTP_TX_HAS_MIXED11_ADDRESSING         STD_ON
#else
#define CANTP_TX_HAS_MIXED11_ADDRESSING         STD_OFF
#endif
#if((CANTP_EXISTS_MIXED29_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG  == STD_ON) && (CANTP_MIXED29_ADDRESSING == STD_ON))
#define CANTP_TX_HAS_MIXED29_ADDRESSING         STD_ON
#else
#define CANTP_TX_HAS_MIXED29_ADDRESSING         STD_OFF
#endif
#if((CANTP_EXISTS_NORMALFIXED_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG  == STD_ON) && (CANTP_NORMALFIXED_ADDRESSING == STD_ON))
#define CANTP_TX_HAS_NORMALFIXED_ADDRESSING     STD_ON
#else
#define CANTP_TX_HAS_NORMALFIXED_ADDRESSING     STD_OFF
#endif
#if( ((CANTP_TX_HAS_STANDARD_ADDRESSING == STD_ON) && (CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON))     || \
      ((CANTP_TX_HAS_STANDARD_ADDRESSING == STD_ON) && (CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON))      || \
      ((CANTP_TX_HAS_STANDARD_ADDRESSING == STD_ON) && (CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON))      || \
      ((CANTP_TX_HAS_STANDARD_ADDRESSING == STD_ON) && (CANTP_TX_HAS_NORMALFIXED_ADDRESSING == STD_ON))  || \
      ((CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON) && (CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON))      || \
      ((CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON) && (CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON))      || \
      ((CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON) && (CANTP_TX_HAS_NORMALFIXED_ADDRESSING == STD_ON))  || \
      ((CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON)  && (CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON))      || \
      ((CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON)  && (CANTP_TX_HAS_NORMALFIXED_ADDRESSING == STD_ON))  || \
      ((CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON)  && (CANTP_TX_HAS_NORMALFIXED_ADDRESSING == STD_ON)) )
#define CANTP_TX_CHECK_ADDRESSING_FORMAT        STD_ON
#else
#define CANTP_TX_CHECK_ADDRESSING_FORMAT        STD_OFF
#endif

#if((CANTP_RX_CHECK_ADDRESSING_FORMAT == STD_ON) || (CANTP_TX_CHECK_ADDRESSING_FORMAT == STD_ON))
#define CANTP_SUPPORT_MULTIPLE_ADDRESSING       STD_ON
#else
#define CANTP_SUPPORT_MULTIPLE_ADDRESSING       STD_OFF
#endif
#if((CANTP_RX_HAS_STANDARD_ADDRESSING == STD_ON) || (CANTP_TX_HAS_STANDARD_ADDRESSING == STD_ON))
#define CANTP_SUPPORT_STANDARD_ADDRESSING       STD_ON
#else
#define CANTP_SUPPORT_STANDARD_ADDRESSING       STD_OFF
#endif
#if((CANTP_RX_HAS_EXTENDED_ADDRESSING == STD_ON) || (CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON))
#define CANTP_SUPPORT_EXTENDED_ADDRESSING       STD_ON
#else
#define CANTP_SUPPORT_EXTENDED_ADDRESSING       STD_OFF
#endif
#if((CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON))
#define CANTP_SUPPORT_MIXED11_ADDRESSING       STD_ON
#else
#define CANTP_SUPPORT_MIXED11_ADDRESSING       STD_OFF
#endif
#if((CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON))
#define CANTP_SUPPORT_MIXED29_ADDRESSING       STD_ON
#else
#define CANTP_SUPPORT_MIXED29_ADDRESSING       STD_OFF
#endif
#if((CANTP_RX_HAS_NORMALFIXED_ADDRESSING == STD_ON) || (CANTP_TX_HAS_NORMALFIXED_ADDRESSING == STD_ON))
#define CANTP_SUPPORT_NORMALFIXED_ADDRESSING   STD_ON
#else
#define CANTP_SUPPORT_NORMALFIXED_ADDRESSING   STD_OFF
#endif

#define CanTp_Cfg_GetNumRxChannels()                   ((PduIdType)(CanTp_GetSizeOfRxState()))
#define CanTp_Cfg_GetNumRxHdls()                       ((PduIdType)(CanTp_GetSizeOfRxSduCfg()))
#define CanTp_Cfg_GetNumRxPdus()                       ((PduIdType)(CanTp_GetSizeOfRxPduMap()))
#if defined (CanTp_GetSizeOfRxSduSnv2Hdl)
#define CanTp_Cfg_GetNumRxSduIds()                    ((PduIdType)(CanTp_GetSizeOfRxSduSnv2Hdl()))
#else
#define CanTp_Cfg_GetNumRxSduIds()                    ((PduIdType)0)
#endif

#define CanTp_Cfg_GetNumTxChannels()                   ((PduIdType)(CanTp_GetSizeOfTxState()))
#define CanTp_Cfg_GetNumTxConfPdus()                   ((PduIdType)(CanTp_GetSizeOfTxSemaphores()))
#define CanTp_Cfg_GetNumTxHdls()                       ((PduIdType)(CanTp_GetSizeOfTxSduCfg()))
#if defined (CanTp_GetSizeOfTxSduSnv2Hdl)
#define CanTp_Cfg_GetNumTxSduIds()                    ((PduIdType)(CanTp_GetSizeOfTxSduSnv2Hdl()))
#else
#define CanTp_Cfg_GetNumTxSduIds()                    ((PduIdType)0)
#endif

#define CanTp_Cfg_GetAddressingTypeByRxPdu(RxPduId)    ((CanTp_AddressingFormatType)(CanTp_GetAddressingFormatOfRxPduMap((RxPduId))))
#define CanTp_Cfg_IsGenericConnectionByRxPdu(RxPduId)  ((CanTp_IsGenericConnectionOfRxPduMap((RxPduId))))
#define CanTp_Cfg_GetPduMetadataLengthByRxPdu(RxPduId) ((uint8)(CanTp_GetPduMetadataLengthOfRxPduMap((RxPduId))))
#define CanTp_Cfg_GetTaskCycle()                       ((CANTP_TASK_CYCLE))
#define CanTp_RxCfg_GetAddressingFormat(Index)         ((CanTp_GetRxAddressingFormatOfRxSduCfg((Index))))
#define CanTp_RxCfg_GetBS(Index)                       ((uint8)(CanTp_GetBlockSizeOfRxSduCfg((Index))))
#define CanTp_RxCfg_GetLoLayerTxFcPduId(Index)         ((PduIdType)(CanTp_GetLoLayerTxFcPduIdOfRxSduCfg((Index))))
#define CanTp_RxCfg_GetCanType(Index)                  ((CanTp_GetCanTypeOfRxSduCfg((Index))))
#define CanTp_RxCfg_GetChannelMode(Index)              ((CanTp_GetChannelModeOfRxSduCfg((Index))))
#define CanTp_RxCfg_GetLoLayerIdx(Index)               ((uint8)(CanTp_GetLoLayerFctsIdxOfRxSduCfg((Index))))
#define CanTp_RxCfg_GetMaxPayload(Index)               ((uint8)(CanTp_GetRxMaxPayloadLengthOfRxSduCfg((Index))))
#define CanTp_RxCfg_GetNAr(Index)                      ((uint16)(CanTp_GetNArOfRxSduCfg((Index))))
#define CanTp_RxCfg_GetNBr(Index)                      ((uint16)(CanTp_GetNBrOfRxSduCfg((Index))))
#define CanTp_RxCfg_GetNCr(Index)                      ((uint16)(CanTp_GetNCrOfRxSduCfg((Index))))
#define CanTp_RxCfg_HasPaddingActivation(Index)        ((CanTp_IsRxPaddingActivationOfRxSduCfg((Index))))
#define CanTp_RxCfg_GetPduRRxSduId(Index)              ((PduIdType)(CanTp_GetPduRRxSduIdOfRxSduCfg((Index))))
#define CanTp_RxCfg_GetRxAddress(Index)                ((uint8)(CanTp_GetRxAddressOfRxSduCfg((Index))))
#define CanTp_RxCfg_GetRxPduId(Index)                  ((PduIdType)(CanTp_GetRxPduIdOfRxSduCfg((Index))))
#define CanTp_RxCfg_GetSTmin(Index)                    ((uint8)(CanTp_GetSTminOfRxSduCfg((Index))))
#define CanTp_RxCfg_GetSduHdlBySNV(SymbolNameValue)    ((PduIdType)(CanTp_GetRxSduCfgIdxOfRxSduSnv2Hdl((SymbolNameValue))))
#define CanTp_RxCfg_GetTAType(Index)                   ((CanTp_GetRxTaTypeOfRxSduCfg((Index))))
#define CanTp_RxCfg_GetTxFcAddress(Index)              ((uint8)(CanTp_GetTxFcAddressOfRxSduCfg((Index))))
#define CanTp_RxCfg_GetTxFcConfPduId(Index)            ((PduIdType)(CanTp_GetTxFcPduConfirmationPduIdOfRxSduCfg((Index))))
#define CanTp_RxCfg_GetTxSduHdl(Index)                 ((PduIdType)(CanTp_GetTxSduCfgIdxOfRxSduCfg((Index))))
#define CanTp_RxCfg_GetWFTmax(Index)                   ((uint16)(CanTp_GetRxWftMaxOfRxSduCfg((Index))))
#define CanTp_RxCfg_PassSduMetadata(Index)             ((CanTp_IsPassSduMetadataOfRxSduCfg((Index))))
#define CanTp_RxCfg_IsGenericConnection(Index)         ((CanTp_IsGenericConnectionOfRxSduCfg((Index))))
#define CanTp_TxCfg_GetAddressingFormat(Index)         ((CanTp_GetTxAddressingFormatOfTxSduCfg((Index))))
#define CanTp_TxCfg_GetLoLayerTxPduId(Index)           ((PduIdType)(CanTp_GetLoLayerTxPduIdOfTxSduCfg((Index))))
#define CanTp_TxCfg_GetCanType(Index)                  ((CanTp_GetCanTypeOfTxSduCfg((Index))))
#define CanTp_TxCfg_GetChannelMode(Index)              ((CanTp_GetChannelModeOfTxSduCfg((Index))))
#define CanTp_TxCfg_GetLoLayerIdx(Index)               ((uint8)(CanTp_GetLoLayerFctsIdxOfTxSduCfg((Index))))
#define CanTp_TxCfg_GetMaxPayload(Index)               ((uint8)(CanTp_GetTxMaxPayloadLengthOfTxSduCfg((Index))))
#define CanTp_TxCfg_GetNAs(Index)                      ((uint16)(CanTp_GetNAsOfTxSduCfg((Index))))
#define CanTp_TxCfg_GetNBs(Index)                      ((uint16)(CanTp_GetNBsOfTxSduCfg((Index))))
#define CanTp_TxCfg_GetNCs(Index)                      ((uint16)(CanTp_GetNCsOfTxSduCfg((Index))))
#define CanTp_TxCfg_HasPaddingActivation(Index)        ((CanTp_IsTxPaddingActivationOfTxSduCfg((Index))))
#define CanTp_TxCfg_GetPduRTxSduId(Index)              ((PduIdType)(CanTp_GetPduRTxSduIdOfTxSduCfg((Index))))
#define CanTp_TxCfg_GetRxFcAddress(Index)              ((uint8)(CanTp_GetRxFcAddressOfTxSduCfg((Index))))
#define CanTp_TxCfg_GetRxFcPduId(Index)                ((PduIdType)(CanTp_GetRxFcPduIdOfTxSduCfg((Index))))
#define CanTp_TxCfg_GetRxSduHdl(Index)                 ((PduIdType)(CanTp_GetRxSduCfgIdxOfTxSduCfg((Index))))
#define CanTp_TxCfg_GetSduHdlBySNV(SymbolNameValue)    ((PduIdType)(CanTp_GetTxSduCfgIdxOfTxSduSnv2Hdl((SymbolNameValue))))
#define CanTp_TxCfg_GetTAType(Index)                   ((CanTp_GetTxTaTypeOfTxSduCfg((Index))))
#define CanTp_TxCfg_GetTxAddress(Index)                ((uint8)(CanTp_GetTxAddressOfTxSduCfg((Index))))
#define CanTp_TxCfg_HasTxCancel(Index)                 ((CanTp_IsTransmitCancellationOfTxSduCfg((Index))))
#define CanTp_TxCfg_GetTxConfPduId(Index)              ((PduIdType)(CanTp_GetTxPduConfirmationPduIdOfTxSduCfg((Index))))
#define CanTp_TxCfg_GetSduMetadataLength(Index)        ((uint8)(CanTp_GetSduMetadataLengthOfTxSduCfg((Index))))

#if(CANTP_RX_CHECK_ADDRESSING_FORMAT == STD_ON)

#define CanTp_RxGetAdrOffset(RxHdl)             (((CanTp_RxCfg_GetAddressingFormat((RxHdl)) == CANTP_ADDRESS_FORMAT_STANDARD)   || \
                                                   (CanTp_RxCfg_GetAddressingFormat((RxHdl)) == CANTP_ADDRESS_FORMAT_NORMALFIXED)  ) ? ((uint8)0) : ((uint8)1))
#else
#if((CANTP_RX_HAS_STANDARD_ADDRESSING == STD_ON) || (CANTP_RX_HAS_NORMALFIXED_ADDRESSING == STD_ON))

#define CanTp_RxGetAdrOffset(RxHdl)            (uint8)0
#else

#define CanTp_RxGetAdrOffset(RxHdl)            (uint8)1
#endif
#endif

#if(CANTP_TX_CHECK_ADDRESSING_FORMAT == STD_ON)

#define CanTp_TxGetAdrOffset(TxHdl)             (((CanTp_TxCfg_GetAddressingFormat((TxHdl)) == CANTP_ADDRESS_FORMAT_STANDARD)   || \
                                                   (CanTp_TxCfg_GetAddressingFormat((TxHdl)) == CANTP_ADDRESS_FORMAT_NORMALFIXED)  ) ? ((uint8)0) : ((uint8)1))
#else
#if((CANTP_TX_HAS_STANDARD_ADDRESSING == STD_ON) || (CANTP_TX_HAS_NORMALFIXED_ADDRESSING == STD_ON))

#define CanTp_TxGetAdrOffset(TxHdl)            (uint8)0
#else

#define CanTp_TxGetAdrOffset(TxHdl)            (uint8)1
#endif
#endif

#define CanTp_RxCfg_GetMaxPayloadSF(RxHdl)      ((uint8)(CANTP_CAN20_FRAME_LENGTH - (CanTp_RxGetAdrOffset((RxHdl)) + CANTP_PCI_LENGTH_SF)))
#define CanTp_RxCfg_GetMaxPayloadLSF(RxSduHdl)  ((uint8)(CanTp_RxCfg_GetMaxPayload((RxSduHdl)) - 1u))
#define CanTp_RxCfg_GetMaxPayloadFF(RxSduHdl)   ((uint8)(CanTp_RxCfg_GetMaxPayload((RxSduHdl)) - 1u))
#define CanTp_RxCfg_GetMaxPayloadLFF(RxSduHdl)  ((uint8)(CanTp_RxCfg_GetMaxPayload((RxSduHdl)) - 5u))
#define CanTp_RxCfg_GetMaxPayloadCF(RxSduHdl)   ((uint8)(CanTp_RxCfg_GetMaxPayload((RxSduHdl))))

#define CanTp_TxCfg_GetMaxPayloadSF(TxHdl)      ((uint8)(CANTP_CAN20_FRAME_LENGTH - (CanTp_TxGetAdrOffset((TxHdl)) + CANTP_PCI_LENGTH_SF)))
#define CanTp_TxCfg_GetMaxPayloadLSF(TxHdl)     ((uint8)(CanTp_TxCfg_GetMaxPayload((TxHdl)) - 1u))
#define CanTp_TxCfg_GetMaxPayloadFF(TxHdl)      ((uint8)(CanTp_TxCfg_GetMaxPayload((TxHdl)) - 1u))
#define CanTp_TxCfg_GetMaxPayloadLFF(TxHdl)     ((uint8)(CanTp_TxCfg_GetMaxPayload((TxHdl)) - 5u))
#define CanTp_TxCfg_GetMaxPayloadCF(TxHdl)      ((uint8)(CanTp_TxCfg_GetMaxPayload((TxHdl))))

#if((CANTP_RX_CHECK_CANTYPE == STD_ON) || (CANTP_RX_HAS_CANFD == STD_ON))

#define CanTp_RxCfg_GetMaxSFDataLength(RxHdl, DLC)   (((DLC) >  (PduLengthType)CANTP_CAN20_FRAME_LENGTH) ? ((DLC) - (CanTp_RxGetAdrOffset((RxHdl)) + (PduLengthType)CANTP_PCI_LENGTH_LSF)) : (CanTp_RxCfg_GetMaxPayloadSF((RxHdl))))
#else

#define CanTp_RxCfg_GetMaxSFDataLength(RxHdl, DLC)  CanTp_RxCfg_GetMaxPayloadSF((RxHdl))
#endif

#if(CANTP_TX_CHECK_CANTYPE == STD_ON)

#define CanTp_TxCfg_GetMaxSFDataLength(TxHdl)   ((CANTP_CANTYPE_CANFD == CanTp_TxCfg_GetCanType((TxHdl))) ? (CanTp_TxCfg_GetMaxPayloadLSF((TxHdl))) : (CanTp_TxCfg_GetMaxPayloadSF((TxHdl))))
#else
#if(CANTP_TX_HAS_CANFD == STD_ON)

#define CanTp_TxCfg_GetMaxSFDataLength(TxHdl)  CanTp_TxCfg_GetMaxPayloadLSF((TxHdl))
#else

#define CanTp_TxCfg_GetMaxSFDataLength(TxHdl)  CanTp_TxCfg_GetMaxPayloadSF((TxHdl))
#endif
#endif

#define CanTp_Data_RxState(RxChannel)            CanTp_GetRxState((RxChannel))
#define CanTp_Data_TxState(TxChannel)            CanTp_GetTxState((TxChannel))
#define CanTp_Data_RxChannelMap(RxHdl)           CanTp_GetRxChannelMap((RxHdl))
#define CanTp_Data_TxChannelMap(TxHdl)           CanTp_GetTxChannelMap((TxHdl))
#define CanTp_Data_CalcBS(RxHdl)                 CanTp_GetCalcBS((RxHdl))
#define CanTp_Data_DynFcParam(RxHdl)             CanTp_GetDynFCParameters((RxHdl))
#define CanTp_Data_TxSemaphore(TxPdu)            CanTp_GetTxSemaphores((TxPdu))
#define CanTp_Data_TxQueue(TxPdu)                CanTp_GetTxQueue((TxPdu))
#define CanTp_Data_InitState()                   SwcServiceCanTp_InitFunctionState
#define CanTp_Data_CfgPtr()                      CanTp_ConfigDataPtr

#define CanTp_Util_Make16Bit(hiByte, loByte)     ((uint16)((((uint16)(hiByte)) << 8) | ((uint16)(loByte))))

#define CanTp_Util_Make32Bit(hihiByte, hiloByte, lohiByte, loloByte) ((uint32)((((uint32)(hihiByte)) << 24) | (((uint32)(hiloByte)) << 16) | \
                                                                               (((uint32)(lohiByte)) << 8)  | ((uint32)(loloByte))))

#define CanTp_Util_GetHiByte(data)               ((uint8)(((uint16)(data)) >> 8))
#define CanTp_Util_GetLoByte(data)               ((uint8)(data))

#define CanTp_Util_GetHiHiByte(data)             ((uint8)(((uint32)(data)) >> 24))
#define CanTp_Util_GetHiLoByte(data)             ((uint8)(((uint32)(data)) >> 16))
#define CanTp_Util_GetLoHiByte(data)             ((uint8)(((uint32)(data)) >> 8))
#define CanTp_Util_GetLoLoByte(data)             ((uint8)(data))

#define CanTp_RxSduSnvIsAvailable(CanTpRxSduId)        CanTp_IsRxSduCfgUsedOfRxSduSnv2Hdl((CanTpRxSduId))
#define CanTp_TxSduSnvIsAvailable(CanTpTxSduId)        CanTp_IsTxSduCfgUsedOfTxSduSnv2Hdl((CanTpTxSduId))

#define CanTp_RxSdu2TxSduRefIsAvailable(CanTpRxSduId)  CanTp_IsTxSduCfgUsedOfRxSduCfg((CanTpRxSduId))
#define CanTp_TxSdu2RxSduRefIsAvailable(CanTpTxSduId)  CanTp_IsRxSduCfgUsedOfTxSduCfg((CanTpTxSduId))

#if(CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)
#define CanTp_CanIfRxPduHasTxSduRef(CanTpRxPduId)     CanTp_IsTxSduCfgIndUsedOfRxPduMap((CanTpRxPduId))
#else
#define CanTp_CanIfRxPduHasTxSduRef(CanTpRxPduId)     FALSE
#endif
#if(CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)
#define CanTp_CanIfRxPduHasRxSduRef(CanTpRxPduId)     CanTp_IsRxSduCfgIndUsedOfRxPduMap((CanTpRxPduId))
#else
#define CanTp_CanIfRxPduHasRxSduRef(CanTpRxPduId)     FALSE
#endif

#if(CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)
#define CanTp_RxGetSduHdlBySduId(CanTpRxSduId)        (PduIdType)CanTp_GetRxSduCfgIdxOfRxSduSnv2Hdl((CanTpRxSduId))
#else
#define CanTp_RxGetSduHdlBySduId(CanTpRxSduId)        (PduIdType)0
#endif
#if(CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)
#define CanTp_TxGetSduHdlBySduId(CanTpTxSduId)        (PduIdType)CanTp_GetTxSduCfgIdxOfTxSduSnv2Hdl((CanTpTxSduId))
#else
#define CanTp_TxGetSduHdlBySduId(CanTpTxSduId)        (PduIdType)0
#endif

#if(CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
#define CanTp_RxGetChannelPtr(RxHdl)            &CanTp_Data_RxState(CanTp_Data_RxChannelMap((RxHdl)))
#define CanTp_TxGetChannelPtr(TxHdl)            &CanTp_Data_TxState(CanTp_Data_TxChannelMap((TxHdl)))

#define CanTp_RxChannelIsIdle(RxHdl)            (CanTp_Data_RxChannelMap((RxHdl)) == CANTP_INVALID_HDL)
#define CanTp_TxChannelIsIdle(TxHdl)            (CanTp_Data_TxChannelMap((TxHdl)) == CANTP_INVALID_HDL)
#else
#define CanTp_RxGetChannelPtr(RxHdl)            &CanTp_Data_RxState((RxHdl))
#define CanTp_TxGetChannelPtr(TxHdl)            &CanTp_Data_TxState((TxHdl))

#define CanTp_RxChannelIsIdle(RxHdl)            (CanTp_Data_RxState((RxHdl)).ChannelState == CANTP_RXSTATE_IDLE )
#define CanTp_TxChannelIsIdle(TxHdl)            (CanTp_Data_TxState((TxHdl)).ChannelState == CANTP_TXSTATE_IDLE)
#endif

#define CANTP_TX_QUEUE_MASK                      (CANTP_TX_QUEUE_SIZE - 1u)
#define CanTp_TxQueueIsEmpty(Id)                 (CanTp_Data_TxQueue(Id).WritePos == CanTp_Data_TxQueue(Id).ReadPos)
#define CanTp_TxQueueIsFull(Id)                  (((CanTp_Data_TxQueue(Id).WritePos + 1u) & CANTP_TX_QUEUE_MASK) == CanTp_Data_TxQueue(Id).ReadPos)
#define CanTp_TxQueueEntryReadPos(Id)            (CanTp_Data_TxQueue((Id)).Entries[CanTp_Data_TxQueue((Id)).ReadPos])
#define CanTp_TxQueueEntryWritePos(Id)           (CanTp_Data_TxQueue((Id)).Entries[CanTp_Data_TxQueue((Id)).WritePos])

#if(CANTP_ENABLE_CHANGE_PARAM == STD_ON)

#define CanTp_RxGetCurrentSTmin(RxHdl)          CanTp_Data_DynFcParam((RxHdl)).STmin
#define CanTp_RxGetCurrentBS(RxHdl)             CanTp_Data_DynFcParam((RxHdl)).BS
#else

#define CanTp_RxGetCurrentSTmin(RxHdl)          CanTp_RxCfg_GetSTmin((RxHdl))
#define CanTp_RxGetCurrentBS(RxHdl)             CanTp_RxCfg_GetBS((RxHdl))
#endif

typedef uint8                                    CanTp_CanType;

typedef uint8                                    CanTp_TxResultType;
#define CANTP_TX_OK                              E_OK
#define CANTP_TX_NOT_OK                          E_NOT_OK
#define CANTP_TX_BUSY                            (0x0Fu)

typedef uint8                                    CanTp_ResetControlType;
#define CANTP_RESET_BUT_KEEP_MAPPING             (CanTp_ResetControlType)(0x00u)
#define CANTP_RESET_ALL                          (CanTp_ResetControlType)(0x01u)

typedef struct sCanTp_PduTxInfoType{
  CanTp_DirectionType    SduDirection;
  PduIdType              SduHdl;
  PduIdType              TxPduId;
  PduIdType              TxConfPduId;
#if(CANTP_PADDING_SUPPORT_REQUIRED == STD_ON)
  uint8                  PaddingLength;
#endif
#if(CANTP_MAX_PDU_METADATA_LENGTH != 0)
  uint8*                 PduMetadata;
  uint8                  PduMetadataLength;
#endif
}CanTp_PduTxInfoType;

#if((CANTP_STANDARD_ADDRESSING != STD_ON) && \
     (CANTP_EXTENDED_ADDRESSING != STD_ON) && \
     (CANTP_MIXED11_ADDRESSING != STD_ON)  && \
     (CANTP_MIXED29_ADDRESSING != STD_ON)  && \
     (CANTP_NORMALFIXED_ADDRESSING != STD_ON))
# error "No Addressing Format is configured!"
#endif

#if((CANTP_DEV_ERROR_REPORT == STD_ON) && (CANTP_DEV_ERROR_DETECT == STD_OFF))
# error "DET reporting is only allowed if DET checks are enabled!"
#endif

#if(CANTP_USE_INIT_POINTER != STD_ON)
#if(CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)

#if((CANTP_NUM_RX_CHANNELS > CANTP_NUM_RX_SDUS) || \
       (CANTP_NUM_TX_CHANNELS > CANTP_NUM_TX_SDUS))
#   error "Inconsistent setting for number of channels; with dynamic channel assignment, more SDUs than channels are expected"
#endif
#else

#if(CANTP_NUM_RX_SDUS == 0)
#if(CANTP_NUM_RX_CHANNELS != 1)
#    error "Inconsistent setting for number of channels; even if no SDU is configured, the config tool should generate at least one dummy channel"
#endif
#else
#if(CANTP_NUM_RX_CHANNELS != CANTP_NUM_RX_SDUS)
#    error "Inconsistent setting for number of channels; in the current configuration, it is expected that for each SDU a separate channel exists"
#endif
#endif

#if(CANTP_NUM_TX_SDUS == 0)
#if(CANTP_NUM_TX_CHANNELS != 1)
#    error "Inconsistent setting for number of channels; even if no SDU is configured, the config tool should generate at least one dummy channel"
#endif
#else
#if(CANTP_NUM_TX_CHANNELS != CANTP_NUM_TX_SDUS)
#    error "Inconsistent setting for number of channels; in the current configuration, it is expected that for each SDU a separate channel exists"
#endif
#endif
#endif
#endif

#if((CANTP_RX_CHECK_HALF_DUPLEX == STD_OFF) && (CANTP_RX_HAS_HALF_DUPLEX == CANTP_RX_HAS_FULL_DUPLEX))
# error "Inconsistent Rx channel mode configuration; either half or full duplex must be configured!"
#endif
#if((CANTP_TX_CHECK_HALF_DUPLEX == STD_OFF) && (CANTP_TX_HAS_HALF_DUPLEX == CANTP_TX_HAS_FULL_DUPLEX))
# error "Inconsistent Tx channel mode configuration; either half or full duplex must be configured!"
#endif

#if((CANTP_RX_CHECK_CANTYPE == STD_OFF) && (CANTP_RX_HAS_CANFD == CANTP_RX_HAS_CAN20))
# error "Inconsistent Rx CanType configuration; either CAN-FD or CAN2.0 must be configured!"
#endif
#if((CANTP_TX_CHECK_CANTYPE == STD_OFF) && (CANTP_TX_HAS_CANFD == CANTP_TX_HAS_CAN20))
# error "Inconsistent Rx CanType configuration; either CAN-FD or CAN2.0 must be configured!"
#endif

#if((CANTP_IGNORE_FC_WITH_RES_STMIN == STD_ON) && \
     (CANTP_REJECT_FC_WITH_RES_STMIN == STD_ON))
# error "Inconsistent setting for handling of reserved STmin"
#endif

#if((CANTP_MAX_PDU_METADATA_LENGTH != 0) && (CANTP_NORMALFIXED_ADDRESSING == STD_OFF) && (CANTP_MIXED29_ADDRESSING == STD_OFF))
# error "Inconsistent PDU metadata configuration. Only the normal fixed and mixed29 addressing modes use PDU metadata!"
#endif

#endif

