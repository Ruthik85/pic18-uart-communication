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

void UART_Read_String(char *buffer, int max_length) {
    int i = 0;
    char temp;

    while (i < (max_length - 1)) {
        temp = UART_Read(); // Get one character
        
        // If "Enter" is pressed (ASCII 13 is \r), stop reading
        if (temp == '\r' || temp == '\n') {
            break;
        }

        // Echo the character back so you can see what you are typing
        TXREG1 = temp; 
        while(!PIR1bits.TX1IF);

        buffer[i] = temp; // Store it in our string array
        i++;
    }
    
    buffer[i] = '\0'; // Null-terminate the string (very important in C!)
}
void main(void) {
    OSCCONbits.IRCF = 0b111; // 16 MHz
    UART_Init();

    char myBuffer[20]; // Array to hold up to 19 characters + null

    while(1) {
        UART_Write_Text("\r\nEnter word: ");
        
        UART_Read_String(myBuffer, 20); 
        
        UART_Write_Text("\r\n Received word: ");
        UART_Write_Text(myBuffer);
        
    }
}