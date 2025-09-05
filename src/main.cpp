#include <iostream>
#include "pico/stdlib.h"

using namespace std;

#define SW_0 9
#define SW_1 8
#define SW_2 7

#define LED_1 22
#define LED_2 21
#define LED_3 22

class GPIOPin
{
    public:
        GPIOPin(int pin, bool input = true, bool pullup = true, bool invert = false);
        GPIOPin(const GPIOPin &) = delete;

        bool read();
        bool operator() ();
        void write(bool value);
        void operator() (bool);
        operator int();

    private:
        int gpio_pin = 0;
        bool state = false;
};

GPIOPin::GPIOPin(int pin, bool input, bool pullup, bool invert)
{

    gpio_init(pin);
    gpio_set_dir(pin, !input);

    if (pullup) {
        gpio_pull_up(pin);
    }

    if (invert && input) {
        gpio_set_inover(pin, GPIO_OVERRIDE_INVERT);
    }
    else if (invert && !input) {
        gpio_set_outover(pin, GPIO_OVERRIDE_INVERT);
    }

    gpio_pin = pin;
}

bool GPIOPin::read() { return state; }
void GPIOPin::write(bool value)
{
    gpio_put(gpio_pin, value);
    state = value;
}

int main(void)
{
    GPIOPin sw0(SW_0, true, true, true);
    GPIOPin sw1(SW_1, true, true, true);
    GPIOPin sw2(SW_2, true, true, true);

    GPIOPin led1(LED_1, false, false, false);
    GPIOPin led2(LED_2, false, false, false);
    GPIOPin led3(LED_3, false, false, false);



    return 0;
}
