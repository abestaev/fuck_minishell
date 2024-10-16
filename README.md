# fuck_minishell
fuck minishell


rouge parsing / noir exec

![minishellroadmap(1)](https://github.com/abestaev/fuck_minishell/assets/104198097/128f6e93-dc21-4747-8212-9fe74a26e367)


---
rajouter : close(minishell->old_fd[0]), close(minishell->old_fd[1]) 
partout ou on ferme le programme + fork

rajouter : tous les messages d'erreur

exemple : 
	waidojiaowjioaw : command not found
	./awdawdawdawdawaw : file not found
	/aiowjdioawadwwdaw/awdawdaw : file not found
	./test (pas read ou pas execute perm dessus) : permission denied

quand exit : garder le code status de la derniere commande si pas dargument

ctrl c = code a 130
ctrl c commande = code a 130

echo exit | exit
ne doit rien afficher (regarder les forks)