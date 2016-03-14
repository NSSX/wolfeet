/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 16:43:07 by avella            #+#    #+#             */
/*   Updated: 2016/03/14 16:48:30 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	hit_or_no(t_inwolf *w, t_struct *mystruct)
{
	while (w->hit == 0)
	{
		if (w->sideDistX < w->sideDistY)
		{
			w->sideDistX += w->deltaDistX;
			w->mapX += w->stepX;
			w->side = 0;
		}
		else
		{
			w->sideDistY += w->deltaDistY;
			w->mapY += w->stepY;
			w->side = 1;
		}
		if (mystruct->worldMap[w->mapX][w->mapY] > 0)
			w->hit = 1;
	}
	if (w->side == 0)
		w->perpWallDist = (w->mapX - w->rayPosX +
				(1 - w->stepX) / 2) / w->rayDirX;
	else
		w->perpWallDist = (w->mapY - w->rayPosY +
				(1 - w->stepY) / 2) / w->rayDirY;
}

void	last_var_give(t_inwolf *w)
{
	w->lineHeight = (int)(HEIGHT / w->perpWallDist);
	w->drawStart = -w->lineHeight / 2 + HEIGHT / 2;
	if (w->drawStart < 0)
		w->drawStart = 0;
	w->drawEnd = w->lineHeight / 2 + HEIGHT / 2;
	if (w->drawEnd >= HEIGHT)
	{
		w->drawEnd = HEIGHT - 1;
	}
	else if (w->drawEnd <= 0)
	{
		w->drawEnd = 1;
	}
}

void	color_choice_yes(t_inwolf *w, t_struct *mystruct)
{
	w->color = 0;
	if (mystruct->worldMap[w->mapX][w->mapY] == 1)
		w->color = 0xFF0000;
	else if (mystruct->worldMap[w->mapX][w->mapY] == 2)
		w->color = 0xFFFFFF;
	else if (mystruct->worldMap[w->mapX][w->mapY] == 3)
		w->color = 0x0045FF;
	else if (mystruct->worldMap[w->mapX][w->mapY] == 4)
		w->color = 0xFFFFFF;
	else if (mystruct->worldMap[w->mapX][w->mapY] == 9)
		w->color = 0x000000;
	else
		w->color = 0x00FFFF;
	if (w->side == 1)
		w->color = w->color / 2;
}

void	side_used(t_inwolf *w, t_struct *mystruct)
{
	if (mystruct->worldMap[w->mapX][w->mapY] == 8)
	{
		if (w->side == 0)
		{
			if (w->stepX < 0)
				w->color = 0xFF0000;
			else
				w->color = 0xFFFF00;
		}
		else
		{
			if (w->stepY < 0)
				w->color = 0x0000FF;
			else
				w->color = 0x00FF00;
		}
	}
}

void	draw2(t_struct *mystruct)
{
	t_inwolf *w;

	w = (t_inwolf *)malloc(sizeof(t_inwolf) * 1);
	w_early_give(w, mystruct);
	while (w->x < WIDTH)
	{
		w_inwhile_give(w);
		use_dir(w);
		hit_or_no(w, mystruct);
		last_var_give(w);
		color_choice_yes(w, mystruct);
		side_used(w, mystruct);
		line(mystruct->img, w->x, 10, w->x, w->drawStart, 0x00F0F0);
		line(mystruct->img, w->x, w->drawStart, w->x, w->drawEnd, w->color);
		line(mystruct->img, w->x, w->drawEnd, w->x, HEIGHT - 2, 0x0000FF / 3);
		w->x++;
	}
}
