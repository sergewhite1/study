" vim-plug manager settings begin =============================================
call plug#begin('~/.vim/plugged')
Plug 'scrooloose/nerdtree', { 'on':  'NERDTreeToggle' }
Plug 'dart-lang/dart-vim-plugin'
Plug 'morhetz/gruvbox'
Plug 'ycm-core/YouCompleteMe', {'on': 'YouCompleteMeToggle' }

" C++			
" Plug 'rip-rip/clang_complete'

call plug#end()
"
" Then reload .vimrc and :PlugInstall to install plugins.
"
" vim-plug manager settings end ===============================================

"colorscheme gruvbox
"let g:gruvbox_termcolors=16
"
" path to directory where library can be found
 let g:clang_library_path='/usr/lib/llvm-6.0/lib/libclang.so.1'

" mappings
map <C-n> :NERDTreeToggle<CR>

set number " Show line number

set hlsearch
set incsearch

set expandtab
set tabstop=2
set shiftwidth=2

set ruler
set showcmd

set completeopt-=preview
