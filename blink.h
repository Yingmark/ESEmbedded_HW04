#ifndef BLINK_H
#define BLINK_H

#define USER_BUTTON 0
#define LED_GREEN 12
#define LED_ORANGE 13
#define LED_RED 14
#define LED_BLUE 15

void blink(unsigned int led);
void blink_count(unsigned int led, unsigned int count);
void button_init(unsigned int pin);
void button_opration(unsigned int button);

#endif