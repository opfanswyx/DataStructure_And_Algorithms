//Following program is a C implementation of the Rabin Karp Algorithm 
//given in the CLRS book
#include <stdio.h>
#include <string.h>


//d is the number of characters in input alphabet
#define d 256

//pat -> pattern    txt -> text        q -> A prime number
void search(char *pat, char *txt, int q)
{
    int m = strlen(pat);
    int n = strlen(txt);

    int i, j;
    
    int p = 0;        //hash value for pattern
    int t = 0;        //hash value for txt
    int h = 1;

    //the value of h would be "pow(d, m - 1) % q"
    for(i = 0; i < m - 1; i++)
    {
        h = (h * d) % q;
    }

    //calculate the hash value of pattern and first window of text
    for(i = 0; i < m; i++)
    {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    //slide the pattern over text one by one
    for(i = 0; i <= n - m; i++)
    {
        //check the hash values of current window of text and pattern
        //if the hash values match then only check for characters on by one
        if(p == t)
        {
            //check for characters one by one
            for(j = 0; j < m; j++)
            {
                if(txt[i + j] != pat[j])
                {
                    break;
                }
            }
            if(j == m)    //found
            {
                printf("Pattern found at index %d\n", i);
            }
        }
        //calulate hash value for next window of text: remove leading digit
        //add trailing digit
        if(i < n - m)
        {
            t = (d * ( t - txt[i] * h) + txt[i + m]) % q;

            //we might get negative value of t, converting it to positive
            if(t < 0)
            {
                t = t + q;
            }
        }
    }
}

int main()
{
    char *txt = "Geeks For Geeks";
    char *pat = "Geek";
    int q = 101;                    //A prime number
    search(pat, txt, q);
    getchar();
    return 0;
}
