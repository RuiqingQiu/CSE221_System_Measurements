if [[ -z $1 ]]
then
  echo 'Select a file to run.'
  exit 1
fi

for i in {1..100}
do
nice -10 $1
done

