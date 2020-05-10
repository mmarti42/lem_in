/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerolamo <jerolamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:00:20 by kdeloise          #+#    #+#             */
/*   Updated: 2020/05/10 17:02:42 by jerolamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include <string.h>

typedef struct			s_d
{
	int					c;
	int					i;
	int					t;
	int					okr;
	int					f;
}						t_d;

typedef struct			s_args
{
	unsigned long long	len;
	va_list				args;
}						t_args;

typedef struct			s_fls
{
	int					mi;
	int					pl;
	int					ze;
	int					oc;
	int					sp;
	int					wdh;
	int					psn;
	int					lnh;
	int					unsign;
	int					re;
	int					nn;
	int					xox;
	int					isxox;
	int					isptr;
	int					f;
}						t_fls;

typedef struct			s_err
{
	int errf;
}						t_err;

void					ft_flag(t_fls *fl, long long int num, int r);
void					ft_flagstr(t_fls *fl, char *str);
void					ft_flagmi(t_fls *fl, long long int num, int r);
int						ft_flagstrmi(t_fls *fl, char *str);
int						ft_lennbr_base_ull(unsigned long long int n, int x);
char					*ft_itoa_base(t_fls *fl, long long int n, int sz,
										char *base);
void					ft_cspec(t_args *ag, t_fls *fl);
char					*ft_pspec(t_args *ag, t_fls *fl);
void					ft_sspec(t_args *ag, t_fls *fl);
int						ft_spec2(const char *fo, t_args *ag, t_fls *fl);
char					*ft_uspec(t_args *ag, t_fls *fl);
char					*ft_xoxspec(t_args *ag, t_fls *fl, const char *fo);
void					ft_procspec(t_fls *fl);
int						ft_psn(const char *fo, t_fls *fl, t_args *ag);
void					ft_wdh(const char *fo, t_fls *fl, t_args *ag);
void					ft_oct(t_fls *fl, char **buff, char *tmp);
void					ft_octmi(t_fls *fl);
t_args					ft_fillta(t_args *ag);
t_fls					*ft_filltf(t_fls *fl);
int						ft_printf(const char *format, ...);
int						ft_flagsproc(const char *fo, t_fls *fl, t_args *ag);
int						ft_flagsdi(const char *fo, t_fls *fl, t_args *ag);
int						ft_flagscsp(const char *fo, t_fls *fl, t_args *ag);
int						ft_flagsf(const char *fo, t_fls *fl, t_args *ag);
int						ft_flagsu(const char *fo, t_fls *fl, t_args *ag);
int						ft_flagsoxx(const char *fo, t_fls *fl, t_args *ag);
int						ft_color(const char *restrict fo);
void					ft_rspec(t_args *ag, t_fls *fl);
char					*ft_dispec(t_args *ag, t_fls *fl);
char					*ft_dtoa(t_fls *fl, long double x, int p);
char					*ft_fspec(t_args *ag, t_fls *fl);
void					ft_fflag(t_fls *fl, char *s, int num);
void					ftplf(char **buff, t_fls *fl, int num);
void					flwdhf(char **buff, t_fls *fl, int r);
void					flspf(char **buff, t_fls *fl);
void					ft_fflagmi(t_fls *fl, char *s, int num);
void					flplmif(t_fls *fl, int num);
void					flnumf(char **buff, t_fls *fl);
int						flagsdi2(const char *fo, t_fls *fl);
void					ft_flagmi2(t_fls *fl, long long int num);
void					ft_flagmi3(t_fls *fl, int r);
void					ft_flag2(char **buff, t_fls *fl, long long int num);
void					ft_flag3(char **buff, t_fls *fl, int r);
void					ft_flag4(char **buff, t_fls *fl, int r);
void					ft_flag5(char **buff, t_fls *fl);
void					ft_flagstr2(t_fls *fl, char *str, char **buff);
void					ft_flagstrr2(t_fls *fl, char *str, char **b);
void					ft_flagstrr3(char *b);
void					ft_rspec2(t_fls *fl);
int						ft_lennbr_base(long long int n, int x);
int						ft_lennbr_base_ull(unsigned long long int n, int x);
int						ft_lennbr_base_ui(unsigned int n, int x);
int						ft_lennbr_base_sh(unsigned short int n, int x);
int						ft_lennbr_base_ch(unsigned char n, int x);
int						flagscsp2(const char *fo, t_fls *fl);
int						flagsf2(const char *fo, t_fls *fl);
int						ft_flagsu2(const char *fo, t_fls *fl);
int						ft_flagsoxx2(const char *fo, t_fls *fl);
int						ft_pricont(const char *fo, t_fls *fl,
										unsigned long long l, t_args *ag);
int						ft_pricont3(const char *fo, t_fls *fl,
										unsigned long long l, t_args *ag);
int						ft_pricont4(const char *fo, t_fls *fl,
										unsigned long long l, t_args *ag);
int						ft_pricont5(const char *fo, t_fls *fl,
										unsigned long long l, t_args *ag);
int						ft_pricont6(const char *fo, t_fls *fl,
										unsigned long long l, t_args *ag);
int						ft_flags(const char *fo, t_fls *fl,
									unsigned long long l, t_args *ag);
void					ft_spec3(const char *fo, t_args *ag, t_fls *fl,
									int f);
int						ft_printf2(const char *format, t_fls *fl,
										t_args *ag, int f);
int						ft_spec(const char *fo, t_args *ag, t_fls *fl);
int						lennbrf(double x);
int						ft_lastbit(double x);
char					*ft_lnh3(t_fls *fl, t_args *ag, const char *fo);
char					*ft_lnh4(t_fls *fl, t_args *ag, const char *fo);
char					*ft_lnh1(t_fls *fl, t_args *ag, const char *fo);
char					*ft_lnh2(t_fls *fl, t_args *ag, const char *fo);
char					*ft_lnh0(t_fls *fl, t_args *ag, const char *fo);

#endif
