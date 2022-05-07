#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include<windows.h>
#include<time.h>


#define INFINITY 9999
#define ef 10000
#define MAX 10

typedef float tPeso;

typedef int tVertice;

typedef struct
{
    tVertice origen;
    tVertice destino;
    tPeso peso;
} tArco;

typedef bool conjuntoVertices[ef];
typedef tPeso conjuntoArcos[ef][ef];

typedef struct
{
    conjuntoVertices vertices;
    conjuntoArcos arcos;
} tGrafoPonderado;

typedef struct
{
    int vIni;
    int vFin;
    float distancia;

} regArcos;

typedef struct
{
    int codCasa;
    char calle[30];
    char nomCli[30];

} regCliente;

regCliente cliente;
regArcos arcosa;

FILE *archivoClientes;
FILE *archivoArcos;

typedef bool conjuntoVertices[ef];
typedef tPeso conjuntoArcos[ef][ef];

void abrirArchivoClientes()
{
    archivoClientes = fopen("archivoClientes.dat", "rb");
}

void abrirArchivoArcos()
{
    archivoArcos = fopen("archivoArcos.dat", "rb");
}

void leerRegistroVertices()
{
    fread(&cliente, sizeof(regCliente), 1, archivoClientes);
}

void leerRegistroArco()
{
    fread(&arcosa, sizeof(regArcos), 1, archivoArcos);
}

void cerrarArchivoClientes()
{
    fclose(archivoClientes);
}

void cerrarArchivoArcos()
{
    fclose(archivoArcos);
}

void incializarGrafo(tGrafoPonderado *);
void agregaVertice(tGrafoPonderado *, int);
void agregaArcoP(tGrafoPonderado *, tArco);
void borrarVertice(tGrafoPonderado *, tVertice);
void borrarArco(tGrafoPonderado *, tArco);
int maxVertice(tGrafoPonderado *);
void visualizarMatrizPesos(tGrafoPonderado *);
void visualizarMatrizAdyacencia(tGrafoPonderado *);
void cargaInicialVertices();
void cargaInicialArcos();
void dijkstra(int G[MAX][MAX],int n,int startnode);
void subMenu();
void menu();

tGrafoPonderado *grafo;
tArco arco;

int contadorcargas=1, contadorcargas2=1;
int nuevamatriz[10][10];

void incializarGrafo(tGrafoPonderado *pGrafo)
{
    int i, j;
    for (i = 1; i < ef; i++) //La condici�n es <n
    {
        pGrafo->vertices[i] = 0;
        for (j = 1; j <= ef; j++)
        {
            pGrafo->arcos[i][j] = 0;
        }
    }
}

void agregaVertice(tGrafoPonderado *pGrafo, int vert)
{
    pGrafo->vertices[vert] = 1;
    printf("Se agrego el vertice %d\n", vert);
}

void agregaArcoP(tGrafoPonderado *pGrafo, tArco arc)
{
    if ((pGrafo->vertices[arc.origen] == 1) && (pGrafo->vertices[arc.destino] == 1))
    {
        pGrafo->arcos[arc.origen][arc.destino] = arc.peso;
        printf("Se agrego el arco [%d, %d]\n", arc.origen, arc.destino);
    }
}

void borrarVertice(tGrafoPonderado *pGrafo, tVertice ver)
{
    pGrafo->vertices[ver] = 0;
    printf("Se borro el vertice %d\n", ver);
}

void borrarArco(tGrafoPonderado *pGrafo, tArco arc)
{
    pGrafo->arcos[arc.origen][arc.destino] = 0;
    printf("Se borro el arco [%d, %d]\n", arc.origen, arc.destino);
}

int maxVertice(tGrafoPonderado *pGrafo)
{
    int i, max;
    max = 0;
    for (i = 1; i <= ef; i++)
    {
        if (pGrafo->vertices[i] == 1)
        {
            max = i;
        }
    }
    return max;
}

void visualizarMatrizPesos(tGrafoPonderado *pGrafo)
{
    int i, j, maxVer;
    printf("\nMATRIZ DE PESOS\n\n");
    maxVer = maxVertice(pGrafo);
    for (i = 1; i <= maxVer; i++)
    {
        for (j = 1; j <= maxVer; j++)
        {
            if (!(pGrafo->arcos[i][j]))
            {
               printf("\t0\t"); 
            }
            else
            {
                
                printf("\t%.1fkm\t", pGrafo->arcos[i][j]);
            }
        }
        printf("\n");
    }
}

void visualizarMatrizAdyacencia(tGrafoPonderado *pGrafo)
{
    int i, j, maxVer;
    printf("\nMATRIZ DE ADYACENCIA\n\n");
    maxVer = maxVertice(pGrafo);
    for (i = 1; i <= maxVer; i++)
    {
        for (j = 1; j <= maxVer; j++)
        {
            if (pGrafo->arcos[i][j] == 0)
            {
                printf("0");
            }
            else
            {
                printf("1");
            }
            printf(" ");
        }
        printf("\n");
    }
}

/*void caminoCorto()
{

    abrirArchivoArcos();
    int pIni, pDest, aux;
    printf("Seleccione punto de inicio: ");
    scanf("%d", &pIni);
    printf("Seleccione punto de destino: ");
    scanf("%d", &pDest);

    leerRegistroArco();
    while(!feof(archivoArcos))
    {
        if (pIni == arco.origen)
        {
            aux = arco.peso;
        }
        leerRegistroArco();
    }

    printf("hola %d", aux);

    cerrarArchivoArcos();
}
*/

void subMenu()
{
    int opc;
    printf("SELECCIONE UNA OPCION \n");
    printf("1. Agregar cliente \n"); /*Pueden hacer que agregue un vertice nuevo, pero sin modificar el archivo
	Cada vez que el programa arranca carga los datos iniciales, y despues le dan al usuario la opci�n de agregar m�s vertices y m�s arcos*/
    printf("2. Agregar conexion \n");
    printf("3. Borrar Cliente \n");
    printf("4. Borrar Conexion \n");
    printf("5. Matriz Adyacencia \n");
    printf("6. Ruta mas optima \n");
    printf("7. Volver al menu \n");
    scanf("%d", &opc);
    switch (opc)
    {
    case 1:
    { /*Solicitar el dato al usuario y agregar un nuevo vertice*/
		agregaVertice(grafo, contadorcargas);
		contadorcargas=contadorcargas+1;
		contadorcargas2=contadorcargas2+1;
		printf("se ha agregado un cliente nuevo\n");
		system("pause");
        system("cls");
		subMenu();
        break;
    }

    case 2:
    {
        /*Solicitar el dato al usuario y agregar un nuevo arco*/
        tArco nuevoarco,nuevoarco2;
        printf("ingrese el punto de origen:");
        scanf("%d",&nuevoarco.origen);
        nuevoarco2.destino=nuevoarco.origen;
        printf("ingrese el punto de destino:");
        scanf("%d",&nuevoarco.destino);
        nuevoarco2.origen=nuevoarco.destino;
        printf("ingrese la distancia de los puntos:");
        scanf("%f",&nuevoarco.peso);
        nuevoarco2.peso=nuevoarco.peso;
        agregaArcoP(grafo, nuevoarco);
        agregaArcoP(grafo, nuevoarco2);
        system("pause");
        system("cls");
        subMenu();
        break;
    }

    case 3:
    {
        int borrar;
        printf("Ingrese codigo de casa que desea borrar: ");
        scanf("%d", &borrar);
        borrarVertice(grafo, borrar);
        contadorcargas=contadorcargas-1;
        system("pause");
        system("cls");
        subMenu();
        break;
    }
    case 4:
    {
        tArco borrar;
        printf("Ingrese el numero de arco que desea borrar: ");
        scanf("%d", &borrar);
        borrarArco(grafo, borrar);
        system("pause");
        system("cls");
        subMenu();
        break;
    }

    case 5:
    {
        //caminoCorto();
        maxVertice(grafo);
        visualizarMatrizAdyacencia(grafo);
        visualizarMatrizPesos(grafo);
        
        subMenu();
        break;
    }
    case 6:
	{
    	int nododbusqueda;
		printf("ingrese el nodo de busqueda: ");
        scanf("%d",&nododbusqueda);
        matrizdijkstra(grafo, contadorcargas2);
        dijkstra(nuevamatriz,contadorcargas2,nododbusqueda);
        system("pause");
        system("cls");
        subMenu();
		break;
	}
	
	case 7:{
		system("cls");
		menu();
		
		break;
	}
    }
}

void cargaInicialVertices()
{
    abrirArchivoClientes();
    leerRegistroVertices();
    while (!feof(archivoClientes))
    {
        printf("%d  %s  %s  \n", cliente.codCasa, cliente.calle, cliente.nomCli);
        agregaVertice(grafo, cliente.codCasa);
        leerRegistroVertices();
        contadorcargas=contadorcargas+1;
        contadorcargas2=contadorcargas2+1;
    }
    cerrarArchivoClientes();
    system("pause");
    system("cls");
}
void cargaInicialArcos()
{
	tArco arco2;
    abrirArchivoArcos();
    leerRegistroArco();

    while (!feof(archivoArcos))
    {
        arco.origen = arcosa.vIni;
        arco.destino = arcosa.vFin;
        arco.peso = arcosa.distancia;
        arco2.destino = arcosa.vIni;
        arco2.origen = arcosa.vFin;
        arco2.peso = arcosa.distancia;
        agregaArcoP(grafo, arco);
        agregaArcoP(grafo, arco2);

        leerRegistroArco();
    }
    

    cerrarArchivoArcos();
    system("pause");
    system("cls");
}
void menu()
{
    int opcion;
    printf("                        ***********************************************\n");
    usleep(100000);
    printf("                        *             *     ********    *      *      *\n");
	usleep(100000); 
    printf("                        * *          **	    *           *     * *     *\n");
    usleep(100000);
    printf("                        *  *        * *	    *           *    *   *    *\n");
	usleep(100000);  
    printf("                        *   *      *  *	    ********    *   *     *   *\n");
    usleep(100000);
    printf("                        *    *    *   *     *           *  *       *  *         \n");
    usleep(100000);
    printf("                        *     *  *    *	    *           * *         * *\n");
    usleep(100000);
    printf("                        *      **     *	    ********    **           **\n");
    usleep(100000);
    printf("                                                       Beta Version 1.0 \n");
    printf("                        ***********************************************   \n");
    usleep(100000);
    
	printf("SELECCIONE UNA OPCION \n");
    printf("1. Ingresar \n");
    printf("2. Salir \n");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:
    {

        //grafo = (tGrafoPonderado *)malloc(sizeof(tGrafoPonderado));
		grafo = (tGrafoPonderado *)malloc(sizeof(tGrafoPonderado));
    	incializarGrafo(grafo);
    	//Se realiza la carga inicial
    	cargaInicialVertices();
    	cargaInicialArcos();
        subMenu();

        break;
    }
    
    case 2: {
		printf("Gracias por usar el programa \n");
		system("pause");
		exit(-1);
		break;
	}
    }
}

int main()
{
    system("color 2");
    menu();
}

void dijkstra(int G[MAX][MAX],int n,int startnode){
 
int cost[MAX][MAX],distance[MAX],pred[MAX];
int visited[MAX],count,mindistance,nextnode,i,j;

for(i=1;i<n;i++)
for(j=1;j<n;j++)
if(G[i][j]==0)
cost[i][j]=INFINITY;
else
cost[i][j]=G[i][j];

for(i=1;i<n;i++)
{
distance[i]=cost[startnode][i];
pred[i]=startnode;
visited[i]=0;
}
distance[startnode]=0;
visited[startnode]=1;
count=1;
while(count<n-1)
{
mindistance=INFINITY;

for(i=1;i<n;i++)
if(distance[i]<mindistance&&!visited[i])
{
mindistance=distance[i];
nextnode=i;
}

visited[nextnode]=1;
for(i=1;i<n;i++)
if(!visited[i])
if(mindistance+cost[nextnode][i]<distance[i])
{
distance[i]=mindistance+cost[nextnode][i];
pred[i]=nextnode;
}
count++;
}
 

for(i=1;i<n;i++)
if(i!=startnode)
{
printf("\nDistancia de la casa %d=%d",i,distance[i]);
printf("\n Camino =%d",i);
j=i;
do
{
j=pred[j];
printf("<-%d",j);
}while(j!=startnode);
}
}
int matrizdijkstra(tGrafoPonderado * grafo, int cantNodos);
int matrizdijkstra(tGrafoPonderado * grafo, int cantNodos){
	int x,y;
	 for(x = 1; x<= cantNodos; x++) {
        for(y = 1; y<= cantNodos; y++) {
            nuevamatriz[x][y] = grafo->arcos[x][y];
        }
    }
}
