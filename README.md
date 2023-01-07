# esp-iot
**Day 1. Install Arduino and ESP**
1. Install Arduino 1.8.19
2. Open arduino IDE
3. To install ESP board in arduino 
4.  Go to file > preference > copy below url and past in board URL section.
*https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json*


**Day 1. Thingspeak Server**
Server link  - https://thingspeak.com/
Day 1.  - Make an account there, add a channel and copy channel number and API key.
Make changes in code lines 19 and 20 in code [send_temprature_server.ino](https://github.com/dev-techshlok/esp-iot/blob/master/send_temprature_server.ino)

Replace with channel number

    unsigned long myChannelNumber = ;  

Replace with API key

    const char * myWriteAPIKey = "";


**Day 2 inter device communication**
Code file - [inter_device_mqtt.ino](https://github.com/dev-techshlok/esp-iot/blob/master/inter_device_mqtt.ino)
Change these line 7 and 8 code for wifi username and password.
   

    const char* ssid = "WIFI_NAME";
    const char* password = "WIFI_PASSWORD";



You have to write you name here. on line 9 in place of "teamA"

    char * sub_topic = "teamA"; //This is YOU (Your team)


You have to write you name here. on line 10 in place of "teamA"

    char * pub_topic = "teamB"; //This is THEM (Another team)
