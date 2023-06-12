#include "noritake-vfd.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"


void display_init(){

    // =============== INIT GPIO ===============
    gpio_init(SI_PIN);
    gpio_set_dir(SI_PIN, GPIO_OUT);

    gpio_init(STB_PIN);
    gpio_set_dir(STB_PIN, GPIO_OUT);

    gpio_init(SCK_PIN);
    gpio_set_dir(SCK_PIN, GPIO_OUT);

    gpio_init(DEBUG_SI_PIN);
    gpio_set_dir(DEBUG_SI_PIN, GPIO_OUT);

    gpio_init(DEBUG_STB_PIN);
    gpio_set_dir(DEBUG_STB_PIN, GPIO_OUT);

    gpio_init(DEBUG_SCK_PIN);
    gpio_set_dir(DEBUG_SCK_PIN, GPIO_OUT);



    gpio_put(SI_PIN, 0);
    gpio_put(STB_PIN, 1);
    gpio_put(SCK_PIN, 0);

    gpio_put(DEBUG_SI_PIN, 0);
    gpio_put(DEBUG_STB_PIN, 1);
    gpio_put(DEBUG_SCK_PIN, 0);

    set_8bit_mode();

}

void write_byte(uint8_t byte){

    for (int i = 0; i < 8; i++) {
        gpio_put(SCK_PIN, 1);
        gpio_put(DEBUG_SCK_PIN, 1);

        gpio_put(SI_PIN, (byte << i) & 0b10000000);
        gpio_put(DEBUG_SI_PIN, (byte << i) & 0b10000000);

        sleep_us(1);
        gpio_put(SCK_PIN, 0);
        gpio_put(DEBUG_SCK_PIN, 0);

        sleep_us(1);
        gpio_put(SCK_PIN, 1);
        gpio_put(DEBUG_SCK_PIN, 1);
    }
    
}

void display_write_command(uint8_t command, bool RS, bool RW ) {
    uint8_t start_byte = 0b11111000;
    start_byte |= (RS << 1);
    start_byte |= (RW << 2);

    gpio_put(STB_PIN, 0);
    gpio_put(DEBUG_STB_PIN, 0);

    sleep_us(1);
    write_byte(start_byte);
    write_byte(command);

    gpio_put(STB_PIN, 1);
    gpio_put(DEBUG_STB_PIN, 1);
}

void display_set_max_brightness(){
    display_write_command(0b00000000, true, false); // 
}

void display_clear(){
    display_write_command(0x01, false, false);
}

void display_home(){
    display_write_command(0x02, false, false);
}

void display_set_cursor(uint8_t row, uint8_t col){
    uint8_t command = 0x80;
    command |= (row << 6);
    command |= col;
    display_write_command(command, false, false);
}

void display_on(){
    display_write_command(0b00001111, false, false); // 0b00001111

}

void enter_character_mode(){
    display_write_command(0b00000111, false, false);
}





