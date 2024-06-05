
#!/bin/bash

# Nome do executável
executable="read"

# Função para iniciar o aplicativo
start_app() {
    ./"$executable" &
}

# Função para encerrar o aplicativo
stop_app() {
    pkill -x "$executable"
}

# Inicia o aplicativo
start_app
sleep 2

# Encerra o aplicativo
stop_app

# Aguarda um pouco antes de reiniciar
sleep 2
start_app

