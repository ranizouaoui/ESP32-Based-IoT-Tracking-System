# ESP32-Based-IoT-Tracking-System

## Overview
Our project aims to develop a <a href="https://github.com/ranizouaoui/ESP32-Based-IoT-Tracking-System/" >Tracking system </a> using the <a href="https://www.u-blox.com/en/product/neo-7-series">NEO-7M GPS module</a>. This system is designed to collect geolocation coordinates, process them and present them in a way that suits the needs of customers. We aim to offer a complete solution that will enable efficient and accurate management of location data, thus providing an optimal experience for users.The app will provide valuable information to users such as latitude, longitude and immediate alerts in case of extreme conditions. To ensure data consistency and accessibility, we will deploy <a href="https://www.docker.com/">Docker</a> containers to run the web application and <a href="https://www.hivemq.com/">HiveMQ </a> to manage real-time data streams. The data will be saved to the <a href="https://www .mongodb.com/">Mongodb</a> database for future analysis.

<div align="center"> 
<img src="https://github.com/ranizouaoui/ESP32-Based-IoT-Tracking-System/blob/main/pictures/user-interface.png" alt="" />
 </div>
 
## Project Map
Our <a href="https://github.com/ranizouaoui/ESP32-Based-IoT-Tracking-System/" >Tracking system </a> uses the <a href="https://www.u-blox.com/en/product/neo-7-series">NEO-7M GPS module</a>  to retrieve real-time GPS data, which is then transmitted to an MQTT (HiveMQ) server. The web application retrieves data from the server and visualizes it on a geographical map. Simultaneously, the data stream is kept in a MongoDB database for future use. This project provides a comprehensive and efficient solution for real-time tracking and management of location data.

<strong> Note:</strong> The <a href="https://www.espressif.com/en/products/socs/esp32" >ESP32 </a>board starts sending data if it is well configured (from the configuration interface)
<div align="center"> 
<img src="https://github.com/ranizouaoui/ESP32-Based-IoT-Tracking-System/blob/main/pictures/synoptique.png" alt="" />
 </div>
 
 ## Manual Setup
 ### ESP32 board setup
 Perform the following steps:

 1- Download and install <a href="https://www.arduino.cc/">Arduino</a>.<br/>
 2- Install <a href="https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/">ESP32 Filesystem Uploader in Arduino IDE</a>.<br/>
 3- Edit the source <a href="https://github.com/ranizouaoui/ESP32-Based-IoT-Tracking-System/blob/main/ESP-codes/Main-code/Main-code.ino">Code</a> (update the broker and the firebase settings).<br/>
 4- Install the libraries used in the arduino code.<br/>
 5- Upload the configuration interface in spiffs on esp32 board (Go to <strong> Tools >ESP32 Data Sketch Upload</strong> and wait for the files to be uploaded).<br/>
 6- Upload the source <a href="https://github.com/ranizouaoui/ESP32-Based-IoT-Tracking-System/blob/main/ESP-codes/Main-code/Main-code.ino">Code</a>. <br/>
 
 <blockquote> <p dir="auto">You will need to create an account in firebase and HiveMQ to be able to modify the arduino code</p></blockquote>

 7- Connect to the "gps-tracker" access point. <br/>
 8- Configure the gps tracker from the configuration interface (http://192.168.4.1/). <br/>
 <img src="https://github.com/ranizouaoui/ESP32-Based-IoT-Tracking-System/blob/main/pictures/synoptique.png" alt="" />
 </div>
 
