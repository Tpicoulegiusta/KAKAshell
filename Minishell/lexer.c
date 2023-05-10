/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:03:13 by tpicoule          #+#    #+#             */
/*   Updated: 2023/05/10 17:05:56 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Fonction pour traiter la chaine de caractere contenue dans le prompt, check les "|" et les ";",
//On doit recuperer la chaine de cara du prompt, checker si il y a des "|" ou ";", si il y en a 
//on ajoute des espaces avant et/ou apres pour pouvoir split la chaine une fois traitée  

void	check_double(char *prompt)
{
	int	i;

	i = 0;
	while(prompt[i])
	{
		if (prompt[i] == '|' && prompt[i + 1] == '|')
			return (write(2, "syntax error Bonus\n", 19));
	}
}

char	*check_bef(char *prompt, int i)
{
	char	*cpy;
	int		j;
	
	j = 0;
	if (prompt[i - 1] == ' ')
		return (prompt);
	cpy = prompt;
	while (prompt[j])
		j++;
	while (j != i)
	{
		
	}
	cpy[j] == ' ';
	while (prompt[j])
	{
		cpy[j] = prompt[j];
		j++;
	}
	cpy[j] = '\0';
	return (cpy);
}

char	*check_aft(char *prompt, int i)
{
	char	*cpy;
	int		j;
	
	j = 0;
	if (prompt[i + 1] == ' ')
		return (prompt);
	cpy = prompt;
	while (j != i)
	{
		cpy[j] = prompt[j];
		j++;
	}
	cpy[j] == ' ';
	while (prompt[j])
	{
		cpy[j] = prompt[j];
		j++;
	}
	cpy[j] = '\0';
	return (cpy);	
}

char *test(char *prompt)
{
	int	i;

	i = 0;
	check_double(prompt);
	while(prompt[i])
	{
		if (prompt[i] == '|' || prompt[i] == ';')
		{
			prompt = check_bef(prompt, i);
			prompt = check_aft(prompt, i);
			i++;
		}
		i++;
	}
	return(test);
}