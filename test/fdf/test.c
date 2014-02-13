/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelage <mdelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/21 16:12:09 by mdelage           #+#    #+#             */
/*   Updated: 2014/01/18 16:27:51 by mdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_dot
{
	int			x;
	int			y;
}				t_dot;

typedef struct	s_pic
{
	int			bpp;
	int			sizeline;
	int			endian;
	void		*pic;
	char		*data;
}				t_pic;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
}				t_env;

void	draw_square(t_env *e, t_pic *pic);
void	draw_line(t_env *e, t_pic *pic, t_dot src, t_dot dest);
void	draw_pixel(t_env *e, t_pic *pic, int x, int y);
int		key_hook(int keycode, t_env *e);
int		expose_hook(t_env *e);
int		mouse_hook(int button, int x, int y, t_env *e);
void	draw(t_env *e);

int		main()
{
	t_env	e;
	char	*win_name = "win_caca";

	e.width = 100;
	e.height = 100;
	e.mlx = mlx_init();
	if (e.mlx != NULL)
	{
		e.win = mlx_new_window(e.mlx, e.width, e.height, win_name);
		if (e.win != NULL)
		{
			mlx_expose_hook(e.win, expose_hook, &e);
			mlx_key_hook(e.win, key_hook, &e);
			mlx_mouse_hook(e.win, mouse_hook, &e);
			mlx_loop(e.mlx);
		}
		else
			printf("Erreur a la creation de la fenetre\n");
	}
	else
		printf("Erreur a l'initialisation de mlx\n");
	return (0);
}

int		mouse_hook(int button, int x, int y, t_env *e)
{
	printf("mouse : %d (%d:%d)\n", button, x, y);
	return (0);
}

int		key_hook(int keycode, t_env *e)
{
	printf("key : %d\n", keycode);
	if (keycode == 65307 || keycode == 65293)
		exit (0);
	return (0);
}

int		expose_hook(t_env *e)
{
	draw(e);
	return (0);
}

void	draw(t_env *e)
{
	t_pic	pic;

	pic.pic = mlx_new_image(e->mlx, e->width, e->height);
	if (pic.pic != NULL)
	{
		pic.data = mlx_get_data_addr(pic.pic, &pic.bpp, &pic.sizeline, &pic.endian);
		draw_square(e, &pic);
		mlx_put_image_to_window(e->mlx, e->win, pic.pic, 0, 0);
	}
	else
		printf("Erreur a la creation de l'image\n");

}

void	draw_square(t_env *e, t_pic *pic)
{
	t_dot	tab[2][2];
	int		i;
	int		j;

	tab[0][0].x = 10;
	tab[0][0].y = 10;
	tab[0][1].x = 90;
	tab[0][1].y = 10;
	tab[1][0].x = 10;
	tab[1][0].y = 90;
	tab[1][1].x = 90;
	tab[1][1].y = 90;
	i = 0;
	while (i < 2)
	{
		j = 0;
		while(j < 2)
		{
			if (j + 1 < 2)
				draw_line(e, pic, tab[i][j], tab[i][j + 1]);
			if (i + 1 < 2)
				draw_line(e, pic, tab[i][j], tab[i + 1][j]);
			j++;
		}
		i++;
	}
}

void	draw_line(t_env *e, t_pic *pic, t_dot src, t_dot dest)
{
	int		diffx;
	int		diffy;
	int		i;

	diffx = dest.x - src.x;
	diffy = dest.y - src.y;
	if (diffx < 0)
		diffx *= -1;
	if (diffy < 0)
		diffy *= -1;
	if (src.x <= dest.x)
	{
		if (diffy <= diffx)
		{
			i = src.x;
			while (i <= dest.x)
			{
				draw_pixel(e, pic, i, src.y + ((dest.y - src.y) *(i - src.x))
						   / (dest.x - src.x));
				i++;
			}
		}
		else
		{
			i = src.y;
			while (i <= dest.y)
			{
				draw_pixel(e, pic, src.x + ((dest.x - src.x) *(i - src.y))
						   / (dest.y - src.y), i);
				i++;
			}
		}
	}
	else
	{
		if (diffy <= diffx)
		{
			i = dest.x;
			while (i <= src.x)
			{
				draw_pixel(e, pic, i, dest.y + ((src.y - dest.y) *(i - dest.x))
						   / (src.x - dest.x));
				i++;
			}
		}
		else
		{
			i = dest.y;
			while (i <= src.y)
			{
				draw_pixel(e, pic, dest.x + ((src.x - dest.x) *(i - dest.y))
						   / (src.y - dest.y), i);
				i++;
			}
		}
	}
}

void	draw_pixel(t_env *e, t_pic *pic, int x, int y)
{
	int				color;
	unsigned int	ucolor;

	color = 16777215;
	ucolor = mlx_get_color_value(e->mlx, color);
	printf("x = %d\ty = %d\n", x ,y);
	pic->data[y * (pic->sizeline) + (pic->bpp / 8) * x] = 255 * x / e-> width;
	pic->data[y * (pic->sizeline) + (pic->bpp / 8) * x + 1] = 255 *y / e-> height;
	pic->data[y * (pic->sizeline) + (pic->bpp / 8) * x + 2] = 255;
}
/*
void	*mlx_init ();
void	*mlx_new_window ( void *mlx_ptr, int size_x, int size_y, char *title );
int		mlx_clear_window ( void *mlx_ptr, void *win_ptr );
int		mlx_destroy_window ( void *mlx_ptr, void *win_ptr );
void	*mlx_new_image ( void *mlx_ptr, int width, int height );
char	*mlx_get_data_addr  ( void *img_ptr, int *bits_per_pixel, int *size_line, int *endian );
int		mlx_put_image_to_window ( void *mlx_ptr, void *win_ptr,  void  *img_ptr, int x, int y );
unsigned int	mlx_get_color_value ( void *mlx_ptr, int color );
void	*mlx_xpm_to_image  (  void  *mlx_ptr,  char  **xpm_data,  int *width, int *height );
void	*mlx_xpm_file_to_image ( void *mlx_ptr, char *filename, int  *width,  int *height );
int		mlx_destroy_image ( void *mlx_ptr, void *img_ptr );
int		mlx_pixel_put ( void *mlx_ptr, void *win_ptr, int x, int y, int color );
int		mlx_string_put ( void *mlx_ptr, void *win_ptr, int x, int y, int  color, char *string );
int		mlx_loop ( void *mlx_ptr );
int		mlx_key_hook ( void *win_ptr, int (*funct_ptr)(), void *param );
int		mlx_mouse_hook ( void *win_ptr, int (*funct_ptr)(), void *param );
int		mlx_expose_hook ( void *win_ptr, int (*funct_ptr)(), void *param );
int		mlx_loop_hook ( void *mlx_ptr, int (*funct_ptr)(), void *param );

*/
