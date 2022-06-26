receiver_port=8080
router_port=8081

make

echo "strat recevier"

cd build
./Receiver.out $receiver_port $router_port

cd ..