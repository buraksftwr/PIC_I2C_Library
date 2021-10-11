#include <stdint.h>

extern void I2C_Wait(void);
extern uint8_t I2C_Start(void);
extern uint8_t I2C_Stop(void);
extern void I2C_ACK(void);
extern void I2C_NACK(void);
extern void I2C_MasterInit(void);
extern void I2C_SlaveInit(void);
extern uint8_t I2C_SendData(uint8_t data);
extern uint8_t I2C_ReadData(uint8_t adress);
extern void I2C_MasterStop(void);