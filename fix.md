## commit 147953c2de153fcc75f282f2beb3e1037c9c5ae2
```
minishell$ git add src/env_add.c
==431159== Invalid read of size 1
==431159==    at 0x403AE5: check_quotes (check.c:28)
==431159==    by 0x403E86: check (check.c:91)
==431159==    by 0x4013EA: main (main.c:79)
==431159==  Address 0x4bb6117 is 0 bytes after a block of size 23 alloc'd
==431159==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==431159==    by 0x48ADBAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==431159==    by 0x488B694: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==431159==    by 0x4895D2A: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==431159==    by 0x4013D4: main (main.c:73)
==431159==
==431159== Invalid read of size 1
==431159==    at 0x403AE5: check_quotes (check.c:28)
==431159==    by 0x403F18: check (check.c:103)
==431159==    by 0x4013EA: main (main.c:79)
==431159==  Address 0x4bb6117 is 0 bytes after a block of size 23 alloc'd
==431159==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==431159==    by 0x48ADBAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==431159==    by 0x488B694: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==431159==    by 0x4895D2A: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==431159==    by 0x4013D4: main (main.c:73)
==431159==
```

PAS DE CHEVRONS
<ENTER> seul -> mauvais message erreur
CTRL C -> PETER
CTRL \ dans commande bloquante -> "^\Quit (core dumped)"
write pas protect dans echo (bash: echo: write error: No space left on device)
echo | echo -> new line
echo -> tu peux mettre plusieurs -n

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

``` #FIXED
minishell$ /bin/fewfwef
/bin/fewfwef: No such file or directory
/bin/fewfwef: command not found
```

``` #FIXED
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

``` #FIXED
minishell$ export a=p
minishell$ export b=w
minishell$ export c=d
minishell$ $a$b$c
(null): command not found
```

```
minishell$ export a="s -a"
minishell: export: `-a': not a valid identifier
```