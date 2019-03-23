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


./compile_files/game $1 $2
#valgrind --leak-check=full ./compile_files/game $1 $2