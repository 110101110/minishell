# Minishell for 42 school
a shell-like program that handles:
-	pipe: '|'
-	redirection:  '<', '>', '>>"
-	heredoc: '<<'
-	signals: ctrl-c, ctrl-d, ctrl-\
-	meta characters interpreted: single, double quote and dollar sign (for variables and exit code)
-	builtin functions: echo, cd, pwd, export, unset, env & exit

To run:
-	clone the repository, run "make" inside the repo
-	./minishell
