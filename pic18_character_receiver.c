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

char UART_Read() 
{
    // Wait for data to be received (RC1IF will be 1 when data is ready)
    while(!PIR1bits.RC1IF); 
    
    // Check for errors (Overrun or Framing errors)
    if(RCSTA1bits.OERR) {
        RCSTA1bits.CREN = 0; // Reset receiver
        RCSTA1bits.CREN = 1;
    }
    
    return RCREG1; // Return the received character
}

void main(void) {
    OSCCONbits.IRCF = 0b111; // 16 MHz
    UART_Init();
    
    char received_char;
    UART_Write_Text("Receiver Ready! Type something...\r\n");

    while(1) {
        received_char = UART_Read();      // Wait for a character
        UART_Write_Text("You typed: ");   // Send a label
        while(!PIR1bits.TX1IF);           // Wait for TX buffer
        TXREG1 = received_char;           // Send the character back (Echo)
        UART_Write_Text("\r\n");          // New line
    }
}