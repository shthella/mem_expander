#define RX_ID 0x1000
#define RX_ID__FRAGMENTMAP_bp 16
#define RX_ID__FRAGMENTMAP_bw 12
#define RX_ID__FRAGMENTMAP_bm 0xfff0000
#define RX_ID__IMPLEMENTATION_bp 8
#define RX_ID__IMPLEMENTATION_bw 8
#define RX_ID__IMPLEMENTATION_bm 0xff00
#define RX_ID__VERSION_bp 0
#define RX_ID__VERSION_bw 8
#define RX_ID__VERSION_bm 0xff
#define RX_INTERFACE_CONTROL_STATUS 0x1004
#define RX_INTERFACE_CONTROL_STATUS__PHYREADY_bp 11
#define RX_INTERFACE_CONTROL_STATUS__PHYREADY_bw 2
#define RX_INTERFACE_CONTROL_STATUS__PHYREADY_bm 0x1800
#define RX_INTERFACE_CONTROL_STATUS__PHYRESET_bp 7
#define RX_INTERFACE_CONTROL_STATUS__PHYRESET_bw 2
#define RX_INTERFACE_CONTROL_STATUS__PHYRESET_bm 0x180
#define RX_INTERFACE_CONTROL_STATUS__LINKRESET_bp 6
#define RX_INTERFACE_CONTROL_STATUS__LINKRESET_bw 1
#define RX_INTERFACE_CONTROL_STATUS__LINKRESET_bm 0x40
#define RX_INTERFACE_CONTROL_STATUS__NUMSLICES_bp 4
#define RX_INTERFACE_CONTROL_STATUS__NUMSLICES_bw 2
#define RX_INTERFACE_CONTROL_STATUS__NUMSLICES_bm 0x30
#define RX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bp 2
#define RX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bw 2
#define RX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bm 0xc
#define RX_INTERFACE_CONTROL_STATUS__MODE_bp 0
#define RX_INTERFACE_CONTROL_STATUS__MODE_bw 2
#define RX_INTERFACE_CONTROL_STATUS__MODE_bm 0x3
#define DDIF_RAS_BANK0_CTRL 0x1020
#define DDIF_RAS_BANK0_CTRL__ERRINJECTDLY_bp 16
#define DDIF_RAS_BANK0_CTRL__ERRINJECTDLY_bw 16
#define DDIF_RAS_BANK0_CTRL__ERRINJECTDLY_bm 0xffff0000
#define DDIF_RAS_BANK0_CTRL__TOTALBANKS_bp 11
#define DDIF_RAS_BANK0_CTRL__TOTALBANKS_bw 5
#define DDIF_RAS_BANK0_CTRL__TOTALBANKS_bm 0xf800
#define DDIF_RAS_BANK0_CTRL__NONCRITERRINTREN_bp 4
#define DDIF_RAS_BANK0_CTRL__NONCRITERRINTREN_bw 1
#define DDIF_RAS_BANK0_CTRL__NONCRITERRINTREN_bm 0x10
#define DDIF_RAS_BANK0_CTRL__FATALERRINTREN_bp 3
#define DDIF_RAS_BANK0_CTRL__FATALERRINTREN_bw 1
#define DDIF_RAS_BANK0_CTRL__FATALERRINTREN_bm 0x8
#define DDIF_RAS_BANK0_CTRL__NMIEN_bp 2
#define DDIF_RAS_BANK0_CTRL__NMIEN_bw 1
#define DDIF_RAS_BANK0_CTRL__NMIEN_bm 0x4
#define DDIF_RAS_BANK0_CTRL__LOGEN_bp 1
#define DDIF_RAS_BANK0_CTRL__LOGEN_bw 1
#define DDIF_RAS_BANK0_CTRL__LOGEN_bm 0x2
#define DDIF_RAS_BANK0_CTRL__CORRRECOVDIS_bp 0
#define DDIF_RAS_BANK0_CTRL__CORRRECOVDIS_bw 1
#define DDIF_RAS_BANK0_CTRL__CORRRECOVDIS_bm 0x1
#define DDIF_RAS_BANK0_STATUS 0x1024
#define DDIF_RAS_BANK0_STATUS__BANKSTATUS_bp 5
#define DDIF_RAS_BANK0_STATUS__BANKSTATUS_bw 27
#define DDIF_RAS_BANK0_STATUS__BANKSTATUS_bm 0xffffffe0
#define DDIF_RAS_BANK0_STATUS__NONCRITERRINTRPEND_bp 4
#define DDIF_RAS_BANK0_STATUS__NONCRITERRINTRPEND_bw 1
#define DDIF_RAS_BANK0_STATUS__NONCRITERRINTRPEND_bm 0x10
#define DDIF_RAS_BANK0_STATUS__FATALERRINTRPEND_bp 3
#define DDIF_RAS_BANK0_STATUS__FATALERRINTRPEND_bw 1
#define DDIF_RAS_BANK0_STATUS__FATALERRINTRPEND_bm 0x8
#define DDIF_RAS_BANK0_STATUS__NMIPEND_bp 2
#define DDIF_RAS_BANK0_STATUS__NMIPEND_bw 1
#define DDIF_RAS_BANK0_STATUS__NMIPEND_bm 0x4
#define DDIF_RAS_BANK0_STATUS__RECENTERR_bp 1
#define DDIF_RAS_BANK0_STATUS__RECENTERR_bw 1
#define DDIF_RAS_BANK0_STATUS__RECENTERR_bm 0x2
#define DDIF_RAS_BANK0_STATUS__VALID_bp 0
#define DDIF_RAS_BANK0_STATUS__VALID_bw 1
#define DDIF_RAS_BANK0_STATUS__VALID_bm 0x1
#define DDIF_RAS_BANK1_CTRL 0x1028
#define DDIF_RAS_BANK1_CTRL__NONCRITERRCINTREN_bp 5
#define DDIF_RAS_BANK1_CTRL__NONCRITERRCINTREN_bw 1
#define DDIF_RAS_BANK1_CTRL__NONCRITERRCINTREN_bm 0x20
#define DDIF_RAS_BANK1_CTRL__NONCRITERRDINTREN_bp 4
#define DDIF_RAS_BANK1_CTRL__NONCRITERRDINTREN_bw 1
#define DDIF_RAS_BANK1_CTRL__NONCRITERRDINTREN_bm 0x10
#define DDIF_RAS_BANK1_CTRL__FATALERRINTREN_bp 3
#define DDIF_RAS_BANK1_CTRL__FATALERRINTREN_bw 1
#define DDIF_RAS_BANK1_CTRL__FATALERRINTREN_bm 0x8
#define DDIF_RAS_BANK1_CTRL__NMIEN_bp 2
#define DDIF_RAS_BANK1_CTRL__NMIEN_bw 1
#define DDIF_RAS_BANK1_CTRL__NMIEN_bm 0x4
#define DDIF_RAS_BANK1_CTRL__LOGEN_bp 1
#define DDIF_RAS_BANK1_CTRL__LOGEN_bw 1
#define DDIF_RAS_BANK1_CTRL__LOGEN_bm 0x2
#define DDIF_RAS_BANK1_CTRL__CORRRECOVDIS_bp 0
#define DDIF_RAS_BANK1_CTRL__CORRRECOVDIS_bw 1
#define DDIF_RAS_BANK1_CTRL__CORRRECOVDIS_bm 0x1
#define DDIF_RAS_BANK1_STATUS 0x102C
#define DDIF_RAS_BANK1_STATUS__CORRERRCNT_bp 20
#define DDIF_RAS_BANK1_STATUS__CORRERRCNT_bw 12
#define DDIF_RAS_BANK1_STATUS__CORRERRCNT_bm 0xfff00000
#define DDIF_RAS_BANK1_STATUS__ACCESSTYPE_bp 16
#define DDIF_RAS_BANK1_STATUS__ACCESSTYPE_bw 4
#define DDIF_RAS_BANK1_STATUS__ACCESSTYPE_bm 0xf0000
#define DDIF_RAS_BANK1_STATUS__ERRTYPE_bp 8
#define DDIF_RAS_BANK1_STATUS__ERRTYPE_bw 8
#define DDIF_RAS_BANK1_STATUS__ERRTYPE_bm 0xff00
#define DDIF_RAS_BANK1_STATUS__INFOVLD_bp 7
#define DDIF_RAS_BANK1_STATUS__INFOVLD_bw 1
#define DDIF_RAS_BANK1_STATUS__INFOVLD_bm 0x80
#define DDIF_RAS_BANK1_STATUS__ADDRVLD_bp 6
#define DDIF_RAS_BANK1_STATUS__ADDRVLD_bw 1
#define DDIF_RAS_BANK1_STATUS__ADDRVLD_bm 0x40
#define DDIF_RAS_BANK1_STATUS__ERRLOGOVERFLOW_bp 5
#define DDIF_RAS_BANK1_STATUS__ERRLOGOVERFLOW_bw 1
#define DDIF_RAS_BANK1_STATUS__ERRLOGOVERFLOW_bm 0x20
#define DDIF_RAS_BANK1_STATUS__CECOVERFLOW_bp 4
#define DDIF_RAS_BANK1_STATUS__CECOVERFLOW_bw 1
#define DDIF_RAS_BANK1_STATUS__CECOVERFLOW_bm 0x10
#define DDIF_RAS_BANK1_STATUS__DEFERREDERR_bp 3
#define DDIF_RAS_BANK1_STATUS__DEFERREDERR_bw 1
#define DDIF_RAS_BANK1_STATUS__DEFERREDERR_bm 0x8
#define DDIF_RAS_BANK1_STATUS__CRITICALERR_bp 2
#define DDIF_RAS_BANK1_STATUS__CRITICALERR_bw 1
#define DDIF_RAS_BANK1_STATUS__CRITICALERR_bm 0x4
#define DDIF_RAS_BANK1_STATUS__ERRDETLOGGED_bp 1
#define DDIF_RAS_BANK1_STATUS__ERRDETLOGGED_bw 1
#define DDIF_RAS_BANK1_STATUS__ERRDETLOGGED_bm 0x2
#define DDIF_RAS_BANK1_STATUS__VALID_bp 0
#define DDIF_RAS_BANK1_STATUS__VALID_bw 1
#define DDIF_RAS_BANK1_STATUS__VALID_bm 0x1
#define DDIF_RAS_BANK1_ADDR_L 0x1030
#define DDIF_RAS_BANK1_ADDR_L__BI32BIT_bp 0
#define DDIF_RAS_BANK1_ADDR_L__BI32BIT_bw 32
#define DDIF_RAS_BANK1_ADDR_L__BI32BIT_bm 0xffffffff
#define DDIF_RAS_BANK1_ADDR_H 0x1034
#define DDIF_RAS_BANK1_ADDR_H__BI32BIT_bp 0
#define DDIF_RAS_BANK1_ADDR_H__BI32BIT_bw 32
#define DDIF_RAS_BANK1_ADDR_H__BI32BIT_bm 0xffffffff
#define DDIF_RAS_BANK1_INFO_L 0x1038
#define DDIF_RAS_BANK1_INFO_L__BI32BIT_bp 0
#define DDIF_RAS_BANK1_INFO_L__BI32BIT_bw 32
#define DDIF_RAS_BANK1_INFO_L__BI32BIT_bm 0xffffffff
#define DDIF_RAS_BANK1_INFO_H 0x103C
#define DDIF_RAS_BANK1_INFO_H__BI32BIT_bp 0
#define DDIF_RAS_BANK1_INFO_H__BI32BIT_bw 32
#define DDIF_RAS_BANK1_INFO_H__BI32BIT_bm 0xffffffff
#define DDIF_RAS_BANK2_CTRL 0x1040
#define DDIF_RAS_BANK2_CTRL__NONCRITERRCINTREN_bp 5
#define DDIF_RAS_BANK2_CTRL__NONCRITERRCINTREN_bw 1
#define DDIF_RAS_BANK2_CTRL__NONCRITERRCINTREN_bm 0x20
#define DDIF_RAS_BANK2_CTRL__NONCRITERRDINTREN_bp 4
#define DDIF_RAS_BANK2_CTRL__NONCRITERRDINTREN_bw 1
#define DDIF_RAS_BANK2_CTRL__NONCRITERRDINTREN_bm 0x10
#define DDIF_RAS_BANK2_CTRL__FATALERRINTREN_bp 3
#define DDIF_RAS_BANK2_CTRL__FATALERRINTREN_bw 1
#define DDIF_RAS_BANK2_CTRL__FATALERRINTREN_bm 0x8
#define DDIF_RAS_BANK2_CTRL__NMIEN_bp 2
#define DDIF_RAS_BANK2_CTRL__NMIEN_bw 1
#define DDIF_RAS_BANK2_CTRL__NMIEN_bm 0x4
#define DDIF_RAS_BANK2_CTRL__LOGEN_bp 1
#define DDIF_RAS_BANK2_CTRL__LOGEN_bw 1
#define DDIF_RAS_BANK2_CTRL__LOGEN_bm 0x2
#define DDIF_RAS_BANK2_CTRL__CORRRECOVDIS_bp 0
#define DDIF_RAS_BANK2_CTRL__CORRRECOVDIS_bw 1
#define DDIF_RAS_BANK2_CTRL__CORRRECOVDIS_bm 0x1
#define DDIF_RAS_BANK2_STATUS 0x1044
#define DDIF_RAS_BANK2_STATUS__CORRERRCNT_bp 20
#define DDIF_RAS_BANK2_STATUS__CORRERRCNT_bw 12
#define DDIF_RAS_BANK2_STATUS__CORRERRCNT_bm 0xfff00000
#define DDIF_RAS_BANK2_STATUS__ACCESSTYPE_bp 16
#define DDIF_RAS_BANK2_STATUS__ACCESSTYPE_bw 4
#define DDIF_RAS_BANK2_STATUS__ACCESSTYPE_bm 0xf0000
#define DDIF_RAS_BANK2_STATUS__ERRTYPE_bp 8
#define DDIF_RAS_BANK2_STATUS__ERRTYPE_bw 8
#define DDIF_RAS_BANK2_STATUS__ERRTYPE_bm 0xff00
#define DDIF_RAS_BANK2_STATUS__INFOVLD_bp 7
#define DDIF_RAS_BANK2_STATUS__INFOVLD_bw 1
#define DDIF_RAS_BANK2_STATUS__INFOVLD_bm 0x80
#define DDIF_RAS_BANK2_STATUS__ADDRVLD_bp 6
#define DDIF_RAS_BANK2_STATUS__ADDRVLD_bw 1
#define DDIF_RAS_BANK2_STATUS__ADDRVLD_bm 0x40
#define DDIF_RAS_BANK2_STATUS__ERRLOGOVERFLOW_bp 5
#define DDIF_RAS_BANK2_STATUS__ERRLOGOVERFLOW_bw 1
#define DDIF_RAS_BANK2_STATUS__ERRLOGOVERFLOW_bm 0x20
#define DDIF_RAS_BANK2_STATUS__CECOVERFLOW_bp 4
#define DDIF_RAS_BANK2_STATUS__CECOVERFLOW_bw 1
#define DDIF_RAS_BANK2_STATUS__CECOVERFLOW_bm 0x10
#define DDIF_RAS_BANK2_STATUS__DEFERREDERR_bp 3
#define DDIF_RAS_BANK2_STATUS__DEFERREDERR_bw 1
#define DDIF_RAS_BANK2_STATUS__DEFERREDERR_bm 0x8
#define DDIF_RAS_BANK2_STATUS__CRITICALERR_bp 2
#define DDIF_RAS_BANK2_STATUS__CRITICALERR_bw 1
#define DDIF_RAS_BANK2_STATUS__CRITICALERR_bm 0x4
#define DDIF_RAS_BANK2_STATUS__ERRDETLOGGED_bp 1
#define DDIF_RAS_BANK2_STATUS__ERRDETLOGGED_bw 1
#define DDIF_RAS_BANK2_STATUS__ERRDETLOGGED_bm 0x2
#define DDIF_RAS_BANK2_STATUS__VALID_bp 0
#define DDIF_RAS_BANK2_STATUS__VALID_bw 1
#define DDIF_RAS_BANK2_STATUS__VALID_bm 0x1
#define DDIF_RAS_BANK2_ADDR_L 0x1048
#define DDIF_RAS_BANK2_ADDR_L__BI32BIT_bp 0
#define DDIF_RAS_BANK2_ADDR_L__BI32BIT_bw 32
#define DDIF_RAS_BANK2_ADDR_L__BI32BIT_bm 0xffffffff
#define DDIF_RAS_BANK2_ADDR_H 0x104C
#define DDIF_RAS_BANK2_ADDR_H__BI32BIT_bp 0
#define DDIF_RAS_BANK2_ADDR_H__BI32BIT_bw 32
#define DDIF_RAS_BANK2_ADDR_H__BI32BIT_bm 0xffffffff
#define DDIF_RAS_BANK2_INFO_L 0x1050
#define DDIF_RAS_BANK2_INFO_L__BI32BIT_bp 0
#define DDIF_RAS_BANK2_INFO_L__BI32BIT_bw 32
#define DDIF_RAS_BANK2_INFO_L__BI32BIT_bm 0xffffffff
#define DDIF_RAS_BANK2_INFO_H 0x1054
#define DDIF_RAS_BANK2_INFO_H__BI32BIT_bp 0
#define DDIF_RAS_BANK2_INFO_H__BI32BIT_bw 32
#define DDIF_RAS_BANK2_INFO_H__BI32BIT_bm 0xffffffff
#define RX_TLP_MSG0 0x1100
#define RX_TLP_MSG0__CLEARRECEIVED_bp 7
#define RX_TLP_MSG0__CLEARRECEIVED_bw 1
#define RX_TLP_MSG0__CLEARRECEIVED_bm 0x20000
#define RX_TLP_MSG0__RECEIVED_bp 6
#define RX_TLP_MSG0__RECEIVED_bw 1
#define RX_TLP_MSG0__RECEIVED_bm 0x10000
#define RX_TLP_MSG0__MESSAGEDATA_bp 0
#define RX_TLP_MSG0__MESSAGEDATA_bw 16
#define RX_TLP_MSG0__MESSAGEDATA_bm 0xffff
#define RX_TRAIN_TRIG_SAMPLE 0x1140
#define RX_TRAIN_TRIG_SAMPLE__TRAINTRIGSAMPLE_bp 0
#define RX_TRAIN_TRIG_SAMPLE__TRAINTRIGSAMPLE_bw 1
#define RX_TRAIN_TRIG_SAMPLE__TRAINTRIGSAMPLE_bm 0x1
#define RX_TRAIN_NUDGE 0x1144
#define RX_TRAIN_NUDGE__NUDGE1_bp 2
#define RX_TRAIN_NUDGE__NUDGE1_bw 2
#define RX_TRAIN_NUDGE__NUDGE1_bm 0xc
#define RX_TRAIN_NUDGE__NUDGE0_bp 0
#define RX_TRAIN_NUDGE__NUDGE0_bw 2
#define RX_TRAIN_NUDGE__NUDGE0_bm 0x3
#define RX_TRAIN_PTRS 0x1148
#define RX_TRAIN_PTRS__READPTR1_bp 9
#define RX_TRAIN_PTRS__READPTR1_bw 3
#define RX_TRAIN_PTRS__READPTR1_bm 0xe00
#define RX_TRAIN_PTRS__WRITEPTR1_bp 6
#define RX_TRAIN_PTRS__WRITEPTR1_bw 3
#define RX_TRAIN_PTRS__WRITEPTR1_bm 0x1c0
#define RX_TRAIN_PTRS__READPTR0_bp 3
#define RX_TRAIN_PTRS__READPTR0_bw 3
#define RX_TRAIN_PTRS__READPTR0_bm 0x38
#define RX_TRAIN_PTRS__WRITEPTR0_bp 0
#define RX_TRAIN_PTRS__WRITEPTR0_bw 3
#define RX_TRAIN_PTRS__WRITEPTR0_bm 0x7
#define DDIF_FLIT_SAMPLE00 0x1400
#define DDIF_FLIT_SAMPLE00__DATA_bp 0
#define DDIF_FLIT_SAMPLE00__DATA_bw 32
#define DDIF_FLIT_SAMPLE00__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE01 0x1404
#define DDIF_FLIT_SAMPLE01__DATA_bp 0
#define DDIF_FLIT_SAMPLE01__DATA_bw 32
#define DDIF_FLIT_SAMPLE01__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE02 0x1408
#define DDIF_FLIT_SAMPLE02__DATA_bp 0
#define DDIF_FLIT_SAMPLE02__DATA_bw 32
#define DDIF_FLIT_SAMPLE02__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE03 0x140C
#define DDIF_FLIT_SAMPLE03__DATA_bp 0
#define DDIF_FLIT_SAMPLE03__DATA_bw 32
#define DDIF_FLIT_SAMPLE03__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE04 0x1410
#define DDIF_FLIT_SAMPLE04__DATA_bp 0
#define DDIF_FLIT_SAMPLE04__DATA_bw 32
#define DDIF_FLIT_SAMPLE04__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE05 0x1414
#define DDIF_FLIT_SAMPLE05__DATA_bp 0
#define DDIF_FLIT_SAMPLE05__DATA_bw 32
#define DDIF_FLIT_SAMPLE05__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE06 0x1418
#define DDIF_FLIT_SAMPLE06__DATA_bp 0
#define DDIF_FLIT_SAMPLE06__DATA_bw 32
#define DDIF_FLIT_SAMPLE06__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE07 0x141C
#define DDIF_FLIT_SAMPLE07__DATA_bp 0
#define DDIF_FLIT_SAMPLE07__DATA_bw 32
#define DDIF_FLIT_SAMPLE07__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE08 0x1420
#define DDIF_FLIT_SAMPLE08__DATA_bp 0
#define DDIF_FLIT_SAMPLE08__DATA_bw 32
#define DDIF_FLIT_SAMPLE08__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE09 0x1424
#define DDIF_FLIT_SAMPLE09__DATA_bp 0
#define DDIF_FLIT_SAMPLE09__DATA_bw 32
#define DDIF_FLIT_SAMPLE09__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE0A 0x1428
#define DDIF_FLIT_SAMPLE0A__DATA_bp 0
#define DDIF_FLIT_SAMPLE0A__DATA_bw 32
#define DDIF_FLIT_SAMPLE0A__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE0B 0x142C
#define DDIF_FLIT_SAMPLE0B__DATA_bp 0
#define DDIF_FLIT_SAMPLE0B__DATA_bw 32
#define DDIF_FLIT_SAMPLE0B__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE0C 0x1430
#define DDIF_FLIT_SAMPLE0C__DATA_bp 0
#define DDIF_FLIT_SAMPLE0C__DATA_bw 32
#define DDIF_FLIT_SAMPLE0C__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE0D 0x1434
#define DDIF_FLIT_SAMPLE0D__DATA_bp 0
#define DDIF_FLIT_SAMPLE0D__DATA_bw 32
#define DDIF_FLIT_SAMPLE0D__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE0E 0x1438
#define DDIF_FLIT_SAMPLE0E__DATA_bp 0
#define DDIF_FLIT_SAMPLE0E__DATA_bw 32
#define DDIF_FLIT_SAMPLE0E__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE0F 0x143C
#define DDIF_FLIT_SAMPLE0F__DATA_bp 0
#define DDIF_FLIT_SAMPLE0F__DATA_bw 32
#define DDIF_FLIT_SAMPLE0F__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE10 0x1440
#define DDIF_FLIT_SAMPLE10__DATA_bp 0
#define DDIF_FLIT_SAMPLE10__DATA_bw 32
#define DDIF_FLIT_SAMPLE10__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE11 0x1444
#define DDIF_FLIT_SAMPLE11__DATA_bp 0
#define DDIF_FLIT_SAMPLE11__DATA_bw 32
#define DDIF_FLIT_SAMPLE11__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE12 0x1448
#define DDIF_FLIT_SAMPLE12__DATA_bp 0
#define DDIF_FLIT_SAMPLE12__DATA_bw 32
#define DDIF_FLIT_SAMPLE12__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE13 0x144C
#define DDIF_FLIT_SAMPLE13__DATA_bp 0
#define DDIF_FLIT_SAMPLE13__DATA_bw 32
#define DDIF_FLIT_SAMPLE13__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE14 0x1450
#define DDIF_FLIT_SAMPLE14__DATA_bp 0
#define DDIF_FLIT_SAMPLE14__DATA_bw 32
#define DDIF_FLIT_SAMPLE14__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE15 0x1454
#define DDIF_FLIT_SAMPLE15__DATA_bp 0
#define DDIF_FLIT_SAMPLE15__DATA_bw 32
#define DDIF_FLIT_SAMPLE15__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE16 0x1458
#define DDIF_FLIT_SAMPLE16__DATA_bp 0
#define DDIF_FLIT_SAMPLE16__DATA_bw 32
#define DDIF_FLIT_SAMPLE16__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE17 0x145C
#define DDIF_FLIT_SAMPLE17__DATA_bp 0
#define DDIF_FLIT_SAMPLE17__DATA_bw 32
#define DDIF_FLIT_SAMPLE17__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE18 0x1460
#define DDIF_FLIT_SAMPLE18__DATA_bp 0
#define DDIF_FLIT_SAMPLE18__DATA_bw 32
#define DDIF_FLIT_SAMPLE18__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE19 0x1464
#define DDIF_FLIT_SAMPLE19__DATA_bp 0
#define DDIF_FLIT_SAMPLE19__DATA_bw 32
#define DDIF_FLIT_SAMPLE19__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE1A 0x1468
#define DDIF_FLIT_SAMPLE1A__DATA_bp 0
#define DDIF_FLIT_SAMPLE1A__DATA_bw 32
#define DDIF_FLIT_SAMPLE1A__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE1B 0x146C
#define DDIF_FLIT_SAMPLE1B__DATA_bp 0
#define DDIF_FLIT_SAMPLE1B__DATA_bw 32
#define DDIF_FLIT_SAMPLE1B__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE1C 0x1470
#define DDIF_FLIT_SAMPLE1C__DATA_bp 0
#define DDIF_FLIT_SAMPLE1C__DATA_bw 32
#define DDIF_FLIT_SAMPLE1C__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE1D 0x1474
#define DDIF_FLIT_SAMPLE1D__DATA_bp 0
#define DDIF_FLIT_SAMPLE1D__DATA_bw 32
#define DDIF_FLIT_SAMPLE1D__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE1E 0x1478
#define DDIF_FLIT_SAMPLE1E__DATA_bp 0
#define DDIF_FLIT_SAMPLE1E__DATA_bw 32
#define DDIF_FLIT_SAMPLE1E__DATA_bm 0xffffffff
#define DDIF_FLIT_SAMPLE1F 0x147C
#define DDIF_FLIT_SAMPLE1F__DATA_bp 0
#define DDIF_FLIT_SAMPLE1F__DATA_bw 32
#define DDIF_FLIT_SAMPLE1F__DATA_bm 0xffffffff
#define RX_VIRTUAL_WIRE_DISABLE00 0x1800
#define RX_VIRTUAL_WIRE_DISABLE00__DISABLE_bp 0
#define RX_VIRTUAL_WIRE_DISABLE00__DISABLE_bw 10
#define RX_VIRTUAL_WIRE_DISABLE00__DISABLE_bm 0x3ff
#define RX_VIRTUAL_WIRE_SET00 0x1880
#define RX_VIRTUAL_WIRE_SET00__WIRE_bp 0
#define RX_VIRTUAL_WIRE_SET00__WIRE_bw 10
#define RX_VIRTUAL_WIRE_SET00__WIRE_bm 0x3ff
#define RX_VIRTUAL_WIRE_CLEAR00 0x1900
#define RX_VIRTUAL_WIRE_CLEAR00__WIRE_bp 0
#define RX_VIRTUAL_WIRE_CLEAR00__WIRE_bw 10
#define RX_VIRTUAL_WIRE_CLEAR00__WIRE_bm 0x3ff
#define RX_NEAR_CREDIT_CONFIG08 0x1C20
#define RX_NEAR_CREDIT_CONFIG08__COUNT_bp 0
#define RX_NEAR_CREDIT_CONFIG08__COUNT_bw 10
#define RX_NEAR_CREDIT_CONFIG08__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_CONFIG09 0x1C24
#define RX_NEAR_CREDIT_CONFIG09__COUNT_bp 0
#define RX_NEAR_CREDIT_CONFIG09__COUNT_bw 10
#define RX_NEAR_CREDIT_CONFIG09__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_CONFIG0A 0x1C28
#define RX_NEAR_CREDIT_CONFIG0A__COUNT_bp 0
#define RX_NEAR_CREDIT_CONFIG0A__COUNT_bw 10
#define RX_NEAR_CREDIT_CONFIG0A__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_CONFIG0B 0x1C2C
#define RX_NEAR_CREDIT_CONFIG0B__COUNT_bp 0
#define RX_NEAR_CREDIT_CONFIG0B__COUNT_bw 10
#define RX_NEAR_CREDIT_CONFIG0B__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_CONFIG10 0x1C40
#define RX_NEAR_CREDIT_CONFIG10__COUNT_bp 0
#define RX_NEAR_CREDIT_CONFIG10__COUNT_bw 10
#define RX_NEAR_CREDIT_CONFIG10__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_CONFIG11 0x1C44
#define RX_NEAR_CREDIT_CONFIG11__COUNT_bp 0
#define RX_NEAR_CREDIT_CONFIG11__COUNT_bw 10
#define RX_NEAR_CREDIT_CONFIG11__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_CONFIG12 0x1C48
#define RX_NEAR_CREDIT_CONFIG12__COUNT_bp 0
#define RX_NEAR_CREDIT_CONFIG12__COUNT_bw 10
#define RX_NEAR_CREDIT_CONFIG12__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_CONFIG13 0x1C4C
#define RX_NEAR_CREDIT_CONFIG13__COUNT_bp 0
#define RX_NEAR_CREDIT_CONFIG13__COUNT_bw 10
#define RX_NEAR_CREDIT_CONFIG13__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_CONFIG14 0x1C50
#define RX_NEAR_CREDIT_CONFIG14__COUNT_bp 0
#define RX_NEAR_CREDIT_CONFIG14__COUNT_bw 10
#define RX_NEAR_CREDIT_CONFIG14__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_LIMIT08 0x1D20
#define RX_NEAR_CREDIT_LIMIT08__COUNT_bp 0
#define RX_NEAR_CREDIT_LIMIT08__COUNT_bw 10
#define RX_NEAR_CREDIT_LIMIT08__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_LIMIT09 0x1D24
#define RX_NEAR_CREDIT_LIMIT09__COUNT_bp 0
#define RX_NEAR_CREDIT_LIMIT09__COUNT_bw 10
#define RX_NEAR_CREDIT_LIMIT09__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_LIMIT0A 0x1D28
#define RX_NEAR_CREDIT_LIMIT0A__COUNT_bp 0
#define RX_NEAR_CREDIT_LIMIT0A__COUNT_bw 10
#define RX_NEAR_CREDIT_LIMIT0A__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_LIMIT0B 0x1D2C
#define RX_NEAR_CREDIT_LIMIT0B__COUNT_bp 0
#define RX_NEAR_CREDIT_LIMIT0B__COUNT_bw 10
#define RX_NEAR_CREDIT_LIMIT0B__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_LIMIT10 0x1D40
#define RX_NEAR_CREDIT_LIMIT10__COUNT_bp 0
#define RX_NEAR_CREDIT_LIMIT10__COUNT_bw 10
#define RX_NEAR_CREDIT_LIMIT10__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_LIMIT11 0x1D44
#define RX_NEAR_CREDIT_LIMIT11__COUNT_bp 0
#define RX_NEAR_CREDIT_LIMIT11__COUNT_bw 10
#define RX_NEAR_CREDIT_LIMIT11__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_LIMIT12 0x1D48
#define RX_NEAR_CREDIT_LIMIT12__COUNT_bp 0
#define RX_NEAR_CREDIT_LIMIT12__COUNT_bw 10
#define RX_NEAR_CREDIT_LIMIT12__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_LIMIT13 0x1D4C
#define RX_NEAR_CREDIT_LIMIT13__COUNT_bp 0
#define RX_NEAR_CREDIT_LIMIT13__COUNT_bw 10
#define RX_NEAR_CREDIT_LIMIT13__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_LIMIT14 0x1D50
#define RX_NEAR_CREDIT_LIMIT14__COUNT_bp 0
#define RX_NEAR_CREDIT_LIMIT14__COUNT_bw 10
#define RX_NEAR_CREDIT_LIMIT14__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_COUNT08 0x1E20
#define RX_NEAR_CREDIT_COUNT08__COUNT_bp 0
#define RX_NEAR_CREDIT_COUNT08__COUNT_bw 10
#define RX_NEAR_CREDIT_COUNT08__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_COUNT09 0x1E24
#define RX_NEAR_CREDIT_COUNT09__COUNT_bp 0
#define RX_NEAR_CREDIT_COUNT09__COUNT_bw 10
#define RX_NEAR_CREDIT_COUNT09__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_COUNT0A 0x1E28
#define RX_NEAR_CREDIT_COUNT0A__COUNT_bp 0
#define RX_NEAR_CREDIT_COUNT0A__COUNT_bw 10
#define RX_NEAR_CREDIT_COUNT0A__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_COUNT0B 0x1E2C
#define RX_NEAR_CREDIT_COUNT0B__COUNT_bp 0
#define RX_NEAR_CREDIT_COUNT0B__COUNT_bw 10
#define RX_NEAR_CREDIT_COUNT0B__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_COUNT10 0x1E40
#define RX_NEAR_CREDIT_COUNT10__COUNT_bp 0
#define RX_NEAR_CREDIT_COUNT10__COUNT_bw 10
#define RX_NEAR_CREDIT_COUNT10__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_COUNT11 0x1E44
#define RX_NEAR_CREDIT_COUNT11__COUNT_bp 0
#define RX_NEAR_CREDIT_COUNT11__COUNT_bw 10
#define RX_NEAR_CREDIT_COUNT11__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_COUNT12 0x1E48
#define RX_NEAR_CREDIT_COUNT12__COUNT_bp 0
#define RX_NEAR_CREDIT_COUNT12__COUNT_bw 10
#define RX_NEAR_CREDIT_COUNT12__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_COUNT13 0x1E4C
#define RX_NEAR_CREDIT_COUNT13__COUNT_bp 0
#define RX_NEAR_CREDIT_COUNT13__COUNT_bw 10
#define RX_NEAR_CREDIT_COUNT13__COUNT_bm 0x3ff
#define RX_NEAR_CREDIT_COUNT14 0x1E50
#define RX_NEAR_CREDIT_COUNT14__COUNT_bp 0
#define RX_NEAR_CREDIT_COUNT14__COUNT_bw 10
#define RX_NEAR_CREDIT_COUNT14__COUNT_bm 0x3ff
#define RX_FAR_CREDIT_COUNT08 0x1F20
#define RX_FAR_CREDIT_COUNT08__COUNT_bp 0
#define RX_FAR_CREDIT_COUNT08__COUNT_bw 10
#define RX_FAR_CREDIT_COUNT08__COUNT_bm 0x3ff
#define RX_FAR_CREDIT_COUNT09 0x1F24
#define RX_FAR_CREDIT_COUNT09__COUNT_bp 0
#define RX_FAR_CREDIT_COUNT09__COUNT_bw 10
#define RX_FAR_CREDIT_COUNT09__COUNT_bm 0x3ff
#define RX_FAR_CREDIT_COUNT0A 0x1F28
#define RX_FAR_CREDIT_COUNT0A__COUNT_bp 0
#define RX_FAR_CREDIT_COUNT0A__COUNT_bw 10
#define RX_FAR_CREDIT_COUNT0A__COUNT_bm 0x3ff
#define RX_FAR_CREDIT_COUNT0B 0x1F2C
#define RX_FAR_CREDIT_COUNT0B__COUNT_bp 0
#define RX_FAR_CREDIT_COUNT0B__COUNT_bw 10
#define RX_FAR_CREDIT_COUNT0B__COUNT_bm 0x3ff
#define RX_FAR_CREDIT_COUNT10 0x1F40
#define RX_FAR_CREDIT_COUNT10__COUNT_bp 0
#define RX_FAR_CREDIT_COUNT10__COUNT_bw 10
#define RX_FAR_CREDIT_COUNT10__COUNT_bm 0x3ff
#define RX_FAR_CREDIT_COUNT11 0x1F44
#define RX_FAR_CREDIT_COUNT11__COUNT_bp 0
#define RX_FAR_CREDIT_COUNT11__COUNT_bw 10
#define RX_FAR_CREDIT_COUNT11__COUNT_bm 0x3ff
#define RX_FAR_CREDIT_COUNT12 0x1F48
#define RX_FAR_CREDIT_COUNT12__COUNT_bp 0
#define RX_FAR_CREDIT_COUNT12__COUNT_bw 10
#define RX_FAR_CREDIT_COUNT12__COUNT_bm 0x3ff
#define RX_FAR_CREDIT_COUNT13 0x1F4C
#define RX_FAR_CREDIT_COUNT13__COUNT_bp 0
#define RX_FAR_CREDIT_COUNT13__COUNT_bw 10
#define RX_FAR_CREDIT_COUNT13__COUNT_bm 0x3ff
#define RX_FAR_CREDIT_COUNT14 0x1F50
#define RX_FAR_CREDIT_COUNT14__COUNT_bp 0
#define RX_FAR_CREDIT_COUNT14__COUNT_bw 10
#define RX_FAR_CREDIT_COUNT14__COUNT_bm 0x3ff
#define TX_ID 0x0
#define TX_ID__FRAGMENTMAP_bp 16
#define TX_ID__FRAGMENTMAP_bw 12
#define TX_ID__FRAGMENTMAP_bm 0xfff0000
#define TX_ID__IMPLEMENTATION_bp 8
#define TX_ID__IMPLEMENTATION_bw 8
#define TX_ID__IMPLEMENTATION_bm 0xff00
#define TX_ID__VERSION_bp 0
#define TX_ID__VERSION_bw 8
#define TX_ID__VERSION_bm 0xff
#define TX_INTERFACE_CONTROL_STATUS 0x4
#define TX_INTERFACE_CONTROL_STATUS__PHYREADY_bp 12
#define TX_INTERFACE_CONTROL_STATUS__PHYREADY_bw 2
#define TX_INTERFACE_CONTROL_STATUS__PHYREADY_bm 0x3000
#define TX_INTERFACE_CONTROL_STATUS__PHYRESET_bp 8
#define TX_INTERFACE_CONTROL_STATUS__PHYRESET_bw 2
#define TX_INTERFACE_CONTROL_STATUS__PHYRESET_bm 0x300
#define TX_INTERFACE_CONTROL_STATUS__LINKRESET_bp 7
#define TX_INTERFACE_CONTROL_STATUS__LINKRESET_bw 1
#define TX_INTERFACE_CONTROL_STATUS__LINKRESET_bm 0x80
#define TX_INTERFACE_CONTROL_STATUS__NUMSLICES_bp 4
#define TX_INTERFACE_CONTROL_STATUS__NUMSLICES_bw 2
#define TX_INTERFACE_CONTROL_STATUS__NUMSLICES_bm 0x30
#define TX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bp 2
#define TX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bw 2
#define TX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bm 0xc
#define TX_INTERFACE_CONTROL_STATUS__MODE_bp 0
#define TX_INTERFACE_CONTROL_STATUS__MODE_bw 2
#define TX_INTERFACE_CONTROL_STATUS__MODE_bm 0x3
#define TX_ERR_INJECTION_CONTROL 0x8
#define TX_ERR_INJECTION_CONTROL__CORRUPTALLCODEWORDS_bp 0
#define TX_ERR_INJECTION_CONTROL__CORRUPTALLCODEWORDS_bw 1
#define TX_ERR_INJECTION_CONTROL__CORRUPTALLCODEWORDS_bm 0x400
#define TX_ERR_INJECTION_CONTROL__CORRUPTLLPBITENABLE_bp 9
#define TX_ERR_INJECTION_CONTROL__CORRUPTLLPBITENABLE_bw 1
#define TX_ERR_INJECTION_CONTROL__CORRUPTLLPBITENABLE_bm 0x200
#define TX_ERR_INJECTION_CONTROL__CORRUPTLLPBITNUMBER_bp 0
#define TX_ERR_INJECTION_CONTROL__CORRUPTLLPBITNUMBER_bw 9
#define TX_ERR_INJECTION_CONTROL__CORRUPTLLPBITNUMBER_bm 0x1ff
#define TX_A_X_I_MUX_CONTROL 0xC
#define TX_A_X_I_MUX_CONTROL__AXIMUXSEL_bp 0
#define TX_A_X_I_MUX_CONTROL__AXIMUXSEL_bw 1
#define TX_A_X_I_MUX_CONTROL__AXIMUXSEL_bm 0x1
#define TX_TLP_MSG0 0x100
#define TX_TLP_MSG0__PENDING_bp 6
#define TX_TLP_MSG0__PENDING_bw 1
#define TX_TLP_MSG0__PENDING_bm 0x10000
#define TX_TLP_MSG0__MESSAGEDATA_bp 0
#define TX_TLP_MSG0__MESSAGEDATA_bw 16
#define TX_TLP_MSG0__MESSAGEDATA_bm 0xffff
#define TX_NEAR_CREDIT_THRESHOLD08 0x420
#define TX_NEAR_CREDIT_THRESHOLD08__THRESHOLD_bp 0
#define TX_NEAR_CREDIT_THRESHOLD08__THRESHOLD_bw 10
#define TX_NEAR_CREDIT_THRESHOLD08__THRESHOLD_bm 0x3ff
#define TX_NEAR_CREDIT_THRESHOLD09 0x424
#define TX_NEAR_CREDIT_THRESHOLD09__THRESHOLD_bp 0
#define TX_NEAR_CREDIT_THRESHOLD09__THRESHOLD_bw 10
#define TX_NEAR_CREDIT_THRESHOLD09__THRESHOLD_bm 0x3ff
#define TX_NEAR_CREDIT_THRESHOLD0A 0x428
#define TX_NEAR_CREDIT_THRESHOLD0A__THRESHOLD_bp 0
#define TX_NEAR_CREDIT_THRESHOLD0A__THRESHOLD_bw 10
#define TX_NEAR_CREDIT_THRESHOLD0A__THRESHOLD_bm 0x3ff
#define TX_NEAR_CREDIT_THRESHOLD0B 0x42C
#define TX_NEAR_CREDIT_THRESHOLD0B__THRESHOLD_bp 0
#define TX_NEAR_CREDIT_THRESHOLD0B__THRESHOLD_bw 10
#define TX_NEAR_CREDIT_THRESHOLD0B__THRESHOLD_bm 0x3ff
#define TX_NEAR_CREDIT_THRESHOLD10 0x440
#define TX_NEAR_CREDIT_THRESHOLD10__THRESHOLD_bp 0
#define TX_NEAR_CREDIT_THRESHOLD10__THRESHOLD_bw 10
#define TX_NEAR_CREDIT_THRESHOLD10__THRESHOLD_bm 0x3ff
#define TX_NEAR_CREDIT_THRESHOLD11 0x444
#define TX_NEAR_CREDIT_THRESHOLD11__THRESHOLD_bp 0
#define TX_NEAR_CREDIT_THRESHOLD11__THRESHOLD_bw 10
#define TX_NEAR_CREDIT_THRESHOLD11__THRESHOLD_bm 0x3ff
#define TX_NEAR_CREDIT_THRESHOLD12 0x448
#define TX_NEAR_CREDIT_THRESHOLD12__THRESHOLD_bp 0
#define TX_NEAR_CREDIT_THRESHOLD12__THRESHOLD_bw 10
#define TX_NEAR_CREDIT_THRESHOLD12__THRESHOLD_bm 0x3ff
#define TX_NEAR_CREDIT_THRESHOLD13 0x44C
#define TX_NEAR_CREDIT_THRESHOLD13__THRESHOLD_bp 0
#define TX_NEAR_CREDIT_THRESHOLD13__THRESHOLD_bw 10
#define TX_NEAR_CREDIT_THRESHOLD13__THRESHOLD_bm 0x3ff
#define TX_NEAR_CREDIT_THRESHOLD14 0x450
#define TX_NEAR_CREDIT_THRESHOLD14__THRESHOLD_bp 0
#define TX_NEAR_CREDIT_THRESHOLD14__THRESHOLD_bw 10
#define TX_NEAR_CREDIT_THRESHOLD14__THRESHOLD_bm 0x3ff
#define TX_NEAR_CREDIT_COUNT08 0x520
#define TX_NEAR_CREDIT_COUNT08__COUNT_bp 0
#define TX_NEAR_CREDIT_COUNT08__COUNT_bw 10
#define TX_NEAR_CREDIT_COUNT08__COUNT_bm 0x3ff
#define TX_NEAR_CREDIT_COUNT09 0x524
#define TX_NEAR_CREDIT_COUNT09__COUNT_bp 0
#define TX_NEAR_CREDIT_COUNT09__COUNT_bw 10
#define TX_NEAR_CREDIT_COUNT09__COUNT_bm 0x3ff
#define TX_NEAR_CREDIT_COUNT0A 0x528
#define TX_NEAR_CREDIT_COUNT0A__COUNT_bp 0
#define TX_NEAR_CREDIT_COUNT0A__COUNT_bw 10
#define TX_NEAR_CREDIT_COUNT0A__COUNT_bm 0x3ff
#define TX_NEAR_CREDIT_COUNT0B 0x52C
#define TX_NEAR_CREDIT_COUNT0B__COUNT_bp 0
#define TX_NEAR_CREDIT_COUNT0B__COUNT_bw 10
#define TX_NEAR_CREDIT_COUNT0B__COUNT_bm 0x3ff
#define TX_NEAR_CREDIT_COUNT10 0x540
#define TX_NEAR_CREDIT_COUNT10__COUNT_bp 0
#define TX_NEAR_CREDIT_COUNT10__COUNT_bw 10
#define TX_NEAR_CREDIT_COUNT10__COUNT_bm 0x3ff
#define TX_NEAR_CREDIT_COUNT11 0x544
#define TX_NEAR_CREDIT_COUNT11__COUNT_bp 0
#define TX_NEAR_CREDIT_COUNT11__COUNT_bw 10
#define TX_NEAR_CREDIT_COUNT11__COUNT_bm 0x3ff
#define TX_NEAR_CREDIT_COUNT12 0x548
#define TX_NEAR_CREDIT_COUNT12__COUNT_bp 0
#define TX_NEAR_CREDIT_COUNT12__COUNT_bw 10
#define TX_NEAR_CREDIT_COUNT12__COUNT_bm 0x3ff
#define TX_NEAR_CREDIT_COUNT13 0x54C
#define TX_NEAR_CREDIT_COUNT13__COUNT_bp 0
#define TX_NEAR_CREDIT_COUNT13__COUNT_bw 10
#define TX_NEAR_CREDIT_COUNT13__COUNT_bm 0x3ff
#define TX_NEAR_CREDIT_COUNT14 0x550
#define TX_NEAR_CREDIT_COUNT14__COUNT_bp 0
#define TX_NEAR_CREDIT_COUNT14__COUNT_bw 10
#define TX_NEAR_CREDIT_COUNT14__COUNT_bm 0x3ff
#define TX_FAR_CREDIT_COUNT08 0x620
#define TX_FAR_CREDIT_COUNT08__COUNT_bp 0
#define TX_FAR_CREDIT_COUNT08__COUNT_bw 10
#define TX_FAR_CREDIT_COUNT08__COUNT_bm 0x3ff
#define TX_FAR_CREDIT_COUNT09 0x624
#define TX_FAR_CREDIT_COUNT09__COUNT_bp 0
#define TX_FAR_CREDIT_COUNT09__COUNT_bw 10
#define TX_FAR_CREDIT_COUNT09__COUNT_bm 0x3ff
#define TX_FAR_CREDIT_COUNT0A 0x628
#define TX_FAR_CREDIT_COUNT0A__COUNT_bp 0
#define TX_FAR_CREDIT_COUNT0A__COUNT_bw 10
#define TX_FAR_CREDIT_COUNT0A__COUNT_bm 0x3ff
#define TX_FAR_CREDIT_COUNT0B 0x62C
#define TX_FAR_CREDIT_COUNT0B__COUNT_bp 0
#define TX_FAR_CREDIT_COUNT0B__COUNT_bw 10
#define TX_FAR_CREDIT_COUNT0B__COUNT_bm 0x3ff
#define TX_FAR_CREDIT_COUNT10 0x640
#define TX_FAR_CREDIT_COUNT10__COUNT_bp 0
#define TX_FAR_CREDIT_COUNT10__COUNT_bw 10
#define TX_FAR_CREDIT_COUNT10__COUNT_bm 0x3ff
#define TX_FAR_CREDIT_COUNT11 0x644
#define TX_FAR_CREDIT_COUNT11__COUNT_bp 0
#define TX_FAR_CREDIT_COUNT11__COUNT_bw 10
#define TX_FAR_CREDIT_COUNT11__COUNT_bm 0x3ff
#define TX_FAR_CREDIT_COUNT12 0x648
#define TX_FAR_CREDIT_COUNT12__COUNT_bp 0
#define TX_FAR_CREDIT_COUNT12__COUNT_bw 10
#define TX_FAR_CREDIT_COUNT12__COUNT_bm 0x3ff
#define TX_FAR_CREDIT_COUNT13 0x64C
#define TX_FAR_CREDIT_COUNT13__COUNT_bp 0
#define TX_FAR_CREDIT_COUNT13__COUNT_bw 10
#define TX_FAR_CREDIT_COUNT13__COUNT_bm 0x3ff
#define TX_FAR_CREDIT_COUNT14 0x650
#define TX_FAR_CREDIT_COUNT14__COUNT_bp 0
#define TX_FAR_CREDIT_COUNT14__COUNT_bw 10
#define TX_FAR_CREDIT_COUNT14__COUNT_bm 0x3ff
#define TX_VIRTUAL_WIRE_DISABLE00 0x800
#define TX_VIRTUAL_WIRE_DISABLE00__DISABLE_bp 0
#define TX_VIRTUAL_WIRE_DISABLE00__DISABLE_bw 10
#define TX_VIRTUAL_WIRE_DISABLE00__DISABLE_bm 0x3ff
#define TX_VIRTUAL_WIRE_SET00 0x880
#define TX_VIRTUAL_WIRE_SET00__WIRE_bp 0
#define TX_VIRTUAL_WIRE_SET00__WIRE_bw 10
#define TX_VIRTUAL_WIRE_SET00__WIRE_bm 0x3ff
#define TX_VIRTUAL_WIRE_CLEAR00 0x900
#define TX_VIRTUAL_WIRE_CLEAR00__WIRE_bp 0
#define TX_VIRTUAL_WIRE_CLEAR00__WIRE_bw 10
#define TX_VIRTUAL_WIRE_CLEAR00__WIRE_bm 0x3ff


typedef union{
	struct{
		uint32_t version:8;
		uint32_t implementation:8;
		uint32_t fragmentMap:12;
		uint32_t rsvd0:4;
	};
	uint32_t val;
} RxId_t;


typedef union{
	struct{
		uint32_t mode:2;
		uint32_t widthPerSlice:2;
		uint32_t numSlices:2;
		uint32_t linkReset:1;
		uint32_t phyReset:2;
		uint32_t rsvd0:2;
		uint32_t phyReady:2;
		uint32_t rsvd1:19;
	};
	uint32_t val;
} RxInterfaceControlStatus_t;


typedef union{
	struct{
		uint32_t corrRecovDis:1;
		uint32_t logEn:1;
		uint32_t nmiEn:1;
		uint32_t fatalErrIntrEn:1;
		uint32_t noncritErrIntrEn:1;
		uint32_t rsvd0:6;
		uint32_t totalBanks:5;
		uint32_t errInjectDly:16;
	};
	uint32_t val;
} DdifRasBank0Ctrl_t;


typedef union{
	struct{
		uint32_t valid:1;
		uint32_t recentErr:1;
		uint32_t nmiPend:1;
		uint32_t fatalErrIntrPend:1;
		uint32_t noncritErrIntrPend:1;
		uint32_t bankStatus:27;
	};
	uint32_t val;
} DdifRasBank0Status_t;


typedef union{
	struct{
		uint32_t corrRecovDis:1;
		uint32_t logEn:1;
		uint32_t nmiEn:1;
		uint32_t fatalErrIntrEn:1;
		uint32_t noncritErrDIntrEn:1;
		uint32_t noncritErrCIntrEn:1;
		uint32_t rsvd0:26;
	};
	uint32_t val;
} DdifRasBank1Ctrl_t;


typedef union{
	struct{
		uint32_t valid:1;
		uint32_t errDetLogged:1;
		uint32_t criticalErr:1;
		uint32_t deferredErr:1;
		uint32_t cecOverflow:1;
		uint32_t errLogOverflow:1;
		uint32_t addrVld:1;
		uint32_t infoVld:1;
		uint32_t errType:8;
		uint32_t accessType:4;
		uint32_t corrErrCnt:12;
	};
	uint32_t val;
} DdifRasBank1Status_t;


typedef union{
	struct{
		uint32_t bi32bit:32;
	};
	uint32_t val;
} DdifRasBank1AddrL_t;


typedef union{
	struct{
		uint32_t bi32bit:32;
	};
	uint32_t val;
} DdifRasBank1AddrH_t;


typedef union{
	struct{
		uint32_t bi32bit:32;
	};
	uint32_t val;
} DdifRasBank1InfoL_t;


typedef union{
	struct{
		uint32_t bi32bit:32;
	};
	uint32_t val;
} DdifRasBank1InfoH_t;


typedef union{
	struct{
		uint32_t corrRecovDis:1;
		uint32_t logEn:1;
		uint32_t nmiEn:1;
		uint32_t fatalErrIntrEn:1;
		uint32_t noncritErrDIntrEn:1;
		uint32_t noncritErrCIntrEn:1;
		uint32_t rsvd0:26;
	};
	uint32_t val;
} DdifRasBank2Ctrl_t;


typedef union{
	struct{
		uint32_t valid:1;
		uint32_t errDetLogged:1;
		uint32_t criticalErr:1;
		uint32_t deferredErr:1;
		uint32_t cecOverflow:1;
		uint32_t errLogOverflow:1;
		uint32_t addrVld:1;
		uint32_t infoVld:1;
		uint32_t errType:8;
		uint32_t accessType:4;
		uint32_t corrErrCnt:12;
	};
	uint32_t val;
} DdifRasBank2Status_t;


typedef union{
	struct{
		uint32_t bi32bit:32;
	};
	uint32_t val;
} DdifRasBank2AddrL_t;


typedef union{
	struct{
		uint32_t bi32bit:32;
	};
	uint32_t val;
} DdifRasBank2AddrH_t;


typedef union{
	struct{
		uint32_t bi32bit:32;
	};
	uint32_t val;
} DdifRasBank2InfoL_t;


typedef union{
	struct{
		uint32_t bi32bit:32;
	};
	uint32_t val;
} DdifRasBank2InfoH_t;


typedef union{
	struct{
		uint32_t messageData:16;
		uint32_t received:1;
		uint32_t clearReceived:1;
		uint32_t rsvd0:14;
	};
	uint32_t val;
} RxTlpMsg0_t;


typedef union{
	struct{
		uint32_t trainTrigSample:1;
		uint32_t rsvd0:31;
	};
	uint32_t val;
} RxTrainTrigSample_t;


typedef union{
	struct{
		uint32_t nudge0:2;
		uint32_t nudge1:2;
		uint32_t rsvd0:28;
	};
	uint32_t val;
} RxTrainNudge_t;


typedef union{
	struct{
		uint32_t writePtr0:3;
		uint32_t readPtr0:3;
		uint32_t writePtr1:3;
		uint32_t readPtr1:3;
		uint32_t rsvd0:20;
	};
	uint32_t val;
} RxTrainPtrs_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample00_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample01_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample02_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample03_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample04_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample05_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample06_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample07_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample08_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample09_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample0a_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample0b_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample0c_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample0d_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample0e_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample0f_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample10_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample11_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample12_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample13_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample14_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample15_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample16_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample17_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample18_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample19_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample1a_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample1b_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample1c_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample1d_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample1e_t;


typedef union{
	struct{
		uint32_t data:32;
	};
	uint32_t val;
} DdifFlitSample1f_t;


typedef union{
	struct{
		uint32_t disable:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxVirtualWireDisable00_t;


typedef union{
	struct{
		uint32_t wire:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxVirtualWireSet00_t;


typedef union{
	struct{
		uint32_t wire:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxVirtualWireClear00_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditConfig08_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditConfig09_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditConfig0a_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditConfig0b_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditConfig10_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditConfig11_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditConfig12_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditConfig13_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditConfig14_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditLimit08_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditLimit09_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditLimit0a_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditLimit0b_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditLimit10_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditLimit11_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditLimit12_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditLimit13_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditLimit14_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditCount08_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditCount09_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditCount0a_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditCount0b_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditCount10_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditCount11_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditCount12_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditCount13_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxNearCreditCount14_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxFarCreditCount08_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxFarCreditCount09_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxFarCreditCount0a_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxFarCreditCount0b_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxFarCreditCount10_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxFarCreditCount11_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxFarCreditCount12_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxFarCreditCount13_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} RxFarCreditCount14_t;


typedef union{
	struct{
		uint32_t version:8;
		uint32_t implementation:8;
		uint32_t fragmentMap:12;
		uint32_t rsvd0:4;
	};
	uint32_t val;
} TxId_t;


typedef union{
	struct{
		uint32_t mode:2;
		uint32_t widthPerSlice:2;
		uint32_t numSlices:2;
		uint32_t rsvd0:1;
		uint32_t linkReset:1;
		uint32_t phyReset:2;
		uint32_t rsvd1:2;
		uint32_t phyReady:2;
		uint32_t rsvd2:18;
	};
	uint32_t val;
} TxInterfaceControlStatus_t;


typedef union{
	struct{
		uint32_t corruptLlpBitNumber:9;
		uint32_t corruptLlpBitEnable:1;
		uint32_t corruptAllCodewords:1;
		uint32_t rsvd0:21;
	};
	uint32_t val;
} TxErrInjectionControl_t;


typedef union{
	struct{
		uint32_t axiMuxSel:1;
		uint32_t rsvd0:31;
	};
	uint32_t val;
} TxAXIMuxControl_t;


typedef union{
	struct{
		uint32_t messageData:16;
		uint32_t pending:1;
		uint32_t rsvd0:15;
	};
	uint32_t val;
} TxTlpMsg0_t;


typedef union{
	struct{
		uint32_t threshold:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxNearCreditThreshold08_t;


typedef union{
	struct{
		uint32_t threshold:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxNearCreditThreshold09_t;


typedef union{
	struct{
		uint32_t threshold:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxNearCreditThreshold0a_t;


typedef union{
	struct{
		uint32_t threshold:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxNearCreditThreshold0b_t;


typedef union{
	struct{
		uint32_t threshold:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxNearCreditThreshold10_t;


typedef union{
	struct{
		uint32_t threshold:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxNearCreditThreshold11_t;


typedef union{
	struct{
		uint32_t threshold:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxNearCreditThreshold12_t;


typedef union{
	struct{
		uint32_t threshold:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxNearCreditThreshold13_t;


typedef union{
	struct{
		uint32_t threshold:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxNearCreditThreshold14_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxNearCreditCount08_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxNearCreditCount09_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxNearCreditCount0a_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxNearCreditCount0b_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxNearCreditCount10_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxNearCreditCount11_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxNearCreditCount12_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxNearCreditCount13_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxNearCreditCount14_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxFarCreditCount08_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxFarCreditCount09_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxFarCreditCount0a_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxFarCreditCount0b_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxFarCreditCount10_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxFarCreditCount11_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxFarCreditCount12_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxFarCreditCount13_t;


typedef union{
	struct{
		uint32_t count:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxFarCreditCount14_t;


typedef union{
	struct{
		uint32_t disable:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxVirtualWireDisable00_t;


typedef union{
	struct{
		uint32_t wire:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxVirtualWireSet00_t;


typedef union{
	struct{
		uint32_t wire:10;
		uint32_t rsvd0:22;
	};
	uint32_t val;
} TxVirtualWireClear00_t;


typedef struct{
	RxId_t rxId;
	RxInterfaceControlStatus_t rxInterfaceControlStatus;
	DdifRasBank0Ctrl_t ddifRasBank0Ctrl;
	DdifRasBank0Status_t ddifRasBank0Status;
	DdifRasBank1Ctrl_t ddifRasBank1Ctrl;
	DdifRasBank1Status_t ddifRasBank1Status;
	DdifRasBank1AddrL_t ddifRasBank1AddrL;
	DdifRasBank1AddrH_t ddifRasBank1AddrH;
	DdifRasBank1InfoL_t ddifRasBank1InfoL;
	DdifRasBank1InfoH_t ddifRasBank1InfoH;
	DdifRasBank2Ctrl_t ddifRasBank2Ctrl;
	DdifRasBank2Status_t ddifRasBank2Status;
	DdifRasBank2AddrL_t ddifRasBank2AddrL;
	DdifRasBank2AddrH_t ddifRasBank2AddrH;
	DdifRasBank2InfoL_t ddifRasBank2InfoL;
	DdifRasBank2InfoH_t ddifRasBank2InfoH;
	RxTlpMsg0_t rxTlpMsg0;
	RxTrainTrigSample_t rxTrainTrigSample;
	RxTrainNudge_t rxTrainNudge;
	RxTrainPtrs_t rxTrainPtrs;
	DdifFlitSample00_t ddifFlitSample00;
	DdifFlitSample01_t ddifFlitSample01;
	DdifFlitSample02_t ddifFlitSample02;
	DdifFlitSample03_t ddifFlitSample03;
	DdifFlitSample04_t ddifFlitSample04;
	DdifFlitSample05_t ddifFlitSample05;
	DdifFlitSample06_t ddifFlitSample06;
	DdifFlitSample07_t ddifFlitSample07;
	DdifFlitSample08_t ddifFlitSample08;
	DdifFlitSample09_t ddifFlitSample09;
	DdifFlitSample0a_t ddifFlitSample0a;
	DdifFlitSample0b_t ddifFlitSample0b;
	DdifFlitSample0c_t ddifFlitSample0c;
	DdifFlitSample0d_t ddifFlitSample0d;
	DdifFlitSample0e_t ddifFlitSample0e;
	DdifFlitSample0f_t ddifFlitSample0f;
	DdifFlitSample10_t ddifFlitSample10;
	DdifFlitSample11_t ddifFlitSample11;
	DdifFlitSample12_t ddifFlitSample12;
	DdifFlitSample13_t ddifFlitSample13;
	DdifFlitSample14_t ddifFlitSample14;
	DdifFlitSample15_t ddifFlitSample15;
	DdifFlitSample16_t ddifFlitSample16;
	DdifFlitSample17_t ddifFlitSample17;
	DdifFlitSample18_t ddifFlitSample18;
	DdifFlitSample19_t ddifFlitSample19;
	DdifFlitSample1a_t ddifFlitSample1a;
	DdifFlitSample1b_t ddifFlitSample1b;
	DdifFlitSample1c_t ddifFlitSample1c;
	DdifFlitSample1d_t ddifFlitSample1d;
	DdifFlitSample1e_t ddifFlitSample1e;
	DdifFlitSample1f_t ddifFlitSample1f;
	RxVirtualWireDisable00_t rxVirtualWireDisable00;
	RxVirtualWireSet00_t rxVirtualWireSet00;
	RxVirtualWireClear00_t rxVirtualWireClear00;
	RxNearCreditConfig08_t rxNearCreditConfig08;
	RxNearCreditConfig09_t rxNearCreditConfig09;
	RxNearCreditConfig0a_t rxNearCreditConfig0a;
	RxNearCreditConfig0b_t rxNearCreditConfig0b;
	RxNearCreditConfig10_t rxNearCreditConfig10;
	RxNearCreditConfig11_t rxNearCreditConfig11;
	RxNearCreditConfig12_t rxNearCreditConfig12;
	RxNearCreditConfig13_t rxNearCreditConfig13;
	RxNearCreditConfig14_t rxNearCreditConfig14;
	RxNearCreditLimit08_t rxNearCreditLimit08;
	RxNearCreditLimit09_t rxNearCreditLimit09;
	RxNearCreditLimit0a_t rxNearCreditLimit0a;
	RxNearCreditLimit0b_t rxNearCreditLimit0b;
	RxNearCreditLimit10_t rxNearCreditLimit10;
	RxNearCreditLimit11_t rxNearCreditLimit11;
	RxNearCreditLimit12_t rxNearCreditLimit12;
	RxNearCreditLimit13_t rxNearCreditLimit13;
	RxNearCreditLimit14_t rxNearCreditLimit14;
	RxNearCreditCount08_t rxNearCreditCount08;
	RxNearCreditCount09_t rxNearCreditCount09;
	RxNearCreditCount0a_t rxNearCreditCount0a;
	RxNearCreditCount0b_t rxNearCreditCount0b;
	RxNearCreditCount10_t rxNearCreditCount10;
	RxNearCreditCount11_t rxNearCreditCount11;
	RxNearCreditCount12_t rxNearCreditCount12;
	RxNearCreditCount13_t rxNearCreditCount13;
	RxNearCreditCount14_t rxNearCreditCount14;
	RxFarCreditCount08_t rxFarCreditCount08;
	RxFarCreditCount09_t rxFarCreditCount09;
	RxFarCreditCount0a_t rxFarCreditCount0a;
	RxFarCreditCount0b_t rxFarCreditCount0b;
	RxFarCreditCount10_t rxFarCreditCount10;
	RxFarCreditCount11_t rxFarCreditCount11;
	RxFarCreditCount12_t rxFarCreditCount12;
	RxFarCreditCount13_t rxFarCreditCount13;
	RxFarCreditCount14_t rxFarCreditCount14;
	TxId_t txId;
	TxInterfaceControlStatus_t txInterfaceControlStatus;
	TxErrInjectionControl_t txErrInjectionControl;
	TxAXIMuxControl_t txAXIMuxControl;
	TxTlpMsg0_t txTlpMsg0;
	TxNearCreditThreshold08_t txNearCreditThreshold08;
	TxNearCreditThreshold09_t txNearCreditThreshold09;
	TxNearCreditThreshold0a_t txNearCreditThreshold0a;
	TxNearCreditThreshold0b_t txNearCreditThreshold0b;
	TxNearCreditThreshold10_t txNearCreditThreshold10;
	TxNearCreditThreshold11_t txNearCreditThreshold11;
	TxNearCreditThreshold12_t txNearCreditThreshold12;
	TxNearCreditThreshold13_t txNearCreditThreshold13;
	TxNearCreditThreshold14_t txNearCreditThreshold14;
	TxNearCreditCount08_t txNearCreditCount08;
	TxNearCreditCount09_t txNearCreditCount09;
	TxNearCreditCount0a_t txNearCreditCount0a;
	TxNearCreditCount0b_t txNearCreditCount0b;
	TxNearCreditCount10_t txNearCreditCount10;
	TxNearCreditCount11_t txNearCreditCount11;
	TxNearCreditCount12_t txNearCreditCount12;
	TxNearCreditCount13_t txNearCreditCount13;
	TxNearCreditCount14_t txNearCreditCount14;
	TxFarCreditCount08_t txFarCreditCount08;
	TxFarCreditCount09_t txFarCreditCount09;
	TxFarCreditCount0a_t txFarCreditCount0a;
	TxFarCreditCount0b_t txFarCreditCount0b;
	TxFarCreditCount10_t txFarCreditCount10;
	TxFarCreditCount11_t txFarCreditCount11;
	TxFarCreditCount12_t txFarCreditCount12;
	TxFarCreditCount13_t txFarCreditCount13;
	TxFarCreditCount14_t txFarCreditCount14;
	TxVirtualWireDisable00_t txVirtualWireDisable00;
	TxVirtualWireSet00_t txVirtualWireSet00;
	TxVirtualWireClear00_t txVirtualWireClear00;

} D2dLLRegBlock;
