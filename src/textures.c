/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 13:01:09 by cbesse            #+#    #+#             */
/*   Updated: 2019/08/08 18:49:12 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	read_header(char *filename, t_text *texture)
{
	int	fd;
	int bpp;

	bpp = 0;
	if ((fd = open(filename, O_RDONLY)) == -1)
		exit(1);
	lseek(fd, 18, SEEK_SET);
	read(fd, &texture->width, 4);
	read(fd, &texture->height, 4);
	lseek(fd, 2, SEEK_CUR);
	read(fd, &bpp, 2);
	close(fd);
	texture->opp = bpp / 8;
	texture->line_size = texture->width * texture->opp;
	texture->width < 0 ? texture->width = -texture->width : 0;
	texture->height < 0 ? texture->height = -texture->height : 0;
	texture->size = texture->line_size * texture->height;
}

void	get_image(t_text *texture, char *temp, int i)
{
	int	h;
	int	j;
	int	size;

	h = 0;
	size = texture->size * 2;
	texture->img = (unsigned char*)ft_memalloc(sizeof(unsigned char) * size);
	while (i > 0)
	{
		i -= texture->line_size;
		j = 0;
		while (j < texture->line_size)
		{
			texture->img[h + j] = (unsigned char)temp[i + j + 2];
			texture->img[h + j + 1] = (unsigned char)temp[i + j + 1];
			texture->img[h + j + 2] = (unsigned char)temp[i + j];
			j += 3;
		}
		h += texture->line_size;
	}
}

void	load_bmp(t_text *text, char *filename)
{
	int		fd;
	int		i;
	char	*temp;

	read_header(filename, text);
	temp = (char*)ft_memalloc(sizeof(char) * text->size + 1);
	if ((fd = open(filename, O_RDONLY)) == -1)
		exit(1);
	lseek(fd, 54, SEEK_SET);
	i = read(fd, temp, text->size);
	get_image(text, temp, i);
	ft_strdel((char**)&temp);
	close(fd);
}
