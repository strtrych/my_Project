#ifndef __SUBWAYLINEMANAGE_C__
#define __SUBWAYLINEMANAGE_C__

#define MAXSIZE 50
#define MAX_NAME_LENGTH 20
#define MAX_PATH_LENGTH 1024
#define FileName "D:/tmpFile/adjLists.txt"

// 数据结构体
typedef struct station {
    char name[MAX_NAME_LENGTH];
    int mileage; // 里程
} Station;

// 链表节点结构体
typedef struct Node {
    Station* data;
    struct Node* next;
} Node;

// 图结构体
typedef struct Graph {
    int size;	//容量
    int num;	//当前大小
    Node** adjLists;
} Graph;


int mainSLM();
void showMenu();
int addPath(Graph* graph);
int keyDown(Graph* graph, int* flag);
Graph* createGraph(int size);
Node* createNode(char* name, int mileage);
int findStation(Graph* graph, char* staName);
Node* getRoute(Node* head, char* name);
void addEdge(Graph* graph, int src, Station* station);
void deleteEdge(Graph* graph, int first, int second);
void init(Graph* graph);
int deleteStation(Graph* graph);
int changeStation(Graph* graph);
int deletePath(Graph* graph);
void showList(Graph* graph);
void freeGraph(Graph* graph);
void writeDataInFile(Graph* graph);
void readDataInFile(Graph* graph);
void printPath(char(*path)[MAX_NAME_LENGTH], int pathIndex, int* sumMileage);
void findAllPathsUtil(Graph* graph, int start, int end, int* visited, char(*path)[MAX_NAME_LENGTH], int* sumMileage, int pathIndex);
int findAllPaths(Graph* graph);
int isPath(Graph* graph, int* start, int* end);
int findMinStationPaths(Graph* graph);

#endif