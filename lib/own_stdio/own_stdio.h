#ifndef STDIO_H
#define STDIO_H

#include <Arduino.h>
#include <stdio.h>
#include <config.h>


void own_stdio_setup();
int own_putchar(char c, FILE *stream);
int own_getchar(FILE *stream);
#endif // STDIO_H