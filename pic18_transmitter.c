#define _XTAL_FREQ 16000000    // 16 MHz
#include <xc.h>
#include <pic18f65k90.h>
#pragma config FOSC = INTIO2    // Internal oscillator
#pragma config WDTEN = OFF      // Watchdog Timer Off
#pragma config MCLRE = ON       // MCLR pin enabled
#pragma config XINST = OFF    // Extended Instruction Set Disabled

void UART_Init() 
{
    TRISCbits.TRISC6 = 0; // TX is Output
    TRISCbits.TRISC7 = 1; // RX is Input

    // Baud Rate = 9600 (Calculated for 16MHz)
    SPBRG1 = 103;         
    TXSTA1bits.BRGH = 1;  // High Speed mode
    
    BAUDCON1bits.BRG16 = 0; // 8-bit Baud Register
    
    TXSTA1bits.SYNC = 0;  // Asynchronous mode
    RCSTA1bits.SPEN = 1;  // Serial Port Enable
    TXSTA1bits.TXEN = 1;  // Transmit Enable
    RCSTA1bits.CREN = 1;  // Receive Enable
}

void UART_Write_Text(char *text) 
{
    for(int i=0; text[i]!='\0'; i++) {
        while(!PIR1bits.TX1IF); // Wait for buffer
        TXREG1 = text[i];
    }
}


void main(void) {
    OSCCONbits.IRCF = 0b111; 

    UART_Init();
    
    __delay_ms(100); // Short wait for voltage to stabilize
    
    while(1) {
        
        while(!PIR1bits.TX1IF); 
        TXREG1 = 'A'; 
        
        __delay_ms(1000);
        UART_Write_Text("\nSystem Running...\r\n");
        UART_Write_Text("\nsunny sky\r\n");
    }
} 