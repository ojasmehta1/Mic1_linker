#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define HEADERS 1
#define NO_HEADERS 0

typedef struct node {
  char name[26];
  int addr;
  struct node *next;
} Entry;

void add_symb( char *symbol, int line);
void compute(int);
void first_print(int);
void append_table( void );
void dump_table( void ); 
int get_sym_val( char *);

Entry *symtab = NULL;
FILE *f1, *f2;
char str[13];

int main(int argc, char* argv[])
{
  int i = 0;
  int start = 0;
  int pc_offset = 0;
  int pc = 0;
  int linum = 0;
  int obj_file = 0;
  int dump_tab = 0;
  int line = 0;
  int new_pc = 0;
  char inst[18];
  char symbol[26]; 

  if(argc > 1 && (strcmp(argv[1], "-s") == 0))
  {
    dump_tab = linum = 1;
  } 
  else if( argc > 1 && (strcmp(argv[1], "-o") == 0 ))
  {
    obj_file = 1;
  }

  if((dump_tab == 1) | (obj_file == 1))
  {
    start = 2;
  } 
  else 
  {
    start = 1;
  }

  f1 = fopen("/tmp/daedalus", "w+");
  unlink("/tmp/daedalus");

  for(i = start; i < argc; i++)
  {
    if((f2 = fopen(argv[i], "r")) == NULL)
	{
      printf("Cant open file named: %s", argv[i]);
      exit(2);
  }

    while(fscanf(f2, "%d %s", &pc, inst) != EOF)
	{
      if(pc == 4096) break;
	  
      new_pc = pc + pc_offset;
      symbol[0] = '\0';

      if(inst[0] == 'U'){
	fscanf(f2, "%s", symbol);
      }

      fprintf(f1, " %d %s %s \n", new_pc, inst, symbol);
    }
    while(fscanf(f2, "%s %d", symbol, &line) != EOF){
      add_symb(symbol, line + pc_offset);
    }

    pc_offset = new_pc + 1;
    fclose(f2);
  }

  if(obj_file){
    first_print(NO_HEADERS);
    printf("4096 x\n");
    append_table();
    return 0;
  }

  if(linum){
    first_print(HEADERS);
  }

  compute(linum);

  return 0;

}

void first_print(int headers)
{

  char input_buffer[81];

  if(headers == HEADERS)
  {
    printf("\n First pass\n");
    rewind(f1);
    while(fgets(input_buffer, 80, f1) != NULL)
	{
      printf(" %s", input_buffer);
    }
    printf("\n Second Pass \n");
  } 
  else 
  {
    rewind(f1);
    while(fgets(input_buffer, 80, f1) != NULL)
	{
      printf(" %s", input_buffer);
    }
  }

}

void compute(int linum)
{

  char inst [18];
  int line = 0;
  int pc = 0;
  int mask = 0;
  intsym_val
  int i = 0
  int j = 0;
  int old_pc = 0;
  int diff = 0;
  char symbol[26];

  line = old_pc = 0;
  rewind(f1);

  while(fscanf(f1, "%d %s", &pc, inst) != EOF)
  {
    if((diff = pc - old_pc) > 1 ){
      for(j = 1; j < diff; j++){
	printf("1111111111111111 \n");
      }
    }
    old_pc = pc;
  

    if(inst[0] == 'U')
	{
      fscanf(f1, "%s", symbol);
      sym_val = get_sym_val(symbol);
      if(sym_val == -1)
	  {
        printf("No Symbol received");
        exit(3);
      }
  
      for(i = 0; i<12; i++)
	  {
        str[i] = '0';
      }
   
      str[12] = '\0';
      mask = 2048;
  
      for(i = 0; i < 12; i++)
	  {
        if(sym_val & mask)
		{
          str[i] = '1';
        }
        mask >>= 1;
      }

      for(i = 0; i < 12; i++)
	  {
        inst[i + 5] = str[i];
      }

      printf("%s\n", &inst[1]);

    } 
	else 
	{
      printf("%s\n", inst);
    }
  }
  return;

}

void add_symb( char *symbol, int line )
{

  Entry *newSymbol;

  newSymbol = (Entry *) malloc (sizeof(Entry));

  if(symtab == NULL)
  {
    symtab = newSymbol;
    newSymbol -> next = NULL;
  } 
  else 
  {
    newSymbol -> next = symtab;
    symtab = newSymbol;
  }

  strcpy(newSymbol -> name, symbol);
  newSymbol -> addr = line;

  return; 
}

void append_table()
{

  while(symtab != NULL)
  {
    printf("%s \t\t\t%d\n", symtab -> name, symtab -> addr); 
    symtab = symtab -> next; 
  }

  return;
}

int get_sym_val(char *symbol){

  int cmp;
  Entry *list = symtab;

  while(list != NULL)
  {
    cmp = strcmp(list -> name, symbol);
    if(cmp == 0)
	{
      return list -> addr;
    } 
	else 
	{
      list = list -> next;
    }
  }
  return -1;
}
