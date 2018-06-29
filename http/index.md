---
title: Home
---

# OpenDrop - Microfluidics Lab-on-a-chip
{% include figure.html file="opendrop_logo.png" caption="OpenDrop Logo" src="http://www.gaudi.ch/OpenDrop/" height="3cm" %}

Since the beginning of microfluidics the technique of controlling small volumes of liquid for all kinds of applications has become more and more popular. It enables new possibilities for biological applications like lab-on-a-chip experiments. The so-called "electrowetting" technique helps automating these processes by making it possible to control the behaviour of fluids via electronical regulation. The change of an electrical field can achieve droplet-movements without direct human interaction and so can avoid external influences or human errors.

The **OpenDrop** (*description drawn from [OpenDrop Official Website](http://www.gaudi.ch/OpenDrop/)*) is an open source digital microfludics platform for research purposes made by the Swiss company GaudiLabs. The device uses recent electro-wetting technology to control small droplets of liquids. Potential applications are lab on a chip devices for automating processes of digital biology.
The design approach chosen relies strongly on Do-It-Your-Self (DIY) and Low-Cost. The aim is to only use standard and widely-available components, materials, and production processes. Also, all design files and software required to operate your hardware are shared under open licenses (Github: [OpenDrop Repository](https://github.com/GaudiLabs/OpenDrop)).

# Versions
Since it's first publication the **OpenDrop** System has been improved a lot and is still being developed to extend the possibilities of the device. The differences between the currently available versions of the OpenDrop System are shown in the following table.

<!--  This table was created with http://tableizer.journalistopia.com -->
<figure>
{% include table_style.html %}
<table class="tableizer-table">
<thead><tr class="tableizer-firstrow"><th>Function</th><th>Version 1</th><th>Version 2</th><th>Version 2.1</th><th>Version 3</th></tr></thead>
<tbody>
 <tr><td>Development Board</td><td>Arduino Uno</td><td>Arduino Micro</td><td>Arduino Micro</td><td>none</td></tr>
 <tr><td>USB</td><td>USB-B</td><td>USB-micro-B</td><td>USB-micro-B</td><td>USB-micro-C</td></tr>
 <tr><td>Microcontroller</td><td>ATmega328P</td><td>ATmega32U4</td><td>ATmega32U4</td><td>AVR SAMD21G18</td></tr>
 <tr><td>Flash Memory</td><td>32 KB</td><td>32 KB</td><td>32 KB</td><td>256KB</td></tr>
 <tr><td>I/O Pins</td><td>20</td><td>32</td><td>32</td><td>38?</td></tr>
 <tr><td>Logic Level Voltage</td><td>5V</td><td>5V</td><td>5V</td><td>5V</td></tr>
 <tr><td>Operating Low Voltage</td><td>12V</td><td>12V</td><td>12V</td><td>12V</td></tr>
 <tr><td>Electrode High Voltage</td><td>150-220 VDC</td><td>65-250 VDC</td><td>65-250 VDC</td><td>65-250 VDC</td></tr>
 <tr><td>Electrodes</td><td>8x8</td><td>16x8</td><td>16x8</td><td>14x8</td></tr>
 <tr><td>Electrode Size</td><td>&nbsp;</td><td>2.75x2.75</td><td>2.75x2.75</td><td>&nbsp;</td></tr>
 <tr><td>Reservoirs</td><td>4</td><td>0</td><td>0</td><td>4</td></tr>
 <tr><td>Matrix Driver</td><td>BSS131, Infineon SIPMOS, Logic-Level, PG-SOT-23</td><td>High Voltage Driver Chip HV507</td><td>High Voltage Driver Chip HV507</td><td>High Voltage Driver Chip HV507</td></tr>
 <tr><td>Buttons</td><td>4</td><td>4</td><td>2</td><td>2</td></tr>
 <tr><td>PCB Carrier inner size</td><td>&nbsp;</td><td>3.4cm x 6.5cm</td><td>3.4cm x 6.5cm</td><td>&nbsp;</td></tr>
 <tr><td>PCB Carrier outer size</td><td>&nbsp;</td><td>10cm x 6.3cm</td><td>10cm x 6.3cm</td><td>&nbsp;</td></tr>
 <tr><td>Joystick</td><td>no</td><td>no</td><td>yes</td><td>yes</td></tr>
 <tr><td>OLED</td><td>no</td><td>yes</td><td>yes</td><td>yes</td></tr>
 <tr><td>WIFI</td><td>no</td><td>yes</td><td>yes</td><td>yes</td></tr>
 <tr><td>Feedback Amplifier</td><td>no</td><td>no</td><td>yes</td><td>yes</td></tr>
 <tr><td>Opto Isolator</td><td>no</td><td>no</td><td>no</td><td>yes</td></tr>
 <tr><td>High AC Voltage Driving Capability</td><td>no</td><td>no</td><td>no</td><td>yes</td></tr>
 <tr><td>Speaker</td><td>yes</td><td>yes</td><td>yes</td><td>yes</td></tr>
 <tr><td>Prepared for Heating / Peltier Element</td><td>&nbsp;</td><td>yes</td><td>yes</td><td></td></tr>
</tbody></table>
</figure>
<figcaption>Table</figcaption>

{% include figure.html file="opendrop_v1.0.png" caption="version 1.0" src="files/opendrop_paper.pdf" file2="opendrop_v2.0.jpg" src2="http://www.gaudi.ch/OpenDrop/?p=17" caption2="version 2.0" height="8cm" %}
&nbsp;
{% include figure.html file="opendrop_v2.1.jpg" caption="version 2.1" file2="opendrop_v3.0.jpg" caption2="version 3.0" src2="http://www.gaudi.ch/OpenDrop/?p=389" height="8cm" %}
&nbsp;

> built using [Jekyll](https://jekyllrb.com/) and [GitHub Pages](https://pages.github.com/) based on the [template from  Evan Will](https://evanwill.github.io/go-go-ghpages/)
