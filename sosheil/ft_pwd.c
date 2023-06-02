/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlc_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:34:18 by tpicoule          #+#    #+#             */
/*   Updated: 2023/06/01 11:35:41 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_pwd(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == 'p' && str[i + 1] == 'w' && str[i + 2] == 'd'
		&& (str[i + 3] == ' ' || str[i + 3] == '\0'))
		return (0);
	return (1);
}

char	*ft_strdup(char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * len(s1) + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	other_check(t_node *tmp)						//FONCTION PRINCIPALE A RAJOUTER AU PARSER
{
	char	buffer[BUFFER_SIZE];

	if (getcwd(buffer, BUFFER_SIZE) == NULL)
		return ;
	if (tmp->prev == NULL)
	{
		if (check_pwd(tmp->str) == 0)
			tmp->str = ft_strdup(getcwd(buffer, BUFFER_SIZE));
	}
	else if (tmp->prev->type == piperino && check_pwd(tmp->str) == 0)
		tmp->str = ft_strdup(getcwd(buffer, BUFFER_SIZE));
	return ;
}
