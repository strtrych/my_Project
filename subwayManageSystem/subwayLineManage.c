#include "main.h"
#include "subwayLineManage.h"



int mainSLM()
{
    Graph* graph = NULL;
    int flag = 1;		//循环结束标志
    if (!graph)
    {
        graph = createGraph(MAXSIZE);
    }
    readDataInFile(graph);
    //init(graph);
    while (flag)
    {
        keyDown(graph, &flag);
        printf("\n");
        system("pause");
        system("cls");
    }
    writeDataInFile(graph);
    freeGraph(graph);
    return 0;
}

// 创建图
Graph* createGraph(int size)
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->size = size;
    graph->num = 0;
    graph->adjLists = (Node**)malloc(size * sizeof(Node*));
    for (int i = 0; i < size; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

// 创建节点
Node* createNode(char* name, int mileage)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    Station* newStation = (Station*)malloc(sizeof(Station));
    strcpy(newStation->name, name);
    newStation->mileage = mileage;
    newNode->data = newStation;
    newNode->next = NULL;
    return newNode;
}

//查找站点，并返回下标
int findStation(Graph* graph, char* staName)
{
    int ret = -1;
    for (int i = 0; i < graph->num; i++)
    {
        if (!memcmp(graph->adjLists[i]->data->name, staName, strlen(staName)))
        {
            ret = i;
            break;
        }
    }
    return ret;
}

//获取路线信息
Node* getRoute(Node* head, char* name)
{
    Node* ret = NULL;
    while (head != NULL)
    {
        if (memcmp(head->data->name, name, strlen(head->data->name)) == 0)
        {
            ret = head;
        }
        head = head->next;
    }
    return ret;
}

// 增加边
void addEdge(Graph* graph, int src, Station* station)
{
    if (!graph)
    {
        printf("graph is null\n");
        return;
    }

    Node* newNode = createNode(station->name, station->mileage);
    newNode->next = graph->adjLists[src]->next;
    graph->adjLists[src]->next = newNode;

    // 因为是无向图，我们也需要在目标节点添加边

    Node* tmpNode = createNode(graph->adjLists[src]->data->name, graph->adjLists[src]->data->mileage);

    int index = findStation(graph, station->name);
    if (index != -1) 	//判断要添加的点是否存在于图中
    {
        tmpNode->next = graph->adjLists[index]->next;
        graph->adjLists[index]->next = tmpNode;
        return;
    }
    newNode = createNode(station->name, station->mileage);
    newNode->next = tmpNode;
    graph->adjLists[(graph->num)++] = newNode;

}

//删除边
void deleteEdge(Graph* graph, int first, int second)
{
    if (!graph)
    {
        printf("graph is null\n");
        return;
    }
    char fname[MAX_NAME_LENGTH];
    strcpy(fname, graph->adjLists[first]->data->name);
    char sname[MAX_NAME_LENGTH];
    strcpy(sname, graph->adjLists[second]->data->name);
    Node* fNode = graph->adjLists[first];
    Node* sNode = graph->adjLists[second];
    Node* tmpNode = fNode->next;
    while (fNode && tmpNode)
    {
        if (memcmp(tmpNode->data->name, sname, strlen(sname)) == 0)
        {
            fNode->next = tmpNode->next;
            free(tmpNode->data);
            free(tmpNode);
            tmpNode = NULL;
            break;
        }
        fNode = tmpNode;
        tmpNode = tmpNode->next;
    }

    tmpNode = sNode->next;
    while (sNode && tmpNode)
    {
        if (memcmp(tmpNode->data->name, fname, strlen(fname)) == 0)
        {
            sNode->next = tmpNode->next;
            free(tmpNode->data);
            free(tmpNode);
            tmpNode = NULL;
            break;
        }
        sNode = tmpNode;
        tmpNode = tmpNode->next;
    }
}

//数据的初始化
void init(Graph* graph)
{
    srand((unsigned int)time(NULL));
    char* stationNames[] = { "后卫寨","纪阳","三桥","六村堡","西窑头","劳动南路","科技二路","吉祥村",//0-7
        "草滩农场","北客站","行政中心","北大街","钟楼","小寨","会展中心","韦曲南","长安科技产业园",//8-16
        "邓店新村","侧坡村","五路口","大差市","新筑","金花路","咸宁中路","大雁塔北","雁南路","纺织城",//17-26
        "韦曲科技产业园","纺织城火车站" };//27-28
    for (int i = 0; i < sizeof(stationNames) / sizeof(stationNames[0]); i++)
    {
        int randNum = (int)1 + rand() % 3;		//生成1-3之间的随机数
        Node* tmpNode = createNode(stationNames[i], randNum);
        graph->adjLists[(graph->num)++] = tmpNode;
    }


    int src = findStation(graph, "后卫寨");
    addEdge(graph, src, graph->adjLists[2]->data);
    src = findStation(graph, "纪阳");
    addEdge(graph, src, graph->adjLists[4]->data);
    src = findStation(graph, "三桥");
    addEdge(graph, src, graph->adjLists[11]->data);
    addEdge(graph, src, graph->adjLists[4]->data);
    src = findStation(graph, "六村堡");
    addEdge(graph, src, graph->adjLists[2]->data);
    src = findStation(graph, "西窑头");
    addEdge(graph, src, graph->adjLists[5]->data);
    src = findStation(graph, "劳动南路");
    addEdge(graph, src, graph->adjLists[6]->data);
    src = findStation(graph, "科技二路");
    addEdge(graph, src, graph->adjLists[7]->data);
    src = findStation(graph, "吉祥村");
    addEdge(graph, src, graph->adjLists[13]->data);
    src = findStation(graph, "草滩农场");
    addEdge(graph, src, graph->adjLists[10]->data);
    src = findStation(graph, "北客站");
    addEdge(graph, src, graph->adjLists[10]->data);
    src = findStation(graph, "行政中心");
    addEdge(graph, src, graph->adjLists[19]->data);
    addEdge(graph, src, graph->adjLists[11]->data);
    src = findStation(graph, "北大街");
    addEdge(graph, src, graph->adjLists[19]->data);
    addEdge(graph, src, graph->adjLists[12]->data);
    src = findStation(graph, "钟楼");
    addEdge(graph, src, graph->adjLists[5]->data);
    src = findStation(graph, "小寨");
    addEdge(graph, src, graph->adjLists[12]->data);
    addEdge(graph, src, graph->adjLists[24]->data);
    src = findStation(graph, "会展中心");
    addEdge(graph, src, graph->adjLists[13]->data);
    src = findStation(graph, "韦曲南");
    addEdge(graph, src, graph->adjLists[14]->data);
    src = findStation(graph, "长安科技产业园");
    addEdge(graph, src, graph->adjLists[17]->data);
    src = findStation(graph, "邓店新村");
    addEdge(graph, src, graph->adjLists[6]->data);
    src = findStation(graph, "侧坡村");
    addEdge(graph, src, graph->adjLists[17]->data);
    src = findStation(graph, "五路口");
    addEdge(graph, src, graph->adjLists[22]->data);
    addEdge(graph, src, graph->adjLists[20]->data);
    src = findStation(graph, "大差市");
    addEdge(graph, src, graph->adjLists[12]->data);
    addEdge(graph, src, graph->adjLists[23]->data);
    src = findStation(graph, "新筑");
    addEdge(graph, src, graph->adjLists[22]->data);
    src = findStation(graph, "金花路");
    addEdge(graph, src, graph->adjLists[23]->data);
    src = findStation(graph, "咸宁中路");
    addEdge(graph, src, graph->adjLists[26]->data);
    src = findStation(graph, "大雁塔北");
    addEdge(graph, src, graph->adjLists[23]->data);
    src = findStation(graph, "雁南路");
    addEdge(graph, src, graph->adjLists[14]->data);
    addEdge(graph, src, graph->adjLists[24]->data);
    src = findStation(graph, "纺织城");
    addEdge(graph, src, graph->adjLists[22]->data);
    src = findStation(graph, "韦曲科技产业园");
    addEdge(graph, src, graph->adjLists[25]->data);
    src = findStation(graph, "纺织城火车站");
    addEdge(graph, src, graph->adjLists[25]->data);

}

// 删除站点
int deleteStation(Graph* graph)
{
    char delName[MAX_NAME_LENGTH];
    printf("请输入要删除的站点名称：");
    scanf("%s", delName);

    int delNum = findStation(graph, delName);
    if (delNum == -1)
    {
        printf("未找到该站点\n");
        return 0;
    }
    Node* headNode = graph->adjLists[delNum]->next;
    while (headNode)
    {
        int num = findStation(graph, headNode->data->name);
        headNode = headNode->next;
        deleteEdge(graph, delNum, num);
       
    }
    free(graph->adjLists[delNum]->data);
    free(graph->adjLists[delNum]);
    graph->adjLists[delNum] = NULL;
    for (int i = delNum; i < graph->num; i++)
    {
        Node* tmp = graph->adjLists[i];
        graph->adjLists[i] = graph->adjLists[i + 1];
        graph->adjLists[i + 1] = tmp;
    }
    graph->num--;
    return 1;
}


// 释放图的内存
void freeGraph(Graph* graph)
{
    for (int i = 0; i < graph->num; i++) {
        Node* temp = graph->adjLists[i];
        while (temp != NULL) {
            if (temp->next == NULL)
            {
                free(temp);
                temp = NULL;
                break;
            }
            Node* toDelete = temp->next;
            temp->next = toDelete->next;
            free(toDelete->data);
            free(toDelete);
        }
    }
    free(graph->adjLists);
    free(graph);
}


//修改站点信息
int changeStation(Graph* graph)
{
    char oldName[MAX_NAME_LENGTH];
    char newName[MAX_NAME_LENGTH];
    int newMileage = 0;
    printf("请输入要修改的站点名称：");
    scanf("%s", oldName);
    int ret = findStation(graph, oldName);
    if (ret == -1)
    {
        printf("未找到该站点\n");
        return 0;
    }
    printf("请输入新的站点名称：");
    scanf("%s", newName);
    printf("请输入新的站点里程：");
    scanf("%d", &newMileage);
    if (newMileage <= 0 || newMileage >= 10)
    {
        printf("输入数据超出范围\n");
        return 0;
    }
    strcpy(graph->adjLists[ret]->data->name, newName);
    graph->adjLists[ret]->data->mileage = newMileage;
    Node* headNode = graph->adjLists[ret]->next;
    while (headNode)
    {
        int num = findStation(graph, headNode->data->name);
        Node* tmpNode = getRoute(graph->adjLists[num], oldName);
        strcpy(tmpNode->data->name, newName);
        tmpNode->data->mileage = newMileage;

        headNode = headNode->next;
    }
    return 1;
}

//显示菜单
void showMenu()
{
    printf("********************************\n");
    printf("-----城市地铁线路管理系统-----\n");
    printf("\t1.添加路线\n");
    printf("\t2.添加站点\n");
    printf("\t3.显示邻接表数据\n");
    printf("\t4.删除路线\n");
    printf("\t5.删除站点\n");
    printf("\t6.查找最短路线\n");
    printf("\t7.显示所有路线\n");
    printf("\t8.修改站点信息\n");
    printf("\t0.退出系统\n");
    printf("********************************\n");
    printf("请执行您的操作（输入数字0~8）：");
}



//添加路线
int addPath(Graph* graph)
{
    char oldName[MAX_NAME_LENGTH];
    Station newStation;
    printf("请输入要添加的路线信息\n");
    printf("请输入已存在的站点名称：");
    scanf("%s", oldName);
    int src = findStation(graph, oldName);
    if (src == -1)
    {
        printf("该站点不存在,请先去添加站点\n");
        return -1;
    }
    printf("请输入另一站点名称：");
    scanf("%s", newStation.name);

    if (getRoute(graph->adjLists[src], newStation.name) != NULL)
    {
        printf("该路线已存在\n");
        return 0;
    }

    int tmp = findStation(graph, newStation.name);
    if (tmp == -1)
    {
        printf("请输入另一站点里程数(1~9)：");
        scanf("%d", &newStation.mileage);
        if (newStation.mileage <= 0 || newStation.mileage >= 10)
        {
            printf("输入数据超出范围\n");
            return 0;
        }
    }
    else
    {
        newStation.mileage = graph->adjLists[tmp]->data->mileage;
    }
    addEdge(graph, src, &newStation);
    return 1;
}

//删除路线
int deletePath(Graph* graph)
{
    char fname[MAX_NAME_LENGTH];
    char sname[MAX_NAME_LENGTH];
    printf("请输入要删除的路线信息\n");
    printf("请输入第一个站点名称：");
    scanf("%s", fname);
    int first = findStation(graph, fname);
    if (first == -1)
    {
        printf("未找到该站点\n");
        return 0;
    }
    printf("请输入第二个站点名称：");
    scanf("%s", sname);
    int second = findStation(graph, sname);
    if (second == -1)
    {
        printf("未找到该站点\n");
        return 0;
    }
    if (getRoute(graph->adjLists[first], graph->adjLists[second]->data->name) == NULL)
    {
        printf("未找到该线路\n");
        return 0;
    }
    deleteEdge(graph, first, second);
    return 1;
}

//增加站点
int addStation(Graph* graph)
{
    if (graph->num >= graph->size)
    {
        printf("空间已满\n");
        return -1;
    }
    char newName[MAX_NAME_LENGTH];
    printf("请输入你要增加的站点信息：\n");
    printf("请输入站点名称：");
    scanf("%s", newName);
    int ret = findStation(graph, newName);
    if (ret != -1)
    {
        printf("站点已存在\n");
        return 0;
    }
    int newMileage;
    printf("请输入站点里程(1~9)：");
    scanf("%d", &newMileage);
    if (newMileage <= 0 || newMileage >= 10)
    {
        printf("输入数据超出范围\n");
        return 0;
    }
    graph->adjLists[graph->num++] = createNode(newName, newMileage);

    return 1;
}

//显示整个邻接表
void showList(Graph* graph)
{
    if (graph->adjLists[0] == NULL)
    {
        printf("邻接表为空\n");
        return ;
    }
    for (int i = 0; i < graph->num; i++)
    {
        Node* tmpNode = graph->adjLists[i];

        while (tmpNode)
        {
            if (tmpNode != graph->adjLists[i])
            {
                printf(" -> ");
            }
            printf("%-15s:%d\t", tmpNode->data->name, tmpNode->data->mileage);
            tmpNode = tmpNode->next;
        }
        printf("\n");
    }
}


//文件写操作
void writeDataInFile(Graph* graph)
{
    FILE* fp = fopen(FileName, "w");
    if (fp == NULL)
    {
        perror("fopen");
        return;
    }
    for (int i = 0; i < graph->num; i++)
    {
        Node* tmpNode = graph->adjLists[i];

        while (tmpNode)
        {

            fprintf(fp, "%-15s:%d\t", tmpNode->data->name, 
			tmpNode->data->mileage);
            tmpNode = tmpNode->next;
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

//文件读操作
void readDataInFile(Graph* graph)
{
    FILE* fp = fopen(FileName, "r");
    if (fp == NULL)
    {
        fp = fopen(FileName, "w+");
    }
    char tmpStr[MAX_NAME_LENGTH];
    char tmpName[MAX_NAME_LENGTH];
    int tmpMileage;
    while (!feof(fp))
    {
    start:

        fgets(tmpStr, 19, fp);
        if (feof(fp))
            break;
        sscanf(tmpStr, "%s :%d\t", tmpName, &tmpMileage);
        Node* tmpNode = createNode(tmpName, tmpMileage);
        if (graph->adjLists[graph->num] == NULL)
        {
            graph->adjLists[graph->num] = tmpNode;
        }
        else
        {
            tmpNode->next = graph->adjLists[graph->num]->next;
            graph->adjLists[graph->num]->next = tmpNode;
        }

        if (fgetc(fp) == '\n')
        {
            graph->num++;
            goto start;
        }
        fseek(fp, -1, SEEK_CUR);
    }
    fclose(fp);
}


// 打印路径
void printPath(char(*path)[MAX_NAME_LENGTH], int pathIndex, int* mileages)
{
    int sumMileage = 0;
    for (int i = 0; i < pathIndex; i++)
    {
        if (i == 0 || i == pathIndex - 1)
        {
            sumMileage += mileages[i];
        }
        else
            sumMileage += mileages[i] + mileages[i];
        printf("%s", path[i]);
        if (i < pathIndex - 1)
        {
            printf(" -> ");
        }
    }
    printf("\n");
    printf("该路线总里程数为:%d公里\n", sumMileage);

}

// 利用DFS深度优先遍历查找从 start 到 end 的所有路径的递归函数		
void findAllPathsUtil(Graph* graph, int start, int end, int* visited, char(*path)[MAX_NAME_LENGTH], int* mileages, int pathIndex)
{

    visited[start] = 1; // 标记当前节点为已访问
    strcpy(path[pathIndex], graph->adjLists[start]->data->name); // 将当前节点添加到路径中
    mileages[pathIndex] = graph->adjLists[start]->data->mileage;
    pathIndex++;

    // 如果当前节点是目标节点，打印路径
    if (start == end)
    {
        if (pathIndex < 15)
            printPath(path, pathIndex, mileages);
    }
    else
    {
        // 遍历当前节点的所有邻接节点
        Node* tmpNode = graph->adjLists[start]->next;
        while (tmpNode != NULL)
        {
            int neighborIndex = findStation(graph, tmpNode->data->name);
            // 如果邻接节点未被访问，递归查找
            if (neighborIndex != -1 && !visited[neighborIndex])
            {
                findAllPathsUtil(graph, neighborIndex, end, visited, path, mileages, pathIndex);
            }
            tmpNode = tmpNode->next;
        }
    }

    // 回溯，标记当前节点为未访问
    pathIndex--;
    visited[start] = 0;
}

// 查找从 start到 end的所有路径
int findAllPaths(Graph* graph)
{
    int start, end;
    if (!isPath(graph, &start, &end))
    {
        return 0;
    }
    int visited[MAXSIZE] = { 0 }; // 标记数组,用来记录站点是否被访问
    char path[MAXSIZE][MAX_NAME_LENGTH]; // 路径数组
    int mileages[MAXSIZE];			//总里程数
    findAllPathsUtil(graph, start, end, visited, path, mileages, 0); // 调用递归函数

    return 1;
}


//判断查询线路时站点信息是否正确
int isPath(Graph* graph, int* start, int* end)
{
    char startName[MAX_NAME_LENGTH];
    char endName[MAX_NAME_LENGTH];
    printf("请输入起始站点：");
    scanf("%s", startName);
    printf("请输入目的站点：");
    scanf("%s", endName);
    *start = findStation(graph, startName);
    *end = findStation(graph, endName);

    // 检查起始或终止站点是否有效
    if (*start == -1 || *end == -1) {
        printf("起始站点或终止站点无效\n");
        return 0;
    }
    return 1;
}




// 计算最短路径
void dijkstra(Graph* graph, int start, int end) 
{
    int dist[MAXSIZE];			//start到各个节点的距离
    int prev[MAXSIZE];			//记录路径
    int visited[MAXSIZE];
    int numVertices = graph->num;
    Node* adjNode;
    
    // 初始化所有距离为无穷大
    for (int i = 0; i < numVertices; i++) 
	{
        dist[i] = INT_MAX;			//INT_MAX:无穷大
        prev[i] = -1;
        visited[i] = 0;
    }

    dist[start] = 0;
    
    for (int i = 0; i < numVertices; i++) 
	{
        // 找到当前未访问的节点中距离最小的节点
        int u = -1;
        for (int j = 0; j < numVertices; j++) 
		{
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) 
			{
                u = j;
            }
        }
        
        if (dist[u] == INT_MAX) break;  // 剩下的节点都是不可达的

        visited[u] = 1;
        adjNode = graph->adjLists[u]->next;

        // 更新邻接节点的距离
        while (adjNode) 
		{
            int v = findStation(graph, adjNode->data->name);	//当前从未访问节点中距离起点最近的节点
            if (v != -1 && dist[u] + adjNode->data->mileage < dist[v]) 
			{
                dist[v] = dist[u] + adjNode->data->mileage;
                prev[v] = u;
            }
            adjNode = adjNode->next;
        }
    }

    // 打印最短路径
    printf("最短路径从站点 %s 到站点 %s 的最短距离是 %d\n", graph->adjLists[start]->data->name, graph->adjLists[end]->data->name, dist[end]);
    printf("路径: ");
    
    int path[MAXSIZE];
    int pathIndex = 0;
    for (int v = end; v != -1; v = prev[v]) {
        path[pathIndex++] = v;
    }
    for (int i = pathIndex - 1; i >= 0; i--) {
        printf("%s", graph->adjLists[path[i]]->data->name);
        if (i > 0) {
            printf(" -> ");
        }
    }
    printf("\n");
}

//查找从 start到 end里程数最小的路径
int findMinMileagePaths(Graph* graph) {
    int start, end;
    if (!isPath(graph, &start, &end)) {
        return 0;
    }

    dijkstra(graph, start, end);
    return 1;
}


//人机交互
int keyDown(Graph* graph, int* flag)
{
    int key;
    showMenu();
    fflush(stdin);		//清空缓冲区
    scanf("%d", &key);

    switch (key)
    {
    case 0:
        *flag = 0;
        break;

    case 1:
        if (addPath(graph) == 1)
        {
            printf("路线添加成功\n");
        }
        break;

    case 2:
        if (addStation(graph) == 1)
        {
            printf("站点添加成功\n");
        }
        break;

    case 3:
        printf("\n");
        printf("\t\t\t\t\t\t邻接表数据显示如下：\n");
        showList(graph);

        break;

    case 4:
        if (deletePath(graph))
        {
            printf("路线删除成功\n");
        }
        break;

    case 5:
        if (deleteStation(graph))
        {
            printf("站点删除成功\n");
        }
        break;

    case 6:
		
		if(findMinMileagePaths(graph))
		{
			printf("最短路径查询完毕....\n");
		}

        break;

    case 7:
        if (findAllPaths(graph))
        {
            printf("\n");
            printf("路径搜索完成....\n");
        }
        break;

    case 8:
        if (changeStation(graph))
        {
            printf("路线修改成功\n");
        }
        break;


    default:
        printf("指令输入错误，请重新输入\n");

        break;
    }
}

