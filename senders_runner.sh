receiver_port=8080
router_port=8081
base_port=8082

echo "cleaning ..."

rm *.txt
rm build/*.txt

for i in $( seq 1 $1 )
do
  port=$(($base_port+$i))
  echo "generater dummy $i"
  python3 file_generator.py test${i}.txt 1
  echo "strat sender $i"
  ./Sender.out $port $receiver_port $router_port test${i}.txt > log_${port}.txt &
done

echo "exiting..."