// #include <stdio.h>

#include "pico/stdlib.h"
// #include "hardware/pwm.h"

int main(void)
{
    gpio_init(22);
    gpio_set_dir(22, GPIO_OUT);

    while (true)
    {
        gpio_put(22, true);
        sleep_ms(1000);
        gpio_put(22, false);
        sleep_ms(1000);
    }

    return 0;
}
