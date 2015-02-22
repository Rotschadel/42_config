#!/bin/bash

git_dir="$HOME/dotfiles"

function backup_and_ln()
{
	if [ -f "$HOME/$1" ]; then
		if [ -f "$HOME/$1_old" ]; then
			rm -rf "$HOME/$1_old"
		fi
		mv "$HOME/$1" "$HOME/$1_old"
	fi
	ln -s "$git_dir/$1" "$HOME/$1"
}

# go in home directory to create the symbolic link
backup_and_ln ".zshrc"
backup_and_ln ".aliases"
backup_and_ln ".ls_colors"
backup_and_ln ".vimrc"
backup_and_ln ".vim"

# install the vim plugin
cd $git_dir
git submodule init
git submodule update
