/*
 * File:   Main.c
 * Author: javie
 *
 * Created on March 20, 2024, 6:55 PM
 */


#define FCY 8000000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpic30.h>
#include "config.h"
#include "lcd.h"
#include <math.h>


void system_init(){
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0000;
    LATB = 0x0000;

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0x001F;
    TRISB = 0x0000;

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPU1 = 0x0000;
    CNPU2 = 0x0000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    //AD1PCFG = 0x0E3C;
     AD1PCFG = 0xFFFF;
  
}




int main(void) {
    int LCD_AUXILIAR=0;
    int ms = 0;
    int s = 0;
    int u_s = 0;
    int d_s = 0;
    int m = 0;
    int u_m = 0;
    int d_m = 0;
    int h =0;
    int u_h = 0;
    int d_h = 0;
    int cont_u_s = 0;
    int cont_d_s = 0;
    int cont_u_m = 0;
    int cont_d_m = 0;
    int cont_u_h = 0;
    int cont_d_h = 0;
    char reloj[] = "00:00:00";
    char aux_zero = 48;
    char dato_u_s = ' ';
    char dato_d_s = ' ';
    char dato_u_m = ' ';
    char dato_d_m = ' ';
    char dato_u_h = ' ';
    char dato_d_h = ' ';
    system_init();
    /*CONFIGURACION INICIAL DE LCD*/
    LCD_Initialize(); //Preder, configurar a 4 bits
    DisplayClr();  // borrar lo que tenga la pantalla
    LCDGoto(0,0); //poner el cursor en la posicion inicial
    
    //config timer
    T1CONbits.TCS = 0;
    TMR1 = 0;
    PR1 = 8000;
    T1CONbits.TON=1;
    
    while (1) {
        
        //inicializacion LCD
        LCD_PORT = LCD_AUXILIAR;
        LCDPutStr(reloj);
        
        
        if (_T1IF==1){
            ms++;
            _T1IF=0; 
        }
        
        //Contador milisegundos NOTA: por efectos practicos de simulacion se bajo el contador de 1000 a 10
        if (ms == 1000){
            u_s++;
            dato_u_s = aux_zero + u_s;
            reloj [7] = dato_u_s;
            cont_u_s++;
            s++;
            
            //contador unidades de segundos 
            if (cont_u_s == 10){
                reloj [7] = '0';
                dato_u_s = ' ';
                u_s = 0;
                cont_u_s = 0;
                d_s++;
                dato_d_s = aux_zero + d_s;
                reloj [6] = dato_d_s;               
                cont_d_s++;
                
                //contador decenas de segundos
                if (cont_d_s == 6){
                    reloj [6] = '0';
                    u_s = 0;
                    cont_u_s = 0;
                    cont_d_s = 0;
                    reloj [6] = '0';
                    dato_d_s = ' ';
                    cont_d_s = 0;
                    d_s = 0;
                }
            }
            ms = 0;
        }
        
        //contador de minutos
        if (s == 60) {
            m++;
            u_m++;
            dato_u_m = aux_zero + u_m;
            reloj [4] = dato_u_m;
            cont_u_m++;
            
            //contador unidades de minutos
            if (cont_u_m == 10) {
                reloj [4] = '0';
                dato_u_m = ' ';
                u_m = 0;
                cont_u_m = 0;
                d_m++;
                dato_d_m = aux_zero + d_m;
                reloj [3] = dato_d_m;
                cont_d_m++;
                
                //contador decenas de minutos
                if (cont_d_m == 6) {
                    reloj [4] = '0';
                    u_m = 0;
                    cont_u_m = 0;
                    cont_d_m = 0;
                    reloj [3] = '0';
                    dato_d_m = ' ';
                    cont_d_m = 0;
                    d_m = 0;
                }
            } 
            s = 0;
        }
        
        //contador unidades de horas
        if (m == 60) {
            h++;
            u_h++;
            dato_u_h = aux_zero + u_h;
            reloj [1] = dato_u_h;
            cont_u_h++;
            
            //contador unidades de horas
            if (cont_u_h == 10) {
                reloj [1] = '0';
                dato_u_h = ' ';
                u_h = 0;
                cont_u_h = 0;
                d_h++;
                dato_d_h = aux_zero + d_h;
                reloj [0] = dato_d_h;
                cont_d_h++;
                
                //contador decenas de horas
                if (cont_d_h == 24) {
                        reloj [1] = '0';
                        u_h = 0;
                        cont_u_h = 0;
                        cont_d_h = 0;
                        reloj [0] = '0';
                        dato_d_h = ' ';
                        cont_d_h = 0;
                        d_h = 0;
                }
            }
            
            m = 0;
        }
        LCDGoto(0,0);
    
        
        
        
        
        
    }
    
            
            
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}

