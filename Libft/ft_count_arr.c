unsigned int	ft_count_arr(void **ar)
{	
    unsigned int i;

    i = 0;
    while (ar[i])
        i++;
    return (i);
}
