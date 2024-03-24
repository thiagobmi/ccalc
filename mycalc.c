#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#define MAXLEN 300

typedef struct word
{
	int len;
	char *letters;
} word_t;

typedef struct dict
{
	int len;
	int max_size;
	word_t* words;
} dict_t;

typedef struct shelf
{
	int len;
	int max_size;
	dict_t **d;
} shelf_t;

dict_t* new_dict(int max_size)
{
	dict_t* d = malloc(sizeof(dict_t));
	d->max_size = max_size;
	d->len=0;
	d->words = malloc(sizeof(word_t)*max_size);
	return d;
}

word_t new_word(char* w)
{
	word_t word;
	word.letters = malloc(sizeof(char)*strlen(w));
	strcpy(word.letters,w);
	word.len = strlen(w);
	return word;
}

dict_t* resize_dict(dict_t* d,int new_size)
{
	if(new_size < d->max_size)
		return d;
	d->max_size = new_size;
	d->words = realloc(d->words,new_size*sizeof(word_t));
	return d;
}

dict_t* add_word(dict_t *d, char* w)
{
	if(d->len + 1 == d->max_size)
		d = resize_dict(d,d->max_size+10);

	d->words[d->len] = new_word(w);
	d->len++;
	return d;
}

shelf_t *new_shelf(int max_size){
	
	shelf_t *s = malloc(sizeof(shelf_t));
	s->d = malloc(sizeof(dict_t*)*max_size);
	s->max_size = max_size;
	s->len=0;
	return s;
}

shelf_t *resize_shelf(shelf_t *s, int new_size){
	if(new_size < s->max_size)
		return s;

	s->max_size = new_size;
	s->d = realloc(s->d, new_size*sizeof(dict_t*));
	return s;
}

shelf_t *add_dict(shelf_t *s,dict_t *d){
	if(s->len + 1 == s->max_size)
		s = resize_shelf(s,s->max_size+10);
	s->d[s->len] = d;
	s->len++;
	return s;
}

char* receive_input()
{
	char* str = malloc(sizeof(char)*MAXLEN);
        scanf("%[^\n]", str);
	return str;
}

int find_bracket(char* str, int index)
{

	int count_open = 1;
	for(int i=index;i<strlen(str);i++){
		if(str[i]=='(')
			count_open++;
		else if(str[i]==')')
			count_open--;
		if(count_open==0)
			return i+1;
	}
}

char *cut_string(char *str, int start, int end)
{

	int j =0;
	char *r = malloc(sizeof(char)*(end-start)+1);
	for(int i = start; i<end;i++)
		r[j++]=str[i];

	r[j]='\0';
	return r;
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

int bracket_type(char *str,int start,int end){

        int count_open=-1;
        for(int i=start;i<end;i++){
                if(str[i] == '(')
                        count_open++;
                else if(str[i]==')')
                        count_open--;
                if((str[i]=='*' || str[i]=='/') && count_open==0)
                        return 1;
		else if((str[i]=='+' || str[i]=='-') && count_open==0)
			return 2;
		else if(str[i]=='^' && count_open==0)
			return 3;
        }
	return -1;
}


int find_next_sign(char* str,int index){

	int count_open=0;
	for(int i=index;i<strlen(str);i++){
		if(str[i] == '(')
			count_open++;
		else if(str[i]==')')
			count_open--;
		if(count_open<0)
			return i;
		if(((str[i]=='-' || str[i]=='+') && count_open==0))
			return i;
	}	
}

int find_last_sign(char *str,int index){
        int count_open=0;
        for(int i=index;i>=0;i--){
		if(i==0)
			return -1;
                if(str[i] == ')')
                        count_open++;
                else if(str[i]=='(')
                        count_open--;
                if(count_open<0)
                        return i;
                if(((str[i]=='-' || str[i]=='+') && count_open==0))
                        return i;
        }
}


int find_next_sign_e(char* str,int index){

        int count_open=0;
        for(int i=index;i<strlen(str);i++){
                if(str[i] == '(')
                        count_open++;
                else if(str[i]==')')
                        count_open--;
                if(count_open<0)
                        return i;
                if((str[i]=='-' || str[i]=='+') && count_open==0)
                        return i;
		if((str[i]=='*' || str[i]=='/') && count_open==0)
			return i;
        }
}

int find_last_sign_e(char *str,int index){
        int count_open=0;
        for(int i=index;i>=0;i--){
                if(i==0)
                        return -1;
                if(str[i] == ')')
                        count_open++;
                else if(str[i]=='(')
                        count_open--;
                if(count_open<0)
                        return i;
                if((str[i]=='-' || str[i]=='+') && count_open==0)
                        return i;

		if((str[i]=='*' || str[i]=='/') && count_open==0)
			return i;
        }
}



char*add_all_exp(char *str, int start, int end){

	for(int i=start;i<end;i++){
		if(str[i]=='^'){
			int next=find_next_sign_e(str,i);
	                int last=find_last_sign_e(str,i);
	                str = add_to_str(str,")",next);
	                i = next;
	               	str = add_to_str(str,"(",last+1);
	        }
	}
	return str;
}


char* add_brackets(char *str,int start,int end,int flag){
	
	for(int i=start;i<end;i++){
		if(str[i]=='*' || str[i]=='/') {
			int next=find_next_sign(str,i);
			int last=find_last_sign(str,i);
			str = add_to_str(str,")",next);
			i = next;
			str = add_to_str(str,"(",last+1);
			if(flag)
				end=strlen(str);
		}
		else if(str[i]=='^'){
			int next=find_next_sign_e(str,i);
			int last=find_last_sign_e(str,i);
			str = add_to_str(str,")",next);
			i = next;
			str = add_to_str(str,"(",last+1);
			if(flag)
				end=strlen(str);
		}
	}
	
	return str;	
}

int check_signs(char*str, int start, int end){

	int count_open=-1;
	int is_plus=0;
	int is_times=0;
	int is_exponential=0;

	for(int i=start;i<end;i++){
		if(str[i] == '(')
                        count_open++;
                else if(str[i]==')')
                        count_open--;
		else if((str[i]=='+' || str[i]=='-') && count_open==0)
			is_plus++;
		else if((str[i]=='*' || str[i]=='/') && count_open==0)
			is_times++;
		else if(str[i]=='^' && count_open==0)
			is_exponential++;
	}
	if((is_times && is_plus) || (is_exponential && is_plus))
		return 1;
	else if(is_times && is_exponential)
	       return 2;

	return 0;
}


char *slice_str(char*str,int start, int end){
	char *r = malloc(sizeof(char)*(end-start+1));

	int j=0;
	for(int i=start;i<end;i++)
		r[j++] = str[i];
	r[j] = '\0';
	return r;

}


int is_edge_case(char* str, int start, int end){
	for(int i=0;i<strlen(str)-1;i++)
		if((str[i]=='/' || str[i]=='*') && str[i+1]=='-')
			return 1;
	return 0;
}

int find_next_nan(char*str, int index){
	for(int i=index;i<strlen(str);i++)
		if(!isdigit(str[i]) && str[i]!='.')
			return i;
}

char* treat_edge_case(char *str){
	int count_open=0;
        for(int i=0;i<strlen(str)-1;i++){
		int a;
                if(((str[i]=='/' || str[i]=='*') && str[i+1]=='-')){
			if(str[i+2]!='('){
                        	str = add_to_str(str,"(",i+1);
				a = find_next_nan(str,i+1);
				i++;
				str = add_to_str(str,")",find_next_nan(str,i+2));
			}
			else{
                        	str = add_to_str(str,"(",i+1);
				i++;
				str = add_to_str(str,")",find_bracket(str,i+3));
        		}
		}
	}
	return str;
}

char* add_more(char* str){
	
	for(int i=0; i<strlen(str);i++){
		if(str[i]=='('){
			if(check_signs(str,i,find_bracket(str,i+1))==1){
				str = add_brackets(str,i,find_bracket(str,i+1),0);
				i=0;
			}
			else if(check_signs(str,i,find_bracket(str,i+1))==2){
				str = add_all_exp(str,i,find_bracket(str,i+1));
				i=0;
			}
			
		}
	}
	return str;

}

char *parse_factor(char *mystring,shelf_t *s);
char *parse_exponential(char *mystring,shelf_t *s);


char *parse_sum(char *mystring,shelf_t *s)
{

	double numbers[100];
	char buffer[500];
	int b_len=0;
	double sum = 0;
	char* result = malloc(sizeof(char)*20);
	
	dict_t *d = new_dict(10);	
	buffer[0]='\0';

	for(int i=0;i<strlen(mystring)+1;i++){
		
		if(mystring[i]=='(')
		{

                        if(bracket_type(mystring,i,find_bracket(mystring,i+1)-1)==1){
                                strcat(buffer,parse_factor(cut_string(mystring,i+1,find_bracket(mystring,i+1)-1),s));
                        }
                        else if(bracket_type(mystring,i,find_bracket(mystring,i+1)-1)==2){
                                strcat(buffer,parse_sum(cut_string(mystring,i+1,find_bracket(mystring,i+1)-1),s));
                        }
                        else{
                                strcat(buffer,parse_exponential(cut_string(mystring,i+1,find_bracket(mystring,i+1)-1),s));
                        }

                        b_len = strlen(buffer);
                        i = find_bracket(mystring,i+1)-1;
                }
		else if(mystring[i]==' ')
			continue;

		else if(mystring[i]=='-')
		{
			buffer[b_len]='\0';
                        add_word(d,buffer);
			buffer[0]='-';
			buffer[1]='\0';
                        b_len=1;
		}
		else if(mystring[i]=='+' || mystring[i]=='\0')
		{
                        buffer[b_len]='\0';
                        add_word(d,buffer);
                        b_len=0;
			buffer[0]='\0';
                }
		else if(mystring[i]!='+')
		{
			buffer[b_len]=mystring[i];
			b_len++;
		}

	}

	for(int i=0;i<d->len;i++)
	{
		numbers[i] = atof(d->words[i].letters);
		sum+=numbers[i];
	}

	sprintf(result, "%lf", sum);

        dict_t *ds = new_dict(2);
        ds = add_word(ds,mystring);
        ds = add_word(ds,result);
        s = add_dict(s,ds);

	return result;
}

char *parse_factor(char *mystring,shelf_t *s)
{

	double numbers[100];
	char buffer[500];
	int b_len=0;
	double sum = 1;
	char* result = malloc(sizeof(char)*10);
	
	dict_t *d = new_dict(20);	
	buffer[0]='\0';

	for(int i=0;i<strlen(mystring)+1;i++){
		
		if(mystring[i]=='(')
		{
                        if(bracket_type(mystring,i,find_bracket(mystring,i+1)-1)==1){
                                strcat(buffer,parse_factor(cut_string(mystring,i+1,find_bracket(mystring,i+1)-1),s));
                        }
                        else if(bracket_type(mystring,i,find_bracket(mystring,i+1)-1)==2){
                                strcat(buffer,parse_sum(cut_string(mystring,i+1,find_bracket(mystring,i+1)-1),s));
                        }
                        else{
                                strcat(buffer,parse_exponential(cut_string(mystring,i+1,find_bracket(mystring,i+1)-1),s));
                        }
                        b_len = strlen(buffer);
                        i = find_bracket(mystring,i+1)-1;
                }
		else if(mystring[i]==' ')
			continue;
		else if(mystring[i]=='/')
		{
			buffer[b_len]='\0';
                        add_word(d,buffer);
			buffer[0]='/';
			buffer[1]='\0';
                        b_len=1;
		}

		else if(mystring[i]=='*' || mystring[i]=='\0')
		{
                        buffer[b_len]='\0';
                        add_word(d,buffer);
                        b_len=0;
			buffer[0]='\0';
                }
		else if(mystring[i]!='*' && mystring[i]!='/')
		{
			buffer[b_len]=mystring[i];
			b_len++;
		}

	}

	for(int i=0;i<d->len;i++)
	{

		if(d->words[i].letters[0]=='/'){
			numbers[i] = atof(cut_string(d->words[i].letters,1,strlen(d->words[i].letters)));
			sum/=numbers[i];
			continue;
		}
		numbers[i] = atof(d->words[i].letters);
		sum*=numbers[i];
	}

	
	sprintf(result, "%lf", sum);

        dict_t *ds = new_dict(2);
        ds = add_word(ds,mystring);
        ds = add_word(ds,result);
        s = add_dict(s,ds);

	return result;
}


char *parse_exponential(char *mystring, shelf_t *s)
{

        double numbers[100];
        char buffer[500];
        int b_len=0;
        double sum = 1;
        char* result = malloc(sizeof(char)*10);

        dict_t *d = new_dict(20);
        buffer[0]='\0';

        for(int i=0;i<strlen(mystring)+1;i++){

                if(mystring[i]=='(')
                {
                        if(bracket_type(mystring,i,find_bracket(mystring,i+1)-1)==1){
                                strcat(buffer,parse_factor(cut_string(mystring,i+1,find_bracket(mystring,i+1)-1),s));
                        }
                        else if(bracket_type(mystring,i,find_bracket(mystring,i+1)-1)==2){
                                strcat(buffer,parse_sum(cut_string(mystring,i+1,find_bracket(mystring,i+1)-1),s));
                        }
			else{
				strcat(buffer,parse_exponential(cut_string(mystring,i+1,find_bracket(mystring,i+1)-1),s));
			}
                        b_len = strlen(buffer);
                        i = find_bracket(mystring,i+1)-1;
                }

                else if(mystring[i]==' ')
                        continue;
                else if(mystring[i]=='^' || mystring[i]=='\0')
                {
                        buffer[b_len]='\0';
                        add_word(d,buffer);
		        b_len=0;
                        buffer[0]='\0';
                }

                else if(mystring[i]!='^')
                {
                        buffer[b_len]=mystring[i];
                        b_len++;
                }

        }
	

        for(int i=0;i<d->len;i++)
        {
                numbers[i] = atof(d->words[i].letters);
                sum =  pow((double)sum,(double)numbers[i]);
		if(i==0)
			sum=numbers[i];
        }

        sprintf(result, "%lf", sum);

        dict_t *ds = new_dict(2);
        ds = add_word(ds,mystring);
        ds = add_word(ds,result);
        s = add_dict(s,ds);

        return result;
}


char *parse_expression(char* mystr){

	shelf_t *s = new_shelf(1);
	mystr=treat_edge_case(mystr);
	mystr=add_brackets(mystr,0,strlen(mystr),1);
	mystr = add_more(mystr);
	mystr= add_all_exp(mystr,0,strlen(mystr));

	printf("\n%s\n",mystr);

	char *result = parse_sum(mystr,s);

	for(int i=0;i<s->len;i++){
		dict_t *ds = s->d[i];
		printf("\nResolvendo: %s\n",ds->words[0].letters);
		printf("[%s = %s]\n",ds->words[0].letters,ds->words[1].letters);


	}
	return result;
}


char* concat_strings(int argc,char **argv){


	char* mystr;
	mystr=malloc(sizeof(char)*MAXLEN);
        mystr[0] = 0;
   	int offset = 0;
   	while(argv++,--argc) {
      		int toWrite = MAXLEN-offset;
      		int written = snprintf(mystr+offset, toWrite, "%s ", *argv);
      		if(toWrite < written) {
        	  	break;
      		}
      		offset += written;
   	}
	return mystr;
}

int valid_brackets(char* str){

	int count_open = 0;
	int len = strlen(str);
        for(int i=0;i<len;i++){
                if(str[i]=='(')
                        count_open++;
                else if(str[i]==')')
                        count_open--;
                if(count_open < 0)
                        return 0;
        }

	if(count_open != 0)
		return 0;
	return 1;


}

char **split_string(char *str){

	int len = strlen(str);

	char **m = malloc(sizeof(char*)*len);

	for(int i = 0; i< len;i++){
		m[i] = malloc(sizeof(char)*2);
		m[i][0] = str[i];
		m[i][1] = '\0';
	}

	return m;

}


int is_in_string(char *str, char *a){
	
	int flag = 0;
	int count = 0;
	int count_2 = 0;

	for(int i=0;i<strlen(str);i++){
		if(str[i] == a[0]){
			for(int j=0;j<strlen(a);j++){
				if(i+j > strlen(str))
					return 0;

				if(str[i+j]==a[j])
					count++;
			}
			if(count == strlen(a))
				return 1;
			else 
				count = 0;
		}
	}

	return 0;

}

int valid_characters(char *str){
	
	char *valid = "()1234567890-+^*/. ";
	char ** m = split_string(valid);
	int is_valid = 0;

	for(int i=0;i<strlen(str);i++){
		is_valid=0;
		for(int j=0;j<strlen(valid);j++)
			if(str[i]==valid[j])
				is_valid++;
		if(!is_valid)
			return 0;
	}

	return 1;
}


int validate_expression(char *str){
	if(!valid_characters(str)){
		return 1;
	}
	if(!valid_brackets(str)){
	   return 1;
	}
	if(is_in_string(str,"()")){
	   return 1;
	}
	if(is_in_string(str,"//")){
	   return 1;	
	}
	if(is_in_string(str,"**")){
	   return 1;
	}
	if(is_in_string(str,"^^")){
		return 1;
	}

	if(is_in_string(str,"++")){
		return 1;
	}

	if(is_in_string(str,"--")){
		return 1;
	}

	if(str[strlen(str)-2]=='+' || str[strlen(str)-2]=='-' || str[strlen(str)-2]=='/' || str[strlen(str)-2]=='*' ||str[strlen(str)-2]=='*')
	{
		return 1;

	}
	if(str[0]=='+' || str[0]=='-' || str[0]=='/' || str[0]=='*' ||str[0]=='*')
	{
		return 1;

	}
	if(is_in_string(str,"+)"))
		return 1;

	if(is_in_string(str,"-)"))
		return 1;

	if(is_in_string(str,"*)"))
		return 1;

	if(is_in_string(str,"/)"))
		return 1;

	if(is_in_string(str,"^)"))
		return 1;

	if(is_in_string(str,"(+"))
		return 1;

	if(is_in_string(str,"(*"))
		return 1;

	if(is_in_string(str,"(/"))
		return 1;

	if(is_in_string(str,"(^"))
		return 1;



	else return 0;
}

int main(int argc, char** argv)
{

	char* mystr;

	if(argc>1)
		mystr = concat_strings(argc,argv);
        else
                mystr = receive_input();

	if(validate_expression(mystr)==0)
		printf("\n\n\t\t%s\n",parse_expression(mystr));
}

