/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Sat Dec  8 22:10:35 2012 Hugues
*/

#include	"include.h"

t_color		*interpolate_color(t_color *color1, t_color *color2,
				   float coeff, t_color *fin_color)
{
  fin_color->r = ((float)(color1->r) * coeff)
    + ((float)(color2->r) * (1.0 - coeff));
  fin_color->g = ((float)(color1->g) * coeff)
    + ((float)(color2->g) * (1.0 - coeff));
  fin_color->b = ((float)(color1->b) * coeff)
    + ((float)(color2->b) * (1.0 - coeff));
  return (fin_color);
}

void		draw_line_y(t_screen_point *p1, t_screen_point *p2,
			    t_init_x *win)
{
  int		imin;
  int		imax;
  int		i;
  t_color	tmp;

  i = 0;
  if (p1->x < p2->x)
    swap_ptr((void*)(&p1), (void*)(&p2));
  imin = p2->x;
  imax = p1->x;
  while ((imin + i) < imax)
    {
      put_pixel_img(win, imin + i, p1->y, INTER_COL);
      i++;
    }
}

void		drawn_line_obl_y(t_screen_point *p1, t_screen_point *p2,
				 t_init_x *win)
{
  float		coeff;
  float		offset;
  int		imin;
  int		imax;
  int		i;
  t_color	tmp;

  i = 0;
  if (p1->y < p2->y)
    swap_ptr((void*)(&p1), (void*)(&p2));
  imin = p2->y;
  imax = p1->y;
  coeff = ((float)(p2->x) - (float)(p1->x))
    / ((float)(p2->y) - (float)(p1->y));
  offset = (float)(p1->x) - (coeff * (float)p1->y);
  while ((imin + i) < imax)
    {
      put_pixel_img(win, LINE_CALC, (imin + i), INTER_COL);
      i++;
    }
}

void		drawn_line_obl(t_screen_point *p1, t_screen_point *p2,
			       t_init_x *win)
{
  float		coeff;
  float		offset;
  int		imin;
  int		imax;
  int		i;
  t_color	tmp;

  i = 0;
  if (p1->x < p2->x)
    swap_ptr((void*)(&p1), (void*)(&p2));
  imin = p2->x;
  imax = p1->x;
  coeff = ((float)(p2->y) - (float)(p1->y))
    / ((float)(p2->x) - (float)(p1->x));
  if (ABS(coeff) > 1.0)
    {
      drawn_line_obl_y(p1, p2, win);
      return;
    }
  offset = (float)(p1->y) - (coeff * (float)p1->x);
  while ((imin + i) < imax)
    {
      put_pixel_img(win, (imin + i), LINE_CALC, INTER_COL);
      i++;
    }
}

void		draw_line(t_screen_point *p1, t_screen_point *p2,
			  t_init_x *win)
{
  int		imin;
  int		imax;
  int		i;
  t_color	tmp;

  i = 0;
  if ((p1->x == p2->x) && (p1->y == p2->y))
    put_pixel_img(win, p1->x, p1->y, &(p1->color));
  else if (p1->x == p2->x)
    {
      if (p1->y < p2->y)
	swap_ptr((void*)(&p1), (void*)(&p2));
      imin = p2->y;
      imax = p1->y;
      while ((imin + i) < imax)
        {
	  put_pixel_img(win, p1->x, imin + i, INTER_COL);
	  i++;
        }
    }
  else if (p1->y == p2->y)
    draw_line_y(p1, p2, win);
  else
    drawn_line_obl(p1, p2, win);
}