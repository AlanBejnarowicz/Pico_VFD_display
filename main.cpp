#include <stdio.h>
#include "pico/stdlib.h"

//#include "Noritake_Lib/Noritake_VFD_CUU.h"
#include "Noritake_Lib/CUU_Interface_lib.h"
#include "Noritake_Lib/CUU_Serial.h"
#include "Noritake_Lib/Noritake_VFD_CUU.cpp"


#include "config.h"
//#include "noritake-vfd.c"



CUU_Serial interface(SI_PIN, STB_PIN, SCK_PIN); // SIO, STB, SCK
CUU_Serial debug_interface(DEBUG_SI_PIN, DEBUG_STB_PIN, DEBUG_SCK_PIN);
Noritake_VFD_CUU vfd;

int seconds = 0;
int minutes = 0;
int hours = 0;

int main() {
    stdio_init_all();
     sleep_ms(500);


    // prepare pin 25
    
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // VFD INIT
    vfd.begin(20, 2);    // 20x2 character module
    vfd.interface(interface); // select which interface to use
    vfd.CUU_init();      // initialize module
    sleep_ms(100);


    vfd.print("Hello Noritake"); // print Hello Noritake on the first line
    sleep_ms(500);
    vfd.CUU_clearScreen(); // clear screen


    

    while (1) {

        // blink led
        gpio_put(LED_PIN, 1);
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        sleep_ms(500);

        //vfd.CUU_clearScreen(); // clear screen

        char s[20]; 
        sprintf(s,"%02d:%02d:%02d", hours,minutes,seconds);

        // print time
        vfd.CUU_setCursor(0, 0);
        vfd.print("         ");
        vfd.CUU_setCursor(0, 0);
        vfd.print(s);

         vfd.CUU_setCursor(0, 1);
        vfd.print("Monday 24.04.2023"); 



        // increment time
        seconds++;
        if (seconds == 60) {
            seconds = 0;
            minutes++;
        }
        if (minutes == 60) {
            minutes = 0;
            hours++;
        }
        if (hours == 24) {
            hours = 0;
        }


    }
    return 0;
}