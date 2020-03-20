# Functional Specification

I want to do a model project that would expose me to the various aspects of making an IoT commercial device. Therefore, I chose to make a smart plug. Through this project I want to explore the possibility of: 
- Making a custom hardware circuit board. 
- Make a mobile saas application that would be used to set up the device.
- Make an IoT device to fit in the existing IoT infrastructure. 
 
Following features needs to be included in the smart device: 
- It should have a software interface that is required to set it up. 
- The users should be able to customize the name of the plug to refer to using Amazon Alexa. 
- It should have a way of communicating whether it is powered on or off, connected to wifi or not. 
- There should be a physical button to switch it on or off.

## User Case

User buys the smart plug module from the store. He connects the smart plug module to one of the plugs. An led signals that the plug is in the pairing mode and searching for connections. The user downloads an app or logs into an online platoform to set up the device. 
The nearby device pops up in the scanning mode (maybe it has a near feild bluetooth function) and the user connects the device to his homes wifi. 

Once the device is connected to the home internet, it can be controlled by alexa, siri and google assistant. The user names the different ports on the module according to his convinience so next time when he is in bed, he can just ask alexa to turn off the lights or turn on the fans. 

The module does features push bottons to toggle the switches on or off. and there is an LED on next to each plug, indicating whether the plug is powered on or off. 
 

## Product Backlog

### Prioritized List

- Understanding and completing the circuit to give an AC power output while powering the particle. 
- Making a software interface to log in and set up the device
- Working on the packaging and custom hardware
- Connecting it to Alexa and Siri
- Making interfaces using RGB LEDs to notify the whether the particle is connected to the internet, whether the plug is powered on or off. 

### Effort/Priority Matrix

|Effort\Priority| High | Low|
|---|----|----|
|**High**| Understanding and completing the circuit | Working on packaging and circuit|
|**Low**|Coonecting to alexa <br> making an interface to login | making an interface to tell if the device is connected|
