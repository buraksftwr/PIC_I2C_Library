#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 4000000
#define baudrate 100000 // The baudrate is configurated to have 100 kbps data rate.

void I2C_Wait(void){
    while((SSPCON2 & 0x1F)||(SSPSTAT & 0x04));
}

uint8_t I2C_Start(void){
    SEN = 1;
    while(SEN);
    SSPIF = 0;
    if(!SSPSTATbits.S)
        return 0;
    return 1;
}

uint8_t I2C_Stop(void){
    PEN = 1;
    while(PEN);
    SSPIF = 0;
    if(!SSPSTATbits.P)
        return 0;
    else
        return 1;
}

void I2C_ACK(void){
    I2C_Wait();
    ACKDT = 0; // 0 -> Receive success(ACK), 1 -> Receive unsuccess(NACK)
    ACKEN = 1;
    while(ACKEN);
}

void I2C_NACK(void){
    I2C_Wait();
    ACKDT = 1; 
    ACKEN = 1;
    while(ACKEN);
}

void I2C_MasterInit(void){
    SSPCON = 0x28;
    SSPCON2 = 0x00;
    SSPSTAT = 0x80;
    SSPADD = ((_XTAL_FREQ/4)/baudrate) - 1;
    TRISC3 = 1;
    TRISC4 = 1;
}

void I2C_MasterStop(void){
    SSPCON = 0x00;
    SSPCON2 = 0x00;
    SSPSTAT = 0x00;
    TRISC3 = 0;
    TRISC4 = 0;
}

void I2C_SlaveInit(uint8_t self_Adress){
    SSPADD = self_Adress;
    SSPSTAT = 0x80;
    SSPCON = 0x36;
    SSPCON2 = 0x01;
    TRISC3 = 1;
    TRISC4 = 1;
    GIE = 1;
    PEIE = 1;
    SSPIF = 0;
    SSPIE = 1; 
}

uint8_t I2C_SendData(uint8_t data){
    I2C_Wait();
    SSPBUF = data;
    I2C_Wait();
    return ACKSTAT;
}

uint8_t I2C_ReadData(void){
    RCEN = 1;
    while(!SSPIF);
    SSPIF = 0;
    return SSPBUF;
}