# AirWick-Controlled-by-Alexa

People have asked how I created the interaction in the video below, well here it is. Its done with a sonoff SV integrated into MQTT. Then it can be controlled by Home Assistant(or any hub/software you use that supports MQTT) as an MQTT Switch. Home assistant exposes it to Alexa as a switch. The interaction in the video was created using a routine in the Alexa App, to add some comedy to it instead of just saying 'Alexa, turn on air freshener'. 

# Watch it in action
[![Watch the video](https://img.youtube.com/vi/hpqI5w-946g/hqdefault.jpg)](https://www.youtube.com/watch?v=hpqI5w-946g)


## How its done:

1. All electronics were removed from the Air Wick except the motor

2. Wire a Sonoff SV (with 5v power supply) directly to the motor of the air wick(do not plug supply in until firmware is flashed)

3. Download the sonoff firmware from this repo

4. Edit the .ino with your wireless credentionals and MQTT credentials(Optionally edit MQTT topics)

5. Then flash the firmware to your sonoff and its ready to integrate into your specific setup using MQTT
