#include "wolf.h"

void line(t_img *myimg, float xi, float yi, float xf, float yf, int color);
void draw2(t_struct *mystruct);
void my_map_draw(t_struct *mystruct);

int             event_mlx(int keycode, t_struct *mystruct)
{
  if (keycode == 53)
    exit(1);
  if(keycode == 14)
    mystruct->eetat = 1;
  if(keycode == 12)
    mystruct->qetat = 1;
  if(keycode == 257)
     mystruct->shiftetat = 1;
  if(keycode == 126)
    mystruct->upetat = 1;
  if(keycode == 124)
    mystruct->rightetat = 1;
  if(keycode == 123)
    mystruct->leftetat = 1;
  if(keycode == 125)
    mystruct->downetat = 1;
  return (0);
}

void gotet(t_struct *mystruct)
{
  int i;
  i = 840;
  while(i < 890)
    {  
      line(mystruct->img, 840, i, 890, i, 0xFFFFFF);  
      i++;
    }
}

int event_release(int keycode, t_struct *mystruct)
{
  if(keycode == 14)
      mystruct->eetat = 0;
  if(keycode == 12)
      mystruct->qetat = 0;
  if(keycode == 257)
      mystruct->shiftetat = 0;
  if(keycode == 126)
      mystruct->upetat = 0;
  if(keycode == 125)
      mystruct->downetat = 0;
  if(keycode == 123)
      mystruct->leftetat = 0;
  if(keycode == 124)
      mystruct->rightetat = 0;
  return (0);
}


void line(t_img *myimg, float xi, float yi, float xf, float yf, int color)
{
  int dx,dy,i,xinc,yinc,cumul,x,y ;
  x = xi ;
  y = yi ;
  dx = xf - xi ;
  dy = yf - yi ;
  xinc = ( dx > 0 ) ? 1 : -1 ;
  yinc = ( dy > 0 ) ? 1 : -1 ;
  dx = abs(dx) ;
  dy = abs(dy) ;
  //  if(ok_draw(yi,yf))
    my_pixel_put_to_image(myimg, x, y, color);
  if ( dx > dy ) {
    cumul = dx / 2 ;
    for ( i = 1 ; i <= dx ; i++ ) {
      x += xinc ;
      cumul += dy ;
      if ( cumul >= dx ) {
	cumul -= dx ;
	y += yinc ; }
      // if(ok_draw(yi,yf))
       my_pixel_put_to_image(myimg, x, y, color); } }
  else {
    cumul = dy / 2 ;
    for ( i = 1 ; i <= dy ; i++ ) {
      y += yinc ;
      cumul += dx ;
      if ( cumul >= dy ) {
	cumul -= dy ;
	x += xinc ; }
      // if(ok_draw(yi,yf))
	my_pixel_put_to_image(myimg, x, y, color); } }
}

static char             *ft_join(char const *s1, char const *s2, int len1, int len2)
{
  char    *join;
  int             i;
  int             j;

  i = 0;
  j = 0;
  join = malloc(sizeof(char) * (len1 + len2) + 1);
  while (s1[i] != '\0')
    {
      join[i] = s1[i];
      i++;
    }
  while (s2[j] != '\0')
    {
      join[i] = s2[j];
      i++;
      j++;
    }
  join[i] = '\0';
  return (join);
}

char                    *ft_strjoins(char const *s1, char const *s2)
{
  int             len1;
  int             len2;
  char    *join;

  if (!s1 || !s2)
    return (NULL);
  len1 = ft_strlen(s1);
  len2 = ft_strlen(s2);
  join = ft_join(s1, s2, len1, len2);
  return (join);
}

char *my_maps(void)
{
 char    *line;
 char    *yt;
 int             fd;
 int             ret;
 char    **tab;

 fd = 0;
 ret = 0;
 fd = open("map", O_RDONLY);
 line = (char *)malloc(sizeof(char) * 2);
 while ((ret = get_next_line(fd, &yt)) && ret != -1)
   {
     line = ft_strjoins(line, yt);
     line = ft_strjoins(line, "\n");
   }
 if (ret == -1 || line[0] == '\0')
   {
     ft_putstr("Bad file descriptor\n");
     exit(1);
   }
 return (line);
}

void give_map_to_struct(char *line, t_struct *mystruct)
{
  int i;
 int x;
 int y;

 i = 0;
 x = 0;
 y = 0;
 while(line[i] != '\0')
   {
     mystruct->worldMap[y][x] = line[i] - '0';
     if(line[i] == '\n')
       {
	 y++;
	 x = 0;
       }
     else
       x++;
     i++;
   }
}

int main(void)
{
  t_struct *mystruct;
  char *line;

  line = my_maps();  
  mystruct = give_struct();
  give_map_to_struct(line, mystruct);
  mlx_key_hook(mystruct->win, event_release, mystruct);
  mlx_hook(mystruct->win, 2, (1L<<1), event_mlx, mystruct);
  mlx_put_image_to_window(mystruct->mlx, mystruct->win, mystruct->img->img_ptr, 0, 0);
  mlx_loop_hook (mystruct->mlx, the_move2, mystruct);
  mlx_loop(mystruct->mlx);
  return (0);
}
