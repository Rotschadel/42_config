# Definition du path
PATH=$HOME/usr/local:$HOME/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin:/usr/texbin

export PATH=/nfs/zfs-student-3/users/2013/mdelage/usr/local/bin:$PATH

# Gestion de l'historique
HISTFILE=~/.zshrc_history
SAVEHIST=5000
HISTSIZE=5000
setopt inc_append_history
setopt share_history

# Correction de la touche Delete
bindkey "\e[3~"   delete-char

# Autocompletion de type menu
autoload -U compinit && compinit
zstyle ':completion:*' menu select

# Couleur prompt
autoload -U colors && colors

# Definition des couleurs
source ~/.ls_colors

# Definition des variables
USER=`/usr/bin/whoami`
export USER
GROUP=`/usr/bin/id -gn $user`
export GROUP
MAIL="$USER@student.42.fr"
export MAIL

# Definition du prompt

PROMPT="%n@%m:%~
> "

precmd ()
{
	ISGIT=$(git status 2> /dev/null)
	if [ -n "$ISGIT" ]
	then
		STATUS=$(echo "$ISGIT" | grep "modified" | cut -d ' ' -f 2)
		if [ -n "$STATUS" ]
		then
			COLOR="%{$fg[red]%}"
		else
			COLOR="%{$fg[green]%}"
		fi			
		NORMAL="%{$reset_color%}"
		BRANCH=$(git branch | cut -d ' ' -f 2 | tr -d '\n')
		RPROMPT="%{$COLOR%}($BRANCH)%{$NORMAL%}"
	else
		RPROMPT=""
	fi
}

# Definition des alias de git
alias ga="git add"
alias gb="git branch"
alias gcm="git commit -m"
alias gco="git checkout"
alias gpl="git pull"
alias gps="git push"
alias gm="git merge"

# Definition des alias
alias em="emacs"
alias files_s="defaults write com.apple.finder AppleShowAllFiles TRUE && killall Finder"
alias files_h="defaults write com.apple.finder AppleShowAllFiles FALSE && killall Finder"
alias gccf='gcc -Wall -Wextra -Werror'
alias gccl="gcc -I ~/libft/includes -L ~/libft -lft"
alias gcclf="gcc -Wall -Wextra -Werror -I ~/libft/includes -L ~/libft -lft"
alias ls='ls -G'
alias l='ls -l'
alias la='ls -lA'
alias modsh='emacs ~/.zshrc'
alias rl='source ~/.zshrc'

# Experimental
TERM=xterm-256color
