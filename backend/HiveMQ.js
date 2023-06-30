// Test file 

var mqtt = require('mqtt')

var options = {
    host: 'XXXXXXXXXX',
    port: 8883,
    protocol: 'mqtts',
    username: 'XXXXXXXXX',
    password: 'XXXXXXXXXX'
}
var data = {
    temperature: '0',
    humidity: '0',
    power: '0',
    voltage: '0',
    current: '0',
    lighting: '0'
}
// initialize the MQTT client
var client = mqtt.connect(options);

// setup the callbacks
client.on('connect', function () {
    console.log('Connected');
});

client.on('error', function (error) {
    console.log(error);
});
// Subscribe to multiple topics
client.subscribe(['voltage', 'current', 'power', 'lighting', 'temperature', 'humidity']);
client.on('message', function (topic, message) {
    // called each time a message is received

    if (topic == 'voltage') {
        data.voltage = message.toString();
    }
    if (topic == 'current') {
        data.current = message.toString();
    }
    if (topic == 'power') {
        data.power = message.toString();
    }
    if (topic == 'lighting') {
        data.lighting = message.toString();
    }
    if (topic == 'temperature') {
        data.temperature = message.toString();
    }
    if (topic == 'humidity') {
        data.humidity = message.toString();
    }
});

