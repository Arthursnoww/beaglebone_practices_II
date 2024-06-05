#!/bin/bash
#
### BEGIN INIT INFO
# Provides:             ssh_root
# Required-Start:       $network
# Required-Stop:        $network
# Default-Start:        S
# Default-Stop:
# Short-Description:    SSH para root@10.0.0.2
# Description:          Este script inicia uma conexão SSH para root@10.0.0.2 durante a inicialização do sistema.
### END INIT INFO

case "$1" in
  start)
    echo "Iniciando SSH para root@10.0.0.2"
    ssh root@10.0.0.2
    ;;
  stop)
    # Não faz nada aqui, pois não há ação de parada necessária.
    ;;
  restart)
    # Não faz sentido reiniciar um comando SSH neste contexto, então não há ação de reinicialização.
    ;;
  *)
    echo "Uso: $0 {start|stop|restart}"
    exit 1
esac

exit $?

