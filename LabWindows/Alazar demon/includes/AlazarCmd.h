#ifndef _ALAZARCMD_H
#define _ALAZARCMD_H
//=============================================================================
//
// Alazar Technologies Inc
// 
//  File Name:
//
//      AlazarCmd.h
//
// Copyright (c) 1998-2010 Alazar Technologies Inc. All Rights Reserved.
// Unpublished - rights reserved under the Copyright laws of the
// United States And Canada.
//
// This product contains confidential information and trade secrets 
// of Alazar Technologies Inc. Use, disclosure, or reproduction is 
// prohibited without the prior express written permission of Alazar 
// Technologies Inc
//
// Description:
//
//      Alazar Set/Get commands file
//
// Revision History:
//		Ver 1.0 - Initial Release
//=============================================================================

enum MemorySizesPerChannel 
{ 
	MEM8K=0,
	MEM64K,
	MEM128K,
	MEM256K,
	MEM512K,
	MEM1M,
	MEM2M,
	MEM4M,
	MEM8M,
	MEM16M,
	MEM32M,
	MEM64M,
	MEM128M,
	MEM256M,
	MEM512M,
	MEM1G,
	MEM2G,
	MEM4G,
	MEM8G,
	MEM16G
};

//*****************************************************************************
//
//	Configuration/Acquisition/Generation Command Set
//
//*****************************************************************************
// sets and gets
#define NUMBER_OF_RECORDS				0x10000001UL
#define PRETRIGGER_AMOUNT				0x10000002UL
#define RECORD_LENGTH					0x10000003UL //rec.length-pre
#define TRIGGER_ENGINE					0x10000004UL
#define TRIGGER_DELAY					0x10000005UL
#define TRIGGER_TIMEOUT					0x10000006UL
#define SAMPLE_RATE						0x10000007UL
#define CONFIGURATION_MODE				0x10000008UL //Independent, Master/Slave, Last Slave
#define DATA_WIDTH						0x10000009UL //8,16,32 bits - Digital IO boards
#define SAMPLE_SIZE						DATA_WIDTH   //8,12,16 - Analog Input boards
#define AUTO_CALIBRATE					0x1000000AUL
#define TRIGGER_XXXXX					0x1000000BUL
#define CLOCK_SOURCE					0x1000000CUL
#define CLOCK_SLOPE						0x1000000DUL
#define IMPEDANCE						0x1000000EUL
#define INPUT_RANGE						0x1000000FUL
#define COUPLING						0x10000010UL
#define MAX_TIMEOUTS_ALLOWED			0x10000011UL
#define OPERATING_MODE					0x10000012UL //Single, Dual, Quad etc...
#define CLOCK_DECIMATION_EXTERNAL		0x10000013UL
#define LED_CONTROL						0x10000014UL
#define ATTENUATOR_RELAY				0x10000018UL
#define	EXT_TRIGGER_COUPLING			0x1000001AUL
#define EXT_TRIGGER_ATTENUATOR_RELAY	0x1000001CUL
#define	TRIGGER_ENGINE_SOURCE			0x1000001EUL
#define TRIGGER_ENGINE_SLOPE			0x10000020UL
#define SEND_DAC_VALUE					0x10000021UL
#define SLEEP_DEVICE					0x10000022UL
#define GET_DAC_VALUE					0x10000023UL
#define GET_SERIAL_NUMBER				0x10000024UL
#define GET_FIRST_CAL_DATE				0x10000025UL
#define GET_LATEST_CAL_DATE				0x10000026UL
#define GET_LATEST_TEST_DATE			0x10000027UL
#define GET_LATEST_CAL_DATE_MONTH		0x1000002DUL
#define GET_LATEST_CAL_DATE_DAY			0x1000002EUL
#define GET_LATEST_CAL_DATE_YEAR		0x1000002FUL
#define GET_PCIE_LINK_SPEED				0x10000030UL
#define GET_PCIE_LINK_WIDTH				0x10000031UL
#define SETGET_ASYNC_BUFFSIZE_BYTES		0x10000039UL
#define SETGET_ASYNC_BUFFCOUNT			0x10000040UL
#define SET_DATA_FORMAT					0x10000041UL
#define GET_DATA_FORMAT					0x10000042UL
#define  DATA_FORMAT_UNSIGNED			0
#define  DATA_FORMAT_SIGNED				1
#define SET_SINGLE_CHANNEL_MODE			0x10000043UL
#define GET_SAMPLES_PER_TIMESTAMP_CLOCK	0x10000044UL
#define GET_RECORDS_CAPTURED			0x10000045UL
#define GET_MAX_PRETRIGGER_SAMPLES		0x10000046UL
#define SET_ADC_MODE					0x10000047UL

// gets board specific parameters
#define MEMORY_SIZE						0x1000002AUL
#define BOARD_TYPE						0x1000002BUL
#define ASOPC_TYPE						0x1000002CUL
#define GET_BOARD_OPTIONS_LOW			0x10000037UL
#define GET_BOARD_OPTIONS_HIGH			0x10000038UL
#define  OPTION_STREAMING_DMA			(1UL << 0)
#define  OPTION_EXTERNAL_CLOCK			(1UL << 1)
#define  OPTION_DUAL_PORT_MEMORY		(1UL << 2)
#define  OPTION_180MHZ_OSCILLATOR		(1UL << 3)
#define  OPTION_LVTTL_EXT_CLOCK			(1UL << 4)
#define  OPTION_OEM_FPGA				(1UL << 47)

// sets and gets
// The transfer offset is defined as the place to start
// the transfer relative to trigger. The value is signed.
// -------TO>>>T>>>>>>>>>TE------------
#define TRANSFER_OFFET					0x10000030UL 
#define TRANSFER_LENGTH					0x10000031UL // TO -> TE
										
// Transfer related constants			
#define TRANSFER_RECORD_OFFSET			0x10000032UL
#define TRANSFER_NUM_OF_RECORDS			0x10000033UL
#define TRANSFER_MAPPING_RATIO			0x10000034UL
										
// only gets
#define TRIGGER_ADDRESS_AND_TIMESTAMP	0x10000035UL

// MASTER/SLAVE CONTROL sets/gets
#define MASTER_SLAVE_INDEPENDENT		0x10000036UL
									
// boolean gets
#define TRIGGERED						0x10000040UL
#define BUSY							0x10000041UL
#define WHO_TRIGGERED					0x10000042UL
#define GET_ASYNC_BUFFERS_PENDING		0x10000050UL
#define GET_ASYNC_BUFFERS_PENDING_FULL	0x10000051UL
#define GET_ASYNC_BUFFERS_PENDING_EMPTY	0x10000052UL
#define ACF_SAMPLES_PER_RECORD			0x10000060UL
#define ACF_RECORDS_TO_AVERAGE			0x10000061UL

//*****************************************************************************
//
//	Constants Used With The Command Set Listed Above
//
//*****************************************************************************

//
// Sample Rate values
//
#define SAMPLE_RATE_1KSPS		0X00000001UL
#define SAMPLE_RATE_2KSPS		0X00000002UL
#define SAMPLE_RATE_5KSPS		0X00000004UL
#define SAMPLE_RATE_10KSPS		0X00000008UL
#define SAMPLE_RATE_20KSPS		0X0000000AUL
#define SAMPLE_RATE_50KSPS		0X0000000CUL
#define SAMPLE_RATE_100KSPS		0X0000000EUL
#define SAMPLE_RATE_200KSPS		0X00000010UL
#define SAMPLE_RATE_500KSPS		0X00000012UL
#define SAMPLE_RATE_1MSPS		0X00000014UL
#define SAMPLE_RATE_2MSPS		0X00000018UL
#define SAMPLE_RATE_5MSPS		0X0000001AUL
#define SAMPLE_RATE_10MSPS		0X0000001CUL
#define SAMPLE_RATE_20MSPS		0X0000001EUL
#define SAMPLE_RATE_25MSPS		0X00000021UL
#define SAMPLE_RATE_50MSPS		0X00000022UL
#define SAMPLE_RATE_100MSPS		0X00000024UL
#define SAMPLE_RATE_125MSPS		0x00000025UL
#define SAMPLE_RATE_160MSPS		0x00000026UL
#define SAMPLE_RATE_180MSPS		0x00000027UL
#define SAMPLE_RATE_200MSPS		0X00000028UL
#define SAMPLE_RATE_250MSPS		0X0000002BUL
#define SAMPLE_RATE_500MSPS		0X00000030UL
#define SAMPLE_RATE_1GSPS		0x00000035UL
#define SAMPLE_RATE_2GSPS		0x0000003AUL
// user define sample rate - used with External Clock
#define SAMPLE_RATE_USER_DEF	0x00000040UL 
// ATS665 Specific Setting for using the PLL
//
// The base value can be used to create a PLL frequency
// in a simple manner.
//
// Ex. 
//        105 MHz = PLL_10MHZ_REF_100MSPS_BASE + 5000000
//        120 MHz = PLL_10MHZ_REF_100MSPS_BASE + 20000000
#define PLL_10MHZ_REF_100MSPS_BASE	0x05F5E100UL

// ATS665 Specific Decimation constants
#define DECIMATE_BY_8			0x00000008UL
#define DECIMATE_BY_64			0x00000040UL

//
// Impedance Values
//
#define IMPEDANCE_1M_OHM		0x00000001UL
#define IMPEDANCE_50_OHM		0x00000002UL
#define IMPEDANCE_75_OHM		0x00000004UL
#define IMPEDANCE_300_OHM		0x00000008UL

//
//Clock Source
//
#define INTERNAL_CLOCK			0x00000001UL
#define EXTERNAL_CLOCK			0x00000002UL
#define FAST_EXTERNAL_CLOCK		0x00000002UL
#define MEDIMUM_EXTERNAL_CLOCK	0x00000003UL //TYPO
#define MEDIUM_EXTERNAL_CLOCK	0x00000003UL
#define SLOW_EXTERNAL_CLOCK		0x00000004UL
#define EXTERNAL_CLOCK_AC		0x00000005UL 
#define EXTERNAL_CLOCK_DC		0x00000006UL 
#define EXTERNAL_CLOCK_10MHz_REF 0x00000007UL 
#define INTERNAL_CLOCK_DIV_5	0x000000010UL

//
//Clock Edge
//
#define CLOCK_EDGE_RISING		0x00000000UL
#define CLOCK_EDGE_FALLING		0x00000001UL

//
// Input Ranges
//
#define INPUT_RANGE_PM_20_MV	0x00000001UL
#define INPUT_RANGE_PM_40_MV	0x00000002UL
#define INPUT_RANGE_PM_50_MV	0x00000003UL
#define INPUT_RANGE_PM_80_MV	0x00000004UL
#define INPUT_RANGE_PM_100_MV	0x00000005UL
#define INPUT_RANGE_PM_200_MV	0x00000006UL
#define INPUT_RANGE_PM_400_MV	0x00000007UL
#define INPUT_RANGE_PM_500_MV	0x00000008UL
#define INPUT_RANGE_PM_800_MV	0x00000009UL
#define INPUT_RANGE_PM_1_V		0x0000000AUL
#define INPUT_RANGE_PM_2_V		0x0000000BUL
#define INPUT_RANGE_PM_4_V		0x0000000CUL
#define INPUT_RANGE_PM_5_V		0x0000000DUL
#define INPUT_RANGE_PM_8_V		0x0000000EUL
#define INPUT_RANGE_PM_10_V		0x0000000FUL
#define INPUT_RANGE_PM_20_V		0x00000010UL
#define INPUT_RANGE_PM_40_V		0x00000011UL
#define INPUT_RANGE_PM_16_V		0x00000012UL
#define INPUT_RANGE_HIFI		0x00000020UL
//
// Coupling Values
//
#define AC_COUPLING				0x00000001UL
#define DC_COUPLING				0x00000002UL

//
// Trigger Engines
//
#define TRIG_ENGINE_J			0x00000000UL
#define TRIG_ENGINE_K			0x00000001UL

//
// Trigger Engine Operation
//
#define TRIG_ENGINE_OP_J			0x00000000UL
#define TRIG_ENGINE_OP_K			0x00000001UL
#define TRIG_ENGINE_OP_J_OR_K		0x00000002UL
#define TRIG_ENGINE_OP_J_AND_K		0x00000003UL
#define TRIG_ENGINE_OP_J_XOR_K		0x00000004UL
#define TRIG_ENGINE_OP_J_AND_NOT_K	0x00000005UL
#define TRIG_ENGINE_OP_NOT_J_AND_K	0x00000006UL

//
// Trigger Engine Sources
//
#define TRIG_CHAN_A				0x00000000UL
#define TRIG_CHAN_B				0x00000001UL
#define TRIG_EXTERNAL			0x00000002UL
#define TRIG_DISABLE			0x00000003UL

//
// Trigger Slope
//
#define TRIGGER_SLOPE_POSITIVE	0x00000001UL
#define TRIGGER_SLOPE_NEGATIVE	0x00000002UL

//
// Channel Selection
//
#define CHANNEL_ALL				0x00000000UL
#define CHANNEL_A				0x00000001UL
#define CHANNEL_B				0x00000002UL
#define CHANNEL_C				0x00000003UL
#define CHANNEL_D				0x00000004UL
#define CHANNEL_E				0x00000005UL
#define CHANNEL_F				0x00000006UL
#define CHANNEL_G				0x00000007UL
#define CHANNEL_H				0x00000008UL


//
// Master/Slave Configuration
//
#define BOARD_IS_INDEPENDENT	0x00000000UL
#define BOARD_IS_MASTER			0x00000001UL
#define BOARD_IS_SLAVE			0x00000002UL
#define BOARD_IS_LAST_SLAVE		0x00000003UL

//
// LED Control
//
#define LED_OFF					0x00000000UL
#define LED_ON					0x00000001UL

//
// Attenuator Relay
//
#define	AR_X1					0x00000000UL
#define	AR_DIV40				0x00000001UL

//
// External Trigger Attenuator Relay
//
#define	ETR_DIV5				0x00000000UL
#define ETR_X1					0x00000001UL
#define	ETR_5V					0x00000000UL
#define ETR_1V					0x00000001UL

//
// Device Sleep state
//
#define POWER_OFF				0x00000000UL
#define POWER_ON				0x00000001UL

//
// Software Events control
//
#define SW_EVENTS_OFF			0x00000000UL
#define SW_EVENTS_ON			0x00000001UL

//
// TimeStamp Value Reset Control
//
#define TIMESTAMP_RESET_FIRSTTIME_ONLY	0x00000000UL
#define TIMESTAMP_RESET_ALWAYS			0x00000001UL

// DAC Names used by API AlazarDACSettingAdjust 
//
// DAC Names Specific to the ATS460
//
#define ATS460_DAC_A_GAIN			0x00000001UL
#define ATS460_DAC_A_OFFSET			0x00000002UL
#define ATS460_DAC_A_POSITION		0x00000003UL
#define ATS460_DAC_B_GAIN			0x00000009UL
#define ATS460_DAC_B_OFFSET			0x0000000AUL
#define ATS460_DAC_B_POSITION		0x0000000BUL
#define ATS460_DAC_EXTERNAL_CLK_REF	0x00000007UL
//
// DAC Names Specific to the ATS660
//
#define ATS660_DAC_A_GAIN			0x00000001UL
#define ATS660_DAC_A_OFFSET			0x00000002UL
#define ATS660_DAC_A_POSITION		0x00000003UL
#define ATS660_DAC_B_GAIN			0x00000009UL
#define ATS660_DAC_B_OFFSET			0x0000000AUL
#define ATS660_DAC_B_POSITION		0x0000000BUL
#define ATS660_DAC_EXTERNAL_CLK_REF	0x00000007UL
//
// DAC Names Specific to the ATS665
//
#define ATS665_DAC_A_GAIN			0x00000001UL
#define ATS665_DAC_A_OFFSET			0x00000002UL
#define ATS665_DAC_A_POSITION		0x00000003UL
#define ATS665_DAC_B_GAIN			0x00000009UL
#define ATS665_DAC_B_OFFSET			0x0000000AUL
#define ATS665_DAC_B_POSITION		0x0000000BUL
#define ATS665_DAC_EXTERNAL_CLK_REF	0x00000007UL
// DAC Names Specific to the ATS860
//  ------------ Not implemented yet ---------
// DAC Names Specific to the ATS310
//  ------------ Not implemented yet ---------
// DAC Names Specific to the ATS330
//  ------------ Not implemented yet ---------
// DAC Names Specific to the ATS850
//  ------------ Not implemented yet ---------
//
// Error return values
//
#define SETDAC_INVALID_SETGET	 660
#define SETDAC_INVALID_CHANNEL   661
#define SETDAC_INVALID_DACNAME	 662
#define SETDAC_INVALID_COUPLING  663
#define SETDAC_INVALID_RANGE	 664
#define SETDAC_INVALID_IMPEDANCE 665
#define SETDAC_BAD_GET_PTR       667
#define SETDAC_INVALID_BOARDTYPE 668

// 
// Auxilary IO 
// 
#define AUX_OUT_TRIGGER					0U
#define AUX_OUT_PACER					2U
#define AUX_OUT_BUSY					4U
#define AUX_OUT_CLOCK					6U
#define AUX_OUT_RESERVED				8U
#define AUX_OUT_CAPTURE_ALMOST_DONE		10U
#define AUX_OUT_AUXILIARY				12U
#define AUX_OUT_SERIAL_DATA				14U
#define AUX_OUT_TRIGGER_ENABLE			20U

#define AUX_IN_TRIGGER_ENABLE			1U
#define AUX_IN_DIGITAL_TRIGGER			3U
#define AUX_IN_GATE						5U
#define AUX_IN_CAPTURE_ON_DEMAND		7U
#define AUX_IN_RESET_TIMESTAMP			9U
#define AUX_IN_SLOW_EXTERNAL_CLOCK		11U
#define AUX_INPUT_AUXILIARY				13U
#define AUX_INPUT_SERIAL_DATA			15U


#endif //_ALAZARCMD_H