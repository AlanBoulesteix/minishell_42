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