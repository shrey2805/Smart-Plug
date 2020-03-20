# Sprint 2: Adding Intelligence

### Sprint Catalog

The goal of this sprint is to
- Add a current sensor 
- Start getting the readings of energy consumed
- Code neopixel to glow from Blue to Green to Red, nudging on the amount of energy consumed. 
The idea is that the smart plug should change the color of the light strip based on qualitative usage and give an estimate of power consumed to the user. These nudges about the energy consumed can be used to change the user behavior. 

### Sprint Review  

I have incorporated a current sensor in my circuit along to collect data about the usage. The details of the current sensor can be found in the Bill of Materials.
The current sensor was used to get the readings of AC current passing through the sensor. 
This current sensor is invasive, i.e it has be to the part of circuit, therefore, it was included in the series with the relay.

Readings were taken to get the baseline value of energy consumed to code the neopixel. Currently, the functionality of adapting the user behavior is not achieved. 

Please find the code attached. 

### End of Sprint Prototype


![alt text](https://github.com/daraghbyrne/advancediot2020/blob/master/students/shreyagr/assets/Final%20Fritzing_bb.jpg)

### Code

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
Following is the code used to add a new library for the current breakout sensor. 

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

The one the hardest challenges in the sprint was to calibrate the current senor. 
For this I had to go through the basics of AC and DC current. Working with AC current is dangerous and can lead to injuries. 
I went to Techspark to calibrate my sensor. There were instruments that could generate a current source with known waveform. 
This was then used to determint the voltage through the sensors. 
The voltage measured was matched with the ammeter readings to calibrate the gain and reference voltage. 

### Next

In the next sprint I look forward to achieve the following in order of priority. 
- Get the data streaming and pulling requests in place
- Get the neopixel working and adapting to the user behaviour
- Making an web based APP to set up the particle and implement in the product. 
