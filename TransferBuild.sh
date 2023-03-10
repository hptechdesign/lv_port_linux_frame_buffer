#Remember to use ssh-keyscan <SERVER> > ~/.ssh/known_hosts to persist the SFTP server fingerprint to avoid interactive prompting


RPI_IP=192.168.0.115
RPI_USER="pi"
RPI_PASSWORD="#d00dlebug!"


SFTP_SERVER=$RPI_IP
SFTP_USER=$RPI_USER
SFTP_PWD=$RPI_PASSWORD

lftp sftp://$SFTP_USER:$SFTP_PWD@$SFTP_SERVER  -e "put ./build/lvgl_fb; bye"
echo "Starting GdbServer on Raspberry PI"
sshpass -p $RPI_PASSWORD ssh $RPI_USER@$RPI_IP 'chmod 771 ./lvgl_fb'
sshpass -p $RPI_PASSWORD ssh $RPI_USER@$RPI_IP 'gdbserver localhost:9999 ./lvgl_fb'
echo "GdbServer on Raspberry PI stopped, ready for next session."