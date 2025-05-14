#include <own_stdio.h>
//static char key = 0;

static FILE stream = {0};
int own_putchar(char c, FILE *stream)
{
    Serial.write(c);
    return 0;
}

int own_getchar(FILE *stream)
{
    while (!Serial.available());
    return Serial.read();
}

void own_stdio_setup()
{
    Serial.begin(BAUD_RATE);
    
    fdev_setup_stream(&stream, own_putchar, own_getchar, _FDEV_SETUP_RW);
    stdin = stdout = &stream;
}