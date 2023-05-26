int bf_ifnHAL_I2C_ChanSel(int bus, uint8_t dev, int chan);
int bf_ifnHAL_SMBUS_Probe( uint8_t ucBus, uint8_t dev );
int bf_ifnHAL_SMBUS_Set(int bus, uint8_t dev, uint16_t daddr, uint8_t alen, uint8_t data, uint8_t dlen);
int bf_ifnHAL_SMBUS_Get(int bus, uint8_t dev, uint16_t daddr, uint8_t alen, uint8_t *data, uint8_t dlen);
int bf_ifnHAL_SMBUS_Write_Byte(int bus, uint8_t dev, uint16_t daddr, uint8_t value);
int bf_ifnHAL_SMBUS_Read_Byte(int bus, uint8_t dev, uint16_t daddr, uint8_t *value);
int bf_ifnHAL_SMBUS_Write_Block(int bus, uint8_t dev, uint16_t daddr, uint8_t *value, uint8_t BufSize);
int bf_ifnHAL_SMBUS_Read_Block(int bus, uint8_t dev, uint16_t daddr, uint8_t *ReplyBuf, uint8_t BufSize);
int bf_ifnHAL_SMBUS_Write_I2C_Block(int bus, uint8_t dev, uint16_t daddr, uint8_t *value, uint16_t BufSize);
int bf_ifnHAL_SMBUS_Read_I2C_Block(int bus, uint8_t dev, uint16_t daddr, uint8_t *ReplyBuf, uint16_t BufSize);


