/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:16:33 by abouabra          #+#    #+#             */
/*   Updated: 2022/11/06 19:31:58 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_hex_original(unsigned int nb, char x, t_vars *vars)
{
	char	*base;

	if (x == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (nb >= 16)
	{
		put_hex_original(nb / 16, x, vars);
		put_hex_original(nb % 16, x, vars);
	}
	else
		ft_putchar_original(base[nb % 16], vars);
}

void	hex_zero_flag(t_vars *vars, int len_of_int, unsigned int nb, char x)
{
	if (vars->flags[zero] == 1)
	{
		if (vars->flags[precision] == 1)
		{
			if (vars->flag_counter[precision] < hex_len(nb))
				vars->flag_counter[precision] = len_of_int;
			handle_padding(vars, vars->flag_counter[zero],
				vars->flag_counter[precision], ' ');
			handle_padding(vars, vars->flag_counter[precision],
				len_of_int, '0');
			if (nb != 0)
				put_hex_original(nb, x, vars);
			set_the_end(vars);
			return ;
		}
		handle_padding(vars, vars->flag_counter[zero], len_of_int, '0');
		put_hex_original(nb, x, vars);
		set_the_end(vars);
	}
}

void	hex_minus_flag(t_vars *vars, int len_of_int, unsigned int nb, char x)
{
	if (vars->flags[minus] == 1)
	{
		if (vars->flags[precision] == 1)
		{
			handle_padding(vars, vars->flag_counter[precision],
				len_of_int, '0');
			if (nb != 0)
				put_hex_original(nb, x, vars);
			if (vars->flag_counter[precision] < hex_len(nb))
				vars->flag_counter[precision] = len_of_int;
			handle_padding(vars, vars->flag_counter[minus],
				vars->flag_counter[precision], ' ');
			set_the_end(vars);
			return ;
		}
		put_hex_original(nb, x, vars);
		handle_padding(vars, vars->flag_counter[minus], len_of_int, ' ');
		set_the_end(vars);
	}
}

void	hex_hashtag_flag(t_vars *vars, int len_of_int, unsigned int nb, char x)
{
	if (vars->flags[hashtag] == 1)
	{
		vars->flags[hashtag] = 0;
		if (nb != 0)
			len_of_int += 2;
		handle_width(vars, len_of_int);
		if (x == 'x' && nb != 0)
			ft_putstr_original("0x", vars);
		else if (x == 'X' && nb != 0)
			ft_putstr_original("0X", vars);
		put_hex_original(nb, x, vars);
		vars->state = 0;
	}
}

void	ft_put_hex_nbr(unsigned int nb, char x, t_vars *vars)
{
	int	len_of_int;

	len_of_int = hex_len(nb);
	if (nb == 0 && vars->flags[precision] == 1)
		len_of_int--;
	if (vars->flags[hashtag] != 1)
		handle_width(vars, hex_len(nb));
	if (vars->state == 0)
	{
		put_hex_original(nb, x, vars);
		return ;
	}
	hex_hashtag_flag(vars, len_of_int, nb, x);
	hex_zero_flag(vars, len_of_int, nb, x);
	hex_minus_flag(vars, len_of_int, nb, x);
	if (vars->flags[precision] == 1)
	{
		handle_padding(vars, vars->flag_counter[precision], len_of_int, '0');
		if (nb != 0)
			put_hex_original(nb, x, vars);
		set_the_end(vars);
	}
}
