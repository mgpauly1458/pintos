heck if an argument was provided
if [ $# -eq 0 ]; then
  echo "No arguments provided."
  exit 1
fi

test_command="$1"

if [ "$test_command" == "read_test" ]; then
	module="$2"
	test_name="$3"
	cat $src_dir/$module/build/tests/$module/$test_name.output
	exit 0
fi

if [ "$test_command" == "delete_test" ]; then
	module="$2"
	test_name="$3"
	test_dir=$src_dir/$module/build/tests/$module
	rm $test_dir/$test_name
	rm $test_dir/$test_name.*
	exit 0		
fi

if [ "$test_command" == "check" ]; then
	module="$2"
	cd $src_dir/module/build
	make check

fi

if [ "$test_command" == "build" ]; then
	echo "\n\nbuild dir $src_dir\n\n"
	modules=("userprog" "threads" "utils" "vm" "filesys" "examples")
	for module in "${modules[@]}"; do
    		cd $src_dir/$module
		make
	done
fi	

if [ "$test_command" == "pintos" ]; then
	cd $src_dir/userprog/build
	command="pintos ${@:2}"	
	$command
fi

if [ "$test_command" == "runner" ]; then
	vim $project_root_dir/pintos_scripts/test_runner.sh
fi

if [ "$test_command" == "vi" ]; then
	module="$2"
	file_name="$3"
	vim $src_dir/$module/$file_name
fi

if [ "$test_command" == "grep" ]; then
	cd $src_dir
	searched_word="$2"
	command="grep $searched_word * -r"
	$command
fi

# Userprog commands (change when debugging other sys)

if [ "$test_command" == "gdb" ]; then
        cd $src_dir/userprog/build
        pintos-gdb kernel.o
fi


if [ "$test_command" == "args-none" ]; then
        cd $src_dir/userprog/build
        pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/args-none -a args-none -- -q  -f run args-none
fi


if [ "$test_command" == "args-none-gdb" ]; then
        cd $src_dir/userprog/build
        pintos -v -k -T 60 --qemu  --filesys-size=2 -p tests/userprog/args-none -a args-none --gdb -- -q  -f run args-none
fi


if [ "$test_command" == "test_write" ]; then
        cd $src_dir/userprog/build
        pintos -v -k -T 60 --qemu --filesys-size=2 -p ../../examples/test_write -a test_write -- -q -f run test_write
fi


if [ "$test_command" == "test_write-gdb" ]; then
        cd $src_dir/userprog/build
        pintos -v -k -T 60 --qemu --filesys-size=2 -p ../../examples/test_write -a test_write --gdb -- -q -f run test_write
fi

if [ "$test_command" == "echo" ]; then
        cd $src_dir/userprog/build
        pintos run 'echo x'
fi


if [ "$test_command" == "test_arg" ]; then
	cd $src_dir/userprog/build
	pintos run 'test_arg 69'
fi


if [ "$test_command" == "test_arg-gdb" ]; then
	cd $src_dir/userprog/build
	pintos --gdb -- run 'test_arg 69'
fi

exit 0
