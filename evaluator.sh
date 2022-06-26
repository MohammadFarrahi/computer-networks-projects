for i in $( seq 1 $1 )
do 
  echo "**testing transmission test${i}.txt"
  diff test${i}.txt build/test${i}.txt
done
