#include "shell.h"

void style1(void)
{
        GREEN;
        printf("|   ");
        BLUE;
        printf("|   ");
        RESET;
}
void style2(void)
{
        GREEN;
        printf("|   ");
        BLUE;
        printf("|   ");
        PURPLE;
        printf("|   ");
        RESET;
}
void style3(void)
{
        GREEN;
        printf("|   ");
        BLUE;
        printf("|   ");
        PURPLE;
        printf("|   ");
        BLUE;
        printf("|   ");
        RESET;
}

/***** main.c *****/
void open_main(void)
{
	GREEN;
	printf("\nmain running...\n");
	printf("|");
	RESET;      
}
void debug_main1(void)
{
	GREEN;
	printf("|\n");
	RESET
}
void close_main(void)
{
	GREEN;
        printf("|\n");
	printf("main clossing...\n");
	RESET;
}

/***** aux_list.c *****/
void open_list_path(void)
{
	GREEN;
	printf("\n|   ");
	BLUE;
	printf("list_path runnig...\n");
	RESET;
        style1();
        printf("list of PATH directories:\n");     
}
void close_list_path(void)
{
	GREEN;
	printf("|   ");
	BLUE;
	printf("list_path clossing...\n");
	RESET;
}

/***** main_shell.c *****/
void open_start_shell(void)
{
	GREEN;
	printf("|   ");
	BLUE;
	printf("start_shell runing...\n");
	RESET;
}
void prompt(void)
{
	style1();
	GREEN;
	printf("baby_shell# ");
	RESET;
}
void debug_1_shell(void)
{
     	style1();
	printf("input_buffer not empty\n");   
}
void debug_2_shell(void)
{
	style1();
	printf("\n");    
}
void debug_3_shell(void)
{
	style1();
	YELLOW;
	printf("exit condition detected\n");
	RESET;   
}
void debug_4_shell(void)
{
	style1();
	printf("fork\n");     
}
void debug_5_shell(int pid, char *str)
{
	style1();
	printf("process %i executing command: (%s)\n", pid, str);
	printf("=====================================================\n");    
}
void debug_6_shell(void)
{
        printf("=====================================================\n");
}
void debug_7_shell(int pid)
{
	printf("=====================================================\n");
	style1();
	printf("process %i cleaning temp input\n", pid);
	style1();
	printf("\n");
	style1();
	printf("\n");        
}
void debug_8_shell(int pid)
{
	style1();
	printf("process %i cleaning input\n", pid);
}
void debug_9_shell(int pid)
{
	style1();
	printf("process %i cleaning input buffer\n", pid);
}
void close_start_shell(int pid)
{
        GREEN;
        printf("|   ");
        BLUE;
        printf("strat_shell clossing by process %i...\n", pid);
        RESET;
}

/***** create_argv *****/
void open_create_argv(void)
{
   	style1();
	printf("\n");
	style1();
	PURPLE;
	printf("create_argv runing...\n");
	RESET;    
}

void debug_1_argv(char *input_buffer)
{
       	style2();
	printf("input_buffer = %s", input_buffer); 
}
void debug_2_argv(char *new_input)
{
	style2();
	printf("\n");
	style2();
	printf("new_input = %s\n", new_input);   
}
void debug_3_argv(int argc)
{
	style2();
	printf("arguments detected: %i\n", argc);   
}
void debug_4_argv(char **argv)
{
        int i =0;

	style2();
	printf("argument vector:\n");
	while (argv[i])
	{
		style2();
		printf("   [%i] = %s.\n", i, argv[i]);
		i++;
	}  
}
void close_create_argv(void)
{
	style1();
	PURPLE;
	printf("create_argv clossing...\n");
	RESET;  
}

/***** create_argv *****/
void open_get_path(void)
{
	style2();
	printf("\n");
	style2();
	BLUE;
	printf("get_path runing...\n");
	RESET;
}
void debug_1_get_path(char *input_buffer, char *input)
{
	style3();
	printf("input_buffer = %s", input_buffer);
	style3();
	printf("input = %s.\n", input);   
}
void debug_2_get_path(char *command)
{
	style3();
	printf("command = %s.\n", command);  
        BLUE;
}
void debug_3_get_path(void)
{
	style3();
	printf("command executable.\n");     
}
void debug_4_get_path(void)
{
	style3();
	printf("command NOT excutable.\n");
	RESET;   
}
void debug_5_get_path(char *slash_command, char *slash_input)
{
	style3();
	printf("slash_command = %s.\n", slash_command);
	style3();
	printf("slash_input = %s.\n", slash_input);   
}
void debug_6_get_path(char *aux)
{
	style3();
	printf("command (%s) it's executable\n", aux);
	RESET;  
}
void debug_7_get_path(char *aux)
{
        style3();
	printf("command to return:(%s)\n", aux);
	style2();
	BLUE;
	printf("get_path clossing...\n");
	RESET; 
}
void debug_8_get_path(char *command, char *input)
{
	style3();
	printf("command: (%s) it's NOT executable in any directory\n", command);
	style3();
	printf("command to return:(%s)\n", input); 
}
void close_get_path(void)
{
	style2();
	BLUE;
	printf("clossing...\n");
	RESET;   
}
/*
void (void)
{
        
}
void (void)
{
        
}
void (void)
{
        
}
void (void)
{
        
}
*/