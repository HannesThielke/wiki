---
title: OD600-Measurement
nav: true
---
{% include mathjax.html %}

# Optical Density Measurement
Description (drawn from <a href="http://www.biotronix.de/Data/EloCheck_Application_Note_1.pdf">Biotronix</a>):

Measuring the optical density of growing cultures is a common method to quantify various important culture parameters like cell concentration, biomass production or changes in the cell morphology. In general, measuring the optical density (OD) is a common method to quantify the concentration of substances (**Beer-Lambert-Law**), since the absorbance is proportional to the concentration of the absorbing species in the sample. Photometers quantify the optical density of liquid samples by comparing the intensity of light that has passed through and the intensity of the light before it enters the sample.

Automating processes like growing cells on a lab-on-a-chip device like the OpenDrop requires a continuous monitoring of the growth process. To do so, measuring the absorbance is a useful method to determine the current cell concentration which helps to regulate the cell growth in a pre-programmed way.

To understand the mathematical and physical background of OD-measurement, a short overview of the basic optical parameter is given in the following.

# General Optical Parameter
{% include figure.html file="optics.png" caption="Comparison of optical parameters" src="https://learn.sparkfun.com/tutorials/temt6000-ambient-light-sensor-hookup-guide?_ga=2.181503214.856477097.1528971890-1685415095.1525085967" height="7cm" %}

Optical quantities can be described in two different systems. Radiometry on the one hand describes electromagnetic radiation including visible light. Photometry on the other hand describes light, in terms of its perceived brightness to the human eye (around 400–700nm). A comparison of the equivalent quantities is given in the following table:

<!--  This table was created with http://tableizer.journalistopia.com -->
<figure>
{% include table_style.html %}
<table class="tableizer-table"  cellspacing="0">
<thead><tr class="tableizer-firstrow"><th>Radiometric Units</th><th>Symbol</th><th>Unit</th><th>Photometric Units</th><th>Symbol</th><th>Unit</th><th>Description</th></tr></thead><tbody>
 <tr><td>Radiant power</td><td>$$P$$</td><td>Watts [W]</td><td>Luminous flux</td><td>$$F$$</td><td>Lumens [lm]</td><td>total perceived power of light</td></tr>
 <tr><td>Radiant intensity</td><td>$$I$$</td><td>Watts per steradian [W/ster]</td><td>Luminous intensity</td><td>$$I_v$$</td><td>Candelas [cd = lm/ster]</td><td>perceived power emitted by a light source in a particular direction per unit solid angle</td></tr>
 <tr><td>Irradiance</td><td>$$E$$</td><td>Watts per square metre [W/m2]</td><td>Illuminance</td><td>$$E_v$$</td><td>Lux [lx = lm/m2]</td><td>total luminous flux incident on a surface, per unit area</td></tr>
</tbody></table>
</figure>
<figcaption>Overview of important optical quantities <a href="">(source)</a></figcaption>

<br>

When doing calculations with optical parameters, the following table is helpful to convert between different units.

<!--  This table was created with http://tableizer.journalistopia.com -->
<figure><center>
<table class="tableizer-table" cellspacing="0">
<thead><tr class="tableizer-firstrow"><th>From</th><th>To</th><th>Given</th><th>Equation</th></tr></thead><tbody>
<tr ><td> Candela (\( I_v \))  </td><td> Lumen (\( \Phi_v \)) </td><td> apex angle &alpha;             </td><td> \( \Phi_v = 2\pi I_v\left( {1 - \cos {\alpha  \over 2}} \right) \) </td></tr>
<tr><td> Lumen (\( \Phi_v \)) </td><td> Candela (\( I_v \))  </td><td> apex angle &alpha;             </td><td> \( I_v = {\Phi_v \over {2\pi \left( {1 - \cos {&frac12; \alpha}} \right)}} \) </td></tr>
<tr ><td> Lumen (\( \Phi_v \)) </td><td> Lux (\( E_v \))      </td><td> surface area A (m<sup>2</sup>) </td><td> \( E_v = {\Phi_v \over A} \) </td></tr>
<tr><td> Lux (\( E_v \))      </td><td> Lumen (\( \Phi_v \)) </td><td> surface area A (m<sup>2</sup>) </td><td> \( \Phi_v = E_v \cdot A \) </td></tr>
<tr ><td> Candela (\( I_v \))  </td><td> Lux (\( E_v \))       </td><td> measuring distance D (m)      </td><td> \( E_v = {I_v \over {D^2}} \) </td></tr>
<tr><td> Lux (\( E_v \))      </td><td> Candela (\( I_v \)) </td><td> measuring distance D (m)        </td><td> \( I_v = E_v \cdot D^2 \) </td></tr>
</tbody></table>
</center></figure>
<figcaption>Conversion table for optical quantities <a href="https://www.compuphase.com/electronics/candela_lumen.htm">(source)</a></figcaption>

A detailed comparison of the different optical quantities can be found here: <a href="https://www.compuphase.com/electronics/candela_lumen.htm">Compuphase.com</a>

## Derivation
According to the **Beer–Lambert law**, the **absorbance** $$A_\lambda$$ of a material for a specific wave length $$\lambda$$ is given by: 

$$A_\lambda=\log_{10}⁡\left(\frac{I_{v0}}{I_{v1}}\right)=\epsilon_\lambda\cdot c \cdot d$$

where $$I_{v0}$$ in $$Wm^{-2}$$ is the intensity of the incident light, $$I_{v1}$$ in $$Wm^{-2}$$ is the intensity of the transmitted light, $$\epsilon_\lambda$$ in e.g. $$m^2 mol^{-1}$$ is the molar absorption coefficient that is dependent on the specific substance, $$c$$ in $$mol \cdot l^{-1}$$ is the concentration of the substance and $$d$$ is the pathlength of the sample.

*Drawn from <a href="http://www.rsc.org/images/EiC-05_2007-spectrophotometer_tcm18-214788.pdf">RSC.org</a>:*

As well as absorption by the compound, other processes reduce the intensity of light that passes through the sample, so it is essential to take a ‘background’ reading for the solvent and the cell, which corresponds to $$I_{v1}$$.
It is assumed that the relationship between the incident light and the measurement values received from the light sensor is linear. In that case, the ratio $$I_{v0}/I_{v1}$$  can be expressed as:

$$\frac{I_{v0}}{I_{v1}} = \frac{I_{sample}}{I_{solvent}} = \frac{V_{sample}-V_{zero}}{V_{solvent}-V_{zero}}$$

where $$V_{sample}$$ and $$V_{solvent}$$ are the readings of the light sensor for the sample cell and the solvent. $$V_{zero}$$ is the measurement value that is received from the sensor when no light is falling on the photodiode. In our case, this offset is $$V_{zero}=0$$. Hence, the absorbance can be calculated by

$$A_\lambda=\log_{10⁡}\left(\frac{V_{sample}}{V_{solvent}}\right)=\epsilon_\lambda \cdot c \cdot d$$

and the concentration we are looking for can be expressed as:

$$c=\frac{1}{\epsilon_\lambda d} \log_{10⁡}\left(\frac{V_{sample}}{V_{solvent}} \right)$$

## Setup
{% include figure.html file="sparkfun_lux_sensor_tempt6000.jpg" caption="TEMT6000 Ambient Light Sensor Breakout Board" src="https://www.sparkfun.com/products/8688" height="4cm" %}

Our OD-measurement-system is based on the TEMT6000 Ambient Light Sensor Breakout Board which is able to measure the illuminance (in lux) of an incident light in the range of 390nm to 700nm. The light emitting source is an orange LED (HLMP-C423) which emmits light with a wavelength of 600nm.
To read the analog values of the light sensor, we are using the Pin A0 on the Arduino which is connected to the Pad P2 on the backside of the OpenDrop System. This pin was originally intended to be used for the polarity pin of the HV507 flash registers that drive the electrodes.
As we don't use the polarity pin, it can be configured as an analog input for the ambient light sensor. The pads P3 (5V) and P12 (GND) can be used as the power source for the LED and the sensor.

{% include figure.html file="OD_measurement_wiring-2.jpg" caption="Wiring the light sensor on the OpenDrop System" height="12cm" %}

A current limiting resistor of 150 Ohm is used to limit the current through the LED. The HLMP-C423 LED has got a voltage drop of 1.9V which results in a forward current of around 20mA. According to Ohm’s law the resistor should be around

$$R = \frac{5V - 1.9V}{20mA} = 155\Omega$$

{% include figure.html file="light_sensor_schematic.png" caption="Light sensor schematic" height="12cm" %}

The common way of doing OD-measurement is to compare the values of a blank material with the results of the substance to be measured.

### Internal Setup
For first tests a 3D-printed setup is used to configure the basic measurement. The liquid is put into a standard 1x1cm cuvette normally used for a professional spectrophotometer.

{% include figure.html file="OD_measurement_extern_1.jpg" caption="External OD-measurement system on the OpenDrop" height="8cm" %}

{% include figure.html file="OD_measurement_extern_3D.png" file2="OD_measurement_extern_2.jpg" caption="3D model of the external OD measurement system" caption2="Assembly of the external OD measurement system on the OpenDrop" height="5cm" %}

To compare the results of the OD measurement on the OpenDrop with a professional spectrophotometer we measured the OD of diluted cell cultures (E.coli) with the [Implen Nanophotometer](https://www.implen.de) and the [WPA Biowave II](http://www.biochrom.co.uk/product/24/biochrom-wpa-biowave-ii-uv-visible-spectrophotometer-with-life-science-methods.html) and compared the results with the measurement on the OpenDrop.

{% include figure.html file="OD_measurement_extern_3D_front.png" height="7cm" caption="Large (left) and small (right) hole in the OD-measurement setup" %}

Interesting results have been occurred after measuring the OD with a small hole and a larger hole in the 3D-printed part whith changes the amount of light passing through the cuvette. A smaller hole caused higher values for the optical density and therefore a higher accuracy.

{% include figure.html file="od_chart_2.png" height="8cm" caption="First OD-measurement" %}
{% include figure.html file="od_chart_3.png" height="8cm" caption="Second OD-measurement" %}


### External Setup
After the first experiments with this external setup we decided to do the OD600 measurement directly on the OpenDrop System. Therefore, the LED is placed on top of the Droplet so that the light beam can pass the hole in the middle of an electrode and can be detected by the Light Sensor on the bottom of the OpenDrop System.

{% include figure.html file="OD_measurement.png" caption="Sketch of the internal OD-measurement principle" height="5cm" %}

To hold the LED and the sensor in place, two 3D-printable parts have been created that can be attached to the OpenDropSystem.

{% include figure.html file="OD_measurement_BOTTOM_3D.png" file2="OD_measurement_TOP_3D.png" caption="3D model of the printable bottom part" caption2="3D model of the printable top part" height="5cm" %}

{% include figure.html file="OD_measurement_BOTTOM_attached.jpg" file2="OD_measurement_TOP_attached.jpg" caption="attached bottom part" caption2="attached top part" height="5cm" %}

After starting the system it was noticed that the light that is received from the sensor is very low so that the analogue reading displays 0. This is caused by the relatively small diameter of the hole. One solution for that problem may be a brighter LED. At a forward current of 20mA this LED dissipates a power of around 38mW. High wattage LEDs cannot be driven form the Arduino pin as this can only provide current up to a maximum of 30mA. Higher currents would destroy the Arduino.