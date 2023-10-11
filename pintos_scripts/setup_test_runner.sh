script_dir="$(pwd)";
project_root_dir=$(dirname "$(pwd)")
src_dir="$project_root_dir/src"


added_code_to_bashrc="

# Test Runner Dependencies

alias graph=\"git log --graph --oneline --decorate --all\"
export script_dir=\"$script_dir\"
export project_root_dir=\"$project_root_dir\"
export src_dir=\"$src_dir\"

t() {
	$script_dir/test_runner.sh \"\$@\"
}

"

echo "$added_code_to_bashrc" >> ~/.bashrc


