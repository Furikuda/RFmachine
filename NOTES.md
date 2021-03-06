# Reverse the F-Machine remotes protocol.

The F-Machine devices tested (Gigolo & Tremblr) both come with a remote with 3 or 5 buttons.

![Remote type A for Gigolo](docs/pics/Gigolo_remote_A_SC2262.jpg)

They control a [SC2262](https://datasheet.lcsc.com/szlcsc/PT2262_C16390.pdf) encoder that sends tri-states bits (1/0/F) as fixed code commands. These are used to then control a 315Mhz RF transmitter to send these as ASK/OOK encoded.

These commands have 12 bits length. Each bit is a waveform consisting of 2 pulse cycles:

 * Bit '0': `2*(short high, long low)`
 * Bit '1': `2*(long high, short low)`
 * But 'F' (floating): `short high, long low, long high, short low`

A 'long' pulse is 3 times longer than a short one.

A command needs to also have a synchronisation bit emitted: `short high, (42*short) low`.

It is also worth noting that according to the reciever (2272) documentation, 2 identical commands need to be emitted for the transmission to be valid, but experimentation show that at the very least, a command needs to be emitted 5 times to make the device react.

As noted on [their website](https://f-machine.com/index.php/remote-control-detail), F-Machine uses 5 different types (A to E), probably with different commands, and maybe different frequencies.

## Listening to the transmissions

While it is possible de deduce the commands being sent by the 2262 by looking at how the address & data pins are connected, it's funnier to just use all your shiny tools.

Using a cheap USB [RTLSDR](https://www.adafruit.com/product/1497), there are two ways to listen to the communications

### Easy way with rtl_433

using [rtl_433](https://github.com/merbanan/rtl_433) to decode the transmissions is as easy as running: `rtl_433 -f  315M -d0` and pressing the buttons on the remote.

Example code for the Gigolo A remote, and the ON/OFF button:

```
time      : 2021-04-14 14:42:48
model     : Generic-Remote                         House Code: 21887
Command   : 48           Tri-State : ZZZZZ1110100
```

### Hard way with gqrx

one can use [gqrx](https://gqrx.dk/) to listen to the transmitted frames.

![gqrx](docs/pics/gqrx.png)

Setting it in AM mode, transmissions can me recorded as a .wav file  after clicking the `Rec` button.

Opening them in Audacity, we end up with the following traces for each button presses:

 * Gigolo (Remote A)
   * Up button (command `FFFFF1111000`) ![Up button](docs/gqrx_am_traces/fmachine_gigolo_a/UP.jpg)
   * ON/OFF button (command `FFFFF1110010`) ![ON/OFF button](docs/gqrx_am_traces/fmachine_gigolo_a/ON_OFF.jpg)
   * Down button (command `FFFFF1110100`) ![Down button](docs/gqrx_am_traces/fmachine_gigolo_a/DOWN.jpg)

 * Tremblr (Remote A)
   * Up button (command `11FFFF001000`) ![Up button](docs/gqrx_am_traces/fmachine_tremblr_a/UP.jpg)
   * ON/OFF button (command `11FFFF000010`) ![ON/OFF button](docs/gqrx_am_traces/fmachine_tremblr_a/ON_OFF.jpg)
   * Down button (command `11FFFF000100`) ![Down button](docs/gqrx_am_traces/fmachine_tremblr_a/DOWN.jpg)
   * Suck Up button (command `11FFFF000001`) ![Suck Up button](docs/gqrx_am_traces/fmachine_tremblr_a/SUCK_UP.jpg)
   * Suck Down button (command `11FFFF010000`) ![Suck Down button](docs/gqrx_am_traces/fmachine_tremblr_a/SUCK_DOWN.jpg)


The .wav files for each remote can be found here (button are pressed top left to bottom-right):

 * [gigolo](docs/gqrx_am_traces/fmachine_gigolo_a/top-down-buttons.wav)
 * [tremblr](docs/gqrx_am_traces/fmachine_tremblr_a/top-down-buttons.wav)

## Protocol

For whatever reason, after the list of tr-state bits are sent, a short "high" transmission is also transmitted.

Each command noted above, is repeatedly transmitted while the button is pressed, and a command needs to be repeated at least 6 times to be acknowledged by the machine.

A pause in transmission is required before sending another command.

