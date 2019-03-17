if [ ! -n "$1" -o ! -n "$2" ]
then
	echo "invalid number of arguments"
    exit
fi

if [ $1 != "Circle" -a $1 != "Square" ]
then
	echo "invalid first argument"
    exit
fi

if [ $2 != "Circle" -a $2 != "Square" ]
then
	echo "invalid second argument"
    exit
fi

export LD_LIBRARY_PATH=$(pwd)/lib-files/SFML/lib && ./compile-files/game $1 $2
