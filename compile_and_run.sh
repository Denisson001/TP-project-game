if [ ! -n "$1" -o ! -n "$2" ]
then
	echo "invalid number of arguments"
    exit
fi

bash compile_game.sh
bash run_game.sh $1 $2