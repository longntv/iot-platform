
var mqtt = require('mqtt')
var request = require('request');

const client = mqtt.connect({servers : [{ host: '192.168.1.8', port: 1883}], username : 'test', password : 'test'})

// const client = connect('mqtt://test.mosquitto.org')

client.on('connect', () => {

   client.subscribe('test/data',{qos:1})

})
client.on('message',function(topic,message) {
    console.log('this message :', message.toString());

    var sendDATA=message.toString();
    var http=require('http');
    const postData=sendDATA;

    let pathApi = '';

    var requestData = {
        adultCount: 1,
        infantInLapCount: 0,
        infantInSeatCount: 0,
        childCount: 0,
        seniorCount: 0
    };
    
    if(topic === 'test/data')
    {
        pathApi = '/api/test';
    }
    var request = require('request');
    request({
            url: "http://localhost:8000/api/test",
            json: true,
            method: "POST",
            headers: {
                "content-type": "application/json",
            },
            body: JSON.stringify(requestData)
        }, function(error, response, body) {
            console.log(body);
    });
});
