#include <unistd.h>
#include <fcntl.h>

typedef char *string;

void printf(string Text);
int strlen(string Text);

int main(void)
{
    string text = "Test Text\n";
    
    printf(text);
    return 0;
}

void printf(string Text)
{
    int length_of_string = strlen(Text);
    
    write(1,Text,length_of_string);
}

int strlen(string Text)
{
    //int size = (int)sizeof(Text)/sizeof(Text[0]);
    int size = (int)sizeof(Text)/sizeof(Text[0] + 3); //somehow fixed?
    return  size;
}
