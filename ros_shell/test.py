#  Blink an LED with the LGPIO library
#  Uses lgpio library, compatible with kernel 5.11
#  Author: William 'jawn-smith' Wilson

import time
import lgpio

LED = 5

# open the gpio chip and set the LED pin as output
h = lgpio.gpiochip_open(0)
lgpio.gpio_claim_output(h, LED)

lgpio.gpio_claim_output(h, 22)
lgpio.gpio_write(h,22, 1)

try:
    while True:
        # Turn the GPIO pin on
        lgpio.gpio_write(h, LED, 1)
        time.sleep(1)

        # Turn the GPIO pin off
        lgpio.gpio_write(h, LED, 0)
        time.sleep(1)
except KeyboardInterrupt:
    lgpio.gpio_write(h, LED, 0)
    lgpio.gpiochip_close(h)
