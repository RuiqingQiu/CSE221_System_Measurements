if [[ ! -e cartographer ]]
then
  echo 'Compile your code.'
  exit 1
fi

for i in map{1..100}.pf
do
  ./cartographer ${i}
done

