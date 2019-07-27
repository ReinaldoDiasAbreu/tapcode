#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

char tapcode[5][5] = {{'a','b','c','d','e'},{'f','g','h','i','j'},{'l','m','n','o','p'},{'q','r','s','t','u'},{'v','w','x','y','z'}};

string returntaps(int n, int tap)
{
    string subtap = "";
    for(int i=1; i <= (n*tap); i++){
        subtap = subtap + ".";
    }
    return subtap;
}

string convertfortap(char c, int ntap)
{
    char letra = tolower(c);
    string tap = "";
    for(int i=0; i < 5; i++){
        for(int j=0; j < 5; j++){
            if(tapcode[i][j] == letra)
            {
                tap = returntaps(i+1, ntap) + " " + returntaps(j+1, ntap) + " ";
            }
        }
    }
    return tap;
}

int main(int argc, char *argv[])
{
    string arqin, arqout;
    int ntaps, convert;

    if(argc == 5)
    {
        arqin = argv[1];
        arqout = argv[2];
        ntaps = atoi(argv[3]);
        convert = atoi(argv[4]);
    }

    switch(argc)
    {
    case 5:
        if(ntaps < 1) ntaps = 1;
        if(convert == 2)
        {
            cout << "Decoding... ";
            char str;
            int linha = 0;
            int coluna = 0;
            bool alt = false;
            int prox = 0;
            FILE *arqentrada = fopen(arqin.c_str(), "r");
            FILE *arqexit = fopen(arqout.c_str(), "w");
            if(arqentrada)
            {
                while(fscanf(arqentrada, "%c", &str) != EOF)
                {
                    if(str == '.'){
                        if(alt == false)
                            linha++;
                        else
                            coluna++;
                    }
                    else
                    {
                        if(alt == true) alt = false;
                        else alt = true;
                        prox++;
                    }

                    if(prox == 2)
                    {
                        linha /= ntaps;
                        coluna /= ntaps;
                        fprintf(arqexit, "%c", tapcode[linha-1][coluna-1]);
                        linha = coluna = prox = 0;
                    }
                }
                fprintf(arqexit, "\n");
            }
            fclose(arqentrada);
            fclose(arqexit);
            cout << "OK!" << endl;
        }
        else
        {
            cout << "Coding... ";
            char caracter;
            FILE *arqentrada = fopen(arqin.c_str(), "r");
            FILE *arqexit = fopen(arqout.c_str(), "w");
            if(arqentrada)
            {
                while(fscanf(arqentrada, "%c", &caracter) != EOF)
                {
                    if(caracter != 'k')
                        fprintf(arqexit, "%s", convertfortap(caracter, ntaps).c_str());
                    else 
                        fprintf(arqexit, "%s", convertfortap('c', ntaps).c_str());
                }
                fprintf(arqexit, "\n");
            }
            fclose(arqentrada);
            fclose(arqexit);
            cout << "OK!" << endl;
        }
    break;
    case 2:
        cout << "HELP TAP CODE" << endl;
        cout << "./tap arq.in arq.out tap op" << endl << endl;
        cout << " -> arq.in and arq.out correspond to the input and output files respectively." << endl;
        cout << " -> Tap correspond to the base number of the points." << endl;
        cout << " -> op type 1 to encode and 2 to decode." << endl << endl;
        cout << " By Reinaldo Junio Dias " << endl;
    break;
    
    default:
        cout << "Invalid Entry!" << endl;
    break;
    }
    
    return 0;
}