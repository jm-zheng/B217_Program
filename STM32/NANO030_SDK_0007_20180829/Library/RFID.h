//------------------------------------------------------------------------------
// RFID.h
//------------------------------------------------------------------------------
#ifndef RFID_H_
#define RFID_H_

#include "OLED.h"
#include "SPI.h"
#include "SoftwareSPI.h"


//------------------------------------------------------------------------------
#define SIC_MAX_ADDR								63
#define SIC_WATER_LEVEL							16
#define SIC_HI_LEVEL								64 - SIC_WATER_LEVEL

//------------------------------------------------------------------------------
// Register for SIC931
//------------------------------------------------------------------------------
#define SIC_PAGE_REG								0x00

#define SIC_COMMAND_REG							0x01
#define SIC_FIFO_DATA_REG						0x02
#define SIC_PRIM_STATUS_REG					0x03
#define SIC_FIFO_LENGTH_REG					0x04
#define SIC_SECOND_STATUS_REG				0x05
#define SIC_INTERRUPT_EN_REG				0x06
#define SIC_INTERRUPT_RQ_REG				0x07

#define SIC_CONTROL_REG							0x09
#define SIC_ERROR_REG								0x0A
#define SIC_COLL_POS_REG						0x0B
#define SIC_TIMER_VAL_REG						0x0C
#define SIC_CRC_RES_LSB							0x0D
#define SIC_CRC_RES_MSB							0x0E
#define SIC_BIT_FRAMING_REG					0x0F

#define SIC_TX_CONTROL_REG					0x11
#define SIC_CW_CONDUCTANCE_REG			0x12
#define SIC_MOD_CONDUCTANCE_REG			0x13
#define SIC_CODER_CONTROL_REG				0x14
#define SIC_MOD_WIDTH_REG						0x15
#define SIC_MOD_WIDTH_SOF_REG				0x16
#define SIC_TYPE_B_FRAMING_REG			0x17

#define SIC_RX_CONTROL1_REG					0x19
#define SIC_DECODER_CONTROL_REG			0x1A
#define SIC_BIT_PHASE_REG	 					0x1B
#define SIC_RX_THRES_HOLD_REG 			0x1C
#define SIC_BPSK_DEMOD_REG	 				0x1D
#define SIC_RX_CONTROL2_REG  				0x1E

#define SIC_RX_WAIT_REG							0x21
#define SIC_CRC_SETTING_REG					0x22
#define SIC_CRC_PRESET_LSB_REG 			0x23
#define SIC_CRC_PRESET_MSB_REG 			0x24

#define SIC_FIFO_LEVEL_REG	  			0x29
#define SIC_TIMER_CLOCK_REG					0x2A
#define SIC_TIMER_CONTROL_REG 			0x2B
#define SIC_TIMER_RELOAD_REG  			0x2C
#define SIC_MAN_FILTER_CTRL_REG			0x2E
#define SIC_FILTER_COR_COEF_REG			0x2F

#define SIC_IO_CONFIG_REG						0x31

#define SIC_SSI_F_VALUE_REG					0x37

#define SIC_TEST_ANA_SEL_REG				0x3A
#define SIC_TX_DISABLE_CTRL_REG			0x3B
#define SIC_ISO15693_HEADER_REG			0x3D
#define SIC_ANALOG_ADJUST1_REG			0x3E
#define SIC_ANALOG_ADJUST2_REG			0x3F

//------------------------------------------------------------------------------
// Command for SIC931
//------------------------------------------------------------------------------
#define SIC_CMD_IDLE								0x00
#define SIC_CMD_TRANSMIT						0x1A
#define SIC_CMD_RECEIVE							0x16
#define SIC_CMD_TRANCEIVE						0x1E

//------------------------------------------------------------------------------
// Mask for Control Reg (Reg 0x09)
#define CRYPTO1_ON_MARK							0x08
#define CRYPTO1_ON_CLEAR_MARK				0xF7
#define FLUSH_FIFO_SET_MASK					0x01

//------------------------------------------------------------------------------
// Mask for TxControl Reg (Reg 0x11)
#define MOD_SOURCE_CLEAR_MASK				0x9F
#define FORCE_100ASK_SET_MASK				0x10
#define FORCE_100ASK_CLEAR_MASK			0xEF
#define TX2_RF_EN_SET_MASK					0x02
#define TX2_RF_EN_CLEAR_MASK				0xFD
#define TX1_RF_EN_SET_MASK					0x01
#define TX1_RF_EN_CLEAR_MASK				0xFE
#define TX2_INV_CLEAR_MASK					0xF7
#define TX2_CW_SET_MASK							0x04
#define TX2_CW_CLEAR_MASK						0xFB

//------------------------------------------------------------------------------
// Mask for Decoder Control Reg (Reg 0x1A)
#define COLL_MARK_VAL_MASK	 				0x40
#define COLL_MARK_VAL_SET_MASK			0x40
#define COLL_MARK_VAL_CLEAR_MASK		0xBF

//------------------------------------------------------------------------------
// Mask for CRCSetting Reg (Reg 0x22)
#define TX_CRC_EN_SET_MASK					0x04
#define TX_CRC_EN_CLEAR_MASK				0xFB
#define RX_CRC_EN_SET_MASK					0x08
#define RX_CRC_EN_CLEAR_MASK				0xF7

//------------------------------------------------------------------------------
// Interrupt Value for SIC931
#define CLEAR_ALL_IRQ_SOURCE				0x3F
#define ALL_IRQ_SOURCE							0x3F
#define TIMER_IRQ										0x20
#define TX_IRQ											0x10
#define RX_IRQ											0x08
#define IDLE_IRQ										0x04
#define HI_ALERT_IRQ								0x02
#define LO_ALERT_IRQ								0x01

//------------------------------------------------------------------------------
// ModSource for SIC931
#define MOD_SOURCE_TRI_STARE				0x00
#define MOD_SOURCE_HIGH							0x01
#define MOD_SOURCE_INTERNAL					0x02
#define MOD_SOURCE_SIGIN0						0x03

//------------------------------------------------------------------------------
// CRC Setting for SIC931
#define TX_CRC_DISABLE							0x00
#define TX_CRC_ENABLE								0x01
#define RX_CRC_DISABLE							0x00
#define RX_CRC_ENABLE								0x01

//------------------------------------------------------------------------------
// Speed For ISO14443A
#define SPEED_106_KBPS							0x00
#define SPEED_212_KBPS							0x01
#define SPEED_424_KBPS							0x02
#define SPEED_848_KBPS							0x03

//------------------------------------------------------------------------------
#define MIFARE_ACK													0x0A

// RF Cmd
#define ISO14443A_REQUEST_RF_CMD						0x26
#define ISO14443A_CASCADE_LEVEL_1_RF_CMD		0x93
#define ISO14443A_CASCADE_LEVEL_2_RF_CMD		0x95
#define MIFARE_AUTHENT_WRITE_BLOCK_RF_CMD		0xA0
#define MIFARE_AUTHENT_READ_BLOCK_RF_CMD		0x30

// Length of response data for each command
#define LEN_ISO14443A_REQUEST_RF_RESP				2
#define LEN_ISO14443A_WAKEUP_RF_RESP				2
#define LEN_ISO14443A_ANTICOLL_RF_RESP			5
#define LEN_ISO14443A_SELECT_RF_RESP				1
#define LEN_ISO14443A_READ_BLOCK_RF_RESP		16

//------------------------------------------------------------------------------
#define SIC_BUFFER_SIZE    									32
class RFID_SIC
{
private:
	SoftwareSPI spi_sic;
	uint8_t _cs_pin;
public:
	void begin(uint8_t cs_pin, uint8_t miso_pin, uint8_t mosi_pin, uint8_t msck_pin);
	//void begin(uint8_t cs_pin);
	uint8_t sicSend(uint8_t ch);
	uint8_t sicRead1Reg(uint8_t addr);
  void sicWrite1Reg(uint8_t addr, uint8_t ch);
  void sicSettingCRC(uint8_t txcrc, uint8_t rxcrc);
  uint8_t sicCheckCryptoBit(void);
  uint8_t sicReadRxLastBit(void);
  uint8_t sicTransceive(uint8_t cmd,uint8_t txlen,uint8_t txbuf[]);
  void sicInit(void);
	void sicRfOn(void);
	void sicRfOff(void);
	
	uint8_t sicData[SIC_BUFFER_SIZE];
	uint8_t sicDataRxLen;
	uint8_t sicUID[7];
	uint8_t sicTemp[7];

	// ISO14443A command
  uint8_t ISO14443A_Request(void);
  uint8_t ISO14443A_Anticoll(uint8_t level);
  uint8_t ISO14443A_Select(uint8_t level);
  uint16_t ISO14443A_getUID(void);
  uint8_t ISO14443A_Write_Block(uint8_t block, uint8_t wrbuf[]);
  uint8_t ISO14443A_Read_Block(uint8_t block, uint8_t rdbuf[]);
};
#endif
