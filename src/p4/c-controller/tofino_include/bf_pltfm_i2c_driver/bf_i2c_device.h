#ifndef __BF_I2C_DEVICE_H__
#define __BF_I2C_DEVICE_H__

#define I2C_MUX_9548_CH_0       0x01
#define I2C_MUX_9548_CH_1       0x02
#define I2C_MUX_9548_CH_2       0x04
#define I2C_MUX_9548_CH_3       0x08
#define I2C_MUX_9548_CH_4       0x10
#define I2C_MUX_9548_CH_5       0x20
#define I2C_MUX_9548_CH_6       0x40
#define I2C_MUX_9548_CH_7       0x80

#define SFP_MUX_ADDR_1          0x74
#define SFP_MUX_ADDR_2          0x75
#define SFP_MUX_ADDR_3          0x76
#define SFP_MUX_ADDR_4          0x77

#define CPLD_ADDR_0             0x32
#define CPLD_ADDR_1             0x34
#define CPLD_ADDR_2             0x35

#define CPLD_0_SFP_PRESENCE_1   0x12
#define CPLD_0_SFP_PRESENCE_2   0x13
#define CPLD_1_SFP_PRESENCE_1   0x08
#define CPLD_1_SFP_PRESENCE_2   0x09
#define CPLD_1_SFP_PRESENCE_3   0x0A
#define CPLD_2_SFP_PRESENCE_1   0x08
#define CPLD_2_SFP_PRESENCE_2   0x09
#define CPLD_2_SFP_PRESENCE_3   0x0A

#define CPLD_0_SFP_LP_MODE_1    0x0E
#define CPLD_0_SFP_LP_MODE_2    0x0F
#define CPLD_1_SFP_LP_MODE_1    0x02
#define CPLD_1_SFP_LP_MODE_2    0x03
#define CPLD_1_SFP_LP_MODE_3    0x04
#define CPLD_2_SFP_LP_MODE_1    0x02
#define CPLD_2_SFP_LP_MODE_2    0x03
#define CPLD_2_SFP_LP_MODE_3    0x04

#define CPLD_0_SFP_RESET_1      0x14
#define CPLD_0_SFP_RESET_2      0x15
#define CPLD_1_SFP_RESET_1      0x0B
#define CPLD_1_SFP_RESET_2      0x0C
#define CPLD_1_SFP_RESET_3      0x0D
#define CPLD_2_SFP_RESET_1      0x0B
#define CPLD_2_SFP_RESET_2      0x0C
#define CPLD_2_SFP_RESET_3      0x0D

#define CPLD_0_SFP_INTERRUPT_1  0x16
#define CPLD_0_SFP_INTERRUPT_2  0x17
#define CPLD_1_SFP_INTERRUPT_1  0x0E
#define CPLD_1_SFP_INTERRUPT_2  0x0F
#define CPLD_1_SFP_INTERRUPT_3  0x10
#define CPLD_2_SFP_INTERRUPT_1  0x0E
#define CPLD_2_SFP_INTERRUPT_2  0x0F
#define CPLD_2_SFP_INTERRUPT_3  0x10

#define I2C0                    0
#define MAIN_MUX_ADDR           0x70

#define SFP_EEPROM_ADDR         0x50
#define SFP_EEPROM_SIZE         256

#define MAX_CPLD_NUM            3
#define MAX_CPLD_REG            3
#define MAX_FRONT_PORT          64

typedef struct CpldDev{
    unsigned int MainChan;
    unsigned int DevAddr;
    unsigned int Presence[MAX_CPLD_REG];
    unsigned int LpMode[MAX_CPLD_REG];
    unsigned int Reset[MAX_CPLD_REG];
    unsigned int Interrupt[MAX_CPLD_REG];
}CpldDev_t;

typedef struct SfpDev{
    unsigned int MainChan;
    unsigned int MuxAddr;
    unsigned int MuxChan;
    unsigned int Number;
}SfpDev_t;

uint64_t regdata_to_portmap(uint64_t data);
uint64_t portmap_to_regdata(uint64_t portmap);

#endif /* __BF_I2C_DEVICE_H__ */