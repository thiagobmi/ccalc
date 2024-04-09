#include "../include/mystring.h"

char *cut_string(char *str, int start, int end)
{

	int j =0;
	char *r = malloc(sizeof(char)*(end-start)+1);
	for(int i = start; i<end;i++)
		r[j++]=str[i];

	r[j]='\0';
	return r;
}


char **split_string(char *str)
{
    int len = strlen(str);
    char **m = malloc(sizeof(char *) * len);

    for (int i = 0; i < len; i++)
    {
        m[i] = malloc(sizeof(char) * 2);
        m[i][0] = str[i];
        m[i][1] = '\0';
    }

    return m;
}

int is_in_string(char *str, char *a)
{

    int flag = 0;
    int count = 0;
    int count_2 = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == a[0])
        {
            for (int j = 0; j < strlen(a); j++)
            {
                if (i + j > strlen(str))
                    return 0;

                if (str[i + j] == a[j])
                    count++;
            }
            if (count == strlen(a))
                return 1;
            else
                count = 0;
        }
    }

    return 0;
}

int find_next_nan(char *str, int index)
{
    for (int i = index; i < strlen(str); i++)
        if (!isdigit(str[i]) && str[i] != '.')
            return i;
}

char *slice_str(char *str, int start, int end)
{
    char *r = malloc(sizeof(char) * (end - start + 1));

    int j = 0;
    for (int i = start; i < end; i++)
        r[j++] = str[i];
    r[j] = '\0';
    return r;
}

char* concat_strings(int argc,char **argv){


	char* mystr;

    int size = 0;
    for(int i = 0; i<argc;i++)
        size+=strlen(argv[i])+1;
	mystr=malloc(sizeof(char)*size);
        mystr[0] = 0;
   	int offset = 0;
   	while(argv++,--argc) {
      		int toWrite = size-offset;
      		int written = snprintf(mystr+offset, toWrite, "%s ", *argv);
      		if(toWrite < written) {
        	  	break;
      		}
      		offset += written;
   	}
	return mystr;
}



char *add_to_str(char* dest, char* src, int index){
	
	int total_size = (strlen(dest) + strlen(src) + 1);
	char* r = malloc((sizeof(char))*(total_size));

	int j = 0, i=0;
	int len = strlen(src);
	int resto = strlen(dest) - index;

	for(i=0;i<index;i++)
		r[i]=dest[i];
	for(i=index;i<index+strlen(src);i++)
		r[i]=src[j++];
	for(j=index,i=index+strlen(src);i<index+strlen(src)+resto;i++)
		r[i]=dest[j++];
	r[total_size-1] = '\0';

	return r;

}

int valid_characters(char *str,char*valid)
{


	char **m = split_string(valid);
	int is_valid = 0;

	for (int i = 0; i < strlen(str); i++)
	{
		is_valid = 0;
		for (int j = 0; j < strlen(valid); j++)
			if (str[i] == valid[j])
				is_valid++;
		if (!is_valid)
			return 0;
	}

	return 1;
}

