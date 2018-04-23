// Precompiler directive, to eliminate multiple compiles of h file
#ifndef STRING_FUNCTIONS_C
#define STRING_FUNCTIONS_C

// header files
#include "stringfunctions.h"


const char STRING_NULL_CHAR = '\0';
const char ZERO = 0;

// Function Definitions

// strcat function, appends the second string to the end of the first string.
char *( strcat ) ( char * restrict string1, const char * restrict string2 )
{
   char *string = string1;

   while ( *string )
   {
      string++;
   }

   while ( ( *string1++ = *string2 ) )
   {
   }

   return string;
}

// strchr function. Locates the first occurence of a char and returns the location of it, or null if none is found.
char *( strchr ) ( const char *string, int target )
{
   while ( *string != ( char ) target )
   {
      if ( !*string++ )
      {
         return NULL;
      }
   }

   return ( char * ) string;
}

// strcmp function. Compares two strings and returns wether or not the strings are equal
// -1, first is less than the second, greater than zero if the first is bigger than the second, and 0 if the strings are equal
int ( strcmp ) ( const char *string1, const char *string2 )
{
   while ( *string1 && ( *string1 == *string2 ) )
   {
      string1++, string2++;
   }

   return *( const unsigned char* )string1 - *( const unsigned char* )string2;
}

// strcpy function. Copies the string pointed to by the second string into the first strings array.
// char *( strcpy ) (char * destination, const char * source )
// {
//
//    int pos = 0;
//
//    while ( source[pos] != '\0' )
//    {
//        //destination[pos] = source[pos];
//        //pos++;
//    }
//
//    destination[pos] = '\0';
//    return destination;
// }

// strlen function. Returns the number of bytes in a string
size_t ( strlen ) ( const char *string )
{
   size_t size;

   for ( size = 0 ; string[size] != STRING_NULL_CHAR ; size++ )
   { }

   return size;
}

// strtok function. Splits the given string into tokens based on the deliminating character passed in.
// THESE NULL CHARS MIGHT JUST BE ZEROS FOR THE NEXT TWO FUNCTIONS
char *( strtok ) ( char * restrict string, const char * restrict deliminator )
{
   static char* point = 0;
   if ( string )
   {
      point = string;
   }
   else if ( !point )
   {
      return 0;
   }

   string = point + strspan( point, deliminator );
   point = string + strcspan( string, deliminator );

   if ( point == string )
   {
      return point = 0;
   }

   point = *point ? *point = 0, point + 1 : 0;
   return string;
}

//strspan function. Counts characters in a string before there is a match in the second string;
size_t ( strspan ) ( const char *string1, const char *string2 )
{
   size_t ret = 0;

   while ( *string1 && strchr( string2, *string1++ ) )
   {
      ret++;
   }

   return ret;
}

// strcpan function computes the length of the max initial segment of the string1 string consisting
// of chars not from the string2 string.
size_t strcspan ( const char *string1, const char *string2 )
{
   size_t ret = 0;

   while ( *string1 )
   {
      if ( strchr( string2, *string1 ) )
      {
         return ret;
      }
      else
      {
         string1++, ret++;
      }
   }

   return ret;
}

char* intToString(int num, char* str, int base)
{
    int i = 0;
    Boolean isNeg = False;

    if( num == 0 )
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    if( num < 0 && base == 10 )
    {
        isNeg = True;
        num = -num;
    }

    while( num != 0 )
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    if( isNeg)
    {
        str[i++] = '-';
    }
    str[i] = '\0';
    reverse(str);

    return str;
}

void reverse( char *str )
{
    /* skip null */
    if (str == 0)
    {
        return;
    }

    /* skip empty string */
    if (*str == 0)
    {
        return;
    }

    /* get range */
    char *start = str;
    char *end = start + strlen(str) - 1; /* -1 for \0 */
    char temp;

    /* reverse */
    while (end > start)
    {
        /* swap */
        temp = *start;
        *start = *end;
        *end = temp;

        /* move */
        ++start;
        --end;
    }
}

int stringToInt( char * str )
{
    int res = 0;

    for( int i = 0; str[i] != '\0'; ++i )
    {
        res = res*10+str[i]-'0';
    }

    return res;
}

#endif // STRING_FUNCTIONS_C
