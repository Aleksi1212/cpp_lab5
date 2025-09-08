#include "pico/stdlib.h"

#define SW_0 9
#define SW_1 8
#define SW_2 7

#define LED_1 22
#define LED_2 21
#define LED_3 20

class GPIOPin
{
    private:
        int pin_num = 0;

    public:
        GPIOPin(
            int pin,
            bool input = true,
            bool pullup = true,
            bool invert = false
        );
        GPIOPin(const GPIOPin &) = delete;

        bool read();
        bool operator() ();
        void write(bool value);
        void operator() (bool);
        operator int();
};

class GPIOPinHandler
{
    private:
        GPIOPin sw;
        GPIOPin led;

        absolute_time_t time_since_sw_press;
    public:
        GPIOPinHandler(int sw_pin, int led_pin);

        void toggle_led_on_sw_press();
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

    pin_num = pin;
}

/*
    GPIOPin methods
*/
bool GPIOPin::read() { return gpio_get(pin_num); }
bool GPIOPin::operator()() { return read(); }

void GPIOPin::write(bool value) { gpio_put(pin_num, value); }
void GPIOPin::operator()(bool value) { write(value); }

GPIOPin::operator int() { return pin_num; }

/*
    GPIOPinHandler methods
*/
GPIOPinHandler::GPIOPinHandler(int sw_pin, int led_pin) :
    sw(sw_pin, true, true, true),
    led(led_pin, false, false, false) {}
void GPIOPinHandler::toggle_led_on_sw_press()
{
    if (sw()) {
        led(true);
        time_since_sw_press = get_absolute_time();
        return;
    }

    int64_t time_diff_ms = absolute_time_diff_us(
        time_since_sw_press,
        get_absolute_time()
    ) / 1000;
    if (time_diff_ms >= 1000) {
        led(false);
    }
}

int main(void)
{
    GPIOPinHandler sw0_led3(SW_0, LED_3);
    GPIOPinHandler sw1_led2(SW_1, LED_2);
    GPIOPinHandler sw2_led1(SW_2, LED_1);

    while (true) {
        sw0_led3.toggle_led_on_sw_press();
        sw1_led2.toggle_led_on_sw_press();
        sw2_led1.toggle_led_on_sw_press();
        sleep_ms(10);
    }

    return 0;
}
