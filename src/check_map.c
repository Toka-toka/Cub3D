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

#include "../includes/cub3d.h"

void		space_surround(t_settings *set, int i, int ii)
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

void		map_chek(char **map, int i, int ii, t_settings *set)
{
	i = 1;
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

void		pars_map(t_settings *set, int len_max, int lists, t_list *h)
{
	int		i;
	t_list	*temp;

	set->map = (char**)malloc((lists + 1) * sizeof(char *));
	i = 0;
	while (i < lists)
	{
		set->map[i] = (char*)malloc((len_max + 1) * sizeof(char ));
		set->map[i] = ft_memset(set->map[i], ' ', len_max);
		set->map[i][len_max] = '\0';
		set->map[i] = ft_memcpy(set->map[i], h->content, h->len);
		temp = h;
		h = h->next;
		free(temp->content);
		free(temp);
		i++;
	}
	set->max_x = len_max;
	set->max_y = lists - 1;
	set->map[i] = NULL;
	len_max = 0;
	map_chek(set->map, 0, 0, set);
}

t_list		*new_map_list(t_settings *set, char *line)
{
	t_list	*new;
	int		i;

	i = 0;
	if (!(new = (t_list *)malloc(sizeof(t_list))))
		error("Malloc problem (new_map_list)", set);
	if (line[0] == '\0')
		error("Empty line in map", set);
	while (line[i] != '\0')
	{
		if (!(ft_strchr("NSEW012 ", line[i])))
			error("Wrong symbol in map", set);
		i++;
	}
	if (line[0] != ' ' && line[0] != '1')
		error("Map is not close", set);
	new->len = ft_strlen(line);
	if (line[new->len - 1] != '1' && line[new->len - 1] != ' ')
		error("Map isnt close", set);
	if (new->len > set->max_x)
		set->max_x = new->len;
	new->content = line;
	new->next = NULL;
	return (new);
}

void		read_map(int fd, t_settings *set, char *line)
{
	t_list	*head;
	t_list	*temp;
	int		i;

	i = 0;
	head = new_map_list(set, line);
	temp = head;
	while (get_next_line(fd, &line) == 1)
	{
		temp->next = new_map_list(set, line);
		temp = temp->next;
		set->max_y++;
	}
	set->max_y++;
	temp->next = new_map_list(set, line);
	while (line[i] != '\0')
	{
		if (line[i] == '1' || line[i] == ' ')
			i++;
		else
			error("The last line of a map is invalid\n", set);
	}
	close(fd);
	pars_map(set, set->max_x, set->max_y, head);
}
