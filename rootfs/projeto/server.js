const express = require('express');
const app = express();
const {exec}=require('child_process')

const ipAdress = '10.0.0.2';
const port = 1000;

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'index.html'));
});


app.get('/ligar/:ledNum', (req, res) => {
    const ledNumber = req.params.ledNum;

    const comand = `echo 1 > /sys/devices/platform/leds/leds/beaglebone:green:usr${ledNumber}/brightness `
    console.log (`ligando led ${ledNumber}`)
    exec (comand)

    res.send("received");
});  

app.get('/desligar/:ledNum', (req, res) => {
    const ledNumber = req.params.ledNum;

    const comand = `echo 0 > /sys/devices/platform/leds/leds/beaglebone:green:usr${ledNumber}/brightness `
    console.log (`desligando led ${ledNumber}`)
    exec (comand)

    res.send("received");
});  

app.listen(port, '0.0.0.0', () => {
    console.log(`Server as online and running in ${port} port!`);
});