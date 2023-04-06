#Remember to use ssh-keyscan <SERVER> > ~/.ssh/known_hosts to persist the SFTP server fingerprint to avoid interactive prompting

RPI_IP=192.168.0.115
RPI_USER="pi"
RPI_PASSWORD="EngineECU"


SFTP_SERVER=$RPI_IP
SFTP_USER=$RPI_USER
SFTP_PWD=$RPI_PASSWORD

echo "Issuing pkill gdbserver command to tidy up Raspberry PI..."
sshpass -p $RPI_PASSWORD ssh $RPI_USER@$RPI_IP 'pkill gdbserver'
echo "Transferring rpi_ecu_display to Raspberry PI..."
sshpass -p $RPI_PASSWORD ssh $RPI_USER@$RPI_IP 'mkdir -p rpi_ecu_display/bin; chmod 771 rpi_ecu_display/bin'
sshpass -p $RPI_PASSWORD ssh $RPI_USER@$RPI_IP 'mkdir -p rpi_ecu_display/log; chmod 771 rpi_ecu_display/log'
lftp sftp://$SFTP_USER:$SFTP_PWD@$SFTP_SERVER  -e "put -O rpi_ecu_display/bin bin/rpi_ecu_display; bye"
echo "Starting GdbServer on Raspberry PI"
sshpass -p $RPI_PASSWORD ssh $RPI_USER@$RPI_IP 'chmod 771 rpi_ecu_display/bin/rpi_ecu_display'
sshpass -p $RPI_PASSWORD ssh $RPI_USER@$RPI_IP 'gdbserver localhost:9999 rpi_ecu_display/bin/rpi_ecu_display'
echo "GdbServer on Raspberry PI stopped, ready for next session."