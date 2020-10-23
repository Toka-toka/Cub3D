/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedric <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 22:37:06 by sedric            #+#    #+#             */
/*   Updated: 2020/10/22 22:37:08 by sedric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	space_surround(t_settings *set, int i, int ii)
{
	if (set->map[i + 1] != NULL)
	{
		if (set->map[i + 1][ii] != '1' && set->map[i + 1][ii] != ' ')
			error("The map is not closed\n", set);
	}
	if (set->map[i - 1][ii] != '1' && set->map[i - 1][ii] != ' ')
		error("The map is not closed\n", set);
	if (set->map[i][ii + 1] != '1' && set->map[i][ii + 1] != ' ')
		error("The map is not closed\n", set);
	if (ii > 0)
	{
		if (set->map[i][ii - 1] != '1' && set->map[i][ii - 1] != ' ')
			error("The map is not closed\n", set);
	}
}

void	pars_plr(t_settings *set, int i, int ii)
{
	if (set->plr->pov != 0)
		error("Double camera plase\n", set);
	set->plr->x = ii * CBSZ + CBSZ / 2;
	set->plr->y = i * CBSZ + CBSZ / 2;
	if (set->map[i][ii] == 'N')
		set->plr->pov = M_PI / 2;
	if (set->map[i][ii] == 'S')
		set->plr->pov = M_PI * 3 / 2;
	if (set->map[i][ii] == 'E')
		set->plr->pov = 2 * M_PI;
	if (set->map[i][ii] == 'W')
		set->plr->pov = M_PI;
	set->map[i][ii] = '0';
}

void	map_chek(char **map, int i, int ii, t_settings *set)
{
	while (map[i] != NULL)
	{
		ii = 0;
		while (map[i][ii + 1] != '\0')
		{
			if (map[i][ii] == '1' || map[i][ii] == '0')
				ii++;
			else if (map[i][ii] == '2')
				new_sprite(i, ii++, set);
			else if (map[i][ii] == ' ')
				space_surround(set, i, ii++);
			else if (ft_strchr("NSEW", map[i][ii]))
				pars_plr(set, i, ii++);
			else
				error("Invalid symbol in map\n", set);
		}
		i++;
	}
	if (set->plr->pov == 0)
		error("No camera plase\n", set);
}

void	pars_map(t_settings *set, int len_max, int lists, t_list *head)
{
	int		i;
	t_list	*temp;

	set->map = (char**)malloc((lists + 1) * sizeof(char *));
	i = 0;
	while (i <= lists)
	{
		if ((head->content[head->len - 1] != '1' && head->content[head->len - 1] != ' ') ||
			(head->content[0] != ' ' && head->content[0] != '1'))
			error("The map is not closed\n", set);
		if (head->content[0] == '\0')
			error("Empty line in map\n", set);
		set->map[i] = (char*)ft_calloc((len_max + 1), sizeof(char ));
		set->map[i] = ft_memcpy(set->map[i], head->content, head->len);
		temp = head;
		head = head->next;
		free(temp->content);
		free(temp);
		i++;
	}
	set->max_x = len_max - 1;
	set->max_y = lists;
	set->map[i] = NULL;
	len_max = 0;
	while (set->map[i - 1][len_max] != '\0')
	{
		if (set->map[i - 1][len_max] == '1' || set->map[i - 1][len_max] == ' ')
			len_max++;
		else
			error("The last line of a map is invalid\n", set);
	}
	map_chek(set->map, 1, 0, set);
}

void	read_map(int fd, t_settings *settings, char *line)
{
	t_list	*head;
	t_list	*temp;
	int		i;
	int		len_max;

	i = 1;
	if ((head = new_list((void *)line)) == NULL)
		error("Malloc problem (fn_read_map)", settings);
	len_max = ft_strlen(line);
	head->len = len_max;
	temp = head;
	while (get_next_line(fd, &line) == 1)
	{
		if ((temp->next = new_list((void *)line)) == NULL)
			error("Malloc problem (fn_read_map)", settings);
		temp = temp->next;
		temp->len = ft_strlen(line);
		len_max = len_max > temp->len ? len_max : temp->len;
		i++;
	}
	temp->next = new_list((void *)line);
	temp = temp->next;
	temp->len = ft_strlen(line);
	close(fd);
	pars_map(settings, len_max, i, head);
}
