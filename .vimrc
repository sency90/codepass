" Specify a directory for plugins
" - For Neovim: stdpath('data') . '/plugged'
" - Avoid using standard Vim directory names like 'plugin'
call plug#begin('~/.vim/plugged')

" Make sure you use single quotes

" Shorthand notation; fetches https://github.com/junegunn/vim-easy-align
Plug 'junegunn/vim-easy-align'

" Any valid git URL is allowed
Plug 'https://github.com/junegunn/vim-github-dashboard.git'

" Multiple Plug commands can be written in a single line using | separators
Plug 'SirVer/ultisnips' | Plug 'honza/vim-snippets'

" On-demand loading
Plug 'scrooloose/nerdtree', { 'on':  'NERDTreeToggle' }
Plug 'tpope/vim-fireplace', { 'for': 'clojure' }

" Using a non-default branch
Plug 'rdnetto/YCM-Generator', { 'branch': 'stable' }

" Using a tagged release; wildcard allowed (requires git 1.9.2 or above)
Plug 'fatih/vim-go', { 'tag': '*' }

" Plugin options
Plug 'nsf/gocode', { 'tag': 'v.20150303', 'rtp': 'vim' }

" Plugin outside ~/.vim/plugged with post-update hook
Plug 'junegunn/fzf', { 'dir': '~/.fzf', 'do': './install --all' }

" Unmanaged plugin (manually installed and updated)
Plug '~/my-prototype-plugin'

Plug 'vim-syntastic/syntastic'
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'

" Initialize plugin system
call plug#end()

set cindent
set smartindent
set ts=4
set shiftwidth=4
set nu
set nowrap
colorscheme peachpuff
set hlsearch
set noerrorbells "경고음을 끈다.
set novisualbell "시각적 경고를 끈다.
set t_vb= "터미널 경고음을 무효화한다.

" syntastic settings
let g:syntastic_cpp_checkers = ['gcc']
let g:syntastic_cpp_compiler_options = ' -std=c++17'

" vim -alirline settings
let g:airline#extensions#tabline#enabled = 1
let g:airline_powerline_fonts = 1
let g:airline#extensions#tabline#fnamemod = ':t'
let g:airline#extensions#tabline#formatter = 'unique_tail'
let g:airline_theme='wombat'

" shortkey settings
nnoremap <F3> :NERDTreeToggle<CR>
nnoremap <F2> :call TogglePasteMode()<CR>

function! TogglePasteMode()
	if &paste
		set nopaste
		echo "Past mode OFF"
	else
		set paste
		echo "Paste mode ON"
	endif
endfunction

let NERDTreeShowHidden=1

"Ctrl + t
nnoremap <C-t> :tabnew<CR>
cnoremap <C-t> :tabnew<CR>
tnoremap <C-t> <C-\><C-n>:tabnew<CR>

"Ctrl + <-
nnoremap <C-Left> :tabprev<CR>
cnoremap <C-Left> :tabprev<CR>
tnoremap <C-Left> <C-\><C-n>:tabprev<CR>

"Ctrl + ->
nnoremap <C-Right> :tabnext<CR>
cnoremap <C-Right> :tabnext<CR>
tnoremap <C-Right> <C-\><C-n>:tabnext<CR>

"F4
tnoremap <F4> <C-\><C-n>

