/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klsirop <klsirop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:08:14 by jmaynard          #+#    #+#             */
/*   Updated: 2020/08/01 17:54:35 by klsirop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# ifndef STDARG_H
#  define STDARG_H
#  include <stdarg.h>
# endif
# ifndef STDLIB_H
#  define STDLIB_H
#  include <stdlib.h>
# endif
# ifndef UNISTD_H
#  define UNISTD_H
#  include <unistd.h>
# endif
# ifndef __LIBFT_H
#  define __LIBFT_H
#  include "libft.h"
# endif
# ifndef WCHAR_H
#  define WCHAR_H
#  include <wchar.h>
# endif

# define RESET_COLOUR	\x1b[0m
# define RED			\x1b[31m
# define GREEN			\x1b[32m
# define YELLOW			\x1b[33m
# define BLUE			\x1b[34m
# define MAGENTA		\x1b[35m
# define CYAN			\x1b[36m

typedef	struct		s_flag
{
	char			*flags;
	int				wid;
	int				pres;
	char			*size;
	int				type;
}					t_flags;

typedef	union		u_float
{
	double			fl;
	__uint64_t		dw;
}					t_fl;

typedef struct		s_formlfb
{
	unsigned long int	mantisa : 64;
	unsigned			exponent : 15;
	unsigned			sign : 1;
}					t_formlfb;

typedef union		u_double
{
	long double		ld;
	t_formlfb		bytes;
}					t_double;

typedef struct		s_float
{
	unsigned long long	m;
	int					e;
	int					s;
	int					n;
}					t_float;

int					ft_printf(const char *format, ...);

int					(*g_func[10])(t_flags *, va_list *);

int					di_con(t_flags *param, va_list *arg);
int					o_con(t_flags *param, va_list *arg);
int					u_con(t_flags *param, va_list *arg);
int					x_con(t_flags *param, va_list *arg);
int					x_up_con(t_flags *param, va_list *arg);
int					f_con(t_flags *param, va_list *arg);
int					c_con(t_flags *param, va_list *arg);
int					s_con(t_flags *param, va_list *arg);
int					p_con(t_flags *param, va_list *arg);

/*
** ft_printf.c
*/

void				create_func();
int					ft_percent(t_flags *param, char c);

/*
** ft_read_alg.c
*/

int					ft_putnstr(const char *s, size_t size);
void				ft_read_arg(va_list *arg, char *format, int *val);
char				*ft_append(char *dst, char *src);
char				*ft_prepend(char *dst, char *src);

/*
**	do_consver.c
*/

char				*ft_consver(char *fmt, va_list *arg, int *val);

/*
** c_conservation.c & cl_cons.c
*/

int					ft_putch(wchar_t wc);
int					c_big(t_flags *param, va_list *arg);
void				ft_cwid(t_flags *param, char c, char *str, int len);

/*
** ft_itoa_base.c
*/
char				*ft_itoa_base_large(__uint64_t value, int base);
char				*ft_itoa_base(unsigned short value, int base);

/*
**	s_conservation.c & sl_consevation.c
*/

char				*ft_crop(char *str, int len);
int					s_big(t_flags *param, va_list *arg);

/*
**	p_conservation.c
*/

int					del(char **str);
int					ft_prescision(t_flags *param, char **str);
int					ft_put_x(char **str, int len, int flag, char *c);

/*
**	x_con
*/
char				*ft_getarg_16(t_flags *param, va_list *arg);
int					ft_width(t_flags *param, char **str, int len);
int					ft_hastag(t_flags *param, int z, char **str, int flag);
int					ft_min_x(char **str, char *s);

/*
**	x_up
*/
int					ft_eq(char **str, char **tmp, int flag, char *c);
char				*ft_difference(char **str, int d, char *c);
int					ft_spaces(char *str);

/*
** do_consver.c
*/

void				ft_init(t_flags *param);
void				ft_free_param(t_flags *param);

/*
** do_flags.c
*/
void				ft_help_valid_flags(t_flags *param);
char				*ft_valid_flag(char *flags, char *fmt, t_flags *param);
char				*ft_flags(char *fmt, t_flags *param);
char				*ft_valid_pres(char *fmt, t_flags *param, va_list *arg);

/*
**	do_wid.c
*/

char				*ft_valid_wid(char *fmt, t_flags *param, va_list *arg);

/*
** do_len.c
*/

char				*ft_valid_len(char *len, char *fmt, t_flags *param);

/*
**	do_type.c
*/

char				*ft_type(char *fmt, t_flags *param);

/*
** di_cons_2.c
*/

int					ft_doing(t_flags *param, int l, int *val, char **str);
int					di_con(t_flags *param, va_list *arg);
int					ft_doing_u(t_flags *param, int l, int *val, char **str);

/*
** di_cons.c
*/

int					di_con_standart(t_flags *param, va_list *arg);
int					ft_put_min(t_flags *param, int l, int *val, char **str);
int					ft_put_plus(t_flags *param, int l, int *val, char **str);
int					ft_put_no_plus(t_flags *param, int l, int *val, char **str);
int					ft_puttostr(t_flags *param, int l, int *val, char **str);

/*
** di_func_1.c
*/

int					ft_check_way(char **str, int *val, int l, int way);
int					ft_fill_symb_0_h(char *str, int val, int ost_pres);
void				ft_fill_symb_0(char *str, int val, int minus, int ost_pres);
void				ft_help_new_norm(int l, char **str, int i, int val);
void				ft_new_norm(char *str, int val, int l, int pres);

/*
** di_func_3.c
*/

int					ft_way_0(char *str, int pres);
int					ft_way_1(char *str, int pres, int val);
int					ft_find_min(char *str, int pres, int way, int val);

/*
** di_func.c
*/

void				ft_help_minus(int l, unsigned long long int new_num,
									char **str, int i);
int					ft_plus_symb(char **str, char c, int *val);
int					ft_help_app_1(char **str, char c, int *val);
int					ft_help_app_2(char **str, char c, int l, int *i);
int					ft_append_symb(char **str, int *val, int l, char c);

/*
** ft_size_1.c
*/

int					ft_h_h(short int *num, int *l, int *val, t_flags *param);
int					ft_h(char **str, va_list *arg, t_flags *param, int *l);
int					ft_h_l(long int *num, int *l, int *val, t_flags *param);
int					ft_l(char **str, va_list *arg, t_flags *param, int *l);

/*
** ft_size_2.c
*/

int					ft_h_ll(long long int *num, int *l, int *val,
							t_flags *param);
int					ft_ll(char **str, va_list *arg, t_flags *param, int *l);
int					ft_h_j(intmax_t *num, int *l, int *val, t_flags *param);
int					ft_j(char **str, va_list *arg, t_flags *param, int *l);

/*
** ft_size_3.c
*/

int					ft_h_z(ssize_t *num, int *l, int *val, t_flags *param);
int					ft_z(char **str, va_list *arg, t_flags *param, int *l);
int					ft_h_lll(int64_t *num, int *l, int *val, t_flags *param);
int					ft_lll(char **str, va_list *arg, t_flags *param, int *l);

/*
** ft_size_u_1.c
*/

int					ft_h_h_u(unsigned short *num, int *l, int *val,
								t_flags *param);
int					ft_h_u(char **str, va_list *arg, t_flags *param, int *l);
int					ft_h_l_u(unsigned long *num, int *l, int *val,
								t_flags *param);
int					ft_l_u(char **str, va_list *arg, t_flags *param, int *l);

/*
** ft_size_u_2.c
*/

int					ft_hllu(unsigned long long *num, int *l, int *val,
							t_flags *param);
int					ft_ll_u(char **str, va_list *arg, t_flags *param, int *l);
int					ft_h_j_u(uintmax_t *num, int *l, int *val, t_flags *param);
int					ft_j_u(char **str, va_list *arg, t_flags *param, int *l);

/*
** ft_size_u_3.c
*/

int					ft_h_z_u(size_t *num, int *l, int *val, t_flags *param);
int					ft_z_u(char **str, va_list *arg, t_flags *param, int *l);
int					ft_h_lll_u(uint64_t *num, int *l, int *val,
								t_flags *param);
int					ft_z_lll(char **str, va_list *arg, t_flags *param, int *l);

/*
** ft_size_u.c
*/

int					ft_h_ns_u(unsigned *num, int *l, int *val, t_flags *param);
int					ft_ns_u(char **str, va_list *arg, t_flags *param, int *l);
int					ft_hu(unsigned char *num, int *l, int *val, t_flags *param);
int					ft_hh_u(char **str, va_list *arg, t_flags *param, int *l);

/*
** ft_size.c
*/

int					ft_h_norm_size(int *num, int *l, int *val, t_flags *param);
int					ft_n_size(char **str, va_list *arg, t_flags *param, int *l);
int					ft_h_hh(signed char *num, int *l, int *val, t_flags *param);
int					ft_hh(char **str, va_list *arg, t_flags *param, int *l);

/*
** u_cons.c
*/

void				ft_no_minus_u(char **str, t_flags *param, int l, int *val);
int					ft_puttostr_u(t_flags *param, int l, int *val, char **str);
int					u_con_standart(t_flags *param, va_list *arg);
int					u_con(t_flags *param, va_list *arg);

/*
** di_ost.c
*/

int					ft_try_put_plus(char **str, int val);
void				ft_di_start(char **str, int *val, int *l);
void				ft_fill_symb(char *str, int val, char c);

/*
 ** bnt.c
*/

char				*ft_sum_h(char *big, char *src, int *lb, int *des);
int					ft_sum_hh(char *big, char *small, char *src, int *lb);
char				*ft_sum(char *big, char *small);
int					ft_diff_h(char **str, char c);
int					ft_diff(char c, char **ta_samaya);

/*
** f_cons_str_h.c
*/

int					ft_put_plus_f(t_flags *param, int l, int *val, char **str);
int					ft_put_no_plus_f(t_flags *param, int l, int *val,
										char **str);
int					ft_puttostr_f(t_flags *param, int l, int *val, char **str);
int					ft_diff_hh(char **ta_samaya, char **str);

/*
** f_cons_str.c
*/

int					ft_way_0_f(char *str);
int					ft_way_1_f(char *str, int val);
int					ft_find_min_f(char *str, int way, int val);
int					ft_put_min_f(t_flags *param, int l, int *val, char **str);
void				ft_new_norm_f(char *str, int val, int l);

/*
** f_cons.c
*/

int					ft_round_h(char **mant, int *i, int *cut);
int					ft_round(char **mant, int i);
int					ft_put_zero(char **mant, int pres);
int					ft_f_pres_h(char **mant, t_flags *param, int *i, int *t);
int					ft_f_pres(char **mant, t_flags *param);

/*
** f_ost.c
*/

int					ft_new_max(int lb, int ls);
int					ft_mv_hh(char **mant, int i);
int					ft_exeption_h(int s, int e, unsigned long long int m,
									char **mant);
int					ft_exeption(int s, int e, unsigned long long int m,
								char **mant);

/*
** f_wid.c
*/

int					ft_f_wid(char **mant, int wid);
void				ft_fill_symb_f(char *str, int val, char c);
void				ft_fill_symb_0_f(char *str, int val, int minus);

/*
** float_h.c
*/

int					ft_find_ind(char *str);
void				ft_mult_h(char **mant, int base, int *des);
int					ft_mult(char **mant, int n, int base);
int					ft_mv_point_h(char **mant, int n);
int					ft_mv_point(char **mant, int n);

/*
** float_hhh.c
*/

int					ft_con_h_2(int s, char **mant, t_flags *param);
int					f_con_h_1(char **mant, int e, int n);
int					ft_cons_h_3(int exp, char **mant);
char				*ft_equal(char *ost, char *str, char **tmp);
int					ft_mult_hh(char **mant, char **tmp, char **tmp1);

/*
** float.c
*/

int					ft_cons_h_4(int e, int m, char **tmp, char **mant);
int					ft_cons_h_5(t_float *field, char **mant, va_list *arg);
void				ft_cons_h_6(t_float *field, t_fl *f, va_list *arg);
int					ft_cons_h_7(t_float *field, char **tmp, char **mant);
int					f_con(t_flags *param, va_list *arg);

/*
** ft_float_hh.c
*/

int					ft_dv_ost(int ekv, char **mant, char **ost);
int					ft_dv_ta_samaya(int ekv, char **mant, char **ta_samaya);
void				ft_dv_h(char **tmp, char **ost, char **mant);
int					ft_dv(char **mant);
int					ft_get_d(va_list *arg, char **mant, int *e,
								unsigned long long int *m);

/*
** multik_h.c
*/

void				ft_new_mult_h(char **str, int i, int *des);
int					ft_new_mult_hh(char **str, int des, int *count);
int					ft_new_mult(char **str);
void				ft_kek(char **str, char c, size_t size);
char				*ft_equal_h(char **tmp, char *str, char *ost);

/*
** multik.c
*/

int					ft_multik_h(char **str, char c);
int					ft_multik_hh(char **str, char **ost,
									char **tmp, char **tmp1);
int					ft_multik_hhh(char **ost, char **str, char **tmp1);
int					ft_multik_hhhh(char **tmp1, char **ost, char **str);
int					ft_multik(char c, char **ost);

/*
** nan.c
*/

int					ft_start_f_h(char *s, int *l, int *val, t_flags *param);
void				ft_help_minus_f(int l, char *s, char **str, int i);
int					ft_start_f_hh(char **s, char **str, int *i);
int					ft_start_f(char **str, t_flags *param, int *l, char **s);

/*
** last_func.c
*/

int					ft_find_a(const char *s, int c, int val);
int					ft_min_od_nul(char **mant);
int					ft_min_od_nul_rev(char **mant, int *i);
int					ft_line_var(char **tmp, char **mant);

/*
** ft_last_func_2.c
*/

int					ft_last_func(char **mant, t_flags *param, int len);

#endif
