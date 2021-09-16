void memory_copy(char * source, char * destination, int no_bytes)
{
    for (int i = 0; i < no_bytes; i++) 
        *(destination + i) = *(source + i);
}
