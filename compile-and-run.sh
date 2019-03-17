if [ ! -n "$1" -o ! -n "$2" ]
then
	echo "invalid number of arguments"
    exit
fi

bash compile-game.sh
bash run-game.sh $1 $2