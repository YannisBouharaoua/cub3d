
int parsing(int ac, char **av)
{
    if(not_directory(av))
    {
        if(good_map())
        {
            printf("GoodMap\n");
            return(0);
        }
        printf("BadMap Format\n");
        return(1);
    }
    printf("Is a Directory\n");
    return(1);

}