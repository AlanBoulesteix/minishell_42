# minishell

   _____         _     _    _ _______   ____  ______         _    _    _____  ____   _____ _____
  / ____|  /\   | |   | |  | |__   __| |  _ \|  ____|   /\  | |  | |  / ____|/ __ \ / ____/ ____|
 | (___   /  \  | |   | |  | |  | |    | |_) | |__     /  \ | |  | | | |  __| |  | | (___| (___
  \___ \ / /\ \ | |   | |  | |  | |    |  _ <|  __|   / /\ \| |  | | | | |_ | |  | |\___ \\___ \
  ____) / ____ \| |___| |__| |  | |    | |_) | |____ / ____ \ |__| | | |__| | |__| |____) |___) |
 |_____/_/    \_\______\____/   |_|    |____/|______/_/    \_\____/   \_____|\____/|_____/_____/

# ROADMAP

- parsing
	- parsing
#iL FAUT SPLIT CHAQUE MOT CE QUI GENERE DES TOKEN, IL FAUT CHECKER SELON LE
	CHAR
	- lexing



- builtin functions
	- custom printf for stdout
- input and output redirections
	- input
	- output
- env
	`env -i ./minishell`

- @TODOs
- verif every malloc fail error
- verif weird cases : weird_cases.md
- verif `./minishell ./minishell ; cd dir ; exit` does not affect current dir of the first shell
- verif exit (maybe not the best solution to exit)
