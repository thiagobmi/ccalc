#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "./include/mystring.h"
#include "./include/dict.h"

#define MAXLEN 1000

char *receive_input()
{
	char *str = malloc(sizeof(char) * MAXLEN);
	scanf("%[^\n]", str);
	return str;
}

int find_bracket(char *str, int index)
{
	int count_open = 1;
	for (int i = index; i < strlen(str); i++)
	{
		if (str[i] == '(')
			count_open++;
		else if (str[i] == ')')
			count_open--;
		if (count_open == 0)
			return i + 1;
	}
}

int find_bracket_exp(char *str, int index)
{
	int count_open = 0;
	for (int i = index; i < strlen(str); i++)
	{
		if (str[i] == '(')
			count_open++;
		else if (str[i] == ')')
			count_open--;
		if (count_open == 0)
			return i + 1;
	}
}
int bracket_type(char *str, int start, int end)
{
	int count_open = -1;
	for (int i = start; i < end; i++)
	{
		if (str[i] == '(')
			count_open++;
		else if (str[i] == ')')
			count_open--;
		if ((str[i] == '*' || str[i] == '/') && count_open == 0)
			return 1;
		else if ((str[i] == '+' || str[i] == '-') && count_open == 0)
			return 2;
		else if (str[i] == '^' && count_open == 0)
			return 3;
	}
	return -1;
}

int find_next_sign(char *str, int index)
{
	int count_open = 0;
	for (int i = index; i < strlen(str); i++)
	{
		if (str[i] == '(')
			count_open++;
		else if (str[i] == ')')
			count_open--;
		if (count_open < 0)
			return i;
		if (((str[i] == '-' || str[i] == '+') && count_open == 0))
			return i;
	}
}

int find_next_number(char *str, int index)
{
	int count_open = 0;
	for (int i = index; i < strlen(str); i++)
	{
		if (str[i] == '(')
			count_open++;
		else if (str[i] == ')')
			count_open--;
		if (count_open < 0)
			return i;
		if ((isdigit(str[i])) && count_open == 0)
			return i;
	}
}
int find_last_sign(char *str, int index)
{
	int count_open = 0;
	for (int i = index; i >= 0; i--)
	{
		if (i == 0)
			return -1;
		if (str[i] == ')')
			count_open++;
		else if (str[i] == '(')
			count_open--;
		if (count_open < 0)
			return i;
		if (((str[i] == '-' || str[i] == '+') && count_open == 0))
			return i;
	}
}

int find_next_exp(char *str, int index){

	int count_open = 0;
	for (int i = index; i < strlen(str); i++)
	{
		if (str[i] == '(')
			count_open++;
		else if (str[i] == ')')
			count_open--;
		if (count_open < 0)
			return i;
		if ((str[i] == '^') && count_open == 0)
			return i;
	}
}

int find_next_sign_exp(char *str, int index)
{

	int count_open = 0;
	for (int i = index; i < strlen(str); i++)
	{
		if (str[i] == '(')
			count_open++;
		else if (str[i] == ')')
			count_open--;
		if (count_open < 0)
			return i;
		if ((str[i] == '-' || str[i] == '+') && count_open == 0)
			return i;
		if ((str[i] == '*' || str[i] == '/') && count_open == 0)
			return i;
	}
}

int find_last_sign_exp(char *str, int index)
{
	int count_open = 0;
	for (int i = index; i >= 0; i--)
	{
		if (i == 0)
			return -1;
		if (str[i] == ')')
			count_open++;
		else if (str[i] == '(')
			count_open--;
		if (count_open < 0)
			return i;
		if ((str[i] == '-' || str[i] == '+') && count_open == 0)
			return i;

		if ((str[i] == '*' || str[i] == '/') && count_open == 0)
			return i;
	}
}




char *add_all_exp(char *str, int start, int end)
{
	
	for (int i = start; i < end; i++)
	{
		if (str[i] == '^')
		{
			
			int last = find_last_sign_exp(str, i);
			str = add_to_str(str, "(", last + 1);
			i++;
			int next;
			if(str[i+1] != '('){
				int a = find_next_number(str,i+1);
				next = find_next_sign_exp(str, a);
			}
			else{
				next = find_bracket_exp(str,i+1);
			}

			str = add_to_str(str, ")", next);
			i = next;
			end = strlen(str);
		}
	}
	
	return str;

}

void print_result(char*str){

	int index = strlen(str)-1;
	
	while(str[index] =='0')
		index--;
	
	if(str[index]=='.')
		index--;
	
	for(int i=0;i<=index;i++)
		printf("%c",str[i]);
}

void display_result(char* str){

	printf("\n\n\t");
	
	print_result(str);	

	printf("\n\n");


}

char *add_brackets(char *str, int start, int end, int flag)
{

	for (int i = start; i < end; i++)
	{
		if (str[i] == '*' || str[i] == '/')
		{
			int next = find_next_sign(str, i);
			int last = find_last_sign(str, i);
			str = add_to_str(str, ")", next);
			i = next;
			str = add_to_str(str, "(", last + 1);
			if (flag)
				end = strlen(str);
		}
		else if (str[i] == '^')
		{
			int a = find_next_number(str,i+1);
			int next = find_next_sign_exp(str, a);
			int last = find_last_sign_exp(str, i);
			str = add_to_str(str, ")", next);
			i = next;
			str = add_to_str(str, "(", last + 1);
			if (flag)
				end = strlen(str);
		}
	}

	return str;
}

int check_signs(char *str, int start, int end)
{

	int count_open = -1;
	int is_plus = 0;
	int is_times = 0;
	int is_exponential = 0;

	for (int i = start; i < end; i++)
	{
		if (str[i] == '(')
			count_open++;
		else if (str[i] == ')')
			count_open--;
		else if ((str[i] == '+' || str[i] == '-') && count_open == 0)
			is_plus++;
		else if ((str[i] == '*' || str[i] == '/') && count_open == 0)
			is_times++;
		else if (str[i] == '^' && count_open == 0)
			is_exponential++;
	}
	if ((is_times && is_plus))
		return 1;
	else if (is_times && is_exponential)
		return 2;
	else if(is_exponential && is_plus)
		return 3;
	else if (is_exponential > 1)
		return 4;
	return 0;
}

int is_edge_case(char *str, int start, int end)
{
	for (int i = 0; i < strlen(str) - 1; i++)
		if ((str[i] == '/' || str[i] == '*' || str[i] == '^') && (str[i + 1] == '-' || str[i+1] =='+'))
			return 1;
	return 0;
}


char *treat_edge_case(char *str)
{
	int count_open = 0;
	for (int i = 0; i < strlen(str) - 1; i++)
	{
		int a;
		if ((str[i] == '/' || str[i] == '*' || str[i] == '-' || str[i]=='^') && (str[i + 1] == '-' || str[i + 1] == '+'))
		{
			if (str[i + 2] != '(')
			{

				str = add_to_str(str, "(", i + 1);      
			        a = find_next_number(str, i + 1);
				i++;
				str = add_to_str(str, ")", find_next_nan(str, a));
			}
			else
			{
				str = add_to_str(str, "(", i + 1);
				i++;
				str = add_to_str(str, ")", find_bracket(str, i + 3));
			}
		}
	}
	return str;
}


char *treat_exp(char*str,int start, int end){

	int count_open = 0;
	for(int j = start;j<end;j++){

		if(str[j] == '(')
			count_open++;
		else if (str[j]==')')
			count_open--;
		if(str[j] == '^' && count_open ==1){
			str = add_to_str(str,"(", j+1);
			j++;
			int a = find_next_number(str,j);
			int next = find_next_exp(str,a);
			str = add_to_str(str,")",next);
			break;
		}
	}
	
	return str;		

}

char *add_brackets_inside(char *str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == '(')
		{
			if(check_signs(str,i,find_bracket(str,i+1)) == 4){
				str = treat_exp(str,i,find_bracket(str,i+1));
				i = 0;
			}

			if (check_signs(str, i, find_bracket(str, i + 1)) == 1)
			{
				str = add_brackets(str, i, find_bracket(str, i + 1), 1);
				i = 0;
			}
			if(check_signs(str,i,find_bracket(str,i+1))==2){
				str = add_all_exp(str,i,find_bracket(str,i+1));
				i=0;
			}			

			if(check_signs(str,i,find_bracket(str,i+1))==3){
				for(int j = i;j < strlen(str);j++){
					if(str[j] == '^'){
						int last = find_last_sign(str,j);
						str = add_to_str(str,"(", last+1);
						j++;
						int next = find_next_sign(str,j);
						str = add_to_str(str,")",next);
						i=0;
						break;
					}
				}
			}
		}
	}
	return str;
}

char *parse_factor(char *mystring, shelf_t *s);
char *parse_exponential(char *mystring, shelf_t *s);

char *parse_sum(char *mystring, shelf_t *s)
{

	double numbers[MAXLEN];
	char buffer[MAXLEN];
	int b_len = 0;
	double sum = 0;
	char *result = malloc(sizeof(char) * 50);

	dict_t *d = new_dict(10);
	buffer[0] = '\0';

	for (int i = 0; i < strlen(mystring) + 1; i++)
	{

		if(buffer[0]=='-' && buffer[1]=='-'){
			for(int j=0;j<strlen(buffer)-2;j++){
				buffer[j] = buffer[j+2];
			}
		}

		if (mystring[i] == '(')
		{
			int start = i + 1;
			int brk_type = bracket_type(mystring, i, find_bracket(mystring, start) - 1);
			int end = find_bracket(mystring,start) - 1;
 
			if (brk_type == 1)
			{
				strcat(buffer, parse_factor(cut_string(mystring, start, end), s));
			}
			else if (brk_type == 2)
			{
				strcat(buffer, parse_sum(cut_string(mystring, start, end), s));
			}
			else
			{
				strcat(buffer, parse_exponential(cut_string(mystring, start, end), s));
			}

			b_len = strlen(buffer);
			i = end;
		}

		else if (mystring[i] == ' ')
			continue;

		else if (mystring[i] == '-')
		{
			buffer[b_len] = '\0';

			if(b_len>0)
				add_word(d, buffer);

			buffer[0] = '-';
			buffer[1] = '\0';
			b_len = 1;
		}
		else if (mystring[i] == '+' || mystring[i] == '\0')
		{
			buffer[b_len] = '\0';

			if(b_len>0)
				add_word(d, buffer);

			b_len = 0;
			buffer[0] = '\0';
		}
		else if (mystring[i] != '+')
		{
			buffer[b_len] = mystring[i];
			b_len++;
		}
	}

	for (int i = 0; i < d->len; i++)
	{
		numbers[i] = atof(d->words[i].letters);
		sum += numbers[i];
	}

	sprintf(result, "%.13lf", sum);

	dict_t *ds = new_dict(2);
	ds = add_word(ds, mystring);
	ds = add_word(ds, result);
	s = add_dict(s, ds);

	return result;
}

char *parse_factor(char *mystring, shelf_t *s)
{

	double numbers[MAXLEN];
	char buffer[MAXLEN];
	int b_len = 0;
	double sum = 1;
	char *result = malloc(sizeof(char) * 50);

	dict_t *d = new_dict(10);
	buffer[0] = '\0';

	for (int i = 0; i < strlen(mystring) + 1; i++)
	{

		if (mystring[i] == '(')
		{
			int start = i + 1;
			int brk_type = bracket_type(mystring, i, find_bracket(mystring, start) - 1);
			int end = find_bracket(mystring,start) - 1;
 
			if (brk_type == 1)
			{
				strcat(buffer, parse_factor(cut_string(mystring, start, end), s));
			}
			else if (brk_type == 2)
			{
				strcat(buffer, parse_sum(cut_string(mystring, start, end), s));
			}
			else
			{
				strcat(buffer, parse_exponential(cut_string(mystring, start, end), s));
			}

			b_len = strlen(buffer);
			i = end;
		}
		else if (mystring[i] == ' ')
			continue;
		else if (mystring[i] == '/')
		{
			buffer[b_len] = '\0';
			add_word(d, buffer);
			buffer[0] = '/';
			buffer[1] = '\0';
			b_len = 1;
		}

		else if (mystring[i] == '*' || mystring[i] == '\0')
		{
			buffer[b_len] = '\0';
			add_word(d, buffer);
			b_len = 0;
			buffer[0] = '\0';
		}
		else if (mystring[i] != '*' && mystring[i] != '/')
		{
			buffer[b_len] = mystring[i];
			b_len++;
		}
	}

	for (int i = 0; i < d->len; i++)
	{

		if (d->words[i].letters[0] == '/')
		{
			numbers[i] = atof(cut_string(d->words[i].letters, 1, strlen(d->words[i].letters)));
			sum /= numbers[i];
			continue;
		}
		numbers[i] = atof(d->words[i].letters);
		sum *= numbers[i];
	}

	sprintf(result, "%.13lf", sum);

	dict_t *ds = new_dict(2);
	ds = add_word(ds, mystring);
	ds = add_word(ds, result);
	s = add_dict(s, ds);

	return result;
}

char *parse_exponential(char *mystring, shelf_t *s)
{

	double numbers[MAXLEN];
	char buffer[MAXLEN];
	int b_len = 0;
	double sum = 1;
	char *result = malloc(sizeof(char) * 50);

	dict_t *d = new_dict(10);
	buffer[0] = '\0';

	for (int i = 0; i < strlen(mystring) + 1; i++)
	{

		if (mystring[i] == '(')
		{
			int start = i + 1;
			int brk_type = bracket_type(mystring, i, find_bracket(mystring, start) - 1);
			int end = find_bracket(mystring,start) - 1;
 
			if (brk_type == 1)
			{
				strcat(buffer, parse_factor(cut_string(mystring, start, end), s));
			}
			else if (brk_type == 2)
			{
				strcat(buffer, parse_sum(cut_string(mystring, start, end), s));
			}
			else
			{
				strcat(buffer, parse_exponential(cut_string(mystring, start, end), s));
			}

			b_len = strlen(buffer);
			i = end;
		}

		else if (mystring[i] == ' ')
			continue;
		else if (mystring[i] == '^' || mystring[i] == '\0')
		{
			buffer[b_len] = '\0';
			add_word(d, buffer);
			b_len = 0;
			buffer[0] = '\0';
		}

		else if (mystring[i] != '^')
		{
			buffer[b_len] = mystring[i];
			b_len++;
		}
	}
	for (int i = 0; i < d->len; i++)
	{
		numbers[i] = atof(d->words[i].letters);
		sum = pow((double)sum, (double)numbers[i]);
		if (i == 0)
			sum = numbers[i];
	}

	sprintf(result, "%.13lf", sum);

	dict_t *ds = new_dict(2);
	ds = add_word(ds, mystring);
	ds = add_word(ds, result);
	s = add_dict(s, ds);

	return result;
}

char *parse_expression(char *mystr)
{

	shelf_t *s = new_shelf(1);
	mystr = add_all_exp(mystr, 0, strlen(mystr));
	mystr = add_brackets(mystr, 0, strlen(mystr), 1);
	mystr = treat_edge_case(mystr);
	mystr = add_brackets_inside(mystr);
	printf("\n%s\n", mystr);

	char *result = parse_sum(mystr, s);

	int max_left_length = 0;
	for (int i = 0; i < s->len; i++)
	{
		dict_t *ds = s->d[i];
		int left_length = strlen(ds->words[0].letters);
		if (left_length > max_left_length)
		{
			max_left_length = left_length;
		}
	}

	for (int i = 0; i < s->len; i++)
	{
		dict_t *ds = s->d[i];
		printf("\nSolving: %s", ds->words[0].letters);
		int space_count = max_left_length - strlen(ds->words[0].letters);
		for (int j = 0; j < space_count; j++)
		{
			printf(" ");
		}

		printf(" = ");
		print_result(ds->words[1].letters);
	}
	return result;
}

int valid_brackets(char *str)
{

	int count_open = 0;
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (str[i] == '(')
			count_open++;
		else if (str[i] == ')')
			count_open--;
		if (count_open < 0)
			return 0;
	}

	if (count_open != 0)
		return 0;
	return 1;
}


int validate_expression(char *str)
{
	char *valid = "()1234567890-+^*/. ";
	if (!valid_characters(str, valid))
	{
		return 1;
	}
	if (!valid_brackets(str))
	{
		
		return 1;
	}
	if (is_in_string(str, "()"))
	{

		return 1;
	}
	if (is_in_string(str, "//"))
	{
		return 1;
	}
	if (is_in_string(str, "**"))
	{
		return 1;
	}
	if (is_in_string(str, "^^"))
	{
		return 1;
	}

	if (is_in_string(str, "++"))
	{
		return 1;
	}

	if (str[strlen(str) - 1] == '+' || str[strlen(str) - 1] == '-' || str[strlen(str) - 1] == '/' || str[strlen(str) - 1] == '*' || str[strlen(str) - 1] == '^')
	{
		return 1;
	}
	if (str[0] == '/' || str[0] == '*' || str[0] == '^')
	{
		return 1;
	}
	if (is_in_string(str, "+)"))
		return 1;

	if (is_in_string(str, "-)"))
		return 1;

	if (is_in_string(str, "*)"))
		return 1;

	if (is_in_string(str, "/)"))
		return 1;

	if (is_in_string(str, "^)"))
		return 1;

	if (is_in_string(str, "(+"))
		return 1;

	if (is_in_string(str, "(*"))
		return 1;

	if (is_in_string(str, "/*"))
		return 1;
	if (is_in_string(str, "(/"))
		return 1;

	if (is_in_string(str, "(^"))
		return 1;

	if (is_in_string(str, "+/"))
		return 1;

	if (is_in_string(str, "+*"))
		return 1;

	if (is_in_string(str, "+^"))
		return 1;

	if (is_in_string(str, ")("))
		return 1;

	else
		return 0;
}

int main(int argc, char **argv)
{

	char *mystr;

	if (argc > 1)
		mystr = concat_strings(argc, argv);
	else
		mystr = receive_input();

	mystr = remove_all_whitespaces(mystr);

	if (validate_expression(mystr) == 0)
		display_result(parse_expression(mystr));
}
