//TODO: CHANGE THE HIVREMQ SETTINGS
const express = require('express')
const { MongoClient } = require('mongodb')
const bodyParser = require('body-parser');
const cors = require("cors");
const app = express();
const port = 3000;
const axios = require('axios');
var mqtt = require('mqtt')
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use(cors());
var city = 'sousse'
async function getCityName(latitude, longitude) {
    try {
        const response = await axios.get(`https://nominatim.openstreetmap.org/reverse?format=json&lat=${latitude}&lon=${longitude}`);
        const data = response.data;

        if (data.address && data.address.city) {
            city = data.address.city;
        } else if (data.address && data.address.town) {
            city = data.address.town;
        } else if (data.address && data.address.village) {
            city = data.address.village;
        } else {
            city = '';
        }
    } catch (error) {
        console.error('Error:', error);
    }
}
// ! Use this link if you work in docker : mongodb://root:example@mongodb:27017/mydatabase?authSource=admin
// ! Use this link if you work in localhost: mongodb://root:example@localhost:27017/mydatabase?authSource=admin

const client = new MongoClient('mongodb://root:example@mongodb:27017/mydatabase?authSource=admin', { useUnifiedTopology: true })
const db = client.db('mydatabase');
const collection = db.collection('greenhouseData');
client.connect().then(() => {
    console.log('Connected to MongoDB')
}).catch(error => {
    console.error(error)
})
var options = {
    host: 'xxxxxxxx',
    port: 8883,
    protocol: 'mqtts',
    username: 'xxxxxxxx',
    password: 'xxxxxxxx'
}

var data = {
    Latitude: '36.516418',
    Longitude: '9.451063',

}
// initialize the MQTT client
var client1 = mqtt.connect(options);

// setup the callbacks
client1.on('connect', function () {
    console.log('Connected');
});
client1.on('error', function (error) {
    console.log(error);
});

// Subscribe to multiple topics
client1.subscribe(['latitude', 'longitude']);
client1.on('message', function (topic, message) {
    // called each time a message is received

    if (topic == 'latitude') {
        data.Latitude = message.toString();
    }
    if (topic == 'longitude') {
        data.Longitude = message.toString();
    }
});
app.get('/messages', async function (req, res) {
    const currentTime = new Date();
    await getCityName(data.Latitude, data.Longitude);
    const messageData = {
        Latitude: data.Latitude,
        Longitude: data.Longitude,
        city: city,
        Timestamp: currentTime
    };
    console.log(messageData);
    collection.insertOne(messageData)
        .then(result => {
            console.log('Data saved to MongoDB:', result);
            res.send(messageData);
        })
        .catch(error => {
            console.error('Error saving data to MongoDB:', error);
            res.status(500).send('Error saving data to MongoDB');
        });

})
app.get('/api/history', async function (req, res) {

    const result = await collection.find().toArray();
    console.log(result);
    res.send(result);
});
app.listen(port, () => {
    console.log(`Example app listening on port ${port}`)
})
