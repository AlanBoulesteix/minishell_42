# TODO
+ PAS DE CHEVRONS
+ CTRL C -> PETER
+ CTRL \ dans commande bloquante -> "^\Quit (core dumped)"

```
unset PWD
cd ..
env | grep PWD -> ni OLDPWD ni PWD
cd /42_minishell
env | grep PWD -> OLDPWD reset
```
TODO (line 37) Execve: Permission denied

```
bash
exit 42
echo $? -> 0
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

```
minishell$ cd
bash: cd: too many arguments
```

minishell$ echo $Sfewfw,el #FIXED

minishell$ echo $PWD$USER #FIXED

```
minishell$ minishell$ echo $?
2
```

```
minishell$ exit 1 1
bash: exit: too many arguments
```

```
minishell$ export $USER=$axel$USER #FIXED
```

guillemets dans le export

minishell$ (ls&&ls)(ls&&ls) -> syntax error

minishell$ export 1 -> bash: export: `1': not a valid identifier

```
minishell$ export a="s -a"
minishell: export: `-a': not a valid identifier
```

# FIXED
+ <ENTER> seul -> mauvais message erreur
+ write pas protect dans echo (bash: echo: write error: No space left on device)
+ echo | echo -> new line
+ echo -> tu peux mettre plusieurs -n

``` #FIXED
minishell$ export a=p
minishell$ export b=w
minishell$ export c=d
minishell$ $a$b$c
(null): command not found
```

``` #FIXED
minishell$ /bin/fewfwef
/bin/fewfwef: No such file or directory
/bin/fewfwef: command not found
```
