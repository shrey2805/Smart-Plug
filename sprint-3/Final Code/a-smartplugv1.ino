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

