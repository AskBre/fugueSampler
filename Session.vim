let SessionLoad = 1
if &cp | set nocp | endif
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/Development/C++/fugueSampler
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +1 src/main.cpp
badd +1 Make
badd +9 Makefile
badd +1 Sampler.h
badd +1 Sampler.cpp
badd +126 src/Sampler.cpp
badd +36 src/Sampler.h
badd +1 Track.h
badd +1 Track.cpp
badd +1 src/SamplerTrack.cpp
badd +1 src/SamplerTrack.h
badd +1 src/MidiReader.h
badd +1 src/MidiReader.cpp
badd +2 TODO
badd +1 TODO.mk
badd +1 src/ClangDiagnostics@14
badd +1 src/ClangDiagnostics@8
badd +6 src/MidiHelper.cpp
badd +10 src/MidiHelper.h
badd +6 src/FugueSampler.cpp
badd +1 src/FugueSampler.h
badd +0 src/SamplerSample.cpp
badd +0 src/SamplerSample.h
argglobal
silent! argdel *
argadd src/main.cpp
set stal=2
edit src/main.cpp
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 16 - ((15 * winheight(0) + 64) / 129)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
16
normal! 0
lcd ~/Development/C++/fugueSampler
tabedit ~/Development/C++/fugueSampler/src/FugueSampler.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 98 + 98) / 196)
exe 'vert 2resize ' . ((&columns * 97 + 98) / 196)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 8 - ((7 * winheight(0) + 64) / 128)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
8
normal! 037|
lcd ~/Development/C++/fugueSampler
wincmd w
argglobal
edit ~/Development/C++/fugueSampler/src/FugueSampler.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 13 - ((12 * winheight(0) + 64) / 128)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
13
normal! 017|
lcd ~/Development/C++/fugueSampler
wincmd w
exe 'vert 1resize ' . ((&columns * 98 + 98) / 196)
exe 'vert 2resize ' . ((&columns * 97 + 98) / 196)
tabedit ~/Development/C++/fugueSampler/src/Sampler.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 98 + 98) / 196)
exe '2resize ' . ((&lines * 121 + 65) / 131)
exe 'vert 2resize ' . ((&columns * 97 + 98) / 196)
exe '3resize ' . ((&lines * 6 + 65) / 131)
exe 'vert 3resize ' . ((&columns * 97 + 98) / 196)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 64) / 128)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
lcd ~/Development/C++/fugueSampler
wincmd w
argglobal
edit ~/Development/C++/fugueSampler/src/Sampler.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 31 - ((30 * winheight(0) + 60) / 121)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
31
normal! 0
lcd ~/Development/C++/fugueSampler
wincmd w
argglobal
edit ~/Development/C++/fugueSampler/src/ClangDiagnostics@8
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 3) / 6)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
lcd ~/Development/C++/fugueSampler/src
wincmd w
exe 'vert 1resize ' . ((&columns * 98 + 98) / 196)
exe '2resize ' . ((&lines * 121 + 65) / 131)
exe 'vert 2resize ' . ((&columns * 97 + 98) / 196)
exe '3resize ' . ((&lines * 6 + 65) / 131)
exe 'vert 3resize ' . ((&columns * 97 + 98) / 196)
tabedit ~/Development/C++/fugueSampler/src/SamplerSample.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 98 + 98) / 196)
exe 'vert 2resize ' . ((&columns * 97 + 98) / 196)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 64) / 128)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
lcd ~/Development/C++/fugueSampler
wincmd w
argglobal
edit ~/Development/C++/fugueSampler/src/SamplerSample.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 64) / 128)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
lcd ~/Development/C++/fugueSampler
wincmd w
2wincmd w
exe 'vert 1resize ' . ((&columns * 98 + 98) / 196)
exe 'vert 2resize ' . ((&columns * 97 + 98) / 196)
tabedit ~/Development/C++/fugueSampler/Makefile
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 97 + 98) / 196)
exe 'vert 2resize ' . ((&columns * 98 + 98) / 196)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 9 - ((8 * winheight(0) + 64) / 128)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
9
normal! 0
lcd ~/Development/C++/fugueSampler
wincmd w
argglobal
edit ~/Development/C++/fugueSampler/TODO.mk
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 2 - ((1 * winheight(0) + 64) / 128)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
2
normal! 027|
lcd ~/Development/C++/fugueSampler
wincmd w
exe 'vert 1resize ' . ((&columns * 97 + 98) / 196)
exe 'vert 2resize ' . ((&columns * 98 + 98) / 196)
tabnext 4
set stal=1
if exists('s:wipebuf')
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToOc
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
