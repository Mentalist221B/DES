#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int message[64], xor_arr[32], rk_arr[32], res_arr[32], res1[32], number[16];         //Array for storing block in binary format
char block[17], hexa[16];              //Array for accepting plaintext block by block

int key[64] = {0,0,0,1,0,0,1,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,1,0,1,1,1,1,0,0,1,
           1,0,0,1,1,0,1,1,1,0,1,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,1};

int PC_1[56] = {57, 49, 41, 33, 25, 17,  9,
                 1, 58, 50, 42, 34, 26, 18,
                10,  2, 59, 51, 43, 35, 27,
                19, 11,  3, 60, 52, 44, 36,
                63, 55, 47, 39, 31, 23, 15,
                 7, 62, 54, 46, 38, 30, 22,
                14,  6, 61, 53, 45, 37, 29,
                21, 13,  5, 28, 20, 12,  4};

int PC_2[48] = {14, 17, 11, 24,  1,  5,
                 3, 28, 15,  6, 21, 10,
                23, 19, 12,  4, 26,  8,
                16,  7, 27, 20, 13,  2,
                41, 52, 31, 37, 47, 55,
                30, 40, 51, 45, 33, 48,
                44, 49, 39, 56, 34, 53,
                46, 42, 50, 36, 29, 32};

int IP[64] = {58, 50, 42, 34, 26, 18, 10, 2,
              60, 52, 44, 36, 28, 20, 12, 4,
              62, 54, 46, 38, 30, 22, 14, 6,
              64, 56, 48, 40, 32, 24, 16, 8,
              57, 49, 41, 33, 25, 17,  9, 1,
              59, 51, 43, 35, 27, 19, 11, 3,
              61, 53, 45, 37, 29, 21, 13, 5,
              63, 55, 47, 39, 31, 23, 15, 7};

int IP_1[64] = {40, 8, 48, 16, 56, 24, 64, 32,
                39, 7, 47, 15, 55, 23, 63, 31,
                38, 6, 46, 14, 54, 22, 62, 30,
                37, 5, 45, 13, 53, 21, 61, 29,
                36, 4, 44, 12, 52, 20, 60, 28,
                35, 3, 43, 11, 51, 19, 59, 27,
                34, 2, 42, 10, 50, 18, 58, 26,
                33, 1, 41,  9, 49, 17, 57, 25};

int E_bit[48] = {32,  1,  2,  3,  4,  5,
                  4,  5,  6,  7,  8,  9,
                  8,  9, 10, 11, 12, 13,
                 12, 13, 14, 15, 16, 17,
                 16, 17, 18, 19, 20, 21,
                 20, 21, 22, 23, 24, 25,
                 24, 25, 26, 27, 28, 29,
                 28, 29, 30, 31, 32,  1};


int S1[4][16] = {14,  4, 13, 1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9, 0,  7,
                  0, 15,  7, 4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5, 3,  8,
                  4,  1, 14, 8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10, 5,  0,
                 15, 12,  8, 2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0, 6, 13};

int S2[4][16] = {15,  1,  8, 14,  6, 11,  3,  4,  9, 7,  2, 13, 12, 0,  5, 10,
                  3, 13,  4,  7, 15,  2,  8, 14, 12, 0,  1, 10,  6, 9, 11,  5,
                  0, 14,  7, 11, 10,  4, 13,  1,  5, 8, 12,  6,  9, 3,  2, 15,
                 13,  8, 10,  1,  3, 15,  4,  2, 11, 6,  7, 12,  0, 5, 14,  9};

int S3[4][16] = {10,  0,  9, 14, 6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
                 13,  7,  0,  9, 3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
                 13,  6,  4,  9, 8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
                  1, 10, 13,  0, 6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12};

int S4[4][16] = {7, 13, 14, 3,  0,  6,  9, 10,  1, 2, 8,  5, 11, 12,  4, 15,
                13,  8, 11, 5,  6, 15,  0,  3,  4, 7, 2, 12,  1, 10, 14,  9,
                10,  6,  9, 0, 12, 11,  7, 13, 15, 1, 3, 14,  5,  2,  8,  4,
                 3, 15,  0, 6, 10,  1, 13,  8,  9, 4, 5, 11, 12,  7,  2, 14};

int S5[4][16] = {2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13, 0, 14,  9,
                14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3, 9,  8,  6,
                 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6, 3,  0, 14,
                11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10, 4,  5,  3};

int S6[4][16] = {12,  1, 10, 15, 9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
                 10, 15,  4,  2, 7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
                  9, 14, 15,  5, 2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
                  4,  3,  2, 12, 9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13};

int S7[4][16] = {4, 11,  2, 14, 15, 0,  8, 13,  3, 12, 9,  7,  5, 10, 6,  1,
                13,  0, 11,  7,  4, 9,  1, 10, 14,  3, 5, 12,  2, 15, 8,  6,
                 1,  4, 11, 13, 12, 3,  7, 14, 10, 15, 6,  8,  0,  5, 9,  2,
                 6, 11, 13,  8,  1, 4, 10,  7,  9,  5, 0, 15, 14,  2, 3, 12};

int S8[4][16] = {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
                  1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
                  7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
                  2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11};

int P[32] = {16,  7, 20, 21,
             29, 12, 28, 17,
              1, 15, 23, 26,
              5, 18, 31, 10,
              2,  8, 24, 14,
             32, 27,  3,  9,
             19, 13, 30,  6,
             22, 11,  4, 25};

int key_plus[56], C[17][28], D[17][28], K[16][48], L[2][32], R[2][32], message_ip[64];

void key_plus_gen()                 //Generates key+ from key
{
    int i;

    for(i=0; i<56; i++)
    {
        key_plus[i] = key[PC_1[i] - 1];
    }

    return;
}

void split_kp()                 //Splits key+ into C0 and D0
{
    int i;

    for(i=0; i<28; i++)
    {
        C[0][i] = key_plus[i];
        D[0][i] = key_plus[i+28];
    }

    return;
}

void left_shift()                   //To generate C1-C16 and D1-D16 using left shifts
{
    int i,j;

    for(i=1; i<=16; i++)
    {
        if(i == 1 || i == 2 || i == 9 || i == 16)
        {
            for(j=0; j<27; j++)
            {
                C[i][j] = C[i-1][j+1];
                D[i][j] = D[i-1][j+1];
            }

            C[i][j] = C[i-1][0];
            D[i][j] = D[i-1][0];
        }
        else
        {
            for(j=0; j<26; j++)
            {
                C[i][j] = C[i-1][j+2];
                D[i][j] = D[i-1][j+2];
            }

            C[i][j] = C[i-1][0];
            D[i][j] = D[i-1][0];
            C[i][j+1] = C[i-1][1];
            D[i][j+1] = D[i-1][1];
        }
    }

    return;
}

void keygen()                   //Generates 16 sub-keys K1-K16
{
    int i,j;

    for(i=0; i<16; i++)
    {
        for(j=0; j<48; j++)
        {
            if(PC_2[j] <= 28)
            {
                K[i][j] = C[i+1][PC_2[j]-1];
            }
            else
            {
                K[i][j] = D[i+1][PC_2[j]-29];
            }
        }
    }

    return;
}

void dec2bin(int []);
void hex2dec(char arr[])          //Converts each character into decimal value
{
    int i,num[16]={0};

    for(i=0; i<16; i++)
    {
        if(arr[i] == '\0')
        {
            break;
        }
        else
        {
            switch(arr[i])
            {
                case '0' : num[i] = 0;
                           break;

                case '1' : num[i] = 1;
                           break;

                case '2' : num[i] = 2;
                           break;

                case '3' : num[i] = 3;
                           break;

                case '4' : num[i] = 4;
                           break;

                case '5' : num[i] = 5;
                           break;

                case '6' : num[i] = 6;
                           break;

                case '7' : num[i] = 7;
                           break;

                case '8' : num[i] = 8;
                           break;

                case '9' : num[i] = 9;
                           break;

                case 'A' : num[i] = 10;
                           break;

                case 'B' : num[i] = 11;
                           break;

                case 'C' : num[i] = 12;
                           break;

                case 'D' : num[i] = 13;
                           break;

                case 'E' : num[i] = 14;
                           break;

                case 'F' : num[i] = 15;
                           break;
            }
        }
    }

    dec2bin(num);

    return;
}

void dec2bin(int num[])           //Converts decimal value into binary value and store it in message
{
    int i,j,rem;

    for(i=0; i<64; i++)
    {
        message[i] = 0;
    }

    for(i=0; i<16; i++)
    {
        for(j=3; j>=0; j--)
        {
            rem = num[i] % 2;
            num[i] /= 2;

            message[(i*4)+j] = rem;
        }
    }

    return;
}

void initial_permutation()
{
    int i;

    for(i=0; i<64; i++)
    {
        if(IP_1[i] <= 32)
        {
            R[1][IP_1[i]-1] = message[i];
        }
        else
        {
            L[1][IP_1[i]-33] = message[i];
        }
    }

    return;
}


void xor()               //XOR function
{
    int i;

    for(i=0; i<32; i++)
    {
        if(R[1][i] == res1[i])
        {
            xor_arr[i] = 0;
        }
        else
        {
            xor_arr[i] = 1;
        }
    }

    return;
}

void SBox(int arr[])
{
    int i, j, dec, rem, index, binR, binC, sblock[6];

    for(i=0; i<32; i++)
    {
        res_arr[i] = 0;
    }

    for(i=0; i<8; i++)
    {
        for(j=0; j<6; j++)
        {
            sblock[j] = arr[(6*i)+j];
        }

        binR = (2*sblock[0]) + sblock[5];
        binC = (8*sblock[1]) + (4*sblock[2]) + (2*sblock[3]) + sblock[4];

        switch(i)
        {
            case 0: dec = S1[binR][binC];
                    index = 3;

                    while(index >= 0)
                    {
                        rem = dec%2;
                        dec /= 2;

                        res_arr[(i*4)+index] = rem;
                        index--;
                    }

                    break;

            case 1: dec = S2[binR][binC];
                    index = 3;

                    while(index >= 0)
                    {
                        rem = dec%2;
                        dec /= 2;

                        res_arr[(i*4)+index] = rem;
                        index--;
                    }

                    break;

            case 2: dec = S3[binR][binC];
                    index = 3;

                    while(index >= 0)
                    {
                        rem = dec%2;
                        dec /= 2;

                        res_arr[(i*4)+index] = rem;
                        index--;
                    }

                    break;

            case 3: dec = S4[binR][binC];
                    index = 3;

                    while(index >= 0)
                    {
                        rem = dec%2;
                        dec /= 2;

                        res_arr[(i*4)+index] = rem;
                        index--;
                    }

                    break;

            case 4: dec = S5[binR][binC];
                    index = 3;

                    while(index >= 0)
                    {
                        rem = dec%2;
                        dec /= 2;

                        res_arr[(i*4)+index] = rem;
                        index--;
                    }

                    break;

            case 5: dec = S6[binR][binC];
                    index = 3;

                    while(index >= 0)
                    {
                        rem = dec%2;
                        dec /= 2;

                        res_arr[(i*4)+index] = rem;
                        index--;
                    }

                    break;

            case 6: dec = S7[binR][binC];
                    index = 3;

                    while(index >= 0)
                    {
                        rem = dec%2;
                        dec /= 2;

                        res_arr[(i*4)+index] = rem;
                        index--;
                    }

                    break;

            case 7: dec = S8[binR][binC];
                    index = 3;

                    while(index >= 0)
                    {
                        rem = dec%2;
                        dec /= 2;

                        res_arr[(i*4)+index] = rem;
                        index--;
                    }

                    break;
        }

    }

    for(i=0; i<32; i++)
    {
        res1[i] = res_arr[P[i]-1];
    }

    return;
}

void rk_fun(int in)
{
    int i, j, subarr[48], Er[48];

    for(i=0; i<48; i++)
    {
        Er[i] = L[1][E_bit[i]-1];
    }

    for(i=0; i<48; i++)
    {
        if(K[in-1][i] == Er[i])
        {
            subarr[i] = 0;
        }
        else
        {
            subarr[i] = 1;
        }
    }

    SBox(subarr);

    return;
}

void initial_fun()                    //Ln = Rn-1
{                                   //Rn = Ln-1 + f(Rn-1,Kn)
    int i,j;

    for(i=16; i>=1; i--)
    {
        for(j=0; j<32; j++)
        {
            R[0][j] = L[1][j];
        }

        rk_fun(i);
        xor();

        for(j=0; j<32; j++)
        {
            R[1][j] = R[0][j];
            L[1][j] = xor_arr[j];
        }
    }

    return;
}

void join()                   //Divides the message_ip into left and right half
{
    int i;

    for(i=0; i<32; i++)
    {
        message_ip[i] = L[1][i];
        message_ip[i+32] = R[1][i];
    }

    return;
}

void final_permutation()                  //Produces an initial permutation of message
{
    int i;

    for(i=0; i<64; i++)
    {
        message[IP[i]-1] = message_ip[i];
    }

    return;
}

void bin2hex()
{
    int i,j,deci;

    for(i=0; i<16; i++)
    {
        deci = 0;

        for(j=0; j<4; j++)
        {
            deci += message[(i*4)+j] * pow(2,(3-j));
        }

        number[i] = deci;
    }

    return;
}

int main()
{
    FILE *fp,*fp1;
    char ch, ech;
    int i,j=0, decimal;

    fp = fopen("Plaintext.txt","r");
    fp1 = fopen("Plaintext.txt","r+");

    if(fp)
    {
        key_plus_gen();
        split_kp();
        left_shift();
        keygen();

        while(1)
        {
            for(i=0; i<16; i++)
            {
                ch = getc(fp);

                if(ch == EOF)
                {
                    break;
                }

                block[i] = ch;
            }


            if(ch == EOF)
            {
                break;
            }

            block[i] = '\0';

            hex2dec(block);
            initial_permutation();
            initial_fun();
            join();
            final_permutation();
            bin2hex();

            decimal = 1;

            for(i=0; i<16; i++)
            {
                decimal = number[i]*16 + number[i+1];

                if(decimal == 0)
                {
                    break;
                }

                ech = decimal;

                fputc(ech, fp1);

                i++;
            }

            j++;
        }

        ech = 32;

        for(i=0; i<8*(j+1); i++)
        {
            fputc(ech,fp1);
        }
    }
    else
    {
        printf("Cannot open file!");
    }

    fclose(fp);
    fclose(fp1);

    return 0;
}
