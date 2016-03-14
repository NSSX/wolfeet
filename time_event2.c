/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_event2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:45:33 by avella            #+#    #+#             */
/*   Updated: 2016/03/14 17:46:01 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	yo_right(t_struct *mystruct)
{
	double olddirx;
	double oldplanex;

	olddirx = mystruct->wolf->dirX;
	oldplanex = mystruct->wolf->planeX;
	if (mystruct->rightetat == 1)
	{
		mystruct->wolf->dirX = mystruct->wolf->dirX *
			cos(-mystruct->rotspeed) - mystruct->wolf->dirY
			* sin(-mystruct->rotspeed);
		mystruct->wolf->dirY = olddirx * sin(-mystruct->rotspeed)
			+ mystruct->wolf->dirY * cos(-mystruct->rotspeed);
		mystruct->wolf->planeX = mystruct->wolf->planeX *
			cos(-mystruct->rotspeed) - mystruct->wolf->planeY
			* sin(-mystruct->rotspeed);
		mystruct->wolf->planeY = oldplanex * sin(-mystruct->rotspeed)
			+ mystruct->wolf->planeY * cos(-mystruct->rotspeed);
	}
}

void	my_left_right(t_struct *mystruct)
{
	double olddirx;
	double oldplanex;

	olddirx = mystruct->wolf->dirX;
	oldplanex = mystruct->wolf->planeX;
	if (mystruct->leftetat == 1)
	{
		mystruct->wolf->dirX = mystruct->wolf->dirX *
			cos(mystruct->rotspeed) - mystruct->wolf->dirY
			* sin(mystruct->rotspeed);
		mystruct->wolf->dirY = olddirx * sin(mystruct->rotspeed) +
			mystruct->wolf->dirY * cos(mystruct->rotspeed);
		mystruct->wolf->planeX = mystruct->wolf->planeX *
			cos(mystruct->rotspeed) - mystruct->wolf->planeY
			* sin(mystruct->rotspeed);
		mystruct->wolf->planeY = oldplanex * sin(mystruct->rotspeed)
			+ mystruct->wolf->planeY * cos(mystruct->rotspeed);
	}
	yo_right(mystruct);
}

void	my_up_down(t_struct *mystruct)
{
	if (mystruct->upetat == 1)
	{
		if (mystruct->worldMap[(int)(mystruct->wolf->posX +
					mystruct->wolf->dirX * mystruct->movespeed)]
				[(int)mystruct->wolf->posY] == 0)
			mystruct->wolf->posX += mystruct->wolf->dirX * mystruct->movespeed;
		if (mystruct->worldMap[(int)(mystruct->wolf->posX)]
				[(int)(mystruct->wolf->posY + mystruct->wolf->dirY
					* mystruct->movespeed)] == 0)
			mystruct->wolf->posY += mystruct->wolf->dirY * mystruct->movespeed;
	}
	if (mystruct->downetat == 1)
	{
		if (mystruct->worldMap[(int)(mystruct->wolf->posX -
					mystruct->wolf->dirX * mystruct->movespeed)]
				[(int)mystruct->wolf->posY] == 0)
			mystruct->wolf->posX -= mystruct->wolf->dirX * mystruct->movespeed;
		if (mystruct->worldMap[(int)(mystruct->wolf->posX)]
				[(int)(mystruct->wolf->posY - mystruct->wolf->dirY
					* mystruct->movespeed)] == 0)
			mystruct->wolf->posY -= mystruct->wolf->dirY * mystruct->movespeed;
	}
}
