### 城市地铁线路管理系统

#### 一、系统简介

该系统是一个基于C语言实现的城市地铁线路管理系统，它提供了用户登录、地铁线路管理、站点操作、线路查询和路径规划等功能。系统由以下关键组件构成：

​    **main.c**：程序的入口点，负责调用登录和地铁线路管理的初始化函数。

​    **login.h/login.c**：包含用户登录和注册的逻辑，处理用户信息的存储和检索。

​    **subwayLineManage.h/subwayLineManage.c**：包含地铁线路管理的逻辑，实现线路的增删改查和路径查询。

​	**main.h**：包含系统使用的宏定义和头文件。

#### 二、系统中主要的数据结构：

​	**User**：存储用户账号和密码信息。

​	**Station**：表示地铁站点，包含站点名称和里程。

​	**Node**：图的邻接表节点，包含站点信息和指向下一个节点的指针。

​	**Graph**：表示地铁线路的图结构，包含邻接表和相关操作。

#### 三、系统主要功能展示

##### 1、登录界面

![loginMenu](https://github.com/strtrych/my_Project/blob/main/subwayManageSystem/pic/loginMenu.png)

##### 2、线路管理界面

![subwayMenu](https://github.com/strtrych/my_Project/blob/main/subwayManageSystem/pic/subwayMenu.png)

##### 3、所有路径查询

![allPath](https://github.com/strtrych/my_Project/blob/main/subwayManageSystem/pic/allPath.png)

##### 4、最短路径查询

![shortestPath](https://github.com/strtrych/my_Project/blob/main/subwayManageSystem/pic/shortestPath.png)

##### 5、显示邻接链表数据

![showList](https://github.com/strtrych/my_Project/blob/main/subwayManageSystem/pic/showList.png)

##### 6、地铁线路展示

![showMap](https://github.com/strtrych/my_Project/blob/main/subwayManageSystem/pic/showMap.png)

#### 四、注意事项

##### 1、编译方法：

​	`gcc`编译：`gcc main.c login.c subwayLineManage.c`

##### 2、注意

记得修改一下`login.h`与`subwayManage.h`中的文件保存路径
