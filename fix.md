# TODO
+ PAS DE CHEVRONS

```
unset PWD -> touche pas a OLDPWD
cd .. -> met OLDPWD dans le export (enleve la valeur a OLDPWD)
env | grep PWD -> ni OLDPWD ni PWD
cd /42_minishell
env | grep PWD -> OLDPWD reset
```
TODO (line 37) Execve: Permission denied

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
minishell$ ls | a
a: command not found
minishell$ echo $?
32512
```

```
aboulest@e2r11p17:~/Documents/42_cursus/4_cercle/minishell/minishell_42$ ls>$PWD
bash: /mnt/nfs/homes/aboulest/Documents/42_cursus/4_cercle/minishell/minishell_42: Is a directory
```

### need only one `minishell$`
```
minishell$ ls | sleep 500 || echo coucou
^C
minishell$
minishell$
```

### ???
```
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


```
minishell$ cd
bash: cd: too many arguments
```

```
minishell$ minishell$ echo $?
2
```

```
minishell$ exit 1 1
bash: exit: too many arguments
```

exit must print exit

guillemets dans le export

minishell$ (ls&&ls)(ls&&ls) -> syntax error

minishell$ export 1 -> bash: export: `1': not a valid identifier

```
minishell$ export a="s -a"
minishell: export: `-a': not a valid identifier
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

+ env in fork -> SHLVL -1

# FIXED
+ <ENTER> seul -> mauvais message erreur
+ write pas protect dans echo (bash: echo: write error: No space left on device)
+ echo | echo -> new line
+ echo -> tu peux mettre plusieurs -n

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