/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_key_assign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 20:19:07 by mzouine           #+#    #+#             */
/*   Updated: 2024/08/01 16:52:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int mz_get_key(void)
{
    int random;
    int key;
    int result;

    random = open("/dev/urandom", O_RDONLY);
    if (random < 0)
        return (0);
    result = read(random, &key, sizeof(key));
    if (result < 0)
    {
        close(random);
        return (0);
    }
    close(random);
    return (key);
}

static    int mz_flag(char c, int flag)
{
    if (c == '\'' && flag == 0)
        return (1);// in single quotes
    else if (c == '\'' && flag == 1)
        return (0);// pure
    else if (c == '\"' && flag == 0)
        return (2);// in double quotes
    else if (c == '\"' && flag == 2)
        return (0);// pure
    else
        return (flag);
}

static int  mz_valid(char c, int *flag)
{
    if (c == '_' || (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
        || (c >= 'A' && c<= 'Z'))
        return (1);
    if (c == '?' && *flag == 0)
    {
        *flag = 1;
        return(1);
    }
    return (0);
}

static int  mz_next_word(t_info *info, char *s, char *key)
{
    int n;
    int flag;

    flag = 0;
    n = 0;
    info->i++;
    while (s[info->i] && mz_valid(s[info->i], &flag) == 1)
        info->final[info->j++] = s[info->i++];
    while(key[n])
        info->final[info->j++] = key[n++];
    return (info->j);
}
//   echo $home "$path" '$xxx'
// $?
static int mz_next_q(t_info *info, char *s, char *key, int flag)
{
    int    i;

    i = 0;
    if (flag == 1)
    {
        info->final[info->j] = '$';
        info->i++;
        return (info->j + 1);
    }
    else if (flag == 0)
    {
        while (key[i])
            info->final[info->j++] = key[i++];
        return (mz_next_word(info, s, key));// call the sufix function here and make it return j
    }
    else if (flag == 2)
    {
        while (key[i])
            info->final[info->j++] = key[i++];
        return (mz_next_word(info, s, key));// call the sufix function here and make it return j
    }
    else
        return (-1);
}

static void mz_key_insert(t_info *info, char *s, char *key, char *key_half)
{
    int        flag;

    info->i = 0;
    info->j = 0;
    flag = 0;
    while(s[info->i])
    {
        flag = mz_flag(s[info->i], flag);
        if (s[info->i] == '$')
        {
            if (s[info->i + 1] == '\"' || s[info->i + 1] == '\'')
                info->j = mz_next_q(info, s, key, 1);
            else if (flag == 0)
                info->j = mz_next_q(info, s, key_half, flag);
            else
                info->j = mz_next_q(info, s, key, flag);
        }
        else
            info->final[info->j++] = s[info->i++];
    }
    info->final[info->j] = '\0';
}

static int mz_size_count(char *s, char *key_s)
{
    int    i;
    int    j;

    i = 0;
    j = 0;
    while (s[i])
    {
        if (s[i] == '$')
            j++;
        i++;
    }
    j = j * (ft_strlen(key_s) + 1) * 2;
    j = j + ft_strlen(s) + 1;
    return (j);
}

int    mz_key_assign(char **s)
{
    int        key;
    char    *key_s;
    t_info    info;
    char    *key_half;

    key = mz_get_key();
    if (key < 0)
        key = key * -1;
    key_s = ft_itoa(key, -1,NULL);
    key_half = ft_itoa(key / 2, -1, NULL);
    info.final = malloc(mz_size_count(*s, key_s));
    mz_key_insert(&info, *s, key_s, key_half);
    // free(*s);
    *s = info.final;
    return (key);
}

// int main(int ac, char **av)
// {
//     int i = 0;
//     int    len = ft_strlen(av[1]);
//     char *s;
//     int key;
//     s = malloc (len + 1);
//     while (av[1][i])
//     {
//         s[i] = av[1][i];
//         i++;
//     }
//     s[i] = '\0';
//     i = 0;
//     printf("Before= * %s * \n", s);
//     key = mz_key_assign(&s);
//     printf("Afterr= * %s * \n->>> %i", s, key);
// }
//echo $pasd "adsad $home sda" 'asdas $pfe '
