/*  Interpreter for brainfuck programming language!  */

#include <stdio.h>
#include <stdlib.h>


/*  The file pointer of the supplied program. 
    Though this is declared in global scope, it is initialized
    inside main() function */
FILE *f;


/*  The memory(a.k.a long strip of integers) on which all the operations 
    are performed */
int memory[30000];


/*  firstcell and lastcell pointers denote the left and right bounds of the memory.
    Access is restriced beyond these limits. */
int *firstcell = &memory[0];
int *lastcell = &memory[29999];


/*  The pointer which specifies the position in the memory in which the program 
    control is currently in */
int *pointer = &memory[0];

int linecount = 1;


/*  Since handle_character() and handle_loop() refer each other,
    declaring those functions beforehand will help get rid of
    warnings during compilation */
void handle_character(char c);
void handle_loop();


/*  Increments the pointer (or moves the pointer to the right on the strip).
    Shows error if attempted to move out of bounds */
void movr()
{
    if (pointer < lastcell)
    {
        pointer += 1;
        return;
    }
    printf("\n[%d:%ld] Error: Attempt to move to the right beyond limits.\n", 
        linecount, ftell(f));
    exit(1);
}


/*  Decrements the pointer (or moves the pointer to the left on the strip).
    Shows error if attempted to move out of bounds */
void movl()
{
    if (pointer > firstcell)
    {
        pointer -= 1;
        return;
    }
    printf("\n[%d:%ld] Error: Attempt to move to the left beyond limits.\n", 
        linecount, ftell(f));
    exit(1);
}


/*  This function handles the processing of every charactes that is read
    from the file stream. It takes a character as an argument and performs
    appropriate action depending upon the character */
void handle_character(char c)
{
    if (c == '>')
        movr();

    else if (c == '<')
        movl();

    else if (c == '+')
        (*pointer)++;

    else if (c == '-')
        (*pointer)--;

    else if (c == '.')
        printf("%c", *pointer);
    

    else if (c == ',')
    {
        char input;
        scanf("%c", &input);
        *pointer = (int)(input);
    }

    else if (c == '\n')
        linecount++;

    else if (c == '[')
        handle_loop();

    else
        return;
}


/*  This function is called by handle_character when it encounters a '[' character.
    This function takes control from the caller, processes all the instructions using 
    handle_character() until it encounters a matching ']'. It then gives control back
    to the caller if *pointer == 0 or sets pointer to the start of loop 
    (i.e the matching '[' character) and continues executing the instructions again. */
void handle_loop()
{


    /*  loopstartline and loopstartpos remembers the line and position respectively 
        of the start of the loop inorder to place the pointer at this position after 
        this block is over and thus executing the instructions again. */
    int loopstartline = linecount;
    long int loopstartpos = ftell(f); // pos of '[', not the first instruction

    char c = getc(f);

    while (1)
    {


        /*  Every open bracket '[' should have a matching close bracket ']'.
            If the loop reaches EOF without finding a matching ']', then there is no 
            matching end bracket for the loop. This is an error and will be promply
            written to the stdout stream */
        if (c == EOF)
        {
            linecount = loopstartline;
            fprintf(stderr, "[%d:%ld] No matching ']' found.\n", linecount, loopstartpos);
            exit(1);
        }


        /*  If there is another '[' inside a loop, this becomes a nested loop and will be
            handled by calling the handle_loop() recursively. */
        if (c == '[')
        {
            handle_loop();
            c = getc(f);
        }

        if (c == ']')
        {

            if (*pointer == 0)
                return;
            
            else
            {
                int status = fseek(f, loopstartpos, SEEK_SET);
                linecount = loopstartline;
                c = getc(f);
                continue;
            }
        }
        handle_character(c);
        c = getc(f);
    }
}

int main(int argc, char *argv[])
{


    /*  Asserting that exactly one argument is given while running this interpreter */
    if (argc < 2)
    {
        fprintf(stderr, "Error: No filename specified.\n");
        return 1;
    }

    else if (argc > 2)
    {
        fprintf(stderr, "Error: Number of args is more than expected.\n");
        return 1;
    }

    else
    {
        f = fopen(argv[1], "r");


        /*  Asserting that given argument is a valid, accessible file */
        if (f == NULL)
        {
            fprintf(stderr, "Error: Cannot find/access specified file.\n");
            return 1;
        }


        /*  Reading every character from the file and handling it accordingly */
        int c = getc(f);
        while (c != EOF)
        {
            handle_character(c);
            c = getc(f);
        }
        fclose(f);
        return 0;
    }
}
