#include <stdio.h>
#include <ctype.h>

int main()
{
        int c;
        int ant;
        int i;

        while((c = getchar()) != EOF  )
                {
                //printf("%d ",c); 
                if ( ( ant==170 ) && ( c==170 ) )
                        {
                        if ((c = getchar()) != EOF && (c == 32))
                                for(i=0;i<32;i++)
                                        {
                                        c = getchar();
                                        if (  i==28 )
                                                {
                                                printf("%d Atención ",c);
                                                c = getchar();
                                                printf("%d\n",c);
                                                c = getchar();
                                                printf("%d Meditación ",c);
                                                c = getchar();
                                                printf(" %d\n",c);
                                                };
                                        }
                        };
                ant=c;                                                                        
                }                                                                             
        return 0;                                                                             
}    
