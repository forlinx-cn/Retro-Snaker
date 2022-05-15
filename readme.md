# 贪吃蛇





## 起始页面 startPage

> 功能
>
> 1. 游戏介绍
>
> 2. 引导玩家身份选择
>
>    默认玩家为default，打印玩家列表，上下键移动光标选中玩家身份，按下回车选择该身份
>    如果在尾行[^ 空白行]输入则提供以下命令：
>
>    | 命令            | 功能描述                                                     |
>    | --------------- | ------------------------------------------------------------ |
>    | add username    | 创建一个未被创建过的<u>username</u>身份<br />如果被创建过，则提示用户是否覆盖原身份记录<br />确认后删除原身份记录并创建<u>username</u>空白身份 |
>    | delete username | 删除<u>username</u>身份<br />确认后删除<br />如果不存在<u>username</u>身份，则提示用户错误 |
>    | username        | 以username身份登录<br />如果不存在该身份提示用户错误         |
>
>    完成身份选择后进入游戏主界面，读取身份记录并加载
>
> 3. 帮助跳转
>
>    清除页面信息 打印帮助信息



## 游戏页面

> 1. 初始化
>
>    读取记录，如果为空：
>
>    - 打印空地图
>    - 初始化蛇
>    - 初始化记录信息
>    - 打印按键提示
>
>    不为空：
>
>    - 加载记录信息
>
> 2. 游戏开始
>
>    | 功能     | 方法名称                                   | 备注                                                         |
>    | -------- | ------------------------------------------ | ------------------------------------------------------------ |
>    | 蛇移动   | void snake_move();                         | 使蛇按照设定方向前进一步                                     |
>    | 蛇转向   | void direction_change(char new_direction); | 改变蛇头前进方向                                             |
>    | 蛇进食   | void snake_eat(int food);                  | 蛇进食，播放进食音频，增加得分                               |
>    | 蛇生长   | void snake_grow(int food);                 | 按照蛇吃进的食物的量，增加蛇的长度、速度                     |
>    | 蛇死亡   | void snake_death();                        | 蛇死亡，游戏结束，保存记录，提示是否重新开始或者退出游戏     |
>    | 游戏暂停 | void game_pause();                         | 按下空格键触发暂停游戏并保存记录，并提示是否退出游戏或重新开始 |
>    
>   ```C
>    typedef struct {
>    	int x, y;
>    	int weight;
>    } Food;
>    typedef struct SnakeNode {
>    	int x, y;
>    } SnakeNode;
>    typedef struct {
>    	char name[100];
>    	SnakeNode snake[100];
>    	int length;
>    	char direction;
>    	int score;
>    	int hGameTime, tGameTime;
>    	int map[map_size][map_size];
>    } Player;
>   ```
>    
>    ``` Record.txt
>    Record.txt文件内容格式
>    Total_Player_Num(一个整数)
>    username1 snakelength 若干个snakenode坐标:(x,y)以空格分割，\n结束 direction score hScore hGameTime foodnum 若干个个food坐标:(x,y)以空格分割，\n结束
>    username2 snakelength 若干个snakenode坐标:(x,y) direction score hScore hGameTime foodnum 若干个个food坐标:(x,y)
>    username3 snakelength 若干个snakenode坐标:(x,y) direction score hScore hGameTime foodnum 若干个个food坐标:(x,y)
>    username4 snakelength 若干个snakenode坐标:(x,y) direction score hScore hGameTime foodnum 若干个个food坐标:(x,y)
>    ...
>    ```
> 
> 



## 帮助页面

> - 主界面按键功能介绍
> - 起始页面命令介绍
> - 版本信息
> - 创作者信息