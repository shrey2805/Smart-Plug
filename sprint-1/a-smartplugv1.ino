
int relay = D12;              // Tells particle the relay is connected to pin 12
int state = 0;
int buttonpin = D3;

void setup()
{
    pinMode(relay, OUTPUT);      // Initialize the Atmel GPIO pin as an output
    pinMode(buttonpin, INPUT_PULLUP);
    Particle.function("toggleswitch", toggleswitch);
}

void loop()                  // Loops forever
{
   
    int buttonstate = digitalRead(buttonpin);
    
    if (buttonstate == LOW){
         if (state == 1){
            digitalWrite(relay, LOW);
            state = 0;
        } else if (state == 0) {
            digitalWrite(relay, HIGH);
            state = 1;
        }
    }
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