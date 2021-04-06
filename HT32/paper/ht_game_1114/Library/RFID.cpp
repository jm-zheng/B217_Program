//------------------------------------------------------------------------------
// RFID_SIC.cpp
//------------------------------------------------------------------------------
#include "RFID.h"

//------------------------------------------------------------------------------
void RFID_SIC::begin(uint8_t cs_pin, uint8_t msck_pin, uint8_t miso_pin, uint8_t mosi_pin)
//void RFID_SIC::begin(uint8_t cs_pin)
{
	_cs_pin = cs_pin;
	pinMode(_cs_pin, OUTPUT);
	digitalWrite(_cs_pin, HIGH);

	spi_sic.setPins(msck_pin, miso_pin, mosi_pin); //sck,miso,mosi
	spi_sic.begin();
	//SPI.begin();
}

//------------------------------------------------------------------------------
uint8_t RFID_SIC::sicSend(uint8_t ch)
{
	return spi_sic.transfer(ch);
	//return SPI.transfer(ch);
}

//------------------------------------------------------------------------------
uint8_t RFID_SIC::sicRead1Reg(uint8_t addr)
{
	uint8_t ch;
	uint8_t ad;

	digitalWrite(_cs_pin, LOW);
	ad = (addr << 1);
	sicSend(ad | 0x80);
	ch = sicSend(0);
	digitalWrite(_cs_pin, HIGH);
	return ch;
}

//------------------------------------------------------------------------------
void RFID_SIC::sicWrite1Reg(uint8_t addr, uint8_t ch)
{
	uint8_t ad;

  delay(1);
	digitalWrite(_cs_pin, LOW);
	ad = (addr << 1) &0x7E;
	sicSend(ad);
	sicSend(ch);
	digitalWrite(_cs_pin, HIGH);
}

//------------------------------------------------------------------------------
void RFID_SIC::sicSettingCRC(uint8_t txcrc, uint8_t rxcrc)
{
	uint8_t crc;

	crc = sicRead1Reg(SIC_CRC_SETTING_REG);
	if (txcrc == TX_CRC_ENABLE)
	{
		crc |= TX_CRC_EN_SET_MASK;
	}
	else
	{
		crc &= TX_CRC_EN_CLEAR_MASK;
	}
	if (rxcrc == RX_CRC_ENABLE)
	{
		crc |= RX_CRC_EN_SET_MASK;
	}
	else
	{
		crc &= RX_CRC_EN_CLEAR_MASK;
	}
	sicWrite1Reg(SIC_CRC_SETTING_REG, crc);
}

//------------------------------------------------------------------------------
uint8_t RFID_SIC::sicReadRxLastBit(void)
{
	uint8_t ch;

	ch = sicRead1Reg(SIC_SECOND_STATUS_REG);

	return (ch &0x07);
}

//------------------------------------------------------------------------------
uint8_t RFID_SIC::sicTransceive(uint8_t cmd,uint8_t txlen,uint8_t txbuf[])
{
	uint8_t timeout;
	uint8_t n, ad;

	// Read Register 0x09 before write
	// Set Only FlushFIFO Bit (Bit0)
	sicWrite1Reg(SIC_CONTROL_REG, (sicRead1Reg(SIC_CONTROL_REG) | FLUSH_FIFO_SET_MASK));

	//----------- Transmit ----------------//
	digitalWrite(_cs_pin, LOW);
	ad = (SIC_FIFO_DATA_REG << 1) &0x7E;
	sicSend(ad);
	for (n = 0; n < txlen; n++)
	{
		sicSend(txbuf[n]);
	}
	digitalWrite(_cs_pin, HIGH);
	delay(1);
	sicWrite1Reg(SIC_COMMAND_REG, cmd);

	//------------------- Recieve -------------------//
	sicWrite1Reg(SIC_INTERRUPT_EN_REG, ALL_IRQ_SOURCE); // Disable Interrupt
	sicWrite1Reg(SIC_INTERRUPT_RQ_REG, ALL_IRQ_SOURCE); // Clear Interrupt Flg
	// Enable HiAlert,Idle,Timer IRQ
	sicWrite1Reg(SIC_INTERRUPT_EN_REG, (0x80 | IDLE_IRQ | TIMER_IRQ));

	timeout = 0;
	while (timeout++ < 200)
	{
		delayMicroseconds(500);
		// Read FIFO length of data
		sicDataRxLen = sicRead1Reg(SIC_FIFO_LENGTH_REG);
		if(sicDataRxLen>0)
		{
			delay(5);
			sicDataRxLen = sicRead1Reg(SIC_FIFO_LENGTH_REG);
			if (sicDataRxLen > SIC_BUFFER_SIZE)
			{
				sicDataRxLen = SIC_BUFFER_SIZE;
			}
			// Read data in FIFO
			digitalWrite(_cs_pin, LOW);
			ad = (SIC_FIFO_DATA_REG << 1);
			sicSend(ad | 0x80);
			for (n = 0; n < sicDataRxLen; n++)
			{
				if (n == (sicDataRxLen - 1))
				{
					ad = 0;
				}
				sicData[n] = sicSend(ad);
			}
			digitalWrite(_cs_pin, HIGH);
			return 1;
		}
	}
	return 0;
}

//------------------------------------------------------------------------------
void RFID_SIC::sicInit(void)
{
	sicWrite1Reg(SIC_RX_CONTROL2_REG, 0x41);
	sicWrite1Reg(SIC_TX_CONTROL_REG, 0x58);
	sicWrite1Reg(SIC_FIFO_LEVEL_REG, SIC_WATER_LEVEL);
	sicWrite1Reg(SIC_IO_CONFIG_REG, 0x00);

	//sicWrite1Reg(SIC_TEST_ANA_SEL_REG, 0x08);
	sicWrite1Reg(SIC_TEST_ANA_SEL_REG, 0x00);

	sicWrite1Reg(SIC_ANALOG_ADJUST1_REG, 0xBF); //SIC9100

	//sicWrite1Reg(SIC_ANALOG_ADJUST2_REG, 0x21);
	sicWrite1Reg(SIC_ANALOG_ADJUST2_REG, 0x19);

	sicWrite1Reg(SIC_TX_DISABLE_CTRL_REG, 0x00);
	sicWrite1Reg(SIC_ISO15693_HEADER_REG, 0x01);

	// ISO14443A Config
	// Tx Session
	// Read Register 0x11 before write
	// Set Only ModulatorSource (Bit5:6)
	sicWrite1Reg(SIC_TX_CONTROL_REG, ((sicRead1Reg(SIC_TX_CONTROL_REG) &MOD_SOURCE_CLEAR_MASK) | (MOD_SOURCE_INTERNAL << 5)));
	// Read Register 0x11 before write
	// Set Only Force100ASK Bit (Bit4)
	sicWrite1Reg(SIC_TX_CONTROL_REG, (sicRead1Reg(SIC_TX_CONTROL_REG) | FORCE_100ASK_SET_MASK));

	sicWrite1Reg(SIC_CW_CONDUCTANCE_REG, 0x3F);

	// Rx Session
	sicWrite1Reg(SIC_RX_THRES_HOLD_REG, 0x8C); // Set CollLevel, MinLevel
	sicWrite1Reg(SIC_BPSK_DEMOD_REG, 0x02); // Set HP2off(0), TauD(00), AGC_EN(1), TauAGC(0)
	sicWrite1Reg(SIC_RX_WAIT_REG, 0x03); // Set RxWait

	// CRC
	sicWrite1Reg(SIC_CRC_SETTING_REG, 0x03); // Parity Odd
	sicWrite1Reg(SIC_CRC_PRESET_LSB_REG, 0x63); // Preset CRC LSB = 0x63
	sicWrite1Reg(SIC_CRC_PRESET_MSB_REG, 0x63); // Preset CRC MSB = 0x63

	// Timer
	sicWrite1Reg(SIC_TIMER_CLOCK_REG, 0x0A); // Selects Timer Prescaler and set Timer Auto-restart
	sicWrite1Reg(SIC_TIMER_RELOAD_REG, 0xFF); // TReload Value

	// Read Register 0x09 before Write
	// Clear Only Crypto Bit (Bit3)
	sicWrite1Reg(SIC_CONTROL_REG, (sicRead1Reg(SIC_CONTROL_REG) &CRYPTO1_ON_CLEAR_MARK));

	sicWrite1Reg(SIC_TEST_ANA_SEL_REG, 0x00);

	//sicWrite1Reg(SIC_ANALOG_ADJUST2_REG, 0x00);
	sicWrite1Reg(SIC_ANALOG_ADJUST2_REG, 0x19);

	// Tx 106 kbps
	sicWrite1Reg(SIC_CODER_CONTROL_REG, 0x19); // Set Tx Coding
	sicWrite1Reg(SIC_MOD_WIDTH_REG, 0x0F); // Set ModWidth
	sicWrite1Reg(SIC_MOD_WIDTH_SOF_REG, 0x0F); // Set ModWidthSOF

	// Rx 106 kbps
	sicWrite1Reg(SIC_RX_CONTROL1_REG, ((sicRead1Reg(SIC_RX_CONTROL1_REG) &0x07) | 0x68)); // Set SubCCar, SubCPulse
	sicWrite1Reg(SIC_DECODER_CONTROL_REG, 0x28); // Set Rx-Framing and Zero after coll
	// Tx 106 kbps
	sicWrite1Reg(SIC_BIT_PHASE_REG, 0x3D); // Set Bitphase

  sicRfOn();
}

//------------------------------------------------------------------------------
void RFID_SIC::sicRfOn(void)
{
	//TX ON
	sicWrite1Reg(SIC_TX_CONTROL_REG, (sicRead1Reg(SIC_TX_CONTROL_REG) | TX2_RF_EN_SET_MASK | TX1_RF_EN_SET_MASK));
}

//------------------------------------------------------------------------------
void RFID_SIC::sicRfOff(void)
{
	//TX OFF
	sicWrite1Reg(SIC_TX_CONTROL_REG, (sicRead1Reg(SIC_TX_CONTROL_REG) &TX2_RF_EN_CLEAR_MASK &TX1_RF_EN_CLEAR_MASK));
}

//------------------------------------------------------------------------------
uint8_t RFID_SIC::ISO14443A_Request(void)
{
	sicRfOff();
  delay(5);
	sicRfOn();
  delay(5);

	// Read Register 0x09 before Write
	// Clear Only Crypto Bit (Bit3)
	sicWrite1Reg(SIC_CONTROL_REG, (sicRead1Reg(SIC_CONTROL_REG) &CRYPTO1_ON_CLEAR_MARK));

	// Tx Send 7 bit
	sicWrite1Reg(SIC_BIT_FRAMING_REG, 7);

	sicSettingCRC(TX_CRC_DISABLE, RX_CRC_DISABLE);

	// Request Cmd
	sicData[0] = ISO14443A_REQUEST_RF_CMD;
	if (sicTransceive(SIC_CMD_TRANCEIVE,1,sicData) == 1)
	{
		if (sicDataRxLen == LEN_ISO14443A_REQUEST_RF_RESP)
		{
			return 1;
		}
	}
  return 0;
}

//------------------------------------------------------------------------------
uint8_t RFID_SIC::ISO14443A_Anticoll(uint8_t level)
{
	uint8_t i;

	sicSettingCRC(TX_CRC_DISABLE, RX_CRC_DISABLE);
	sicWrite1Reg(SIC_DECODER_CONTROL_REG, (sicRead1Reg(SIC_DECODER_CONTROL_REG) &COLL_MARK_VAL_CLEAR_MASK)); // Clear CollMaskValue Bit = '0'
	sicWrite1Reg(SIC_BIT_FRAMING_REG, 0);

	sicData[0] = level;
	sicData[1] = 0x20; // NVB Cmd
	if (sicTransceive(SIC_CMD_TRANCEIVE,2,sicData) == 1)
	{
		if (sicDataRxLen == LEN_ISO14443A_ANTICOLL_RF_RESP)
		{
			if (sicData[4] == (sicData[0] ^ sicData[1] ^ sicData[2] ^ sicData[3]))
			{
				for (i = 0; i < 5; i++)
				{
					sicUID[i] = sicData[i];
				}
				return 1;
			}
		}
	}
	return 0;
}

//------------------------------------------------------------------------------
uint8_t RFID_SIC::ISO14443A_Select(uint8_t level)
{
	uint8_t i;

	sicSettingCRC(TX_CRC_ENABLE, RX_CRC_ENABLE);
  sicData[0] = level;
	sicData[1] = 0x70; // NVB
	for (i = 0; i < 5; i++)
	{
		sicData[i + 2] = sicUID[i]; // UID 4 Bytes + chksum
	}
	return sicTransceive(SIC_CMD_TRANCEIVE,7,sicData);
}

//------------------------------------------------------------------------------
uint8_t RFID_SIC::ISO14443A_Write_Block(uint8_t block, uint8_t wrbuf[])
{
	uint8_t i;
	uint8_t rxbit;

	sicSettingCRC(TX_CRC_ENABLE, RX_CRC_DISABLE);
	sicData[0] = MIFARE_AUTHENT_WRITE_BLOCK_RF_CMD; // Write Mifare Command
	sicData[1] = block;
	if (sicTransceive(SIC_CMD_TRANCEIVE, 2,sicData) == 1)
	{
		rxbit = sicReadRxLastBit();
		if (((sicDataRxLen) == 1) && (rxbit == 4) && (sicData[0] == MIFARE_ACK))
		{
			for (i = 0; i < 16; i++)
			{
				sicData[i] = wrbuf[i];
			}
			if (sicTransceive(SIC_CMD_TRANCEIVE, 16, sicData) == 1)
			{
				rxbit = sicReadRxLastBit();
				if (((sicDataRxLen) == 1) && (rxbit == 4) && (sicData[0] == MIFARE_ACK))
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

//------------------------------------------------------------------------------
uint8_t RFID_SIC::ISO14443A_Read_Block(uint8_t block,uint8_t rdbuf[])
{
	uint8_t i;
	sicSettingCRC(TX_CRC_ENABLE, RX_CRC_ENABLE);
	sicData[0] = MIFARE_AUTHENT_READ_BLOCK_RF_CMD; // Read Mifare Command
	sicData[1] = block;
	if (sicTransceive(SIC_CMD_TRANCEIVE, 2,sicData) == 1)
	{
		if (sicDataRxLen == LEN_ISO14443A_READ_BLOCK_RF_RESP)
		{
			for (i = 0; i < 16; i++)
			{
				rdbuf[i]=sicData[i];
			}
			return 1;
		}
	}
	return 0;
}

//------------------------------------------------------------------------------
uint16_t RFID_SIC::ISO14443A_getUID(void)
{
	uint8_t i,uid7;
	uint16_t type;

 	if(ISO14443A_Request()==1)
	{
    type=sicData[0];
		if (type== 0x44)
		{
			uid7 = 1;
		}
		else
		{
			uid7 = 0;
		}
		type=(type<<8)+sicData[1];
		if (ISO14443A_Anticoll(ISO14443A_CASCADE_LEVEL_1_RF_CMD) == 1)
		{
			if (ISO14443A_Select(ISO14443A_CASCADE_LEVEL_1_RF_CMD) == 1)
			{
				if (uid7 == 1)
				{
					for (i = 0; i < 3; i++)
					{
						sicTemp[i] = sicUID[i + 1];
					}
					if (ISO14443A_Anticoll(ISO14443A_CASCADE_LEVEL_2_RF_CMD) == 1)
					{
						if (ISO14443A_Select(ISO14443A_CASCADE_LEVEL_2_RF_CMD) == 1)
						{
							for (i = 0; i < 4; i++)
							{
								sicTemp[i + 3] = sicUID[i];
							}
							for (i = 0; i < 7; i++)
							{
								sicUID[i] = sicTemp[i];
							}
						}
					}
				}
				else
				{
					for (i = 4; i < 7; i++)
					{
						sicUID[i] = 0x00;
					}
				}
				return type;
			}
		}
	}
	return 0;
}
