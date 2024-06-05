document.addEventListener('DOMContentLoaded', function () {

    const serverIP = '10.0.0.2';
    const serverPort = 1000;

    const leds = [
        { ligarBtnId: 'ligarLed0', desligarBtnId: 'desligarLed0', ledNum: 0 },
        { ligarBtnId: 'ligarLed1', desligarBtnId: 'desligarLed1', ledNum: 1 },
        { ligarBtnId: 'ligarLed2', desligarBtnId: 'desligarLed2', ledNum: 2 },
        { ligarBtnId: 'ligarLed3', desligarBtnId: 'desligarLed3', ledNum: 3 }
    ];

    // Função para enviar uma requisição para ligar um LED
    function ligarLED(ledNum) {
        fetch(`http://${serverIP}:${serverPort}/ligar/${ledNum}`)
            .then(response => {
                if (!response.ok) {
                    console.error(`Erro ao ligar o LED ${ledNum}`);
                } else {
                    console.log(`LED ${ledNum} ligado`);
                }
            })
            .catch(error => {
                console.error(`Erro ao ligar o LED ${ledNum}: ${error.message}`);
            });
    }

    // Função para enviar uma requisição para desligar um LED
    function desligarLED(ledNum) {
        fetch(`http://${serverIP}:${serverPort}/desligar/${ledNum}`)
            .then(response => {
                if (!response.ok) {
                    console.error(`Erro ao desligar o LED ${ledNum}`);
                } else {
                    console.log(`LED ${ledNum} desligado`);
                }
            })
            .catch(error => {
                console.error(`Erro ao desligar o LED ${ledNum}: ${error.message}`);
            });
    }

    // Configurar eventos de clique para os botões de ligar e desligar LEDs
    leds.forEach(led => {
        const ligarBtn = document.getElementById(led.ligarBtnId);
        const desligarBtn = document.getElementById(led.desligarBtnId);

        ligarBtn.addEventListener('click', () => {
            ligarLED(led.ledNum);
        });

        desligarBtn.addEventListener('click', () => {
            desligarLED(led.ledNum);
        });
    });
});

