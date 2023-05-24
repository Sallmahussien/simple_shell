#!/bin/bash

alias ccc="gcc -Wall -Werror -Wextra -pedantic *.c -o shsh"
alias cccw="gcc -Wall -Wextra -pedantic *.c -o shsh"
testt()
{
	# if the second argument is c, compile before running
	if [ "$2" = "c" ]
	then
		ccc
		echo "Compiled"
	fi
	if [ -z "$1" ]
	then
		echo "Usage: test <input_file> [c]"
	else
		echo "Running ./tests/checker.bash ./shsh $1"
		./tests/checker.bash ./shsh "$1" > output.txt
	fi
}
testtv()
{
	# if the second argument is c, compile before running
	if [ "$2" = "c" ]
	then
		ccc
		echo "Compiled"
	fi
	if [ -z "$1" ]
	then
		echo "Usage: testv <input_file> [c]"
	else
		./tests/checker.bash --valgrind ./shsh "$1" > output.txt
	fi
}
test()
{
	# if the second argument is c, compile before running
	if [ "$2" = "c" ]
	then
		ccc
		echo "Compiled"
	fi
	if [ -z "$1" ]
	then
		echo "Usage: test <input_file> [c]"
	else
		x=$(./tests/checker.bash ./shsh "$1")
		filename="Test file name: $1"
		spacer="------------------------------"
		if [[ "$x" = "OK" ]];
		then
			echo $spacer
			echo $filename
			echo "$x"
		else
			echo $spacer
			echo $filename
			echo FAILED
			echo $spacer >> output.txt
			echo $filename >> output.txt
			echo "" >> output.txt
			echo "$x" >> output.txt
			exit 1
		fi
	fi
}
tests()
{
	makeMidWrapper()
	{
		echo '#!/bin/bash' > wrapperZXC.sh
		echo 'source ./tests/utils.bash' >> wrapperZXC.sh
		echo 'test "$@"' >> wrapperZXC.sh
		chmod +x wrapperZXC.sh
	}
	makeMidWrapper

	echo "" > output.txt
	cccw
	#check if there is an error exit
	if [ $? -ne 0 ]
	then
		echo "Compilation failed, stopping tests"
		return 1
	fi
	echo "Compiled ignoring warnings"
	if [ -z "$1" ]
	then
		echo "Usage: tests <input_dir>"
		echo "where <input_dir> is a directory containing .bash test files"
	else
		echo "Running ./tests/checker.bash ./shsh on the directory $1"
		echo "" > output.txt
		find "$1"/*.bash -type f -exec ./wrapperZXC.sh {} \;
	fi
	rm wrapperZXC.sh
	echo "Done"
}