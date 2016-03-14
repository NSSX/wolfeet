/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_give.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 16:53:05 by avella            #+#    #+#             */
/*   Updated: 2016/03/14 16:53:35 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	w_early_give(t_inwolf *w, t_struct *mystruct)
{
	w->posX = mystruct->wolf->posX;
	w->posY = mystruct->wolf->posY;
	w->dirX = mystruct->wolf->dirX;
	w->dirY = mystruct->wolf->dirY;
	w->planeX = mystruct->wolf->planeX;
	w->planeY = mystruct->wolf->planeY;
	w->time = 0;
	w->oldTime = 0;
	w->x = 0;
}

void	w_inwhile_give(t_inwolf *w)
{
	w->cameraX = 2 * w->x / (double)(WIDTH) - 1;
	w->rayPosX = w->posX;
	w->rayPosY = w->posY;
	w->rayDirX = w->dirX + w->planeX * w->cameraX;
	w->rayDirY = w->dirY + w->planeY * w->cameraX;
	w->mapX = (int)w->rayPosX;
	w->mapY = (int)w->rayPosY;
	w->sideDistX = 0;
	w->sideDistY = 0;
	w->deltaDistX = sqrt(1 + (w->rayDirY * w->rayDirY)
			/ (w->rayDirX * w->rayDirX));
	w->deltaDistY = sqrt(1 + (w->rayDirX * w->rayDirX)
			/ (w->rayDirY * w->rayDirY));
	w->perpWallDist = 0;
	w->stepX = 0;
	w->stepY = 0;
	w->hit = 0;
	w->side = 0;
}

void	use_dir(t_inwolf *w)
{
	if (w->rayDirX < 0)
	{
		w->stepX = -1;
		w->sideDistX = (w->rayPosX - w->mapX) * w->deltaDistX;
	}
	else
	{
		w->stepX = 1;
		w->sideDistX = (w->mapX + 1.0 - w->rayPosX) * w->deltaDistX;
	}
	if (w->rayDirY < 0)
	{
		w->stepY = -1;
		w->sideDistY = (w->rayPosY - w->mapY) * w->deltaDistY;
	}
	else
	{
		w->stepY = 1;
		w->sideDistY = (w->mapY + 1.0 - w->rayPosY) * w->deltaDistY;
	}
}
