//
// Created by Leto Vania on 20/09/2019.
//

#ifndef FILLIT_H
# define FILLIT_H
#ifndef I_PIECE
# define I_PIECE (int[8]) {0,0,0,1,0,2,0,3}
#endif
#ifndef IH_PIECE
# define IH_PIECE (int[8]) {0,0,1,0,2,0,3,0}
#endif
#ifndef O_PIECE
# define O_PIECE (int[8]) {0,0,1,0,0,1,1,1}
#endif
#ifndef L_PIECE
# define L_PIECE (int[8]) {0,0,0,1,0,2,1,2}
#endif
#ifndef LR_PIECE
# define LR_PIECE (int[8]) {0,0,1,0,2,0,0,1}
#endif
#ifndef LD_PIECE
# define LD_PIECE (int[8]) {0,0,1,0,1,1,1,2}
#endif
#ifndef LL_PIECE
# define LL_PIECE (int[8]) {2,0,0,1,1,1,2,1}
#endif
#ifndef J_PIECE
# define J_PIECE (int[8]) {1,0,1,1,0,2,1,2}
#endif
#ifndef JR_PIECE
# define JR_PIECE (int[8]) {0,0,0,1,1,1,2,1}
#endif
#ifndef JD_PIECE
# define JD_PIECE (int[8]) {0,0,1,0,0,1,0,2}
#endif
#ifndef JL_PIECE
# define JL_PIECE (int[8]) {0,0,1,0,2,0,2,1}
#endif
#ifndef T_PIECE
# define T_PIECE (int[8]) {1,0,0,1,1,1,2,1}
#endif
#ifndef TR_PIECE
# define TR_PIECE (int[8]) {0,0,0,1,1,1,0,2}
#endif
#ifndef TD_PIECE
# define TD_PIECE (int[8]) {0,0,1,0,2,0,1,1}
#endif
#ifndef TL_PIECE
# define TL_PIECE (int[8]) {1,0,0,1,1,1,1,2}
#endif
#ifndef S_PIECE
# define S_PIECE (int[8]) {1,0,2,0,0,1,1,1}
#endif
#ifndef SR_PIECE
# define SR_PIECE (int[8]) {0,0,0,1,1,1,1,2}
#endif
#ifndef Z_PIECE
# define Z_PIECE (int[8]) {0,0,1,0,1,1,2,1}
#endif
#ifndef ZR_PIECE
# define ZR_PIECE (int[8]) {1,0,0,1,1,1,0,2}
#endif
# include "libft/libft.h"

typedef struct			s_termito
{
	char 				alpha;
	int					*position;
	struct s_termito	*next;
}						t_termito;

typedef struct			s_shape
{
	char		letter;
	int				coord[8];
	struct s_shape	*next;
}						t_shape;


void		parser(char **file, t_shape **shape);
#endif //FILLIT_FILLIT_H
