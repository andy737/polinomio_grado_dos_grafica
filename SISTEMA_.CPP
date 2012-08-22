/*
Universidad Tecnológica de Tecámac
División: Informática
Título: Programa para analizar polinomios de segundo grado.
Objetivo: Proyecto final para la evaluación de las materias Ingeniería Económica
y Matemáticas para TI.
Descripción: Esta aplicación realiza la gráfica, muestra los ceros, máximos, mínimos, discriminante
y determina la apertura del polinomio de grado 2.
Autor: Andrés de Jesús Hernández Martínez
       Idania Aquino Cruz
Grupo: 7ITI1
Fecha de creación: 1/08/12
Última modificación: 20/08/12
Versión: 0.3
*/

//Declaración de librerías
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<math.h>
#include<string.h>

//Declaración de funciones
int set_graph(void);
int arregloXY(float max, float min);
void eje_xy(float max, float min);
void ingresaMN(void);
void cuadratica(float max, float min);
void grafica_cuad(float a, float b, float c, float max, float min);
void trazaEscx(int totalUx, int unidades, float max, float min );
void trazo_cuad(float x[], float y[], int tam);
void escalaTy(float y[], int tam);
float *escalax(float max, float min, int totalUx);
void solucionE(float a, float b, float c);

//Variables globales
int max_x, max_y; //valores máximos del monitor
float maxGy, maxGx, escX, escY, ux, uy; //valores que determinan la escala del trazo

//Constantes
const int rangoEs=5; //Determina el rango entre cada punto de la escala numérica en el eje x

//****************************Calculo y trazo de escalas en el eje x,y****************************//

//Determina la escala del eje x
float *escalax(float max, float min, int totalUx)
{
    maxGx=0;
    float maximo=0;
    float *valoresx; //Arreglo que contendrá los valores numéricos para la escala x
    int tamano = (totalUx/2)/rangoEs; //Determina el número de putos  a trazar en el eje x
    valoresx = (float*) malloc ( sizeof(float) * tamano);//Se crea el arreglo
    if(max<0)
    {
        max=max*-1; //valor absoluto para max
    }
    if(min<0)
    {
        min=min*-1; //valor absoluto para mínimo
    }
    if(max>min) //Determina el número máximo entre mínimo y máximos para definir la escala en el eje x
    {
        maximo=max;
    }
    else
    {
        maximo=min;
    }
    maxGx=maximo;
    //Calcula los valores de la escala por cada división del eje x
    for(int i=0; i<=((totalUx/2)/rangoEs); i++)
    {
        valoresx[i]=(maximo-(i*(maximo/((totalUx/2)/rangoEs))))*-1;//Guarda valores de la escala numérica para el lado izquierdo del eje x
    }
    return valoresx;
}

//Determina la escala del eje y
void escalaTy(float y[], int tam)
{
    maxGy=0;
    float maximo=0,aux=0;
    int rango=0,j=0,k=0;
    float *valoresy, *tmpy; // declaramos el arreglo
    char *numero; //Guarda temporalmente la conversión a char de un número para la escala X
    int unidady=(max_y/20)/(max_y/200); //Determina el tamaño de división a división en el eje y
    int totalUy=(max_y/unidady)-3; //Determina el número de divisiones en el eje y
    int tamano = (totalUy/2)/rangoEs; //Tamano de las divisiones en el eje X
    valoresy = (float*) malloc ( sizeof(float) * tamano);//Se crea el arreglo para y
    tmpy = (float*) malloc ( sizeof(float) * tamano);//Se crea el temporal para y
    while(k<tam)
    {
        if(y[k]<0)
            tmpy[k]=y[k]*-1; //Valor absoluto para el número contenido en el array y
        else
            tmpy[k]=y[k];
        k++;
    }
    for(k=0; k<tam; k++) //Ordena el array de menor a mayor
    {
        j=k;
        aux=tmpy[k];
        while(j>0&&aux<tmpy[j-1])
        {
            tmpy[j]=tmpy[j-1];
            j=j-1;
        }
        tmpy[j]=aux;
    }
    maximo=tmpy[tam-1];
    maxGy=maximo;
    //Calcula los valores de la escala por cada división del eje y
    for(int i=0; i<=((totalUy/2)/rangoEs); i++)
    {
        valoresy[i]=(maximo-(i*(maximo/((totalUy/2)/rangoEs))))*-1;//Guarda valores de la escala numérica para el eje y (arriba)
    }
    for(i=0; i<((totalUy/2)/rangoEs); i++) //Evita la impresión del 0
    {
        sprint(numero,"%.2f",valoresy[i]*-1);//Convierte los valores del array int en char* uno por uno
        outtextxy((max_x/2)+9,(max_y/2)-(((totalUy/2)-rango)*(unidady))-2,numero);//Imprime los números de la escala (arriba eje y)
        rango=rango+rangoEs;
    }
    rango=rango+rangoEs;
    for(i=((totalUy/2)/rangoEs)-1; i>=0; i--)//Evita la impresión del 0
    {
        sprintf(numero,"%.2f",valoresy[i]);//Mide el tamaño del valor a imprimir para determinar su posición en la escala del eje y
        outtextxy((max_x/2)+9,(max_y/2)-(((totalUy/2)-rango)*(unidady))-2,numero); //Imprime el resto de los números de la escala (abajo eje y)
        rango=rango+rangoEs;
    }
}

//Imprime en pantalla la escala numérica del eje x
void trazaEscx(int totalUx, int unidadx, float max, float min )
{
    float *valoresx; // declaramos el arreglo
    int tamA=0, rango=0;
    //Array temporal para números de la escala x
    char *numero; //Guarda temporalmente la conversión a char de un número para la escala X
    char *xy[2]= {"Y","X"}; //Letras del eje x,y
    numero= (char *)malloc(6); //Crea el array
    valoresx = escalax(max, min, totalUx); // Función encargada de devolver el array de enteros para la escala x
    outtextxy((max_x/2)-12,4,xy[0]); //Imprime la letra Y en el eje Y
    outtextxy(max_x-12,(max_y/2)-12,xy[1]); //Imprime la letra X en el eje X
    settextstyle(2,0,0); //Define estilo de texto
    setusercharsize(2,3,2,3); //Define tamano de texto
    //Determina la alineación y espaciado dé la impresión de la escala en el eje x
    for(int i=0; i<((totalUx/2)/rangoEs); i++) //Evita la impresión del 0
    {
        sprintf(numero,"%.2f",valoresx[i]);//Convierte los valores del array int en char* uno por uno
        tamA=strlen(numero);//Mide el tamano del valor a imprimir para determinar su posición en la escala del eje x
        outtextxy((max_x/2)-(((totalUx/2)-rango)*(unidadx))-tamA-2,(max_y/2)+6,numero); //Imprime el resto de los números de la escala (izquierda eje x)
        rango=rango+rangoEs;
    }
    rango=rango+rangoEs;//Evita la impresión del 0
    for(i=((totalUx/2)/rangoEs)-1; i>=0; i--)
    {
        sprintf(numero,"%.2f",(valoresx[i]*-1));//Mide el tamaño del valor a imprimir para determinar su posición en la escala del eje x
        tamA=strlen(numero);
        outtextxy((max_x/2)-(((totalUx/2)-rango)*(unidadx))-tamA-2,(max_y/2)+6,numero); //Imprime el resto de los números de la escala (derecha eje x)
        rango=rango+rangoEs;
    }
}

//****************************Trazo de los eje x,y****************************//

//Función que traza los ejes x,y
void eje_xy(float max, float min)
{
    escY=0;
    escX=0;
    ux=0;
    uy=0;
    setbkcolor(0); //Establece el color de fondo
    setcolor(15);  //Establece el color de los trazos
    //Determina escala de divisiones en el eje x
    float caly=1.8; //Calibra al eje y debido a variaciones con respecto a las unidades del eje x
    int unidadx=(max_x/20)/(max_x/200); //Determina el tamaño de unidad por cada división en la escala y
    int totalUx=(max_x/unidadx)-3; //Determina el total de divisiones en el eje x corrección (-3)
    //Determina escala de divisiones en el eje y
    int unidady=(max_y/20)/(max_y/200); //Determina el tamaño de unidad por cada división en la escala y
    int totalUy=(max_y/unidady)-3; //Determina el total de divisiones en el eje y correccion (+3)
    int limitesx=max_x/unidadx; //Limite para trazado de escala x
    int limitesy=max_y/unidady; //Limite para trazado de escala y
    line(0,max_y/2,max_x,max_y/2); //Traza el eje de las x
    line(max_x/2,0,max_x/2,max_y); //Traza el eje de las y
    //Convierte el máximo en pantalla entre la unidad definida en un múltiplo de 5
    while((limitesx%5)!=0)
    {
        limitesx=limitesx-1;
    }
    while((limitesy%5)!=0)
    {
        limitesy=limitesy-1;
    }
    //Imprime las líneas de escala en el eje x
    for(int i=0; i<=totalUx+2; i++)
    {
        if((i*unidadx)<=((limitesx/2)*10))
        {
            line(((max_x/2)-(i*unidadx)),max_y/2,((max_x/2)-(i*unidadx)),((max_y/2)+3)); //Traza la escala en el eje x izquierda
        }
        if((i*unidadx)>((limitesx/2)+2)*10) //Corrige trazo faltante en eje x (+2)
        {
            line((i*unidadx),max_y/2,(i*unidadx),((max_y/2)+3)); //Traza la escala en el eje x derecha
        }
    }
    //Imprime las líneas de escala en el eje y
    for(int j=0; j<=totalUy; j++)
    {

        if((j*(unidady))<=(((limitesy+2)/2)*10))//Corrige el trazo del eje y (+2)
        {
            line(max_x/2,(j*unidady)+caly*unidady,((max_x/2)+3),(j*unidady)+caly*unidady); //Traza la escala en el eje y abajo del eje x
        }
        if((i*(unidady))>=(((limitesy+2)/2)*10))
        {
            line(max_x/2,(j*unidady)+caly*unidady,((max_x/2)+3),(j*unidady)+caly*unidady); //Traza la escala en el eje y arriba del eje x
        }
    }
    escX=totalUx/2;
    escY=totalUy/2;
    ux=unidadx;
    uy=unidady;
    trazaEscx(totalUx, unidadx, max, min );
}

//****************************Inicia modo grafico****************************//

//Inicializa el modo grafico
int set_graph(void)
{
    //Declaración de variables locales
    int graphdriver = VGA, graphmode= VGAHI, error_code;
    //Inicializa modo grafico del sistema en modo VGAHI
    initgraph(&graphdriver, &graphmode, "C:\\TC\\BGI");
    error_code = graphresult();
    if (error_code != grOk)
        return(-1);  // No se encontró hardware que soporte gráficos
    if (graphdriver != VGA)
    {
        closegraph(); //Finaliza el modo gráfico
        return 0;
    }
    return(1);  // Modo gráfico aceptado
}

//****************************Trazo e impresión de la gráfica en pantalla****************************//

//Coordenadas máximas
void calc_coords(void)
{
    max_x=0;
    max_y=0;
    //Determina las coordenadas máximas del monitor
    max_x = getmaxx();     // Coordenadas máximas en x
    max_y = getmaxy();     // Coordenadas máximas en y
}

//Calcula el tamaño de los arreglos que almacenaran las coordenadas x,y
int arregloXY(float max, float min)
{
    int tam=0;
    for(float i=min; i<=max; i=i+0.1)
    {
        tam++;
    }
    return tam;
}


//Calculo de coordenadas para la gráfica
void grafica_cuad(float a, float b, float c,float max, float min)
{
    //Declaración de variables locales
    int tam=arregloXY(max, min); //Determina el tamaño del arreglo para x,y
    float *x;
    float *y;
    int j=0;
    x = (float*) malloc ( sizeof(float) * tam);//Se crea el arreglo para x
    y = (float*) malloc ( sizeof(float) * tam);//Se crea el arreglo para y
    //Calculo de las coordenadas x,y
    for(float i=min; i<=max; i=i+0.1)
    {
        y[j]=-1*(a*pow(i,2)+b*i+c);//Corrección de la apertura de la curva
        x[j]=i;
        j++;
    }
    escalaTy(y,tam);
    trazo_cuad(x, y, tam);
}

//Imprime la gráfica del polinomio de grado 2
void trazo_cuad(float x[], float y[], int tam)
{
    float comy=0,comx=0,xl=0,yl=0;
    comy=escY/maxGy;
    comx=escX/maxGx;
    setcolor(12);
    for(int i=0; i<tam; i++)
    {
        if(x[tam-1]<20)
        {
            circle((max_x/2)+x[i]*comx*10,(max_y/2)+y[i]*comy*11,1); //Realiza el trazo de los puntos x,y en el plano cartesiano
        }
        else
        {
            putpixel((max_x/2)+x[i]*comx*10,(max_y/2)+y[i]*comy*11,12); //Realiza el trazo de los puntos x,y en el plano cartesiano
        }
        xl=(max_x/2)+x[i]*comx*10;
        yl=(max_y/2)+y[i]*comy*11;
        //Genera trazo continuo en los puntos x,y marcados en el plano cartesiano
        if(i<tam-1)
        {
            line(xl,yl,(max_x/2)+x[i+1]*comx*10,(max_y/2)+y[i+1]*comy*11);
        }
    }
}

//****************************Petición y entrada de datos****************************//

//Toma y valida los valores del polinomio de grado 2 del polinomio de grado 2
void cuadratica(float max, float min)
{
    //Declaración de variables locales
    char a1[10], b1[10], c1[10];
    int val=0,z=0;
    float a=0,b=0,c=0,av=0,bv=0,cv=0;
    char *var[]= {"a","b","c"};
    char *finalPtr;
    for(int i=0; i<3; i++) //Asignación de variables
    {
        do
        {
            z=0;
            fflush (stdin);
            system("cls");//Limpia la pantalla de consola
            printf("Ecuacion de la forma f(x)=ax^2+bx+c.\n\n");
            printf("Ingresa el valor de %s (###, #.## o -###):", var[i]);
            fflush (stdin);//Limpia el buffer de entrada
            if(i==0)
            {
                if(scanf("%G",&a)==1)//Valida entrada de datos (cast a float)
                {
                    if(a>=-9999&&a<=9948) //Determina que el valor de variable ingresada este dentro del rango permitido
                    {
                        if(a!=0)
                        {
                            sprintf(a1,"%G",a);
                            if(strtod(a1, &finalPtr)!=0)//Verificador de entero o flotante
                            {
                                av=a;
                                val=1;
                            }
                        }
                        else
                        {
                            z=1;
                        }
                    }
                }
                else
                    val=0;
            }
            if(i==1)
            {
                if(scanf("%G",&b)==1)//Valida entrada de datos (cast a float)
                {
                    if(b>=-9999&&b<=9948)//Determina que el valor de variable ingresada este dentro del rango permitido
                    {
                        sprintf(b1,"%G",b);
                        if(strtod(b1, &finalPtr)!=0)//Verificador de entero o flotante
                        {
                            bv=b;
                            val=1;
                        }
                    }
                }
                else
                    val=0;
            }
            if(i==2)
            {
                if(scanf("%G",&c)==1)//Valida entrada de datos (cast a float)
                {
                    if(b>=-9999&&b<=9948)//Determina que el valor de variable ingresada este dentro del rango permitido
                    {
                        sprintf(c1,"%G",c);
                        if(strtod(c1, &finalPtr)!=0)//Verificador de entero o flotante
                        {
                            cv=c;//Convierte el array en un número flotante
                            val=1;
                        }
                    }
                }
                else
                    val=0;
            }
            if(val==0&&z!=1)//Error dato invalido
            {
                system("cls");
                printf("\nEntrada de datos incorrecta.\n\n");
                system("PAUSE");
            }
            if(z==1)//Error cero en la variable a
            {
                system("cls");
                printf("\nEl valor de \"a\" debe ser diferente de cero.\n\n");
                system("PAUSE");
            }
        }
        while(val==0||z==1); //Valida si la entrada es un digito
    }
    //Imprime en pantalla el análisis del polinomio de grado 2
    system("cls");
    solucionE(av, bv, cv);
    system("PAUSE");
    system("cls");
    //Determina si se puede ejecutar el modo gráfico
    if (set_graph() != 1)
    {
        printf("Este programa requiere ejecución en modo VGA.\n");
    }
    else
    {
        //Funciones encargadas de la gráfica del polinomio
        calc_coords();
        eje_xy(max,min);
        grafica_cuad(av, bv, cv, max, min);
        system("PAUSE");
        closegraph(); // Termina el modo gráfico
    }
}

//Función encargada de  mostrar en consola, la petición
//de valores max y min para graficar en el eje x,y
void ingresaMN(void)
{
    //Declaración de variables locales
    const int tam=8; //Determina el tamaño del dato de entrada incluyendo punto decimal y signo negativo (El signo positivo[+] no es usado)
    float max1=0,min1=0,Mn=0,tmv=0;
    int val1=0,val2=0,valnum=0;
    int min_x_gr=-9999; //Determina el rango de valores para "x" mínimos para graficar
    int max_x_gr=9984;  //Determina el rango de valores para "x" máximos para graficar
    char x[tam];
    char *var[2]= {"minimo","maximo"};
    char *finalPtr;
    do
    {
        val2=1;
        for(int i=0; i<2; i++)
        {
            do
            {
                val1=1;
                valnum=1;
                memset(x,0,sizeof(x)); //Limpia el array
                system("cls");//Limpia la pantalla de consola
                printf("\nIngresa el rango %s de valores para x:\n",var[i]);
                fflush (stdin);//Limpia el buffer de entrada
                if(scanf("%G",&tmv)==1)//Valida entrada de datos (cast a float)
                {
                    sprintf(x,"%G",tmv); //Convierte la entrada de datos a una arreglo char
                    if((strtod(x, &finalPtr)!=0)||tmv==0)//Verifica que el dato ingresado sea un número +,-,entero, flotante o 0
                    {
                        if(i==0)
                        {
                            min1=tmv;
                            Mn=tmv;
                        }
                        else
                        {
                            max1=tmv;
                            Mn=tmv;
                        }
                        if(Mn<min_x_gr||Mn>max_x_gr)//Verifica que el valor mínimo este dentro del rango
                        {
                            system("cls");
                            printf("Valor fuera de rango.\n\n");
                            val1=0;
                            memset(x,0,sizeof(x)); //Limpia el array
                            system("PAUSE");
                        }
                    }
                    else
                    {
                        system("cls");
                        printf("Entrada de datos incorrecta.\n\n");
                        memset(x,0,sizeof(x)); //Limpia el array
                        valnum=0;
                        system("PAUSE");
                    }
                }
                else
                {
                    system("cls");
                    printf("Entrada de datos incorrecta.\n\n");
                    memset(x,0,sizeof(x)); //Limpia el array
                    valnum=0;
                    system("PAUSE");
                }
            }
            while(val1==0||valnum==0);
        }
        if((min1>max1))
        {
            system("cls");
            printf("El valor minimo es mayor que el valor maximo.\n\n");
            val2=0;
            memset(x,0,sizeof(x)); //Limpia el array
            system("PAUSE");
        }
    }
    while(val2==0);
    system("cls");
    cuadratica(max1, min1);
}

//****************************Solución del polinomio de grado dos****************************//

//Función encargada de resolver el polinomio de grado 2
void solucionE(float a, float b, float c)
{
    //Declaración de variables locales
    float x1=0, x2=0, f=0, p=0,x=0;
    //Calculo del discriminate
    f=b*b-4*a*c;
    p=c-((b*b)/(4*a));
    x=-b/(2*a);
    //Verifica que el discriminate sea mayor o igual que 0 (raíces reales)
    if(f>=0)
    {
        //Calculo de las soluciones para x1 y x2
        x1=(-b+sqrt(f))/(2*a);
        x2=(-b-sqrt(f))/(2*a);
        //Imprime resultados
        printf("La ecuación tiene raíces reales.\n\nCeros de la función:\n");
        printf("\nx1 = %.2f", x1);
        printf("\nx2 = %.2f\n\n", x2);
    }
    else
    {
        //Calculo de la solución para x1 y x2 (raíces imaginarias)
        b=-b/(2*a);
        x1=sqrt(f*-1)/(2*a);
        x2=x1;
        //Imprime resultados
        printf("La función tiene raíces imaginarias.\n\nCeros de la función:\n");
        printf("\nx1 = %.2f + %.2fi", b, x1);
        printf("\nx2 = %.2f - %.2fi\n\n", b, x2);
    }
    if(a<0)
    {
        printf("La parabola abre hacia abajo.\n\n");
        printf("Discriminante = %.2f\n",f);
        printf("Valor maximo = %.2f para x = %.2f\n",p,x);
        printf("Valor minimo = la función no tiene valores mínimos.\n");
        printf("Punto maximo (%.2f,%.2f)\n\n",x,p);
        printf("Dominio = |R\n");
        printf("Rango = \{ y E |R : y <= %.2f\}\n\n",p);
    }
    if(a>0)
    {
        printf("La parabola abre hacia arriba.\n\n");
        printf("Discriminante = %.2f\n",f);
        printf("Valor maximo = la función no tiene valores máximos\n",p);
        printf("Valor minimo = %.2f para x = %.2f\n\n",p,x);
        printf("Punto minimo (%.2f,%.2f)\n\n",x,p);
        printf("Dominio = |R\n");
        printf("Rango = \{ y E |R : y >= %.2f\}\n\n",p);
    }


    printf("A continuación se muestra la gráfica de este polinomio.\n\n",x,p);
}


//****************************Menú principal***************************//

//Despliega  el menú principal
int main()
{
    //Declaración de variables locales
    int op=0;
    do
    {
        system("cls");
        printf("Programa de Analisis para Polinomios de Grado 2\n\n");
        printf("\t 1 Analizar función cuadratica.\n");
        printf("\t 2 Salir\n\n");
        printf("Selecciona una opcion: ");
        fflush(stdin);
        scanf("%i", &op);
        switch(op)//Selecciona la opción
        {
        case 1://Grafica el polinomio de grado 2
            system("cls");
            ingresaMN();
            break;
        case 2://Sale del menu principal
            system("cls");
            printf("Esta es una version preliminar que puede contener bugs,\nsi ha encontrado algun bug favor de reportarlo\nal siguiente email: andy1818ster@gmail.com\n\n");
            system("PAUSE");
            break;
        default://Error de seleccion
            printf("\nOpcion incorrecta.\n\n");
            system("PAUSE");
            break;
        }
    }
    while(op!=2);
    system("cls");//Limpia la pantalla de consola
    return 0;//Termina la ejecución de la aplicación
}
