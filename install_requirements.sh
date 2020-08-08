for requirement in `cat requirements.txt | tr ',' '\n'`; do 
    sudo apt -y install $requirement ;
done