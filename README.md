# ESP32-Based-IoT-Tracking-System

## Overview
Our project aims to develop a tracking system using the <a href="https://www.u-blox.com/en/product/neo-7-series">NEO-7M</a> GPS module. This system is designed to collect geolocation coordinates, process them and present them in a way that suits the needs of customers. We aim to offer a complete solution that will enable efficient and accurate management of location data, thus providing an optimal experience for users.The app will provide valuable information to users such as latitude, longitude and immediate alerts in case of extreme conditions. To ensure data consistency and accessibility, we will deploy <a href="https://www.docker.com/">Docker</a> containers to run the web application and <a href="https://www.hivemq.com/">HiveMQ </a> to manage real-time data streams. The data will be saved to the <a href="https://www .mongodb.com/">Mongodb</a> database for future analysis.

<div align="center"> 
<img src="https://github.com/ranizouaoui/ESP32-Based-IoT-Tracking-System/blob/main/pictures/user-interface.png" alt="" />
 </div>
 
## Project Map
Our <a href="https://github.com/ranizouaoui/ESP32-Based-IoT-Tracking-System/" >tracking system </a> uses the NEO-7M GPS module to retrieve real-time GPS data, which is then transmitted to an MQTT (HiveMQ) server. The web application retrieves data from the server and visualizes it on a geographical map. Simultaneously, the data stream is kept in a MongoDB database for future use. This project provides a comprehensive and efficient solution for real-time tracking and management of location data.

<strong> Note:</strong> The esp32 board starts sending data if it is well configured (from the configuration interface)
