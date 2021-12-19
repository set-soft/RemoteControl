sudo apt install docker docker-compose

# Add cpputest folder for code completion (see: platformio.ini).
FileName=cpputest-4.0.tar.gz
wget https://github.com/cpputest/cpputest/releases/download/v4.0/$FileName
tar -xf $FileName
rm $FileName
