# minerva

## Minerva is a software that assists piloting the Rx graphite calorimeter at ENEA-INMRI

The [Italian National Institute for Metrology of Ionizing Radiation](http://www.inmri.enea.it) runs a series of *primary standards* for the measurement of *quantities* related to the many uses of ionizing radiation. Among these, *absorbed dose to water* is the main quantity of interest in *dosimetry for radiation therapy of cancer*.

Minerva is a Microsoft Visual Studio-based software that was initiated around 2012 by Stefano Loreti at ENEA-INMRI to digitalize the calorimetry expertiese that existed at the time in the institute. The sofware was written to pilot the recently constructed graphite calorimeter for HDR Brachytherapy dosimetry (Guerra et al, 2012). It was then expanded for the x-ray dosimetry calorimeter (Pinto et al, 2016), which is the basis for this repository, and it's being concurrently adopted for the oldest and most established calorimeter at ENEA-INMRI, the four-bodied calorimeter for dosimetry on 60-Co beams. 

Since these calorimeters have several conceptual as well as operational features in common, the sofware basis will eventually become the same, with hopefully the creation of a _calorimeter class_, and a more polished code overall. Given how specialised these codes are at this moment, they may be difficult to use unless you are really at ENEA-INMRI. If you are interested, [please write to us](mailto:massimo.pinto@enea.it).

The hardware that this software is piloting consists, other than the actual calorimeter, of:

1. _Pairs_ of _Precision Current Sources_, Keithley mod. 6220, and _nanoVoltmeters_, Keithley mod. 2182A. These are connected to [Wheatstone bridges](https://en.wikipedia.org/wiki/Wheatstone_bridge) consisting of three high precision resistors and an NTC [thermistor](https://en.wikipedia.org/wiki/Thermistor). The pair of 6220 and 2182A can be run either in _Delta Mode_  or in conventional, continuous mode.
2. _Sources Meters_, Keithley 2400. These are used to inject heating currents in the thermistors that are embedded in each of the bodies that constitute the specific calorimeter. 
3. A dual card, 16 channel-_switch system_, Keithley 7001. This is used to switch the sensing thermistors that are linked to a single Whetastone bridge, when a bridge is not fully dedicated to a specific thermistor.

The actual number of instruments connected together via a GPIB network depends on the number of graphite bodies in the calorimeter and the number Wheatstone bridges available. 

The Current developers of these sets of codes are [Massimo Pinto](http://massimopinto.github.io), Gianluca Cappadozzi, and Marco D'Arienzo, all of ENEA-INMRI. 

## References 
1.	Guerra AS, Loreti S, Pimpinella M, Quini M, D'Arienzo M, Astefanoaei I, et al. A standard graphite calorimeter for dosimetry in brachytherapy with high dose rate 192Ir sources. Metrologia. IOP Publishing; 2012 Aug 10;49(5):S179–83. [doi:10.1088/0026-1394/49/5/S179](dx.doi.org/10.1088/0026-1394/49/5/S17)
2.	Pinto M, Pimpinella M, Quini M, D'Arienzo M, Astefanoaei I, Loreti S, et al. A graphite calorimeter for absolute measurements of absorbed dose to water: application in medium-energy x-ray filtered beams. Phys Med Biol. IOP Publishing; 2016 Feb 21;61(4):1738–64. [doi:10.1088/0031-9155/61/4/1738](http://dx.doi.org/10.1088/0031-9155/61/4/1738)  
