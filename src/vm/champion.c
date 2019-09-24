/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drosa-ta <drosa-ta@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:28:58 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/16 21:58:24 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/corewar.h"

static int	endian_swap(int n)
{
	void *nptr;

	nptr = &n;
	ft_swapbytes(nptr, nptr + 3);
	ft_swapbytes(nptr + 1, nptr + 2);
	return (n);
}

#define THROW_ERROR(E) return ft_error(E, -1);

static int	read_champion_header(int fd, t_champion *champion, char *filename)
{
	t_header	header;
	int			bytes_read;

	bytes_read = read(fd, &header, sizeof(t_header));
	if (bytes_read < (int)sizeof(t_header))
		THROW_ERROR("Error: Failed to read header\n");
	if (endian_swap(header.magic) != COREWAR_EXEC_MAGIC)
	{
		ft_fdprintf(2, "Error: %s is not a corewar file.\n", filename);
		return (-1);
	}
	champion->size = endian_swap(header.prog_size);
	if (champion->size > CHAMP_MAX_SIZE)
		THROW_ERROR("Error: Champion is too big!\n");
	champion->name = ft_strdup(header.prog_name);
	champion->comment = ft_strdup(header.comment);
	if (champion->name == NULL || champion->comment == NULL)
	{
		free(champion->name);
		free(champion->comment);
		return (-1);
	}
	return (0);
}

static int	read_champion_bytecode(int fd, t_champion *champion, char *filename)
{
	int bytes_read;
	int total_bytes_read;

	total_bytes_read = 0;
	while (total_bytes_read < (int)champion->size)
	{
		bytes_read = read(fd, champion->bytecode + total_bytes_read,
				champion->size - total_bytes_read);
		if (bytes_read == -1)
		{
			ft_fdprintf(2, "Read fail on %s\n", filename);
			return (-1);
		}
		else if (bytes_read == 0)
		{
			ft_fdprintf(2, "Unexpected end of file: %s\n", filename);
			return (-1);
		}
		total_bytes_read += bytes_read;
	}
	return (0);
}

t_champion	*read_champion_from_file(char *file)
{
	t_champion	*champ;
	int			fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_fdprintf(2, "Failed to open file %s\n", file);
		return (NULL);
	}
	champ = (t_champion *)malloc(sizeof(t_champion));
	if (champ == NULL)
		return (NULL);
	if (read_champion_header(fd, champ, file) == -1)
	{
		free(champ);
		return (NULL);
	}
	if (read_champion_bytecode(fd, champ, file) == -1)
	{
		free(champ);
		return (NULL);
	}
	close(fd);
	champ->filename = file;
	return (champ);
}
