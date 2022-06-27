for i in $( seq 1 $1 )
do 
  echo "**testing transmission test${i}.txt"
  diff hostA/test${i}.txt hostB/test${i}.txt
done
