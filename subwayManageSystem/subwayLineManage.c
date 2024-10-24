#include "main.h"
#include "subwayLineManage.h"



int mainSLM()
{
    Graph* graph = NULL;
    int flag = 1;		//ѭ��������־
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

// ����ͼ
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

// �����ڵ�
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

//����վ�㣬�������±�
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

//��ȡ·����Ϣ
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

// ���ӱ�
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

    // ��Ϊ������ͼ������Ҳ��Ҫ��Ŀ��ڵ���ӱ�

    Node* tmpNode = createNode(graph->adjLists[src]->data->name, graph->adjLists[src]->data->mileage);

    int index = findStation(graph, station->name);
    if (index != -1) 	//�ж�Ҫ��ӵĵ��Ƿ������ͼ��
    {
        tmpNode->next = graph->adjLists[index]->next;
        graph->adjLists[index]->next = tmpNode;
        return;
    }
    newNode = createNode(station->name, station->mileage);
    newNode->next = tmpNode;
    graph->adjLists[(graph->num)++] = newNode;

}

//ɾ����
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

//���ݵĳ�ʼ��
void init(Graph* graph)
{
    srand((unsigned int)time(NULL));
    char* stationNames[] = { "����կ","����","����","���層","��Ҥͷ","�Ͷ���·","�Ƽ���·","�����",//0-7
        "��̲ũ��","����վ","��������","�����","��¥","Сկ","��չ����","Τ����","�����Ƽ���ҵ԰",//8-16
        "�˵��´�","���´�","��·��","�����","����","��·","������·","��������","����·","��֯��",//17-26
        "Τ���Ƽ���ҵ԰","��֯�ǻ�վ" };//27-28
    for (int i = 0; i < sizeof(stationNames) / sizeof(stationNames[0]); i++)
    {
        int randNum = (int)1 + rand() % 3;		//����1-3֮��������
        Node* tmpNode = createNode(stationNames[i], randNum);
        graph->adjLists[(graph->num)++] = tmpNode;
    }


    int src = findStation(graph, "����կ");
    addEdge(graph, src, graph->adjLists[2]->data);
    src = findStation(graph, "����");
    addEdge(graph, src, graph->adjLists[4]->data);
    src = findStation(graph, "����");
    addEdge(graph, src, graph->adjLists[11]->data);
    addEdge(graph, src, graph->adjLists[4]->data);
    src = findStation(graph, "���層");
    addEdge(graph, src, graph->adjLists[2]->data);
    src = findStation(graph, "��Ҥͷ");
    addEdge(graph, src, graph->adjLists[5]->data);
    src = findStation(graph, "�Ͷ���·");
    addEdge(graph, src, graph->adjLists[6]->data);
    src = findStation(graph, "�Ƽ���·");
    addEdge(graph, src, graph->adjLists[7]->data);
    src = findStation(graph, "�����");
    addEdge(graph, src, graph->adjLists[13]->data);
    src = findStation(graph, "��̲ũ��");
    addEdge(graph, src, graph->adjLists[10]->data);
    src = findStation(graph, "����վ");
    addEdge(graph, src, graph->adjLists[10]->data);
    src = findStation(graph, "��������");
    addEdge(graph, src, graph->adjLists[19]->data);
    addEdge(graph, src, graph->adjLists[11]->data);
    src = findStation(graph, "�����");
    addEdge(graph, src, graph->adjLists[19]->data);
    addEdge(graph, src, graph->adjLists[12]->data);
    src = findStation(graph, "��¥");
    addEdge(graph, src, graph->adjLists[5]->data);
    src = findStation(graph, "Сկ");
    addEdge(graph, src, graph->adjLists[12]->data);
    addEdge(graph, src, graph->adjLists[24]->data);
    src = findStation(graph, "��չ����");
    addEdge(graph, src, graph->adjLists[13]->data);
    src = findStation(graph, "Τ����");
    addEdge(graph, src, graph->adjLists[14]->data);
    src = findStation(graph, "�����Ƽ���ҵ԰");
    addEdge(graph, src, graph->adjLists[17]->data);
    src = findStation(graph, "�˵��´�");
    addEdge(graph, src, graph->adjLists[6]->data);
    src = findStation(graph, "���´�");
    addEdge(graph, src, graph->adjLists[17]->data);
    src = findStation(graph, "��·��");
    addEdge(graph, src, graph->adjLists[22]->data);
    addEdge(graph, src, graph->adjLists[20]->data);
    src = findStation(graph, "�����");
    addEdge(graph, src, graph->adjLists[12]->data);
    addEdge(graph, src, graph->adjLists[23]->data);
    src = findStation(graph, "����");
    addEdge(graph, src, graph->adjLists[22]->data);
    src = findStation(graph, "��·");
    addEdge(graph, src, graph->adjLists[23]->data);
    src = findStation(graph, "������·");
    addEdge(graph, src, graph->adjLists[26]->data);
    src = findStation(graph, "��������");
    addEdge(graph, src, graph->adjLists[23]->data);
    src = findStation(graph, "����·");
    addEdge(graph, src, graph->adjLists[14]->data);
    addEdge(graph, src, graph->adjLists[24]->data);
    src = findStation(graph, "��֯��");
    addEdge(graph, src, graph->adjLists[22]->data);
    src = findStation(graph, "Τ���Ƽ���ҵ԰");
    addEdge(graph, src, graph->adjLists[25]->data);
    src = findStation(graph, "��֯�ǻ�վ");
    addEdge(graph, src, graph->adjLists[25]->data);

}

// ɾ��վ��
int deleteStation(Graph* graph)
{
    char delName[MAX_NAME_LENGTH];
    printf("������Ҫɾ����վ�����ƣ�");
    scanf("%s", delName);

    int delNum = findStation(graph, delName);
    if (delNum == -1)
    {
        printf("δ�ҵ���վ��\n");
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


// �ͷ�ͼ���ڴ�
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


//�޸�վ����Ϣ
int changeStation(Graph* graph)
{
    char oldName[MAX_NAME_LENGTH];
    char newName[MAX_NAME_LENGTH];
    int newMileage = 0;
    printf("������Ҫ�޸ĵ�վ�����ƣ�");
    scanf("%s", oldName);
    int ret = findStation(graph, oldName);
    if (ret == -1)
    {
        printf("δ�ҵ���վ��\n");
        return 0;
    }
    printf("�������µ�վ�����ƣ�");
    scanf("%s", newName);
    printf("�������µ�վ����̣�");
    scanf("%d", &newMileage);
    if (newMileage <= 0 || newMileage >= 10)
    {
        printf("�������ݳ�����Χ\n");
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

//��ʾ�˵�
void showMenu()
{
    printf("********************************\n");
    printf("-----���е�����·����ϵͳ-----\n");
    printf("\t1.���·��\n");
    printf("\t2.���վ��\n");
    printf("\t3.��ʾ�ڽӱ�����\n");
    printf("\t4.ɾ��·��\n");
    printf("\t5.ɾ��վ��\n");
    printf("\t6.�������·��\n");
    printf("\t7.��ʾ����·��\n");
    printf("\t8.�޸�վ����Ϣ\n");
    printf("\t0.�˳�ϵͳ\n");
    printf("********************************\n");
    printf("��ִ�����Ĳ�������������0~8����");
}



//���·��
int addPath(Graph* graph)
{
    char oldName[MAX_NAME_LENGTH];
    Station newStation;
    printf("������Ҫ��ӵ�·����Ϣ\n");
    printf("�������Ѵ��ڵ�վ�����ƣ�");
    scanf("%s", oldName);
    int src = findStation(graph, oldName);
    if (src == -1)
    {
        printf("��վ�㲻����,����ȥ���վ��\n");
        return -1;
    }
    printf("��������һվ�����ƣ�");
    scanf("%s", newStation.name);

    if (getRoute(graph->adjLists[src], newStation.name) != NULL)
    {
        printf("��·���Ѵ���\n");
        return 0;
    }

    int tmp = findStation(graph, newStation.name);
    if (tmp == -1)
    {
        printf("��������һվ�������(1~9)��");
        scanf("%d", &newStation.mileage);
        if (newStation.mileage <= 0 || newStation.mileage >= 10)
        {
            printf("�������ݳ�����Χ\n");
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

//ɾ��·��
int deletePath(Graph* graph)
{
    char fname[MAX_NAME_LENGTH];
    char sname[MAX_NAME_LENGTH];
    printf("������Ҫɾ����·����Ϣ\n");
    printf("�������һ��վ�����ƣ�");
    scanf("%s", fname);
    int first = findStation(graph, fname);
    if (first == -1)
    {
        printf("δ�ҵ���վ��\n");
        return 0;
    }
    printf("������ڶ���վ�����ƣ�");
    scanf("%s", sname);
    int second = findStation(graph, sname);
    if (second == -1)
    {
        printf("δ�ҵ���վ��\n");
        return 0;
    }
    if (getRoute(graph->adjLists[first], graph->adjLists[second]->data->name) == NULL)
    {
        printf("δ�ҵ�����·\n");
        return 0;
    }
    deleteEdge(graph, first, second);
    return 1;
}

//����վ��
int addStation(Graph* graph)
{
    if (graph->num >= graph->size)
    {
        printf("�ռ�����\n");
        return -1;
    }
    char newName[MAX_NAME_LENGTH];
    printf("��������Ҫ���ӵ�վ����Ϣ��\n");
    printf("������վ�����ƣ�");
    scanf("%s", newName);
    int ret = findStation(graph, newName);
    if (ret != -1)
    {
        printf("վ���Ѵ���\n");
        return 0;
    }
    int newMileage;
    printf("������վ�����(1~9)��");
    scanf("%d", &newMileage);
    if (newMileage <= 0 || newMileage >= 10)
    {
        printf("�������ݳ�����Χ\n");
        return 0;
    }
    graph->adjLists[graph->num++] = createNode(newName, newMileage);

    return 1;
}

//��ʾ�����ڽӱ�
void showList(Graph* graph)
{
    if (graph->adjLists[0] == NULL)
    {
        printf("�ڽӱ�Ϊ��\n");
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


//�ļ�д����
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

//�ļ�������
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


// ��ӡ·��
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
    printf("��·���������Ϊ:%d����\n", sumMileage);

}

// ����DFS������ȱ������Ҵ� start �� end ������·���ĵݹ麯��		
void findAllPathsUtil(Graph* graph, int start, int end, int* visited, char(*path)[MAX_NAME_LENGTH], int* mileages, int pathIndex)
{

    visited[start] = 1; // ��ǵ�ǰ�ڵ�Ϊ�ѷ���
    strcpy(path[pathIndex], graph->adjLists[start]->data->name); // ����ǰ�ڵ���ӵ�·����
    mileages[pathIndex] = graph->adjLists[start]->data->mileage;
    pathIndex++;

    // �����ǰ�ڵ���Ŀ��ڵ㣬��ӡ·��
    if (start == end)
    {
        if (pathIndex < 15)
            printPath(path, pathIndex, mileages);
    }
    else
    {
        // ������ǰ�ڵ�������ڽӽڵ�
        Node* tmpNode = graph->adjLists[start]->next;
        while (tmpNode != NULL)
        {
            int neighborIndex = findStation(graph, tmpNode->data->name);
            // ����ڽӽڵ�δ�����ʣ��ݹ����
            if (neighborIndex != -1 && !visited[neighborIndex])
            {
                findAllPathsUtil(graph, neighborIndex, end, visited, path, mileages, pathIndex);
            }
            tmpNode = tmpNode->next;
        }
    }

    // ���ݣ���ǵ�ǰ�ڵ�Ϊδ����
    pathIndex--;
    visited[start] = 0;
}

// ���Ҵ� start�� end������·��
int findAllPaths(Graph* graph)
{
    int start, end;
    if (!isPath(graph, &start, &end))
    {
        return 0;
    }
    int visited[MAXSIZE] = { 0 }; // �������,������¼վ���Ƿ񱻷���
    char path[MAXSIZE][MAX_NAME_LENGTH]; // ·������
    int mileages[MAXSIZE];			//�������
    findAllPathsUtil(graph, start, end, visited, path, mileages, 0); // ���õݹ麯��

    return 1;
}


//�жϲ�ѯ��·ʱվ����Ϣ�Ƿ���ȷ
int isPath(Graph* graph, int* start, int* end)
{
    char startName[MAX_NAME_LENGTH];
    char endName[MAX_NAME_LENGTH];
    printf("��������ʼվ�㣺");
    scanf("%s", startName);
    printf("������Ŀ��վ�㣺");
    scanf("%s", endName);
    *start = findStation(graph, startName);
    *end = findStation(graph, endName);

    // �����ʼ����ֹվ���Ƿ���Ч
    if (*start == -1 || *end == -1) {
        printf("��ʼվ�����ֹվ����Ч\n");
        return 0;
    }
    return 1;
}




// �������·��
void dijkstra(Graph* graph, int start, int end) 
{
    int dist[MAXSIZE];			//start�������ڵ�ľ���
    int prev[MAXSIZE];			//��¼·��
    int visited[MAXSIZE];
    int numVertices = graph->num;
    Node* adjNode;
    
    // ��ʼ�����о���Ϊ�����
    for (int i = 0; i < numVertices; i++) 
	{
        dist[i] = INT_MAX;			//INT_MAX:�����
        prev[i] = -1;
        visited[i] = 0;
    }

    dist[start] = 0;
    
    for (int i = 0; i < numVertices; i++) 
	{
        // �ҵ���ǰδ���ʵĽڵ��о�����С�Ľڵ�
        int u = -1;
        for (int j = 0; j < numVertices; j++) 
		{
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) 
			{
                u = j;
            }
        }
        
        if (dist[u] == INT_MAX) break;  // ʣ�µĽڵ㶼�ǲ��ɴ��

        visited[u] = 1;
        adjNode = graph->adjLists[u]->next;

        // �����ڽӽڵ�ľ���
        while (adjNode) 
		{
            int v = findStation(graph, adjNode->data->name);	//��ǰ��δ���ʽڵ��о����������Ľڵ�
            if (v != -1 && dist[u] + adjNode->data->mileage < dist[v]) 
			{
                dist[v] = dist[u] + adjNode->data->mileage;
                prev[v] = u;
            }
            adjNode = adjNode->next;
        }
    }

    // ��ӡ���·��
    printf("���·����վ�� %s ��վ�� %s ����̾����� %d\n", graph->adjLists[start]->data->name, graph->adjLists[end]->data->name, dist[end]);
    printf("·��: ");
    
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

//���Ҵ� start�� end�������С��·��
int findMinMileagePaths(Graph* graph) {
    int start, end;
    if (!isPath(graph, &start, &end)) {
        return 0;
    }

    dijkstra(graph, start, end);
    return 1;
}


//�˻�����
int keyDown(Graph* graph, int* flag)
{
    int key;
    showMenu();
    fflush(stdin);		//��ջ�����
    scanf("%d", &key);

    switch (key)
    {
    case 0:
        *flag = 0;
        break;

    case 1:
        if (addPath(graph) == 1)
        {
            printf("·����ӳɹ�\n");
        }
        break;

    case 2:
        if (addStation(graph) == 1)
        {
            printf("վ����ӳɹ�\n");
        }
        break;

    case 3:
        printf("\n");
        printf("\t\t\t\t\t\t�ڽӱ�������ʾ���£�\n");
        showList(graph);

        break;

    case 4:
        if (deletePath(graph))
        {
            printf("·��ɾ���ɹ�\n");
        }
        break;

    case 5:
        if (deleteStation(graph))
        {
            printf("վ��ɾ���ɹ�\n");
        }
        break;

    case 6:
		
		if(findMinMileagePaths(graph))
		{
			printf("���·����ѯ���....\n");
		}

        break;

    case 7:
        if (findAllPaths(graph))
        {
            printf("\n");
            printf("·���������....\n");
        }
        break;

    case 8:
        if (changeStation(graph))
        {
            printf("·���޸ĳɹ�\n");
        }
        break;


    default:
        printf("ָ�������������������\n");

        break;
    }
}

