/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 16:17:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/05/18 13:51:40 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

static char *precision_cut(char *str, t_flags *flags, char speci)
{
    char *ret;

    ret = NULL;
    if (flags->precision > (int)ft_strlen(str))
    {
        ret = (char *)malloc(flags->precision + 1);
        if (ret)
        {
            // printf("precision: [%i]\n", flags->precision);
            ret[flags->precision] = '\0';
            ret = ft_strncpy(ret, str, flags->precision-1);
            //free(str);
            //printf("[%s]\n", ret);
            return (ret);
        }
    }
    if (flags->precision == 0 && (speci == 'x' || speci == 'X'))
        str[flags->precision] = '\0';
    return (str);
}

static char *ft_float_base(int val)
{
    int     len;
    int     tmp;
    char    *ret;

    len = 1;
    tmp = val;
    while (tmp)
    {
        len++;
        tmp /= 10;
    }
    if (val == 0)
        len++;
    ret = (char *)malloc(len + 1);
    if (ret) // Fix Float precision problem
    {
        ret[len--] = '\0';
        ret[len--] = '.';
        if (val == 0)
            ret[len] = '0';
        while(val)
        {
            ret[len--] = (val % 10) + '0';
            val /= 10;
        }
        return (ret);
    }
    return (NULL);
}

static void ft_banker_round(char *ret, double nbr, int index)
{
    double tmp;

    tmp = (nbr - (int)nbr)*10;
    if (tmp >= 5)
        ret[--index]++;
}

static char *ft_float_convert(double nbr, t_flags *flags)
{
    char    *ret;
    char    *tmp;
    char    *first_part;
    int     base;
    int     len;
    int     i;

    i = 0;
    ret = NULL;
    first_part = NULL;
    base = (int)nbr;
    first_part = ft_float_base(base);
    if (flags->precision > 0)
        len = flags->precision;
    else
        len = 6;
    ret = (char *)malloc(len + 1);
    if (ret)
    {
        ret[len] = '\0';
        nbr = nbr - (double)base;
        while (i < len)
        {
            nbr *= 10;
            base = (int)nbr;
            ret[i++] = (base % 10) + '0';
        }
        ft_banker_round(ret, nbr, i);
        tmp = ft_strjoin(first_part, ret);
        ft_strdel(&first_part);
        ft_strdel(&ret);
        return (tmp);
    }
    return (NULL);
}

static char *plus_hash(t_flags *flags, char *str, char *width, char specifier)
{
    char    *ret;
    char    *tmp;
    char    *precision;
    int     len;
    int     int_tmp;

    ret = NULL;
    int_tmp = flags->precision;
    if (str && *str != '0')
    {
        len = ft_strlen(str);
        if (specifier == 'i' || specifier == 'd')
            if (flags->plus)
                ret = ft_strjoin("+", str);
        if (int_tmp > 1 && int_tmp > len)
        {
            int_tmp -= len;
            precision = (char *)malloc(int_tmp);
            precision[int_tmp] = '\0';
            while (int_tmp > 0)
                    precision[--int_tmp] = '0';
            tmp = str;
            str = ft_strjoin(precision, str);
            free(tmp);
        }
        if (flags->hash)
        {
            if (specifier == 'o')
                ret = ft_strjoin("0", str);
            if (specifier == 'x')
            {
                if (!width || flags->zero == 0 || flags->minus)
                    ret = ft_strjoin("0x", str);
                else
                    width[1] = 'x';
                    
            }
            if (specifier == 'X')
            {
                if (!width || flags->zero == 0 || flags->minus)
                    ret = ft_strjoin("0X", str);
                else
                    width[1] = 'X';
            }
        }
            
        if (ret)
        {
            free(str);
            str = ret;
        }
    }
    return (str);
}

char    *ft_nbr_converter(t_arg *arg, t_flags *flags, t_modifier *mod)
{
    char            *ret;
    char            *width;
    int             index;

    index = 0;
    ret = NULL;
    width = ft_min_width_generator(flags);
    if (arg->specifier == 'd' || arg->specifier == 'i')
    {
        if (mod->mod == 0)
            ret = ft_itoa_base(va_arg(arg->arg, int), 10);
        if (mod->mod == 1)
            ret = ft_itoa_base((short)va_arg(arg->arg, int), 10);
        if (mod->mod == 2)
            ret = ft_itoa_base((unsigned short)va_arg(arg->arg, int), 10);
        if (mod->mod == 3)
            ret = ft_litoa_base(va_arg(arg->arg, long), 10);
        if (mod->mod == 5)
            ret = ft_llitoa_base(va_arg(arg->arg, long long), 10);
    }
    if (arg->specifier == 'o')
    {
        if (mod->mod == 0)
            ret = ft_itoa_base(va_arg(arg->arg, int), 8);
        if (mod->mod == 1)
            ret = ft_itoa_base((short)va_arg(arg->arg, int), 8);
        if (mod->mod == 2)
            ret = ft_itoa_base((unsigned short)va_arg(arg->arg, int), 8);
        if (mod->mod == 3)
            ret = ft_litoa_base(va_arg(arg->arg, long), 8);
        if (mod->mod == 5)
            ret = ft_llitoa_base(va_arg(arg->arg, long long), 8);
    }
    if (arg->specifier == 'x' || arg->specifier == 'X')
    {
        if (mod->mod == 0)
        {
            ret = ft_itoa_base(va_arg(arg->arg, int), 16);
        }
        if (mod->mod == 1)
            ret = ft_itoa_base((short)va_arg(arg->arg, int), 16);
        if (mod->mod == 2)
            ret = ft_itoa_base((unsigned short)va_arg(arg->arg, int), 16);
        if (mod->mod == 3)
            ret = ft_litoa_base(va_arg(arg->arg, long), 16);
        if (mod->mod == 5)
            ret = ft_llitoa_base(va_arg(arg->arg, long long), 16);
        if (arg->specifier == 'X')
            while (ret[index] != '\0')
            {
                ret[index] = ft_toupper(ret[index]);
                index++;
            }
    }
   
    ret = plus_hash(flags, ret, width, arg->specifier);
    if (arg->specifier == 'u')
    {
        if (mod->mod == 0)
            ret = ft_itoa_base(va_arg(arg->arg, int), 10);
        if (mod->mod == 1)
            ret = ft_itoa_base((short)va_arg(arg->arg, int), 10);
        if (mod->mod == 2)
            ret = ft_itoa_base((unsigned short)va_arg(arg->arg, int), 10);
        if (mod->mod == 3)
            ret = ft_litoa_base(va_arg(arg->arg, long), 10);
        if (mod->mod == 5)
            ret = ft_ullitoa_base(va_arg(arg->arg, unsigned long long), 10);
    }
    if (arg->specifier == 'f')
    {
        if (flags->dot > 0 && flags->precision == 0)
            ret = ft_itoa_base((int)va_arg(arg->arg, double), 10);
        else
            ret = ft_float_convert(va_arg(arg->arg, double), flags);
    }
    // Cut for precision
    ret = precision_cut(ret, flags, arg->specifier);
    // printf("width[%i]\n", flags->width)
    ft_width_joiner(width, ret, flags, ft_strlen(ret));
    // printf("ret %s]", ret);
    return (ret);
}