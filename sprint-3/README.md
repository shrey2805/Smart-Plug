# Sprint 3: Connectivity

### Sprint Catalog

The objectives of the sprint are:
- Give the hardware the final form and shape to avoid any mishaps working with AC current.
- Add the neopixel and build the functionality of nudging the user when they are using more energy than they usually do. 
- Solder all the compenents on a Protoboard. 
- Start uploading the data to microsoft azure and make a dashboard. 

### Sprint Review  

I was successfully able to make the form of the circuit. All the pieces have been soldered and test runs have been successful.
I am able to stream the data using serial monitor.
This data has been used to code the neopixel to shine red on an threshold value of energy consumption.

One of the problems that I am currently facing is the particle is not turning on when connected with a 5V DC supply. 
I am unable to get the prediction modelling/windowed average working for the prototype.
I was able to set up the microsoft azure account and started relaying data on it.


### End of Sprint Prototype

![alt text](https://github.com/daraghbyrne/advancediot2020/blob/master/students/shreyagr/assets/Protoboard%20Circuit.jpg)

### Code
This is the main code, the included library can be found following this code. 
```
// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>

// This #include statement was automatically added by the Particle IDE.
#include "reading.h"
#define PIXEL_PIN D3
#define PIXEL_COUNT 30
#define PIXEL_TYPE WS2812

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);


int relay = D12;                    // Tells particle the relay is connected to pin 12
int state = 0;                      // This is used to map the current state of the switch
int buttonpin = D2;                 // Used a physical button to actuate the relay in addition to voice command. 
unsigned long lastbp;               // This is a variable that ensures that there is a min delay between the two times the button is pressed. 
// pin A3 is taken for the current sensor

// Variables for neopixel
//this is the value that I will be getting from the predictive modelling or windowed average. 
int dailyavg = 6000;                // This is a pre set baseline value, after which the newpixel is coded to glow red.          
int color;                          // a variable defined to temporarily store the value of color 
int energy=0;                       // This variable 
unsigned long start;                //marks when the switch was first turned on ; it measures millis()

int a = 6000;                       //energy consumed in nth cycle
int b = 6000;                       //energy consumed in n-1th cycle
int c = 6000;                       //energy consumed in n-2th cycle

void setup()
{
    pinMode(relay, OUTPUT);         // Initialize the Atmel GPIO pin as an output
    pinMode(buttonpin, INPUT_PULLUP);
    Particle.function("toggleswitch", toggleswitch);
    strip.begin();                  
    //strip.setBrightness(30);
    // initialize serial communications at 9600 bps:
    Serial.begin(9600);
}

void loop()                         // Loops forever
{
    //           //This is a temporary hack to take a windowed average
    
    // this part of the code makes the physical button work
    int buttonstate = HIGH;
    
    // The button is glitchy, therefore, I have set a min time before 2 consecutive readings ////////////////////
    if (millis() - lastbp > 1000){
        buttonstate = digitalRead(buttonpin);
        lastbp = millis();
    }
 
    // to change the relay mode when the button is pressed///////////////////////////////////////////////////////
    
    if (buttonstate == LOW){
        if (state == 1){
            digitalWrite(relay, LOW);
            state = 0;
        } else if (state == 0) {
            digitalWrite(relay, HIGH);
            state = 1;
        }
    }    
    
    
    //******************* To check if the state is working properly *************///////////////////////////////
    //Serial.print(state);
    //**********************************************************************************************************
    
    
    //********************************* ENERGY CALCULATION *****************************************************
    
   
    if (state ==1){                                     //calculate the energy only is the switch is turned on
        energy = reading()*reading() + energy;          // this calculates the total energy consumed. This will always be a positive number. 
        if (energy< 1){
            energy = 0;                                 // to give a margin of error
        }
        // Serial.print(energy);           
        // Serial.print("\n");
    }
    else {                                              // Implementing the windowed average
        if ( energy > 10){
            c=b;                                            // this stores the previous value of b
            b=a;                                            // this stores the previous value of a 
            a=energy;                                       // a will store the latest value of energy before energy is declared 0
            dailyavg = (a+b+c)/3;
            energy = 0;                                     // value of energy is reset to 0 to make it ready for next iteration.
            // String data1 = String(a);
            // String data2 = String(b);
            // String data3 = String(c);
            // String data4 = String(dailyavg);
            // Trigger the integration
            // Particle.publish("a", data1, PRIVATE);
            // delay(100);
            // Particle.publish("b", data2, PRIVATE);
            // delay(100);
            // Particle.publish("c", data3, PRIVATE);
            // delay(100);
            // Particle.publish("dailyavg", data4, PRIVATE);
            // Wait 60 seconds
            }
    }
    
    
    if (energy >= dailyavg){
        dailyavg = energy;
    }
    color = map(energy , 0, dailyavg , 0 , 255);
    
    
    
    uint32_t c; // this is the variable for declaring the neopixel color
    if (state == 1){
        if( color > 125 ){
            //TempRG = map(watert, 36,70,0,255);
            c = strip.Color(color, 255-color, 0); 
        }
        else {
            //TempGB = map(watert, 10,35,0,255);
            c = strip.Color(0, color, 255-color);   
        }
    }
    else if (state == 0){
        c = strip.Color( 50,50,50);
    }
    
    
    // *********************setting the color of the neopixel*******************************
    for( int i = 0; i < strip.numPixels(); i++ ){
        strip.setPixelColor(i, c); // set a color 
        } 
    strip.show();
    
    // Get some data
    String data = String(energy);
    // Trigger the integration
    Particle.publish("energy", data, PRIVATE);
    // Wait 60 seconds
    delay(100);
    
}

int toggleswitch(String args){
    if (state == 1){
        digitalWrite(relay, LOW);
        state = 0;
    } else if (state == 0) {
        digitalWrite(relay, HIGH);
        state = 1;
    }
    //something should go here
    return 1;
   
}


```
Following is hte library that contains the code for the current sensor breakout. 
```
#include "application.h"
#include "Particle.h"

const int analogInPin = A3;

// Number of samples to average the reading over
// Change this to make the reading smoother... but beware of buffer overflows!
const int avgSamples = 50;

 int sensorValue = 0;

 float sensitivity = 400.0/10000.0; //100mA per 500mV = 0.2
 float Vref = 10100; // Output voltage with no current: ~ 2500mV or 2.5V


 int reading() {
  // read the analog in value:
  for (int i = 0; i < avgSamples; i++)
  {
     sensorValue += analogRead(analogInPin);

     // wait 2 milliseconds before the next loop
     // for the analog-to-digital converter to settle
     // after the last reading:
     delay(2);

  }

  sensorValue = sensorValue / avgSamples;

  // The on-board ADC is 10-bits -> 2^10 = 1024 -> 5V / 1024 ~= 4.88mV
  // The voltage is in millivolts
  float voltage = (4.88 * sensorValue);

  // This will calculate the actual current (in mA)
  // Using the Vref and sensitivity settings you configure
  float current = (voltage - Vref) * sensitivity;

  // This is the raw sensor value, not very useful without some calculations
  //Serial.print(sensorValue);
  //Serial.print("\n");
  /*************************************************************************************
  * Step 1.)
  * Uncomment and run the following code to set up the baseline voltage 
  * (the voltage with 0 current flowing through the device).
  * Make sure no current is flowing through the IP+ and IP- terminals during this part!
  * 
  * The output units are in millivolts. Use the Arduino IDE's Tools->Serial Plotter
  * To see a plot of the output. Adjust the Vref potentiometer to set the reference
  * voltage. This allows the sensor to output positive and negative currents!
  *************************************************************************************/
  //Serial.print(voltage);
  //Serial.print("mV");

  /*************************************************************************************
  * Step 2.)
  * Keep running the same code as above to set up the sensitivity
  * (how many millivolts are output per Amp of current.
  * 
  * This time, use a known load current (measure this with a multimeter)
  * to give a constant output voltage. Adjust the sensitivity by turning the
  * gain potentiometer.
  * 
  * The sensitivity will be (known current)/(Vreading - Vref).
  *************************************************************************************/
  /*************************************************************************************
  * Step 3.)
  * Comment out the code used for the last two parts and uncomment the following code.
  * When you have performed the calibration steps above, make sure to change the 
  * global variables "sensitivity" and "Vref" to what you have set up.
  * 
  * This next line of code will print out the calculated current from these parameters.
  * The output is in mA
  *************************************************************************************/
  //Serial.print(current);
  //Serial.print("mA");
  // -- DO NOT UNCOMMENT BELOW THIS LINE --
  //Serial.print("\n");

  // Reset the sensor value for the next reading
  sensorValue = 0;
  return current;
 }

```
### Sprint Retrospective 

Everything was working well when suddenly the particle is not turning.
Challenges faced were:
- Placing the sub parts of the circuit in he right way. The AC module of the circuit should be spearated from the DC module to reduce the possibility of short circuit.
- Placing the current sensor well separated from the DC power adapter. The current sensor works on sensing the magnetic feild of the AC current passing through IP+ and IP-. The DC Power source generates strong electro-magnetic feild to generate the DC current from AC. If they are placed in the proximity, it can cause the sensor to give inaccurate readings. 

### Next

Next step is to
- Make the dashboard on the microsoft azure to get the current sensor reading. 
- Get the prediction modelling working. 
- Make a 3-D printed/ foam core hardware usint to install the circuit in it. 
- Diagnose why the particle is not turining on.

