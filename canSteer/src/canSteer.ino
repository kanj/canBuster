/*
 canBrake
 
 created 11JUL2016
 by Kirk Terrell
 
  This example is based off an example code from Arduino's site
 http://arduino.cc/en/Tutorial/Datalogger and it shows how to 
 log data from three analog sensors with a timestamp based on when
 the Arduino began running the current program to an SD card using
 the SD library https://github.com/greiman/SdFat by William 
 Greiman. This example code also includes an output to the 
 Serial Monitor for debugging.
 	
 
 This example code is in the public domain.
 */

 
#include <SPI.h>
#include <SD.h>

#include "Canbus.h"
#include "mcp2515.h"
#include "canbuster.h"



char UserInput;
int state=-1;
char buffer[456];  //Data will be temporarily stored to this buffer before being written to the file
tCAN message;
File dataFile;
unsigned long timeStamp,now;

// Chip Select pin is tied to pin 9 on the SparkFun CAN-Bus Shield
const int chipSelect = 9;  

void writeFile(tCAN message, int state) {

    File dataFile = SD.open("STEER/LOG.TXT", FILE_WRITE);  //Create directory
    
    //Serial.println(message.id,HEX);
    //write to uSD card
    dataFile.print(millis());
    dataFile.print(" ms");
    dataFile.print(", ");
    dataFile.print(state,DEC);
    dataFile.print(", ");
    dataFile.print(message.id,HEX);
    dataFile.print(", ");
    for (int i=0;i<8;i++) {
        dataFile.print(message.data[i],DEC);
        if ( i < 7) dataFile.print(", ");
			            
        }	
    dataFile.println();
    delay(10);
    dataFile.close();   //close file
    return;
}

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(chipSelect, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  
  Serial.println("card initialized.");
  SD.mkdir("STEER");
  File dataFile = SD.open("STEER/LOG.TXT", FILE_WRITE);  //Create directory
  dataFile.println("Time, state, AID, D0,D1,D2,D3,D4,D5,D6,D7");
  dataFile.close();
  if(Canbus.init(CANSPEED_500))  /* Initialise MCP2515 CAN controller at the specified speed */
  {
    Serial.println("CAN Init ok");
  } else
  {
    Serial.println("Can't init CAN");
  } 
   
  while (!mcp2515_check_message()){ 
    delay(100);
  }  
  Serial.println("CAN traffic detected");
  delay(5000); 
}

void loop()
{
  
  
      
    now=millis();
    state=-state;
    
    if ( state==1)
        Serial.println("Move Steering Wheel ");
    else
        Serial.println("Keep Steering Wheel steady ");
         
    delay(1000);  // This allows for reaction time
    
    while ( millis()-now <= 5000) {
               
        
    
        if (mcp2515_check_message()) {
					
	        if (mcp2515_get_message(&message)) {
			    
			    switch (message.id) {
			        case ecuBRAKE01:        //Ignore message from this ECU
			            break;
			        case ecuBRAKE02:        //Ignore message from this ECU
			            break;    
			        default:       
			            writeFile(message,state);
			            break;
                }			            
			        
                    
                    
                	}        
                }
            
        }			    
    
    
    
    
    
    
}
