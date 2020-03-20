
## Smart Plug 
Submitted By Shrey Agrawal 

Final documentation for IoT Advanced Course 

![alt text](https://github.com/daraghbyrne/advancediot2020/blob/master/students/shreyagr/assets/Poster.png)

### Why a Smart Plug? 

Based on the primary and secondary research, I found out that people have a natural tendency to take the energy they consume for granted. 

There is already a dirth of natural resources and humans are trying to combact the climate change. As the human population keeps on increasing, the demand of energy is going up. 
This means more natural resouces are consumed to meet this demand. There is a limit to the energy that can be generated through renewable resources and equitable use of this energy is very important moving forward. 
There is enough for man's need but not greed ~ Mahatma Gandhi

#### Scenario
It happens very frequently that people leave their houses with AC, fan and lights open. The bigger problem is that when they come back to realise that the appliances have been running, the user's don't feel guilty, or there is no change in their behavior
I identified that there is an urgent need to make the user's aware of their energy consumption and more imporatantly, nudging their behavior is very important. 
All housees have their energy meters installed, giving out readings for exact amounts of energy consumed, but that is not helping. 
I wanted to make these nudges subtle and just in time. The user's should get the access to information qualitatively when they want, the effort from the user's end should be as low as possible.

#### Learning Objective
Through this project, I wanted to learn about the IoT framework hollistically.
- A hardware module consisting of the particle microprocessor, current breakout sensor, and the output device i.e. neopixel led ring
- Integration with the exhisting IoT infrastructure, i.e. making it compatible to take voice commands from Siri, using webhooks and uploading data to could platforms. 
- Giving the project more meaning by using cloud computing by making an IoT hub on Microsoft Azure.

The real value in the IoT devices is generating from using the data collected to achieve more functionality and I wanted to explore this domain through my project. 

### Approach
- The approach is to make a hardware module, that can sense the energy usage patterns. This data gathered about energy usage patterns is uploaded to azure. 
- Azure is used to perform data analysis and model the user behavior. 
- The threshold of the NeoPixel in the smartplug is dynamically updated and the plug learns from the usage patterns. 

### Process
Agile process was used to complete this project in a seven week duration. 
The process started with an ideation phase and looking at precedents. The list of precedents can be found in refrences. 

The process started with an ideation phase of the rpoduct and identifying the requirements and mapping them out on an Importance Pirority matrix. 

![alt text](https://github.com/daraghbyrne/advancediot2020/blob/master/students/shreyagr/assets/effort%20priority%20matrix.JPG)

#### Sprint 1
The complete documentation of the sprint 1 can be found in the folder: https://github.com/daraghbyrne/advancediot2020/tree/master/students/shreyagr/sprint-1

- In this sprint, an MVP was realised and the functionality of interfacing the particle with Siri was achieved. 
To see the detailed process, please refer to the tutorial here: https://github.com/daraghbyrne/advancediot2020/blob/master/students/shreyagr/tutorial/IoT%20Demo%20%20(1).pdf

#### Sprint 2
The complete documentation for sprint 2 can be found here: https://github.com/daraghbyrne/advancediot2020/tree/master/students/shreyagr/sprint-2
- This sprint focussed on adding the current breakout sensor, calibrating it and start achieving reliable data from the sensor. 
- Also, adding the neopixel and coding it's functionality in a desired manner. 

#### Sprint 3
The complete documentation for sprint 3 can be found here: https://github.com/daraghbyrne/advancediot2020/tree/master/students/shreyagr/sprint-3
- This sprint focussed on making the final hardware
- Making the plug learn from the user behavior 
- Uploading the data to cloud platforma and making a dakshboard for data visualization.

### Final Outcome
![alt text]{https://github.com/daraghbyrne/advancediot2020/blob/master/students/shreyagr/assets/WhatsApp%20Image%202020-03-07%20at%207.23.11%20PM.jpeg}
![alt text](https://github.com/daraghbyrne/advancediot2020/blob/master/students/shreyagr/assets/WhatsApp%20Image%202020-03-07%20at%207.23.09%20PM.jpeg)
![alt text](https://github.com/daraghbyrne/advancediot2020/blob/master/students/shreyagr/assets/WhatsApp%20Image%202020-03-07%20at%207.23.06%20PM.jpeg)

### Bill of Materials
Bill of materials can be found at: https://github.com/daraghbyrne/advancediot2020/blob/master/students/shreyagr/bom.md

### Code
The final code can be found here: https://github.com/daraghbyrne/advancediot2020/tree/master/students/shreyagr/sprint-3/Final%20Code
Note: You might need to do the sensor calibration and find out the Vref and Resistance of the sensor. 

### References
- Hackster smart plug project : https://www.hackster.io/daniel0524/building-a-wifi-outlet-cf3d0c
- Adafruit controllable 4 power outlet relay: https://www.adafruit.com/product/2935?

