" .vimrc

set nocompatible                 " Vim is better than Vi
set encoding=utf-8               " utf8 or gtfo

let mapleader = ' '        " leader key used by some plugins
"let g:mapleader = ' '     " gvim leader key used by some plugins

filetype plugin off

" Pathogen plugin management
call pathogen#infect()
call pathogen#helptags()        " Generate doc for all plugins

filetype plugin indent on        " activate filetype detection,

" Vimscript file settings {{{
augroup filetype_vim
    autocmd!
    autocmd FileType vim setlocal foldmethod=marker
augroup END
" }}}

" stupid way of loading ftplugins {{{
try
    runtime! bundle/ccimpl/ftplugin/ccimpl.vim
catch
endtry
try
    runtime! python_match/ftplugin/python_match.vim
catch
endtry
" }}}

" auto-reload .vimrc {{{
augroup reload_vimrc " {
    autocmd!
    autocmd BufWritePost $MYVIMRC source $MYVIMRC
augroup END " }
" }}}

" ruler with line number
set number

" Visual settings
set t_Co=256                     " force vim to use 256 colors
set background=dark

" theme
colorscheme kalahari

" status line
set laststatus=2                 " always display the status line
set shortmess=atI                " short messages to avoid scrolling
set title
set ruler                        " show the cursor position all the time
set showcmd                      " display incomplete commands

" autocompletion {{{
set wildmenu                     " show more than one suggestion for completion
set wildmode=list:longest        " shell-like completion (up to ambiguity point)
set wildignore=*.o,*.out,*.obj,*.pyc,.git,.hgignore,.svn,.cvsignore

set autoread                     " watch if the file is modified outside of vim
set hidden                       " allow switching edited buffers without saving
" }}}

" break long lines visually (not actual lines)
set wrap linebreak
set tw=0 wm=0

"set autowrite                   " Auto-save before :next, :make, etc.

" Highlighting spaces and tabulations {{{
" (\zs & \ze == start and end of match, \s == any space)
match ErrorMsg '\s\+$'           " Match trailing whitespace
match ErrorMsg '\ \+\t'          " & spaces before a tab
match ErrorMsg '[^\t]\zs\t\+'    " & tabs not at the begining of a line
match ErrorMsg '\[^\s\]\zs\ \{2,\}' " & 2+ spaces not at the begining of a line
" }}}

if exists('+colorcolumn')
    set colorcolumn=80
    "else
    "  au BufWinEnter * let w:m2=matchadd('ErrorMsg', '\%>80v.\+', -1)
endif

set textwidth=0
"set whichwrap=<,>,h,l
"map <C-UP> g k
"map <C-UP> g k
set viminfo=%,'50,\"100,:100,n~/.viminfo
set history=100                  " keep 100 lines of command line history

set scrolloff=2
set sidescrolloff=5

" search
set incsearch                    " incremental searching
set smartcase                    " if no caps in patern, not case sensitive
" if the terminal has colors
" switch syntax highlighting on
" & highlight last research
if &t_Co > 2 || has("gui_running")
    syntax on
    set hlsearch
endif

" Put all backup and swap in one place {{{
set backupdir=~/.vim/tmp,~/.tmp,~/tmp,/var/tmp,/tmp
set directory=~/.vim/tmp,~/.tmp,~/tmp,/var/tmp,/tmp
" }}}

if has("vms")
    set nobackup                   " use versions instead of backup file
else
    set backup                     " keep a backup file
endif

" http://tedlogan.com/techblog3.html
set tabstop=4 softtabstop=4 shiftwidth=4 expandtab

" Only do this part when compiled with support for autocommands.
if has("autocmd")

    augroup vimrcEx " {
        au!

        " For all text files set 'textwidth' to 80 characters.
        autocmd FileType text setlocal textwidth=80

        " Jump to the last known cursor position when editing a file
        autocmd BufReadPost *
                    \ if line("'\"") > 1 && line("'\"") <= line("$") |
                    \   exe "normal! g`\"" |
                    \ endif

        " FileType {{{
        " http://tedlogan.com/techblog3.html
        autocmd FileType sh setlocal ts=4 sts=4 sw=4 noet ai " sh
        autocmd FileType c,cpp setlocal ts=4 sts=4 sw=4 noet ai " c
        autocmd FileType make setlocal ts=4 sts=4 sw=4 noet ai " Makefile
        autocmd FileType vim setlocal ts=2 sts=2 sw=2 noet ai " Vim
        autocmd FileType text setlocal ts=2 sts=2 sw=2 noet ai " Text
        autocmd FileType markdown setlocal ts=4 sts=4 sw=4 noet ai " Markdown
        autocmd FileType html setlocal ts=2 sts=2 sw=2 noet ai " (x)HTML
        autocmd FileType php,java setlocal ts=2 sts=2 sw=2 noet ai nocindent " PHP & Java
        autocmd FileType javascript setlocal ts=2 sts=2 sw=2 noet ai nocindent " JavaScript
        autocmd BufNewFile,BufRead *.h set ft=c
        autocmd BufNewFile,BufRead *.json set ft=javascript
        autocmd BufNewFile,BufRead *.webapp set ft=javascript
        autocmd BufNewFile,BufRead *.tpp set ft=cpp
        " }}}

    augroup END " }

    " c gates {{{
    function! s:insert_c_gates()
        let gatename = substitute(toupper(expand("%:t")), "\\.", "_", "g")
        let cName = substitute(expand("%:t"), ".h", "", "")
        execute "normal! i#ifndef " . gatename
        execute "normal! o# define " . gatename
        execute	"normal! o"
        execute "normal! Go#endif /* " . gatename . " */"
        normal! kk
    endfunction
    " }}}

    " c++ gates {{{
    function! s:insert_cpp_gates()
        let gatename = substitute(toupper(expand("%:t")), "\\.", "_", "g")
        let cName = substitute(expand("%:t"), ".hpp", "", "")
        execute "normal! i#ifndef " . gatename
        execute "normal! o# define " . gatename
        execute	"normal! o"
        execute	"normal! oclass " . cName
        execute	"normal! o{"
        execute	"normal! opublic:"
        execute "normal! o" . cName . "( void );"
        execute "normal! o" . cName . "(" . cName." const & src );"
        execute "normal! o~" . cName . "( void );"
        execute "normal! o" . cName . " &	operator=( " . cName . " const & rhs );"
        execute	"normal! o"
        execute	"normal! oprivate:"
        execute	"normal! o};"
        execute	"normal! o"
        execute "normal! Go#endif /* " . gatename . " */"
        normal! kk
    endfunction
    " }}}

    " gates autocmd {{{
    augroup gates
        autocmd!
        autocmd BufNewFile *.{h} call <SID>insert_c_gates()
        autocmd BufNewFile *.{hpp} call <SID>insert_cpp_gates()
    augroup END
    " }}}

    " Suppression of space at end of line {{{
    augroup delete_space
        autocmd!
        autocmd BufWrite * silent! %s/[\r \t]\+$//
    augroup END
    " }}}

    " compilo {{{
    augroup compilo
        autocmd!
        autocmd Filetype cpp :nnoremap <leader>m :!g++ -Wall -Wextra -Werror %
        autocmd Filetype c :nnoremap <leader>m :!gcc -Wall -Wextra -Werror %
    augroup END
    " }}}

else
    set autoindent                 " always set autoindent (ai) on
endif " has("autocmd")

" use mouse
" set mouse=a                       " mouse

" Don't use Ex mode, use Q for formatting
map Q gq

" CTRL-U in insert mode deletes a lot. Use CTRL-G u to first break undo,
" so that you can undo CTRL-U after inserting a line break.
inoremap <C-U> <C-G>u<C-U>

" Arrow desactivation {{{
" inactivate arrows, home and end keys in insert mode
"inoremap <Up> <nop>
"inoremap <Down> <nop>
"inoremap <Left> <nop>
"inoremap <Right> <nop>
"inoremap <home> <nop>
"inoremap <End> <nop>
"inoremap <Up> <nop>

" inactivate arrows, home and end keys in normal mode
"noremap <Up> <nop>
"noremap <Down> <nop>
"noremap <Left> <nop>
"noremap <Right> <nop>
"noremap <home> <nop>
"noremap <End> <nop>
"noremap <Up> <nop>
" }}}

set backspace=indent,eol,start   " allow backspacing over everything in insert mode
set formatoptions=cqrt           " comments newline when already in a comment

" scroll more than one line up/down at a time
" nnoremap <C-e> 3<C-e>
" nnoremap <C-y> 3<C-y>

" Convenient command to see the difference between the current buffer and the
" file it was loaded from, thus the changes you made.
" Only define it when not defined already.
if !exists(":DiffOrig")
    command DiffOrig vert new | set bt=nofile | r # | 0d_ | diffthis
                \ | wincmd p | diffthis
endif

nnoremap <silent> <Leader>/ :nohlsearch<CR>

" Toggle spellcheck and choose the language each time {{{
nmap <silent> <leader>ss :call ToggleSpell()<CR>
function! ToggleSpell() " {
    if &spell == 0 " {
        call inputsave()
        let g:myLang = input('lang: ')
        call inputrestore()
        let &l:spelllang = g:myLang
        setlocal spell
    else
        setlocal nospell
    endif " }
endfunction " }
" }}}

" Open man in vim
runtime! ftplugin/man.vim

" split screen below and right instead of vim natural
set splitbelow
set splitright

" rebind increase
nnoremap <C-c> <C-a>

" Moving to beginning or end of line {{{
nnoremap <C-a> <Home>
nnoremap <C-e> <End>
inoremap <C-a> <Home>
inoremap <C-e> <End>
vnoremap <C-a> <Home>
vnoremap <C-e> <End>
" }}}

" Some shortcut for insert mode
inoremap <Nul> <C-n>
inoremap <c-u> <esc>viwUi<esc>`>
" inoremap ( ()<left>
" inoremap [ []<left>
" inoremap { {}<left>

" NerdTree
nnoremap <C-n> :NERDTreeTabsToggle<CR>
autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTreeType") && b:NERDTreeType == "primary") | q | endif

" Some shortcut with leader {{{
nnoremap <leader>w :wa<cr>
nnoremap <leader>a :wqa<cr>
nnoremap <leader>! :qa!<cr>
nnoremap <leader>t :tabedit<space>
nnoremap <leader>ev :vs $MYVIMRC<cr>
nnoremap <leader>n :NERDTreeFocusToggle<cr>
nnoremap <leader><tab> gt
nnoremap <leader><leader> :!
" }}}

" Syntastic {{{
let g:syntastic_check_on_open=1
let g:syntastic_enable_signs=1
let g:syntastic_error_symbol='★'
let g:syntastic_style_error_symbol='>'
let g:syntastic_warning_symbol='⚠'
let g:syntastic_style_warning_symbol='>'
let g:syntastic_c_include_dirs=[ '.', './includes', '../includes', './libft/includes' , '../libft/includes' ]
" }}}
