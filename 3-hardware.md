---
title: Hardware
nav: true
---

The following picture illustrates the general functions of the OpenDrop v2.1 System:
{% include figure.html file="opendrop_v2.1_label_front.png" alt="OpenDrop Peripherals (front)" height="11cm" %}

On the top there are the following peripherals:
- **12V DC Power Supply Socket**: To deliver the high input voltage for the HV507PG driver chips a power supply is used that transforms the low input voltage to a higher level. According to the performance tests on the [Power Supply Unit](http://desmith.net/NMdS/Electronics/NixiePSU.html#highcurrent) the input current stays under 1A. Hence, a 1A power supply should be enough to power the OpenDrop Device. We used a 12V/2A Power Supply with a 2.5mm DC plug.
- **Piezo Speaker**: The piezo speaker is used to give an audio feedback. Sounds can be turned off in the OpenDrop Library.
- **OLED Display**: The display is an Adafruit 128x64 OLED based on the SSD1306 single-chip CMOS display driver. It communicates with the Arduino Micro via a SPI bus.
- **Micro USB Port**: Used to program the Arduino
- **V_GND**:
- **Fluxl-Matrix**: 16×8 electrodes array, 2.75mm2 in size
- **Button 1**: Free to use for any additional features
- **Button 2**: Start-Button
- **Joystick**: Used for moving around the droplets
- **High Voltage Potentiometer**: The high voltage level that is used to drive the electrode array can be controlled with the potentiometer. Turn clockwise to increase the output voltage
- **High voltage switch**: This switch is a safety feature that provides the possibility to turn the high voltage off if needed

{% include figure.html file="opendrop_v2.1_label_back.png" alt="OpenDrop Peripherals (back)" height="10cm" %}

On the back of the OpenDrop System you can find the following peripherals:
- **Arduino Micro (Socket)**: The heart of the system which controls the functionality of the OpenDrop System.
- **High Voltage Boost Converter**: The [power supply unit](http://desmith.net/NMdS/Electronics/NixiePSU.html) was originally created for Nixie Tubes and is adopted to the OpenDrop System. It boosts the incoming 12V DC voltage to the high voltage (65-250VDC depending on the potentiometer)
- **HV507PG**: The HV507PG is a 64-Channel Serial-to-Parallel Converter with High-Voltage Push-Pull Outputs. It is used to deliver the high voltage for the electrodes. To drive all 128 electrodes two HV507 chips are used in series. More information: see below.
- **Wifi Socket**: The wifi socket can be used to add wifi capability based on the ESP8266 Chip
- **Feedback Amplifier**: The feedback amplifier circuit amplifies the voltage signal from the feedback pin and creates a higher voltage level that can be read by the Arduino
- **Arduino Pin A1**: This pin was originally intended to be used for the polarity pin of the HV507 flash registers that drive the electrodes. It can be configured as an analog input for OD measurement setup.

## HV507PG Serial to Parallel Converter
{% include figure.html file="hv507pg_cascade.png" alt="HV507" height="5cm" %}
According to it’s [datasheet](files/hv507_datasheet.pdf), the HV507PG is “a low-voltage to high-voltage serial-to-parallel converter with 64 push-pull outputs”. It is used to drive the electrodes in the middle of the OpenDrop. To drive all 128 electrodes, two serial-to-parallel converters are used in series (as a cascade). The DIOA pin of the first chip is configured as the main serial input. The DIOB pin is configured as the output and is connected to the DIOA input of the second chip. In this way it is possible to drive 128 high voltage outputs instead of 64.

<!--  This table was created with http://tableizer.journalistopia.com -->
<figure>
{% include table_style.html %}
<table class="tableizer-table"  cellspacing="0">
<thead><tr class="tableizer-firstrow"><th>Pin Nr.</th><th>Pin Name</th><th>Description</th></tr></thead><tbody>
 <tr><td>25 + 40 </td><td>VPP </td><td>High-voltage power supply </td></tr>
 <tr><td>26</td><td>DIOA </td><td>Serial Data Input/Output A à here configured as data input</td></tr>
 <tr><td>29</td><td>BL </td><td>Blanking pin</td></tr>
 <tr><td>30</td><td>POL </td><td>Polarity </td></tr>
 <tr><td>31</td><td>VDD </td><td>Low-voltage power supply </td></tr>
 <tr><td>32</td><td>DIR </td><td>Direction pin: DIR is physically connected to GND à DIOA is data in and DIOB is data out. Data is shifted from HVOUT64 to</td></tr>
 <tr><td>33</td><td>GND </td><td>Logic voltage ground </td></tr>
 <tr><td>34</td><td>HVGND </td><td>High-voltage power supply </td></tr>
 <tr><td>37</td><td>CLK </td><td>Data Shift Register Clock. Inputs are shifted into the Shift register on the positive edge of the clock. </td></tr>
 <tr><td>38</td><td>LE </td><td>Latch Enable </td></tr>
 <tr><td>39</td><td>DIOB </td><td>Serial Data Input/Output B</td></tr>
</tbody></table>
</figure>
<figcaption>Overview of a selection of pins on the HV507 chip</figcaption>

The electrodes can be turned on or off by sending a 128bit code to the DIOA pin of the first HV507PG chip. This data is first send to the static shift register and afterwards stored in the latches. To send the data to the actual electrode matrix - thus activating the high voltage electrodes – the blanking pin must be activated.

{% include figure.html file="hlm507_functional_block_diagram.png" alt="HV507" caption="HV507 Functional Block Diagram" src="files/hv507_datasheet.pdf" height="10cm" %}
