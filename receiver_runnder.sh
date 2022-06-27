receiver_port=8080
router_port=8081


rm -fR hostB
mkdir hostB
make
cp Receiver.out hostB/
cd hostB

echo "strat recevier"
./Receiver.out $receiver_port $router_port