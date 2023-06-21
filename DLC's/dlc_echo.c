

//fonction pour gerer plusieurs n// Envoyer l'adresse de option i pour gerer//
int	ft_option(t_node *tmp)
{
	
}

void	and_another_check(t_node *tmp)
{
	int	i;
	int	option;

	i = 0;
	option = 0;
	if ((tmp->prev == NULL && ft_strcmp(tmp->str, "echo") == 0)
		|| (tmp->prev == NULL && ft_strcmp(tmp->str, "echo") == 0))
	{
		if (tmp->next && ft_strcmp(tmp->next->str, "-n") == 0 || )
		{
			option = 1;
			tmp = tmp->next;
			//si rien apres le -n ajouter condtion ou int//
		}
		printf("option === > %d\n", option);
		if (tmp->next)
			tmp = tmp->next;
		printf("tmp === > %s\n", tmp->str);
/*  		if (tmp->next )
		{
			while (tmp ||  ft_strcmp(tmp->str, "|") != 0)
			{
				while (tmp->str[i])
				{
					puts("maga");
					write(1, &tmp->str[i], 1);
					i++;
				}
				tmp = tmp->next;
			}
		} */
		//FAIRE MARCHER CETTE BOUCLE DE MERDE//
		if (option != 0)
		{
			write(1, "\n", 1);
		}
		//puts("caca");
	}
}
