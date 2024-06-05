const express = require('express');
const fs = require('fs');
const app = express();
const port = 3000;

// Servir arquivos estáticos na mesma pasta do servidor
app.use(express.static('.'));

app.get('/temperatura', (req, res) => {
    fs.readFile('temp.txt', 'utf8', (err, data) => {
        if (err) {
            console.error(err);
            return res.sendStatus(500);
        }
        res.send(data);
    });
});

app.listen(port, '10.0.0.2', () => {
    console.log(`Servidor rodando em http://10.0.0.2:${port}`);
});
