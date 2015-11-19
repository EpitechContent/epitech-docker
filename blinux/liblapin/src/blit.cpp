// Jason Brillante "Damdoshi"
// Epitech 1999-2042
//
// Lapin library

#include			<iostream>
#include			"lapin_private.h"

void				bunny_blit(t_bunny_buffer		*output,
					   const t_bunny_clipable	*picture,
					   const t_bunny_position	*pos)
{
  static t_bunny_position	defaul = {0, 0};

  if (pos == NULL)
    pos = &defaul;

  size_t			*type = (size_t*)output;
  size_t			*input_type = (size_t*)picture;
  sf::Sprite			*spr;
  sf::Texture			_txt;
  sf::Sprite			_spr;

  if (*input_type == GRAPHIC_RAM)
    {
      struct bunny_picture *pic = (struct bunny_picture*)picture;

      pic->tex = &pic->texture->getTexture();
      pic->sprite.setTexture(*pic->tex);
      pic->sprite.setTextureRect(pic->rect);
      pic->sprite.setPosition(pos->x, pos->y);
      pic->sprite.setOrigin(pic->x_origin, pic->y_origin);
      pic->sprite.setScale(pic->x_scale, pic->y_scale);
      pic->sprite.setRotation(pic->rotation);
      spr = &pic->sprite;
    }
  else
    {
      struct bunny_pixelarray	*pic = (struct bunny_pixelarray*)picture;
      int			i;
      int			j;

      for (j = picture->clip_y_position; j < picture->clip_y_position + picture->clip_height; ++j)
	for (i = picture->clip_x_position; i < picture->clip_x_position + picture->clip_width; ++i)
	  {
	    unsigned int	c = pic->rawpixels[i + j * pic->width];

	    pic->image.setPixel
	      (i, j,
	       sf::Color
	       ((c >> (RED_CMP * 8)) & 0xFF,
		(c >> (GREEN_CMP * 8)) & 0xFF,
		(c >> (BLUE_CMP * 8)) & 0xFF,
		(c >> (ALPHA_CMP * 8)) & 0xFF
		)
	       );
	  }
      pic->tex.loadFromImage(pic->image, pic->rect);
      pic->sprite.setTexture(pic->tex, true);
      pic->sprite.setPosition(pos->x, pos->y);
      /* Ignore other fields */
      spr = &pic->sprite;
    }

  switch (*type)
    {
    case WINDOW:
      {
	struct bunny_window	*out = (struct bunny_window*)output;

	if (*input_type == GRAPHIC_RAM)
	  out->window->draw(*spr);
	else
	  out->window->draw(*spr, sf::RenderStates(sf::BlendNone));
	return ;
      }
    case GRAPHIC_RAM:
      {
	struct bunny_picture	*out = (struct bunny_picture*)output;

	if (*input_type == GRAPHIC_RAM)
	  out->texture->draw(*spr);
	else
	  out->texture->draw(*spr, sf::RenderStates(sf::BlendNone));
	return ;
      }
    case SYSTEM_RAM:
      {
	struct bunny_pixelarray	*out = (struct bunny_pixelarray*)output;

	if (*input_type == SYSTEM_RAM)
	  {
	    const t_bunny_pixelarray	*pic = (const t_bunny_pixelarray*)picture;

	    gl_bunny_my_blit((t_bunny_pixelarray*)out, pic, pos);
	  }
	else
	  {
	    const bunny_pixelarray	*pic = (const bunny_pixelarray*)output;
	    sf::Image			img = spr->getTexture()->copyToImage();
	    int				i;
	    int				j;

	    for (j = picture->clip_y_position;
		 j < picture->clip_y_position + picture->clip_height;
		 ++j)
	      for (i = picture->clip_x_position;
		   i < picture->clip_x_position + picture->clip_width;
		   ++i)
		{
		  sf::Color		c = img.getPixel(i, j);
		  int			i = i + j * pic->width;

		  ((t_color*)pic->rawpixels)[i].argb[ALPHA_CMP] = c.a;
		  ((t_color*)pic->rawpixels)[i].argb[RED_CMP] = c.r;
		  ((t_color*)pic->rawpixels)[i].argb[GREEN_CMP] = c.g;
		  ((t_color*)pic->rawpixels)[i].argb[BLUE_CMP] = c.b;
		}
	  }
	return ;
      }
    }
}
