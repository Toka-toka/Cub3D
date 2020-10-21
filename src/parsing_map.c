#include "../includes/cub3D.h"

t_list	*new_list(char *line)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new->content = line;
	new->next = NULL;
	return (new);
}

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

void	pars_plr(t_settings *settings, int i, int ii)
{
	if (settings->plr->pov != 0)
		error("Double camera plase\n", settings);
	settings->plr->x = ii * CBSZ + CBSZ / 2;
	settings->plr->y = i * CBSZ + CBSZ / 2;
	if (settings->map[i][ii] == 'N')
		settings->plr->pov = M_PI / 2;
	if (settings->map[i][ii] == 'S')
		settings->plr->pov = M_PI * 3 / 2;
	if (settings->map[i][ii] == 'E')
		settings->plr->pov = 2 * M_PI;
	if (settings->map[i][ii] == 'W')
		settings->plr->pov = M_PI;
	settings->map[i][ii] = '0';
}

void	map_chek(char **map, int i, int ii, t_settings *settings)
{
	while (map[i] != NULL)
	{
		ii = 0;
		while (map[i][ii + 1] != '\0')
		{
			if (map[i][ii] == '1' || map[i][ii] == '0')
				ii++;
			else if (map[i][ii] == '2')
				new_sprite(i, ii++, settings);
			else if (map[i][ii] == ' ')
				space_surround(settings, i, ii++);
			else if (ft_strchr("NSEW", map[i][ii]))
				pars_plr(settings, i, ii++);
			else
				error("Invalid symbol in map\n", settings);
		}
		i++;
	}
	if (settings->plr->pov == 0)
		error("No camera plase\n", settings);
}

void	pars_map(t_settings *settings, int len_max, int lists, t_list *head)
{
	int		i;
	t_list	*temp;

	settings->map = (char**)malloc((lists + 1) * sizeof(char *));
	i = 0;
	while (i <= lists)
	{
		if (head->content[head->len - 1] == '0' || head->content[0] == '0')
			error("The map is not closed\n", settings);
		if (head->content[0] == '\0')
			error("Empty line in map\n", settings);
		settings->map[i] = (char*)ft_calloc((len_max + 1), sizeof(char ));
		settings->map[i] = ft_memcpy(settings->map[i], head->content, head->len);
		temp = head;
		head = head->next;
		free(temp->content);
		free(temp);
		i++;
	}
	settings->max_x = len_max - 1;
	settings->max_y = lists;
	settings->map[i] = NULL;
	len_max = 0;
	while (settings->map[i - 1][len_max] != '\0')
	{
		if (settings->map[i -1][len_max] == '1' || settings->map[i -1][len_max] == ' ')
			len_max++;
		else
			error("The last line of a map is invalid\n", settings);
	}
//	settings->map[i] = NULL;
	map_chek(settings->map, 1, 0, settings);
}
