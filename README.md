# RFmachine
Arduino code to control F-Machine devices via a H34A 315Mhz dongle

## Hardware

Any Arduino compatible device should do. Tested on a [Adafruit Trinket M0](https://www.adafruit.com/product/3500).

For the transciever I use a cheap [H34A in 315Mhz version](https://de.aliexpress.com/item/4000511964218.html) but any ASK/OOK 315Mhz emitter should work.

Just connect some wire to `ANT`, `VCC` to some 5V, `GND` to the ground, and `DATA` to your arduino data pin (D0 is the default in my code).

## Software

Unfortunately, because Python is a bit heavy, it's hard to make it do proper sub-millisecond timings.
That's why the code is (horrible) C++.

