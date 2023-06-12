#ifndef noritake_vhd_h // include guard
#define noritake_vhd_h

// =============== PINS ===============
#define STB_PIN 1
#define SCK_PIN 2
#define SI_PIN 0

#define DEBUG_STB_PIN 11
#define DEBUG_SCK_PIN 12
#define DEBUG_SI_PIN 13

void display_init(void);
void display_clear(void);
void display_home(void);
void display_set_cursor(uint8_t row, uint8_t col);
void display_on(void);
void display_set_max_brightness(void);
void set_8bit_mode(void);

#endif /* MY_CLASS_H */