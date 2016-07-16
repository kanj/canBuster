# canBuster
INTRO:

	Sparkfun provides libraries for the CAN-BUS Arduino shield that allows querying for standard diagnostic 
	information using the OBD-II specification. In addition, each vehicle has its own unique CAN bus protcol
	(https://en.wikipedia.org/wiki/CAN_bus). This project is dedicated to identifying and decoding this traffic. 
	The Mazda 3 will be the example used, but the process should be readily adapted to other vehicles. 

	A number of Electronic Control Units (ECU) communicate on the bus. Each message will contain an 
	Arbitration ID and 8 bytes of data. An ECU may use more than one Arbitration ID, but will not share 
	Arbitration IDs with other ECUs.

	By presenting different stimuli, e.g. alternating pressing and releasing the brake, and recording 
	the CAN bus traffic, one can identify the Arbitration ID and data byte(s) associated with the brake ECU.  
	Once one identifies the Arbitration ID for braking, one can filter this out from the bus traffic when looking 
	for the Arbitration ID associated with steering. The data analysis can be done using Libre Office spreadsheet. 
	
USAGE:

	You will need the following hardware:
		Arduino Uno
		CAN_BUS-SHILED
		micro SD Card (FAT Format)
		OBD-II to 9 pin serial cable
	You will need teh following Softare
		Arduino IDE or INO to compile
		If using INO you will need PicoComm 
		Libre Office
		
	Download or clone the repository. 
	
