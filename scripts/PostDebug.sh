RPI_IP=192.168.0.115
RPI_USER="pi"
RPI_PASSWORD="EngineECU"


SFTP_SERVER=$RPI_IP
SFTP_USER=$RPI_USER
SFTP_PWD=$RPI_PASSWORD


sshpass -p $RPI_PASSWORD ssh $RPI_USER@$RPI_IP 'pkill gdbserver'
echo "Killed GdbServer on Raspberry PI"