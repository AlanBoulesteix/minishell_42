# TODO

minishell$ ''>''
minishell: : No such file or directory
: command not found

vlepille@paul-f3Br7s5:~/Documents/common-core/minishell$ ls >" "
vlepille@paul-f3Br7s5:~/Documents/common-core/minishell$ ls >""
bash: : No such file or directory
vlepille@paul-f3Br7s5:~/Documents/common-core/minishell$ export tg=" "
vlepille@paul-f3Br7s5:~/Documents/common-core/minishell$ ls >a$tg
vlepille@paul-f3Br7s5:~/Documents/common-core/minishell$ ls >$tg-
vlepille@paul-f3Br7s5:~/Documents/common-core/minishell$ ls >$tg$tg
bash: $tg$tg: ambiguous redirect

```
Enbigous redirection a gerer
export a="ls -l"
ls >$a
bash: $a: ambiguous redirect
```


>a$"
segfault

minishell$ ''>
==1105322== Invalid write of size 4
==1105322==    at 0x40669B: find_redir (token.c:47)
==1105322==    by 0x406AA9: tokenization (token.c:134)
==1105322==    by 0x406D4E: init_commande (create_cmd.c:59)
==1105322==    by 0x405C40: exec_cmd (execution.c:84)
==1105322==    by 0x406361: exec_block (execution.c:227)
==1105322==    by 0x40138A: exec_input (main.c:40)
==1105322==    by 0x4014EF: main (main.c:77)
==1105322==  Address 0x4b7c7d8 is 16 bytes after a block of size 24 alloc'd
==1105322==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1105322==    by 0x403924: my_malloc (utils_garbage.c:101)
==1105322==    by 0x40696E: tokenization (token.c:116)
==1105322==    by 0x406D4E: init_commande (create_cmd.c:59)
==1105322==    by 0x405C40: exec_cmd (execution.c:84)
==1105322==    by 0x406361: exec_block (execution.c:227)
==1105322==    by 0x40138A: exec_input (main.c:40)
==1105322==    by 0x4014EF: main (main.c:77)
==1105322==
==1105322== Invalid write of size 8
==1105322==    at 0x406AD1: tokenization (token.c:135)
==1105322==    by 0x406D4E: init_commande (create_cmd.c:59)
==1105322==    by 0x405C40: exec_cmd (execution.c:84)
==1105322==    by 0x406361: exec_block (execution.c:227)
==1105322==    by 0x40138A: exec_input (main.c:40)
==1105322==    by 0x4014EF: main (main.c:77)
==1105322==  Address 0x4b7c7c8 is 0 bytes after a block of size 24 alloc'd
==1105322==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1105322==    by 0x403924: my_malloc (utils_garbage.c:101)
==1105322==    by 0x40696E: tokenization (token.c:116)
==1105322==    by 0x406D4E: init_commande (create_cmd.c:59)
==1105322==    by 0x405C40: exec_cmd (execution.c:84)
==1105322==    by 0x406361: exec_block (execution.c:227)
==1105322==    by 0x40138A: exec_input (main.c:40)
==1105322==    by 0x4014EF: main (main.c:77)
==1105322==
==1105322== Invalid write of size 4
==1105322==    at 0x406AE6: tokenization (token.c:136)
==1105322==    by 0x406D4E: init_commande (create_cmd.c:59)
==1105322==    by 0x405C40: exec_cmd (execution.c:84)
==1105322==    by 0x406361: exec_block (execution.c:227)
==1105322==    by 0x40138A: exec_input (main.c:40)
==1105322==    by 0x4014EF: main (main.c:77)
==1105322==  Address 0x4b7c7dc is 20 bytes after a block of size 24 alloc'd
==1105322==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1105322==    by 0x403924: my_malloc (utils_garbage.c:101)
==1105322==    by 0x40696E: tokenization (token.c:116)
==1105322==    by 0x406D4E: init_commande (create_cmd.c:59)
==1105322==    by 0x405C40: exec_cmd (execution.c:84)
==1105322==    by 0x406361: exec_block (execution.c:227)
==1105322==    by 0x40138A: exec_input (main.c:40)
==1105322==    by 0x4014EF: main (main.c:77)
==1105322==
: command not found


# ?????
<<"" "" <<""

# that exit
minishell$ <<eof cat | export

ajouter des frees

```bash
export l'=$cmd
```
com : premier lancement

export test="

!surrended
(echo a) > b

try malloc fail de get_path et tout le tointoin

!surrended
+ cd in linked directory fail

____________________________________________________________________________________________________________

# FIXED
+ <ENTER> seul -> mauvais message erreur
+ write pas protect dans echo (bash: echo: write error: No space left on device)
+ echo | echo -> new line
+ echo -> tu peux mettre plusieurs -n
+ minishell$ (ls&&ls)(ls&&ls) -> syntax error

```
minishell$ export a="s -a"
minishell: export: `-a': not a valid identifier
```


```
aboulest@e2r11p17:~/Documents/42_cursus/4_cercle/minishell/minishell_42$ ls>$PWD
bash: /mnt/nfs/homes/aboulest/Documents/42_cursus/4_cercle/minishell/minishell_42: Is a directory
```

```
minishell$ export a=p
minishell$ export b=w
minishell$ export c=d
minishell$ $a$b$c
(null): command not found
```

```
minishell$ /bin/fewfwef
/bin/fewfwef: No such file or directory
/bin/fewfwef: command not found
```

```
minishell$ export $USER=$axel$USER
```

+ minishell$ echo $Sfewfw,el

+ minishell$ echo $PWD$USER

```
bash
exit 42
echo $? -> 0
```

+ CTRL C -> PETER quand minishell dans minishell
+ CTRL \ dans commande bloquante -> "^\Quit (core dumped)"

```
unset PWD -> touche pas a OLDPWD
cd .. -> met OLDPWD dans le export (enleve la valeur a OLDPWD)
env | grep PWD -> ni OLDPWD ni PWD
cd /42_minishell
env | grep PWD -> OLDPWD reset
```

TODO (line 37) Execve: Permission denied

```
minishell$ cd
bash: cd: too many arguments
```

```
minishell$ ls | a
a: command not found
minishell$ echo $?
32512
```

```
vlepille@paul-f3Ar6s7:~$ env -i bash
vlepille@paul-f3Ar6s7:/mnt/nfs/homes/vlepille$ cd
bash: cd: HOME not set
vlepille@paul-f3Ar6s7:/mnt/nfs/homes/vlepille$ unset OLDPWD
vlepille@paul-f3Ar6s7:/mnt/nfs/homes/vlepille$ cd -
bash: cd: OLDPWD not set
vlepille@paul-f3Ar6s7:/mnt/nfs/homes/vlepille$
```

```
minishell$ exit 1 1
bash: exit: too many arguments
```

exit must print exit

guillemets dans le export

export =

export 123

```bash
exit dit pas exit # pas bien
```

exit hello

```bash
exit 9223372036854775807 # bien
exit 9223372036854775808 # pas bien
exit -9223372036854775808 # bien
exit -9223372036854775809 # pas bien
```

``` bash
echo $1caca-pipi # caca-pipi
echo $caca-pipi # -pipi
```

```
minishell$ git add .
minishell$ git commit -m "Add he bug on SHLVL to env function in fork"
error: pathspec 'he' did not match any file(s) known to git
error: pathspec 'bug' did not match any file(s) known to git
error: pathspec 'on' did not match any file(s) known to git
error: pathspec 'SHLVL' did not match any file(s) known to git
error: pathspec 'to' did not match any file(s) known to git
error: pathspec 'env' did not match any file(s) known to git
error: pathspec 'function' did not match any file(s) known to git
error: pathspec 'in' did not match any file(s) known to git
error: pathspec 'fork' did not match any file(s) known to git
```

```bash
minishell$ (ls)
minishell: syntax error near unexpected token `('
minishell$ (ls && ls)
minishell: syntax error near unexpected token `('
minishell$ (exit)
minishell: syntax error near unexpected token `('
minishell$ ()()
minishell: syntax error near unexpected token `('
minishell$ (ls)(ls)
minishell: syntax error near unexpected token `('
minishell$ (
minishell: syntax error near unexpected token `('
minishell$ ()
```

(exit 42)
echo $? -> 42


### need only one `minishell$`
```bash
minishell$ ls | sleep 500 || echo coucou
^C
minishell$
minishell$
```

+ env in fork -> SHLVL -1

```bash
sleep 500 | (sleep 500 | sleep 500) || echo coucou
```

### ???
```bash
vlepille@e2r11p18:~/Documents/common-core/minishell$ ls | sleep 500 || echo coucou
^C
vlepille@e2r11p18:~/Documents/common-core/minishell$ ls | (exit 0) || echo coucou
vlepille@e2r11p18:~/Documents/common-core/minishell$ ls | (exit 500) || echo coucou
coucou
vlepille@e2r11p18:~/Documents/common-core/minishell$ ls | sleep 500
^C
vlepille@e2r11p18:~/Documents/common-core/minishell$ echo $?
130

#HELP:#
vlepille@e2r11p18:~/Documents/common-core/minishell$ sleep 2 || echo coucou
^C
vlepille@e2r11p18:~/Documents/common-core/minishell$ echo $?
130

###AND###

vlepille@e2r11p18:~/Documents/common-core/minishell$ sleep 2 || echo coucou
vlepille@e2r11p18:~/Documents/common-core/minishell$ sleep 2 || echo coucou
^C
vlepille@e2r11p18:~/Documents/common-core/minishell$ sleep 2
^C
vlepille@e2r11p18:~/Documents/common-core/minishell$ echo $?
130

###AND###
vlepille@e2r11p18:~/Documents/common-core/minishell$ ps -aux | grep sleep
vlepille 1230598  0.0  0.0   8140  1004 pts/2    S+   19:25   0:00 sleep 500
vlepille 1230618  0.0  0.0   8848  2236 pts/1    S+   19:25   0:00 grep sleep
vlepille@e2r11p18:~/Documents/common-core/minishell$ kill -USR1 1230598
#in parrallel#
vlepille@e2r11p18:~/Documents/common-core/minishell$ sleep 500 || echo coucou
User defined signal 1
coucou
```
```bash
minishell$ ()
(): command not found
```
#### mot[0] == 'e' && mot[1] == 'x' && mot[2] == 'p' && mot[3] == 'o' && mot[4] == 'r' && mot[5] == 't' && mot[6].is_delimiter()
``` bash
export a="ls -al"
export"" c=$a
INVALID ARG -al
export c=$a
```

```
minishell$ """" : SEGFAULT
minishell$ '''' : SEGFAULT
''e -> SEGFAULT
"$USER"e -> SEGFAULT
```

```
minishell$ <<a<<b
==813366== Invalid write of size 1
==813366==    at 0x408924: expend_quote (heredoc.c:66)
==813366==    by 0x408958: heredoc (heredoc.c:79)
==813366==    by 0x408289: open_heredoc (redirection.c:80)
==813366==    by 0x404863: get_blocks (tree.c:69)
==813366==    by 0x40137D: exec_input (main.c:39)
==813366==    by 0x4014EF: main (main.c:77)
==813366==  Address 0x4b6aa41 is 0 bytes after a block of size 1 alloc'd
==813366==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==813366==    by 0x403924: my_malloc (utils_garbage.c:101)
==813366==    by 0x40886E: expend_quote (heredoc.c:53)
==813366==    by 0x408958: heredoc (heredoc.c:79)
==813366==    by 0x408289: open_heredoc (redirection.c:80)
==813366==    by 0x404863: get_blocks (tree.c:69)
==813366==    by 0x40137D: exec_input (main.c:39)
==813366==    by 0x4014EF: main (main.c:77)


>
>
>
>
> s
>
>
>
>
> b
>
> r
>
>
> a
==813374== Invalid read of size 1
==813374==    at 0x402D65: ft_streq (utils_str.c:18)
==813374==    by 0x408A1A: heredoc (heredoc.c:99)
==813374==    by 0x408289: open_heredoc (redirection.c:80)
==813374==    by 0x404863: get_blocks (tree.c:69)
==813374==    by 0x40137D: exec_input (main.c:39)
==813374==    by 0x4014EF: main (main.c:77)
==813374==  Address 0x4b6aa41 is 0 bytes after a block of size 1 alloc'd
==813374==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==813374==    by 0x403924: my_malloc (utils_garbage.c:101)
==813374==    by 0x40886E: expend_quote (heredoc.c:53)
==813374==    by 0x408958: heredoc (heredoc.c:79)
==813374==    by 0x408289: open_heredoc (redirection.c:80)
==813374==    by 0x404863: get_blocks (tree.c:69)
==813374==    by 0x40137D: exec_input (main.c:39)
==813374==    by 0x4014EF: main (main.c:77)

```

```
minishell$ |ls
build  fix.md  includes  lib  Makefile	minishell  README.md  src  TODO
```

```
minishell$ echo $0"&&&&"
minishell: syntax error near unexpected token `&&'
indice lettre colle direct
```

```
minishell$ <<$
==815073== Invalid write of size 1
==815073==    at 0x408924: expend_quote (heredoc.c:66)
==815073==    by 0x408958: heredoc (heredoc.c:79)
==815073==    by 0x408289: open_heredoc (redirection.c:80)
==815073==    by 0x404863: get_blocks (tree.c:69)
==815073==    by 0x40137D: exec_input (main.c:39)
==815073==    by 0x4014EF: main (main.c:77)
==815073==  Address 0x4b70561 is 0 bytes after a block of size 1 alloc'd
==815073==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==815073==    by 0x403924: my_malloc (utils_garbage.c:101)
==815073==    by 0x40886E: expend_quote (heredoc.c:53)
==815073==    by 0x408958: heredoc (heredoc.c:79)
==815073==    by 0x408289: open_heredoc (redirection.c:80)
==815073==    by 0x404863: get_blocks (tree.c:69)
==815073==    by 0x40137D: exec_input (main.c:39)
==815073==    by 0x4014EF: main (main.c:77)
```

```bash
minishell$ export | export
==813684== Invalid read of size 1
==813684==    at 0x408E9E: expend_size (expender_var.c:75)
==813684==    by 0x409362: expend_var (expender_var.c:189)
==813684==    by 0x406E2B: init_commande (create_cmd.c:57)
==813684==    by 0x405C40: exec_cmd (execution.c:84)
==813684==    by 0x406361: exec_block (execution.c:227)
==813684==    by 0x40138A: exec_input (main.c:40)
==813684==    by 0x405EB7: pipe_child (execution.c:129)
==813684==    by 0x40605B: exec_pipe (execution.c:166)
==813684==    by 0x406381: exec_block (execution.c:232)
==813684==    by 0x40138A: exec_input (main.c:40)
==813684==    by 0x4014EF: main (main.c:77)
==813684==  Address 0x4b6a2c8 is 0 bytes after a block of size 8 alloc'd
==813684==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==813684==    by 0x403924: my_malloc (utils_garbage.c:101)
==813684==    by 0x404914: block_dup (tree_to_tab.c:39)
==813684==    by 0x4049E4: fill_tab_block (tree_to_tab.c:54)
==813684==    by 0x4049BD: fill_tab_block (tree_to_tab.c:51)
==813684==    by 0x404A55: get_tab_block (tree_to_tab.c:68)
==813684==    by 0x405F64: exec_pipe (execution.c:155)
==813684==    by 0x406381: exec_block (execution.c:232)
==813684==    by 0x40138A: exec_input (main.c:40)
==813684==    by 0x4014EF: main (main.c:77)
==813684==
```

.

export cmd="ls -l"
export $cmd=$cmd
export -l=$cmd -> full dingz
(si not a valid identifier, le expend du export est remis comme de base)

