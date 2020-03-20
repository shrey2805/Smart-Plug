# Sprint 1: MVP

### Sprint Catalog

The goal of this sprint is to make an MVP using a relay, and connecting particle to Siri and using voice command to actuate the relay to turn a lamp on and off. 

### Sprint Review  

Working with AC current is extremely dangerous and any loose connections can lead to fatal injuries. 

Therefore, for this sprint, I used a Sparkfun Relay Module, mentioned in the BOM. This is a temporary measure for this sprint and would be replaced by 
I completed the connection of the particle to the hardware module. I have tested a photosensor and tried to get the automation that when the light is too low, then the lamp would turn on automatically. Although this functionality is useful but it is not ideal. Next I would like to explore the possibility to connect the device to Alexa and Siri using the cloud connectivity. 

### End of Sprint Prototype

[Document the current implementation, add code, images inline, circuit diagrams, etc to this folder]

### Sprint Retrospective 

#### Custom Hardware: 
It is very difficult to design a custom hardware specially when working with AC current. There is always a risk of loose wiring and electric shock. 
Resorting to the hardware module made by the sparkfun takes away a lot of headache and I could focus on connectivity. 

I explored relays as the part of my project and they are very instrumental in designing IoT platforms. One of the possible areas of exploration for me can be developing a better understanding of the relays and actually making a custom hardware but that is low on the pripority list. 

#### Wiring the particle. 
Currently I am using one of the ports on the sparkfun module to power the particle, but ideally, I want a dc source built in, this would add complexity to the hardware and another area of further exploration. 



### Next

The next sprint focusses on getting connected to alexa and siri. 
- How to make custom voice commands and ask particle to perform required actions. 
- Explore the possibility to automate the routine like turing on the instant pot/coffee machine and turning it off remotely. 
