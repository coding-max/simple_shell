#!/bin/bash
# test suite for simple_shell project
source log/config
gcc -g -Wall -Werror -Wextra -pedantic $FOLDER/*.c -o hsh

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# create directories for testing files
mkdir log/expected
mkdir log/obtained

function execute()
{
	$COMMAND > log/expected/test$TEST 2>&1
	echo $COMMAND | ./hsh > log/obtained/test$TEST 2>&1
	DIFF=$(diff -sq log/expected/test$TEST log/obtained/test$TEST)
	RESULT=$(echo $DIFF | grep -c "identical")
	if [ $RESULT -ne 1 ]
	then
		echo -e "${RED}test $TEST fails: \"$COMMAND\"${NC}"
		echo "------------------------------------------------------------------"
		sleep 2
		echo -e "${RED}test $TEST fails - EXPECTED:${NC}"
		$COMMAND
		echo "------------------------------------------------------------------"
		sleep 2
		echo -e "${RED}test $TEST fails - OBTAINED:${NC}"
		echo $COMMAND | ./hsh
		echo "------------------------------------------------------------------"
		sleep 2
		echo -e "${RED}test $TEST fails - DIFFERENCES:${NC}"
		cat log/test$TEST
		echo "------------------------------------------------------------------"
		sleep 2
		echo -e "${RED}test $TEST fails - SUMMARY:${NC}"
		echo $COMMAND | valgrind --leak-check=full ./hsh
		echo "------------------------------------------------------------------"
		rm -rf log/expected
		rm -rf log/obtained
		rm hsh
		exit
	fi
}

echo "Checking errors... in $FOLDER"
sleep 1

TEST=01
COMMAND=""
execute

TEST=02
COMMAND=" "
execute

TEST=03
COMMAND="                   "
execute

TEST=04
COMMAND="/bin/ls"
execute

TEST=05
COMMAND="          /bin/pwd"
execute

TEST=06
COMMAND="/bin/pwd          "
execute

TEST=07
COMMAND="     /bin/pwd     "
execute

TEST=08
COMMAND="/usr/bin/whoami"
execute

TEST=09
COMMAND="/usr/bin/whoami"
execute

TEST=10
COMMAND="/usr/bin/whoami"
execute

TEST=11
COMMAND="/bin/ls -l"
execute

TEST=12
COMMAND="/bin/ls -l -a -r -d -s -t"
execute

TEST=13
COMMAND="/bin/ls --help"
execute

TEST=14
COMMAND="     /bin/ls     -l -a -r -d -s -t"
execute

TEST=15
COMMAND="     /bin/ls      -l   -a   -r   -d   -s   -t     "
execute

TEST=16
COMMAND="pwd"
execute

TEST=17
COMMAND="whoami"
execute

TEST=18
COMMAND="ls"
execute

TEST=19
COMMAND="ls -las"
execute

TEST=20
COMMAND="     ls      -l   -a   -r   -d   -s   -t     "
execute

TEST=21
COMMAND="echo \"por ahora funciona creo xdd\""
execute

TEST=22
COMMAND="cat ../README.md"
execute

TEST=23
COMMAND="env"
execute

TEST=24
COMMAND="this_isnt_a_command"
execute

TEST=25
COMMAND="     fail?"
execute

TEST=26
COMMAND="¿¿¿fail????¿¿¿fail????¿¿¿fail????¿¿¿fail????¿¿¿fail????¿¿¿fail????¿¿¿fail????¿¿¿fail????¿¿¿fail????¿¿¿fail????¿¿¿fail????¿¿¿fail????"
execute


rm -rf log/expected
rm -rf log/obtained
rm hsh