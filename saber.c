#include "saber.h"

#define True 1
#define False 0

/* structure for strinfo call */
struct info
{
    int len; /* word lenght */
    int wc;  /* word count */
    int bc;  /* blank counter */
    int vc;  /* voucal counter */
    int cc;  /* consonant counter */
    int nc;  /* number counter */
    int oc;  /* other chars */    
};


/* ################################################# */
/* type conversions */

/* integer (int) to binary (char *) */
char *dtob (int decimal)
{
    char *bin;

    int i, j;

    for (i = 1, j = decimal; j; j /= 2, i++);

    bin = malloc (sizeof (char) * (i + 1));
    
    for (*(bin + --i) = '\0', i--; decimal; decimal /= 2, i--)
        *(bin + i) = (decimal % 2) ? '1' : '0';
    

    return bin;
}

/* integer (int) to hexadecimal (char *) */
char *dtoh (int decimal)
{
    char *hex;

    int i, j;

    
    for (i = 1, j = decimal; j; j /= 16, i++);

    hex = malloc (sizeof (char) * (i + 1));

    for (*(hex + --i) = '\0', i--; decimal; decimal /= 16, i--)
    {
        if ((j = decimal % 16) > 9)
            switch (j)
            {
                case 10:
                    *(hex + i) = 'A';

                case 11:
                    *(hex + i) = 'B';
                    
                case 12:
                    *(hex + i) = 'C';

                case 13:
                    *(hex + i) = 'D';

                case 14:
                    *(hex + i) = 'E';

                case 15:
                    *(hex + i) = 'F';
            }
        else
            *(hex + i) = j + '0';
    }


    return hex;
}

int stoi (char *s)
{
    int num;
    int neg;
    int i;

    
    if (!(*s))
        neg = i = 1;
    else
        neg = i = 0;

    for (num = 0; *(s + i) != '\0'; i++)
        num = 10 * num + *(s + i) - '0';
        
    if (neg)
        num *= -1;
    

    return num;
}

/* ################################################# */
/* string manipulation */

/* acquire string from stdin given a maximum length (char *) */
char *strstdin (const int len)
{
    char *s;

    int c;
    int i;

    
    s = malloc (sizeof (char) * (len + 1));

    for (i = 0; (c = getchar ()) != '\n' && c != EOF; i++)
        if (i < len)
            *(s + i) = c;
    *(s + i) = '\0';

    realloc (s, sizeof (char) * i);
     

    return s;
}

/* reverses the input string (char *) */
char *revstr (char *s)
{
    int i, j;
    int c;


    for (i = 0, j = strlen (s) - 1; i < j; i++, j--)
    {
        c = *(s + i);
        *(s + i) = *(s + j);
        *(s + j) = c;
    }

    
    return s;
}

/* converts any "from" str any to "to" */
char *strsost (char *s, char *from, char *to)
{
    char *out;

    int len, fromLen, toLen;
    int i, j, m, n;
    int c;

    len = strlen (s);
    fromLen = strlen (from);
    toLen = strlen (to);


    for (i = j = 0; i < len; i++)
        if (*from == *(s + i))
            j++;
    
    if (!j)
        return s;

    out = malloc (sizeof (char) * (len + (toLen * j)));
   
    for (i = j = m = n = 0; i < len; i++, n++)
    {
        if (*(s + i) == *from)
        {
            for (m = i + 1, j = 1; *(from + j) == *(s + m) && *(s + m) != '\0'; j++, m++);

            if (j == fromLen)
            {
                for (j = 0; j < toLen; j++, n++)
                    if (*(to + j) != '\0')
                        *(out + n) = *(to + j);
                i += (fromLen - 1);
                n--;    
            }
            else
                *(out + n) = *(s + i);          
        }
        else
            *(out + n) = *(s + i);
    }
    *(out + n) = '\0';

    realloc (out, sizeof (char) * n);

    
    return out;
}

struct info *strinfo (char *s)
{
    int c;
    int i;
    int state;

    struct info *ptr;

    ptr = malloc (sizeof (struct info));


//    printf ("# -- >> %s -- #\n", s);
    for (state = 1, ptr->wc = ptr->vc = ptr->cc = ptr->nc = ptr->oc = i = 0; *(s + i) != '\0'; i++)
    {
        //printf ("%2d) %c --> %3x / %3d / %3o / %s\n", i, c = *(s + i), *(s + i), *(s + i), *(s + i), dtob (*(s + i)));
        
        if ((c = tolower (c)) >= 'a' && c <= 'z')
           switch (c)
           {
                case 'a':
                case 'e':
                case 'i':
                case 'o':
                case 'u':
                    ptr->vc++;
                    break;

                default:
                    ptr->cc++;
                    break;
            }
        else if (c >= '0' && c <= '9')
            ptr->nc++;
        else if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
            ptr->bc++;
        else
            ptr->oc++;

        if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
            state = 1;
        else if (state || (state && *(s + i + 1) == '\0'))
        {
            state = 0;
            ptr->wc++;
        }
            
    }
    //printf ("# -- LEN:%d / WC:%d / VC:%d / CC:%d / NC:%d / BC:%d / OC:%d --#\n", ptr->len = i, ptr->wc, ptr->vc, ptr->cc, ptr->nc, ptr->bc, ptr->oc);
    
    
    return ptr;
}

char *strupper (char *s)
{
    int i;


    for (i = 0; *(s + i) != '\0'; i++)
        if (*(s + i) >= 'a' && *(s + i) <= 'z')
            *(s + i) -= 32;


    return s;
}

char *strlower (char *s)
{
    int i;


    for (i = 0; *(s + i) != '\0'; i++)
        if (*(s + i) >= 'A' && *(s + i) <= 'Z')
            *(s + i) += 32;


    return s;
}

char *strtrim (char *s)
{
    int i, j; 


    for (i = 0; s[i] != '\0'; i++)
        switch (*(s + i))
        {
            case '\n':
            case '\t':
            case '\r':
            case ' ':
                for (j = i++; *(s + j) != '\0'; j++)
                    *(s + j) = *(s + j + 1);
                break;

            default: 
                break;
        }


    return s;
}

char **strmatdiv (char *s)
{
    char **mat;

    int chr;
    int r, c;
    int i;

    struct info *ptr;


    ptr = strinfo (s);
    

    mat = malloc (sizeof (char *) * (ptr->wc + 1));
    for (r = c = i = 0; r < ptr->wc; i++)
        if (!isspace (*(s + i)))
        {
            *(mat + r) = malloc (sizeof (char) * (ptr->len + 1));

            for (c = 0; !isspace (*(s + i)) && *(s + i) != '\0'; c++, i++)
                *(*(mat + r) + c) = *(s + i);
            *(*(mat + r) + c) = '\0';
        
            realloc (*(mat + r++), sizeof (char) * c);
        }
    *(mat + r) = NULL;


    return mat;
}

