# Research Sprint 2
## Algorithm and Sensor Research

_Prompt: Identify 3-5 advanced technical approaches, code implementations, algorithms, software or sensors that are relevant to your project and that could help you make your implementation more robust_

In this sprint, I focussed on adding the current sensor to the circuit to start getting the readings for energy calculations. 
I researched on various types of current sensors and which is the best to include in the circuit. 
Here are links to the sensors: 

Link 1: Non Invasive current sensor: https://www.sparkfun.com/products/11005
Link 2: ACS 723 Invasive current sensor: https://www.sparkfun.com/products/13679
Link 3: ACS 723 Low current invasive current sensor: https://www.sparkfun.com/products/14544

### Summary

The goal of the research was to find a current sensor suitable for the application of a lamp. Because the lamp drew only 1.66 A current, I required a sensor that ould provide me a good level of details in the readings. Also, the sensor should have a suitable safety margin. 

Also, I planned to include the sensor in the circuit itself, therefore non-invasive current sensor was good for testing the early prototypes, but later, to get more reliable readings, invasive current sensor was included in the circuit. 

### Findings

I found 2 invasive current sensors apt for my use: 
ACS 723 and ACS 723 Low current sensor. 
I used the ACS 723 Current sensor. This sensor is good for measuring current from 1A to 5A. 
For getting finer details, it is better to use the ACS 723 Low Current sensor. This sensor has an advantage that the Reference voltage and gain can be adjusted to obtain finer details. 

### Relevance
From this exercise, I learned about various current sensors and the revisited the basics of electrical engineering. 
Also, I got to learn about safety measures and regulations related to devices that run on AC current. 
