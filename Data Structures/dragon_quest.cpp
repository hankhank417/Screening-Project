#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <string.h>
#include<windows.h>
#include "MMSystem.h"

#define SCREEN_HEIGHT 500 //設定遊戲視窗高度 
#define SCREEN_WIDTH 500 //設定遊戲視窗寬度
#define GRID_SIDE 40 //設定遊戲方陣每邊格子數量 
#define LEFT_MARGINE 30 //設定左邊界 
#define TOP_MARGINE 40 //設定上邊界 
#define FOOD_AMOUT 2 //設定每次產生食物數量
#define MAX_QUEUE_SIZE 1600 //設定柱列大小 
#define initializeScoreSum 1000 //設定初始分數
#define INIT_SPEED  1 //設定初始移動速度
#define CROWD_SPEED  200 //設定緩速區移動速度
#define SLOW_SPEED  600 //設定緩速技能移動速度 
#define FLASH_STEP 3 //設定閃現距離長度 
#define MISSILE_RANGE 2 //設定飛彈爆炸範圍 ( 範圍 = x*2+1 ) 
#define MODE 1 //設定PlayerAI的模式 ( 0原本、1 ROOM )

//宣告前進方向列舉函數 
enum Direction {
	RIGHT, 
	LEFT, 
	UP, 
	DOWN 
};

//宣告遊戲場出現物體列舉函數 
enum Object {
	EMPTY, //空白 
	WALL, //牆或障礙物 
	FOOD, //食物 
	HOLE,
	crowd
};

//宣告惡龍身體節點結構 
struct Node {
	int row; //節點位在第幾行 
	int col; //節點位在第幾列 
	Direction direct; //該節點的前進方向 
	struct Node *next;	//指向下一個節點 
}; 

//定義指向節點結構的指標變數 
typedef struct Node *NodePointer;

//定義座標結構 
struct Location {
	int row;
	int col;
};

typedef struct PathNode *PathPointer;

//定義路徑節點結構，用來建立移動路徑 
struct PathNode {
	int cost; //距離原點的步數 
	int steps; //距離目標的步數 
	Location loc;
	PathPointer parent;
	PathPointer next;
};

void openWindow(); //開啟游戲視窗 
void closeGame(NodePointer dragon); //處理遊戲結束邏輯 
int playGame(int field[][GRID_SIDE], NodePointer dragon, NodePointer player, NodePointer missile); //遊戲進行邏輯
bool IsGameOver(NodePointer dragon, NodePointer player, int field[][GRID_SIDE]); //惡龍是否死亡(死亡條件：撞牆和撞到自己身體) 
int showGameOverMsg(); //遊戲結束訊息
void showInfo(); //顯示遊戲相關資訊 
void drawGameField(int field[][GRID_SIDE]); //繪製遊戲區域 
void drawSquare(int row, int col, int color); //繪製方塊 _填滿 
void drawSquare2(int row, int col, int color); //繪製方塊_斜線 
void drawSquare3(int field[][GRID_SIDE]); //繪製方塊_緩速區填補 
void controlDragonDirection(int field[][GRID_SIDE], NodePointer dragon, NodePointer player); //讀取AI輸入，並設定到所有惡龍節點 
void controlPlayerDirection(int field[][GRID_SIDE], NodePointer player, NodePointer dragon); //讀取鍵盤方向輸入，或者AI輸入 
void moveNext(int field[][GRID_SIDE], NodePointer dragon, NodePointer player, NodePointer missile); //繪製每前進一步的身體改變
void createFood(int field[][GRID_SIDE], NodePointer dragon); //產生食物 
bool IsAtWall(int field[][GRID_SIDE], int row, int col); //判斷是否撞到牆 
bool IsAtHole(int field[][GRID_SIDE], int row, int col); //判斷是否進入時空洞
bool IsAtDragon(NodePointer dragon, int row, int col); //判斷是否撞到惡龍自己的身體
void addPointTodragonField(int dragonField[][2],int row,int col); //新增龍的領域範圍
bool IsbumpDragon(int dragonField[][2], int row, int col); //判斷勇者是否進入龍的領域
void dragonEatFood(int field[][GRID_SIDE], NodePointer dragon); //處理惡龍吃到食物邏輯 
void playerEatFood(int field[][GRID_SIDE], NodePointer dragon, NodePointer player); //處理玩家吃到食物邏輯
void playerEnterHole(int field[][GRID_SIDE], NodePointer player); //處理玩家進入時空洞邏輯
void setHole(int field[][GRID_SIDE], int X, int Y); //設定時空洞座標
Location teleportStepLoc(NodePointer player, int X, int Y, int original_X, int original_Y); //時空洞進入&傳送座標
void setCrowd(int field[][GRID_SIDE], int upBorder, int rightBorder, int bottomBorder, int leftBorder); //設定緩慢區範圍
int crowdControl(int field[][GRID_SIDE], NodePointer player); //進入緩慢區 
void addNode(NodePointer dragon); //增加惡龍身體節點
Location findNearestFood(int field[][GRID_SIDE], NodePointer dragon); //尋找最接近食物的座標 
Location findNearestFood2(int field[][GRID_SIDE], NodePointer me); //尋找最接近食物的座標_避開龍的領域
Direction safeDirection(int field[][GRID_SIDE], NodePointer dragon); //取得安全方向，只考慮會不會撞牆 
Location nextStepLoc(NodePointer node, Direction direct); //取得下一步座標 
PathPointer findPath(int field[][GRID_SIDE], Location startLoc, Location goalLoc); //尋找兩點之間可到達的路徑
PathPointer findPath2(int field[][GRID_SIDE], Location startLoc, Location goalLoc); //尋找兩點之間可到達的路徑_避開龍的領域
int findPath3(int field[][GRID_SIDE], Location startLoc, Location goalLoc); //尋找勇者與食物之間可到達的最短步數並回傳步數
void addPathQueue(PathNode pathNode); //將之後要拜訪的節點放入佇列裡 
PathPointer popPathQueue(); //傳回柱列中的元素，並將它從柱列中刪除 
bool isPathQueueEmpty(); //判斷柱列是否為空 
void resetPathQueue(); //重設柱列 
void sortPathQueue(); //對柱列中的元素進行排序 
bool IsInPathQueue(PathNode pathNode); //判斷該元素是否在柱列之中 
PathPointer buildPath(PathPointer goal); //回傳到目標位置的路徑串列 
int buildPath2(PathPointer goal); //回傳到目標位置的路徑串列所需步數
int calcSteps(Location start, Location goal); //計算兩點之間需要移動的步數 
bool visited(Location loc); //判斷是否該節點已經拜訪過 
Direction getDirectionByPath(NodePointer dragon, PathPointer path); //從路徑資料判斷下一步方向 

Direction dragonAI(int field[][GRID_SIDE], NodePointer dragon, NodePointer player); //惡龍AI 
Direction playerAI(int field[][GRID_SIDE], NodePointer player, NodePointer dragon); //勇者AI 
NodePointer Mode_1(int field[][GRID_SIDE], NodePointer player, NodePointer dragon, Direction direct); //勇者AI Mode1
bool around(int field[][GRID_SIDE], NodePointer dragon ,NodePointer player);

void skilTimeOut(); //技能_時間暫停 
int skilSlow(); //技能_緩速 
Location skilFlash(NodePointer player); //技能_閃現 
void skilMakeWall(int field[][GRID_SIDE], NodePointer player); //技能_造牆 
NodePointer skilMissile(int field[][GRID_SIDE], NodePointer player, NodePointer dragon, NodePointer missile); //技能_飛彈
void missileMove(int field[][GRID_SIDE], NodePointer player, NodePointer dragon, NodePointer missile); //飛彈發射中...

struct PathNode pathQueue[MAX_QUEUE_SIZE]; //宣告將要拜訪的節點柱列 
int front; //queue 第一個元素的前一個位置 
int rear; //queue 最後一個元素的位置

int speed; //遊戲移動速度
int scoreSum = initializeScoreSum; //紀錄分數 
int totalTime = 0; //紀錄遊戲時間 
int const scorePerFood = 1; //每一份食物可得分數 
int holeLocation[1600][2]; //放入時空洞座標
int holeCount = 0; //計算時空洞數量
int crowdLocation[4]; //緩速區範圍 ( 上, 右, 下, 左 )
int dragonField[25000][2]; //放入龍的領域座標
int dragonRoom = 0; //計算龍的領域數量
int fieldCount = 0;
int dragonLength = 0;
bool meetSelfWillDie = false; //決定惡龍撞到自己身體是否會死掉
bool IFPlayAI = false; //是否開啟AI模式 (*非使用者設定)
bool IFSlowSpeed = false; //是否開啟緩速技能 (*非使用者設定)
bool IFIsmissileShot = false; //是否飛彈射出 (*非使用者設定)
bool IFDragonMore = false; //龍是否到特定長度 (*非使用者設定)
bool IFPlugins = true; //是否開啟外掛
bool IFCrowdControl = false; //是否開啟緩速區
bool IFHole = false; //是否開始時空洞

// 主程式      
int main( ){  	
	openWindow();
	
	while(TRUE){
		Node headPlayer = {2, 6, RIGHT, NULL}; //設定勇者初始位置和方向
		Node headDragon = {37, 3, RIGHT, NULL}; //設定龍頭初始位置和方向 
		Node headMissile; //設定飛彈
		NodePointer dragon = &headDragon;
		NodePointer player = &headPlayer;
		NodePointer missile = &headMissile;
		speed = INIT_SPEED;
		holeCount = 0;

		//設定遊戲場和障礙物
		int field[GRID_SIDE][GRID_SIDE] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		   								   {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
										   {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
										   {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
										   {1,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
										   {1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,2,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,1,1,1,1,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1,1,1,1,1,0,0,1},
										   {1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1},
										   {1,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,1},
										   {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
										   {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
										   {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
										   {1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
										   {1,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1},
										   {1,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,2,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

		int field1[GRID_SIDE][GRID_SIDE] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
											{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1},
											{1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1},
											{1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
											{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
		int field2[GRID_SIDE][GRID_SIDE] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,5,0,0,0,0,5,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,0,1},
								             {1,0,0,0,0,6,0,0,6,0,6,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,5,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,6,0,6,0,0,6,0,0,6,0,6,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,5,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,5,0,0,0,0,0,0,1},
								             {1,0,0,6,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,5,0,5,0,0,0,0,0,0,0,0,0,5,0,5,0,0,1},
								             {1,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,5,0,0,0,0,0,0,1},
								             {1,0,0,6,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,5,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,5,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,6,0,6,0,0,6,0,0,6,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,6,0,0,6,0,6,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,5,0,0,5,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,5,0,0,0,0,5,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,7,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,8,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,7,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,8,0,0,0,0,0,1},
								             {1,0,0,0,0,0,7,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,8,0,0,0,0,1},
								             {1,0,0,0,0,7,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,8,0,0,0,1},
								             {1,0,0,0,7,7,7,0,0,0,0,0,7,7,7,0,0,0,0,0,0,0,0,0,0,8,8,0,0,0,0,0,0,0,0,8,8,0,0,1},
								             {1,0,0,0,0,7,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,8,8,0,0,0,0,8,0,1},
								             {1,0,0,0,7,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,8,8,0,0,8,0,0,0,1},
								             {1,0,0,7,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,8,0,0,0,1},
								             {1,0,7,7,7,7,7,7,0,0,0,7,7,7,7,7,7,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,8,0,0,0,1},
								             {1,0,0,0,0,0,0,7,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,8,0,0,0,1},
								             {1,0,0,0,0,0,0,7,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,8,0,0,0,1},
								             {1,0,0,0,0,0,0,7,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,8,0,0,0,1},
								             {1,0,0,0,0,0,0,7,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,8,8,8,8,8,8,8,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

		int field3[GRID_SIDE][GRID_SIDE] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    					         			 {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,9,9,9,9,9,9,0,0,0,0,0,0,0,0,9,9,9,0,9,9,9,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,9,0,0,0,0,0,0,9,0,0,0,0,0,0,9,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,9,0,0,0,0,0,0,0,0,9,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,9,0,0,0,0,0,0,0,0,0,0,9,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,9,0,0,0,0,0,0,9,9,9,9,9,9,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,9,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,9,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,9,0,0,0,0,0,0,0,9,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,9,0,0,0,0,0,9,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,9,9,9,9,9,0,0,0,0,0,0,0,0,0,9,9,9,0,9,9,9,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								             {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
		char key;
		if(fieldCount%4==0){
			//設定緩慢區範圍
			if(IFCrowdControl)
				setCrowd(field3, 14, 23, 22, 15);

	        //設定時空洞
	        if(IFHole){
	        	setHole(field3,4,4);
				setHole(field3,35,35);
				setHole(field3,4,35);
				setHole(field3,35,4);
			}
			 PlaySound(TEXT("D:\\Word\\University\\Sophomore-1\\Data structure\\finalProject\\KnightVSDragon\\music.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
			key = playGame(field3, dragon, player, missile); //進行遊戲
		}else if(fieldCount%4==1){
			//設定緩慢區範圍
			if(IFCrowdControl)
				setCrowd(field, 14, 23, 22, 15);

	        //設定時空洞
	        if(IFHole){
				setHole(field,4,35);
				setHole(field,35,4);
			}
			 PlaySound(TEXT("D:\\Word\\University\\Sophomore-1\\Data structure\\finalProject\\KnightVSDragon\\music.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
			key = playGame(field, dragon, player, missile); //進行遊戲
		}else if(fieldCount%4==2){
			if(IFCrowdControl)
				setCrowd(field1, 14, 23, 22, 15);

	        //設定時空洞
	        if(IFHole){
	        	setHole(field1,4,6);
				setHole(field1,30,34);
				setHole(field1,6,33);
				setHole(field1,33,10);
			}
			PlaySound(TEXT("D:\\Word\\University\\Sophomore-1\\Data structure\\finalProject\\KnightVSDragon\\music.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
			key = playGame(field1, dragon, player, missile); //進行遊戲
		}else if(fieldCount%4==3){
			if(IFCrowdControl)
				setCrowd(field2, 14, 23, 22, 15);

	        //設定時空洞
	        if(IFHole){
	        	setHole(field2,9,9);
				setHole(field2,34,30);
				setHole(field2,8,29);
				setHole(field2,30,9);
			}
			PlaySound(TEXT("D:\\Word\\University\\Sophomore-1\\Data structure\\finalProject\\KnightVSDragon\\music.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
			key = playGame(field2, dragon, player, missile); //進行遊戲
		}
			
			
		
		
		if (key == 'q' || key == 'Q')
			closeGame(dragon); //如果玩家輸入'q'離開遊戲	
		else if (key == 's' || key == 'S'){
			IFDragonMore = false;
			continue; //如果玩家輸入's' 繼續遊戲 	
		}else if(key == 'z' || key == 'Z'){ //切換地圖
			fieldCount++;
			IFDragonMore = false;
		}else if(key == 'x' || key == 'X'){
			IFCrowdControl = !IFCrowdControl;
		}else if(key == 'c' || key == 'C'){
			IFHole = !IFHole;
		}
		scoreSum = initializeScoreSum;
		totalTime = 0;
		dragonLength = 0;
	}
}

//開啟游戲視窗
void openWindow(){
	initwindow(SCREEN_WIDTH*1.44 + LEFT_MARGINE * 3, SCREEN_HEIGHT + TOP_MARGINE * 3, "Hungry dragon Game");
}

//處理遊戲結束邏輯 
void closeGame(NodePointer dragon){
	free(dragon);
	exit(0);
}

//遊戲進行邏輯
int playGame(int field[][GRID_SIDE], NodePointer dragon, NodePointer player, NodePointer missile) {
	
	drawGameField(field); //繪製遊戲區域 
	createFood(field, dragon); //產生第一份食物 
	
	while(true){
				
		int key = 0;
		if(IFCrowdControl)
			drawSquare3(field); //重新繪製緩速區
		controlDragonDirection(field, dragon, player); 
		controlPlayerDirection(field, player, dragon);//讀取玩家輸入方向鍵，並將新方向設定到各惡龍節點 
		moveNext(field, dragon, player, missile); //依據節點的方向，繪製新的惡龍位置
		dragonEatFood(field, dragon); //判斷惡龍是否有吃到食物，如果有新增節點到尾巴
		playerEatFood(field, dragon, player); //判斷玩家是否有吃到食物，如果有增加分數 
		if(IFHole)
			playerEnterHole(field, player); //判斷是否進入時空洞
		if(IFCrowdControl)
			speed = crowdControl(field, player); //判斷是否進入緩慢區
		
		if(IFSlowSpeed)	//判斷是否開啟緩速技能 
			speed = skilSlow();
			
		if(IFIsmissileShot)
			missileMove(field, player, dragon, missile);
		if(IFIsmissileShot)
			missileMove(field, player, dragon, missile);
		
		showInfo(); //顯示時間和分數資訊 

		if(dragonLength >= 320 && !IFDragonMore){
			printf(" You feel an evil presence watching you... ");
			PlaySound(TEXT("D:\\Word\\University\\Sophomore-1\\Data structure\\finalProject\\KnightVSDragon\\music2.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
			IFDragonMore = !IFDragonMore;
		}

		if(IsGameOver(dragon, player, field)){ //判斷是否符合遊戲結束條件，
			PlaySound(TEXT("D:\\Word\\University\\Sophomore-1\\Data structure\\finalProject\\KnightVSDragon\\GameOver.wav"),NULL,SND_FILENAME|SND_ASYNC);
			return showGameOverMsg(); //顯示遊戲結束訊息，並等待玩家輸入選項
		}

		
		//除了吃到食物會產生新食物，系統也隨機產生新食物 
		srand((unsigned)time(NULL));
		if (rand() % 20 == 0)
			createFood(field, dragon);
			
		if(key != 0)
			return key;
		
		delay(speed); //決定物件移動速度，speed越小移動越快 
		
		//讀取非方向鍵的其他鍵盤輸入 
	   	if(kbhit()) {
	   		char key;
			key = getch();	
			
			//只有輸入大小寫的a, q 和 s，系統才有反應並將輸入結果拋到外層等待處理 
			if (key == 'q' || key == 'Q' || key == 's' || key == 'S' || key == 'z' || key == 'Z' || key == 'x' || key == 'X' || key == 'c' || key == 'C')
				return key; 				
			else if (key == 'a' || key == 'A') //決定是否改變模式 ，主要有玩家模式和電腦操控的AI模式 
				IFPlayAI = !IFPlayAI;
			else if (key == 'v' || key == 'V')
				IFPlugins = !IFPlugins;
			else if (key == 't' || key == 'T') //使用暫停技能 
				skilTimeOut();
			else if (key == 'e' || key == 'E'){ //使用緩速技能
				if( !IFSlowSpeed && scoreSum>=3)
					IFSlowSpeed = !IFSlowSpeed;
			}
			else if (key == 'r' || key == 'R') //使用閃現技能 
				skilFlash(player);
			else if (key == 'w' || key == 'W') //使用造牆技能 
				skilMakeWall(field, player);
			else if (key == 'g' || key == 'G') //使用飛彈技能 
				if(!IFIsmissileShot)
					missile = skilMissile(field, player, dragon, missile);
		}
	}
}

//繪製遊戲區域，依據遊戲場矩陣設定繪製物件 
void drawGameField(int field[][GRID_SIDE]){
   	int row = 0, col = 0;
   	cleardevice(); //清理螢幕畫面 
	for(row = 0; row < GRID_SIDE; row ++){
   		for(col = 0; col <  GRID_SIDE; col++){
				switch(field[row][col])	{
					case 0: //背景
						drawSquare(row, col, 0);
						break;
					case 1: //牆在矩陣中的值是1 
						drawSquare(row, col, 14);
						break;
					case 2: //食物在矩陣中的值是2
						drawSquare(row, col, 3);
						break;
					case 3: //時空洞在矩陣中的值是3
						if(IFHole)
							drawSquare(row, col, 1);
						break;
					case 4: //緩速區在矩陣中的值是4 
						if(IFCrowdControl)
							drawSquare2(row, col, 9);
						break;
					case 5:
						drawSquare(row, col, 14);
						break;
					case 6:
						drawSquare(row, col, 15);
						break;
					case 7:
						drawSquare(row, col, 2);
						break;
					case 8:
						drawSquare(row, col, 6);
						break;
					case 9:
						drawSquare(row, col, 4);
						break;
				}	
		   }
	}
}

//繪製方塊_填滿 
void drawSquare(int row, int col, int color){
	
	int squareHeight = SCREEN_HEIGHT / GRID_SIDE;
   	int SquareWidth = SCREEN_WIDTH / GRID_SIDE;
	int left = 0, right = 0, bottom = 0, top = 0;
	left = LEFT_MARGINE + col * SquareWidth + col;
   	top =  TOP_MARGINE + row * squareHeight + row;
	right = left + SquareWidth;
   	bottom = top + squareHeight;
   	 
	setfillstyle(SOLID_FILL,color); //設定繪製物件的為實心和顏色 
   	bar(left , top, right, bottom);	//設定繪製方塊的位置 
}
//繪製方塊_斜線
void drawSquare2(int row, int col, int color){
	
	int squareHeight = SCREEN_HEIGHT / GRID_SIDE;
   	int SquareWidth = SCREEN_WIDTH / GRID_SIDE;
	int left = 0, right = 0, bottom = 0, top = 0;
	left = LEFT_MARGINE + col * SquareWidth + col;
   	top =  TOP_MARGINE + row * squareHeight + row;
	right = left + SquareWidth;
   	bottom = top + squareHeight;
   	 
	setfillstyle(SLASH_FILL ,color); //設定繪製物件的為斜線和顏色 
   	bar(left , top, right, bottom);	//設定繪製方塊的位置 
}

////繪製方塊_緩速區(補空) 
void drawSquare3(int field[][GRID_SIDE]){
	int i,j;
	for(i=crowdLocation[0];i<=crowdLocation[2];i++){
		for(j=crowdLocation[3];j<=crowdLocation[1];j++){
			if(field[i][j] == 4){
				drawSquare2(i, j, 6);
			}
		}
	}
}

//繪製每前進一步的身體改變
void moveNext(int field[][GRID_SIDE], NodePointer dragon, NodePointer player, NodePointer missile) {
	NodePointer initializeDragon = dragon;
	int currRow, currCol;
	int dragonHeadRow = dragon->row;
	int dragonHeadCol = dragon->col;
	int first = 0;
	dragonRoom = 0;
	int i;
	if(IFHole){
		for( i=0 ;i<holeCount ; i++){
			drawSquare(holeLocation[i][0], holeLocation[i][1], WHITE);
		}
	}
	while (dragon != NULL){
		currRow = dragon->row;
		currCol = dragon->col;
		if(MODE == 1)
			addPointTodragonField(dragonField, currRow, currCol);
		//依據節點的方向屬性，設定移動下一步的位置	
		switch(dragon->direct){
			case RIGHT:
				dragon->col++;
				break;			
			case LEFT:
				dragon->col--;
				break;
			case UP:
				dragon->row--;
				break;			
			case DOWN:
				dragon->row++;
				break;
		}
		
		if(first == 0){
			first++;
			printf("Dragon( %d , %d ) , ", dragon->row, dragon->col);
		}
		if(dragonHeadRow == currRow && dragonHeadCol==currCol){
			drawSquare(dragon->row, dragon->col, 12);
		}else{
			drawSquare(dragon->row, dragon->col, RED);
		}
		if (!IsAtDragon(dragon, currRow, currCol)){
			if( dragon->row>=crowdLocation[0]+1 && dragon->row<=crowdLocation[2]-1 && dragon->col>=crowdLocation[3]+1 && dragon->col<=crowdLocation[1]-1 ){
				if(IFCrowdControl){
					drawSquare2(currRow, currCol, 6);
				}else{
					drawSquare(currRow, currCol, BLACK);
				}
			}else{
				drawSquare(currRow, currCol, BLACK);
			}
		}
		if(dragon -> next == NULL){
			addPointTodragonField(dragonField, currRow+1, currCol);
			addPointTodragonField(dragonField, currRow-1, currCol);
			addPointTodragonField(dragonField, currRow, currCol+1);
			addPointTodragonField(dragonField, currRow, currCol-1);
		}
		dragon = dragon -> next;	
	}
	
	if (player != NULL){
		currRow = player->row;
		currCol = player->col;
		
		switch(player->direct){
			case RIGHT:
				player->col++;
				break;			
			case LEFT:
				player->col--;
				break;
			case UP:
				player->row--;
				break;			
			case DOWN:
				player->row++;
				break;
		}
		if(around(field, dragon , player)){
			missile = skilMissile(field, player, dragon, missile);
		}
		if (IFPlayAI){
			if(MODE == 1){
				player = Mode_1(field,player,initializeDragon, player->direct);
			}
		}
		
		printf("Player( %d , %d )\n", player->row, player->col);
		drawSquare(player->row, player->col, BLUE);
		if( player->row>=crowdLocation[0]+1 && player->row<=crowdLocation[2]-1 && player->col>=crowdLocation[3]+1 && player->col<=crowdLocation[1]-1 ){
			if(IFCrowdControl){
				drawSquare2(currRow, currCol, 6);
			}else{
				drawSquare(currRow, currCol, BLACK);
			}
		}else{
			drawSquare(currRow, currCol, BLACK);
		}
	}
}

//PlayerAI MODE1
NodePointer Mode_1(int field[][GRID_SIDE], NodePointer player, NodePointer dragon, Direction direct){
	int currRow =  player -> row;
	int currCol = player -> col;
	if( IsAtWall(field, currRow, currCol) || IsbumpDragon(dragonField, currRow, currCol)){
		switch(direct){
			case RIGHT:
				if( !IsAtWall(field, currRow+1, currCol-1) && (!IsbumpDragon(dragonField, currRow+1, currCol-1) || !IsAtDragon(dragon, currRow+1, currCol-1)) ){
					currRow += 1;
					currCol -= 1;
				}else if( !IsAtWall(field, currRow-1, currCol-1) && (!IsbumpDragon(dragonField, currRow-1, currCol-1) || !IsAtDragon(dragon, currRow-1, currCol-1)) ){
					currRow -= 1;
					currCol -= 1;
				}else if( !IsAtWall(field, currRow, currCol-2) && (!IsbumpDragon(dragonField, currRow, currCol-2) || !IsAtDragon(dragon, currRow, currCol-2)) ){
					currCol -= 2;
				}
				break;
			case LEFT:
				if( !IsAtWall(field, currRow+1, currCol+1) && (!IsbumpDragon(dragonField, currRow+1, currCol+1) || !IsAtDragon(dragon, currRow+1, currCol+1)) ){
					currRow += 1;
					currCol += 1;
				}else if( !IsAtWall(field, currRow-1, currCol+1) && (!IsbumpDragon(dragonField, currRow-1, currCol+1) || !IsAtDragon(dragon, currRow-1, currCol+1)) ){
					currRow -= 1;
					currCol += 1;
				}else if( !IsAtWall(field, currRow, currCol+2) && (!IsbumpDragon(dragonField, currRow, currCol+2) || !IsAtDragon(dragon, currRow, currCol+2)) ){
					currCol += 2;
				}
				break;
			case UP:
				if( !IsAtWall(field, currRow+1, currCol+1) && (!IsbumpDragon(dragonField, currRow+1, currCol+1) || !IsAtDragon(dragon, currRow+1, currCol+1)) ){
					currRow += 1;
					currCol += 1;
				}else if( !IsAtWall(field, currRow+1, currCol-1) && (!IsbumpDragon(dragonField, currRow+1, currCol-1) || !IsAtDragon(dragon, currRow+1, currCol-1)) ){
					currRow += 1;
					currCol -= 1;
				}else if( !IsAtWall(field, currRow+2, currCol) && (!IsbumpDragon(dragonField, currRow+2, currCol) || !IsAtDragon(dragon, currRow+2, currCol)) ){
					currRow += 2;
				}
				break;
			case DOWN:
				if( !IsAtWall(field, currRow-1, currCol+1) && (!IsbumpDragon(dragonField, currRow-1, currCol+1) || !IsAtDragon(dragon, currRow-1, currCol+1)) ){
					currRow -= 1;
					currCol += 1;
				}else if( !IsAtWall(field, currRow-1, currCol-1) && (!IsbumpDragon(dragonField, currRow-1, currCol-1) || !IsAtDragon(dragon, currRow-1, currCol-1)) ){
					currRow -= 1;
					currCol -= 1;
				}else if( !IsAtWall(field, currRow-2, currCol) && (!IsbumpDragon(dragonField, currRow-2, currCol) || !IsAtDragon(dragon, currRow-2, currCol)) ){
					currRow -= 2;
				}
				break;
		}
	}
	player->row = currRow;
	player->col = currCol;
	return player;
}


//新增龍的領域範圍
void addPointTodragonField(int dragonField[][2],int row,int col){
	int i,j;
	int dirSize = 4;
	int iDir[] = {1, 0, -1, 0};
	int jDir[] = {0, 1, 0, -1};
	if(dragonRoom<=5){
		for(i=0, j=0; i<dirSize; i++, j++){
			if( (row + iDir[i]) != 0 && (row + iDir[i]) != 39 && (col + jDir[j]) != 0 && (col + jDir[j]) != 39 ){
				dragonField[dragonRoom][0] = row + iDir[i];
				dragonField[dragonRoom][1] = col + jDir[j];
				dragonRoom++;
			}
		}
	}else{
		dragonField[dragonRoom][0] = row;
		dragonField[dragonRoom][1] = col;
		dragonRoom++;
	}
}

//判斷勇者是否進入龍的領域
bool IsbumpDragon(int dragonField[][2], int row, int col){
	int l=0;
	while(l<=dragonRoom){
		if(dragonField[l][0]==row&&dragonField[l][1]==col){
			return true;
		}
		l++;
	}
	return false;
}

//惡龍是否死亡(死亡條件：撞牆和撞到自己身體) 
bool IsGameOver(NodePointer dragon, NodePointer player, int field[][GRID_SIDE]){
	NodePointer head = dragon;
	
	//判斷是否撞到牆 
	if (IsAtWall(field, head->row, head->col))
		return true;
	if (IsAtWall(field, player->row, player->col))
		return true;
	
	//判斷是否撞到惡龍自己 
	if(meetSelfWillDie)
		return IsAtDragon(dragon->next, head->row, head->col);
	
	//檢查是否AI撞到龍 
	if(player != NULL) {
		if(IsAtDragon(dragon, player->row, player->col)){
			return true;
		}
	}
	
	if(dragon == NULL){
		return true;
	}
	
	return false;
}

//判斷是否撞到牆
bool IsAtWall(int field[][GRID_SIDE], int row, int col){
		if (field[row][col] == 1 || field[row][col] == 5 ||field[row][col] == 6 || field[row][col] == 7 || field[row][col] == 8 || field[row][col] == 9)
			return true;
		return false;
}
//判斷是否進入時空洞 
bool IsAtHole(int field[][GRID_SIDE], int row, int col){
		if (field[row][col] == HOLE)
			return true;
		return false;
}

//判斷是否撞到惡龍自己的身體
bool IsAtDragon(NodePointer dragon, int row, int col){

	while(dragon != NULL){
		if (row == dragon->row && col == dragon->col)
			return true;
		dragon = dragon -> next;
	}
	return false;
}

bool around(int field[][GRID_SIDE], NodePointer dragon ,NodePointer player){
	if(IFPlayAI && !IFIsmissileShot && scoreSum>=200 && IFPlugins){
		if( IsbumpDragon(dragonField, player->row +1, player->col) || IsAtWall(field, player->row+1, player->col) || IsbumpDragon(dragonField, player->row +2, player->col) || IsAtWall(field, player->row+2, player->col))
			if( IsbumpDragon(dragonField, player->row-1, player->col) || IsAtWall(field, player->row-1, player->col) || IsbumpDragon(dragonField, player->row-2, player->col) || IsAtWall(field, player->row-2, player->col))
				if( IsbumpDragon(dragonField, player->row, player->col+1) || IsAtWall(field, player->row, player->col+1) || IsbumpDragon(dragonField, player->row, player->col+2) || IsAtWall(field, player->row, player->col+2))
					if( IsbumpDragon(dragonField, player->row, player->col-1) || IsAtWall(field, player->row, player->col-1) || IsbumpDragon(dragonField, player->row, player->col-2) || IsAtWall(field, player->row, player->col-2))
						return true;
	}
	return false;
}

//遊戲結束訊息
int showGameOverMsg(){
   	//cleardevice(); //清理所有螢幕資料，如果希望只顯示訊息時，取消註解 

	int i = 0;
	char msg1[15] = "Game Over!!";
	char msg2[60] = "    press [q] to quit or [s] to restart!!          ";
	char msg3[60] = "   助教超帥超正，資結大家滿分 !!!                  ";
   	for(; ; i++){
	   	setcolor(i%14);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 7);
	   	outtextxy(0, SCREEN_HEIGHT / 2, msg1);
	   	
	   	setcolor(i%14);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
	   	outtextxy(20, SCREEN_HEIGHT / 2 + 70, msg3);
	   	
	   	setcolor(WHITE);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
	   	outtextxy(20, SCREEN_HEIGHT / 2 + 90, msg2);
	   	
	   	delay(200);
	   	
	   	setcolor(BLACK);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 7);
	   	outtextxy(0, SCREEN_HEIGHT / 2, msg1);

		setcolor(BLACK);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
	   	outtextxy(10, SCREEN_HEIGHT / 2 + 70, msg3);
		   	
	   	if(kbhit()) {
	   		char key;
			key = getch();	
			if (key == 'q' || key == 'Q' || key == 's' || key == 'S') {
				return key; 				
			}
		}
	}	
}

//顯示遊戲相關資訊
void showInfo(){
	totalTime += speed;
	char skilTimeOut[20] = "時間暫停(T) 5 cost";
	char skilSlow[20] = "緩速(E) 3 cost";
	char skilFlash[20] = "閃現(R) 3 cost";
	char skilMakeWall[20] = "造牆(W) 2 cost";
	char skilMissile[20] = "飛彈(G) 50 cost";
	char timeMsg[45] = " Time:";
	char scoreMsg[45] = "Score:";
	char modeMsg[20] = "";
	char optMsg1[50] = "press [q] to quit, [s] to restart or";
	char optMsg2[50] = "press [a] to change mode, [z] to change map.";
	char member0[40] = "B054020001 陳佳宏";
	char member1[40] = "B054020002 胡捷翔";
	char member2[40] = "B054020003 蔡宗諺";
	char member3[40] = "B054020007 楊  宸";
	char member4[40] = "B054020029 洪子軒";
	char setting0[20] = "Crow Control : On ";
	char setting1[20] = "Crow Control : Off";
	char setting2[20] = "Wormhole : On ";
	char setting3[20] = "Wormhole : Off";
	char setting4[20] = "Plugins : On ";
	char setting5[20] = "Plugins : Off";

	char time[10];
	char score[10];
	
	sprintf(time, "%5d", totalTime/1000);
	strcat(timeMsg, time);
	strcat(timeMsg, " sec.");
	
	setcolor(WHITE); //設定文字顏色 
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1); //設定字型，水平或垂直和字型大小 
   	outtextxy(0, 0, timeMsg); //依據坐標輸出文字到螢幕	
	
	sprintf(score, "%5d", scoreSum);
	strcat(scoreMsg, score);
	strcat(scoreMsg, " point.");

	setcolor(WHITE);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	outtextxy(0, 19, scoreMsg);
   	
   	outtextxy(580, 60, skilMakeWall);
   	outtextxy(580, 85, skilSlow);
   	outtextxy(580, 110, skilFlash);
   	outtextxy(580, 135, skilTimeOut);
   	outtextxy(580, 160, skilMissile);
   	
   	if(IFCrowdControl){
   		outtextxy(580, 260, setting0);
	}else{
		outtextxy(580, 260, setting1);
	}
	if(IFHole){
   		outtextxy(580, 285, setting2);
	}else{
		outtextxy(580, 285, setting3);
	}
	if(IFPlugins){
   		outtextxy(580, 310, setting4);
	}else{
		outtextxy(580, 310, setting5);
	}
   	
   	if(IFPlayAI){
   		strcat(modeMsg, "AI Mode    ");
	}else{
   		strcat(modeMsg, "Player Mode");
	}
			
   	setcolor(LIGHTMAGENTA);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	outtextxy(SCREEN_HEIGHT - LEFT_MARGINE * 2, 0, modeMsg);
   	
   	setcolor(LIGHTGREEN);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	outtextxy(0, TOP_MARGINE + (GRID_SIDE + 2) * SCREEN_HEIGHT / GRID_SIDE, optMsg1);
	outtextxy(0, TOP_MARGINE + (GRID_SIDE + 2) * SCREEN_HEIGHT / GRID_SIDE + 20, optMsg2);
	
	outtextxy(580, TOP_MARGINE + (GRID_SIDE + 2) * SCREEN_HEIGHT / GRID_SIDE-120, member0);
	outtextxy(580, TOP_MARGINE + (GRID_SIDE + 2) * SCREEN_HEIGHT / GRID_SIDE-90, member1);
	outtextxy(580, TOP_MARGINE + (GRID_SIDE + 2) * SCREEN_HEIGHT / GRID_SIDE-60, member2);
	outtextxy(580, TOP_MARGINE + (GRID_SIDE + 2) * SCREEN_HEIGHT / GRID_SIDE-30, member3);
	outtextxy(580, TOP_MARGINE + (GRID_SIDE + 2) * SCREEN_HEIGHT / GRID_SIDE, member4);
}

//讀取鍵盤方向輸入，並設定到所有惡龍節點 
void controlPlayerDirection(int field[][GRID_SIDE], NodePointer player, NodePointer dragon) {
	
	Direction playerDirect = player -> direct;
	
	//get key code by pressing keybord
	int key;
	if(kbhit()) 
		key = getch();
		
	//decide dragon's moving direction	
	switch(key){
		case KEY_RIGHT:
			playerDirect = RIGHT;
			break;			
		case KEY_LEFT:
			playerDirect = LEFT;
			break;		
		case KEY_UP:
			playerDirect = UP;
			break;				
		case KEY_DOWN:
			playerDirect = DOWN;
			break;				
	}
		
	if (IFPlayAI)
		playerDirect = playerAI(field, player, dragon);
	
	
	player -> direct = playerDirect;
			
}


//讀取鍵盤方向輸入，並設定到所有惡龍節點 
void controlDragonDirection(int field[][GRID_SIDE], NodePointer dragon, NodePointer player) {
		
	Direction dragonDirect = dragonAI(field, dragon, player);
	//為了達到像龍一樣移動方式，當龍改變方向時，並不是整個身體一起改變，
	//而是延遲性地，各個節點逐一改變，當一個節點收到新的前進方向時，
	//會將自己目前的方向傳給下一個。 
	Direction temp;
	while(dragon != NULL){
		temp = dragon -> direct;
		dragon -> direct = dragonDirect;
		dragonDirect = temp;
		dragon = dragon -> next;
	}
}

//產生食物
void createFood(int field[][GRID_SIDE], NodePointer dragon){
	int row, col, i, foodAmount = FOOD_AMOUT;
	srand((unsigned)time(NULL)); //取目前系統時間作為亂數種子 

	for(i=0; i< foodAmount; i++){
		//如果亂數產生的位置是在牆和龍身體重疊，則重新產生，直到符合條件為止 
		do{
			row = rand() % GRID_SIDE;
			col = rand() % GRID_SIDE;	
		}while(IsAtWall(field, row, col) || IsAtDragon(dragon, row, col) || IsAtHole(field, row, col));
	
		field[row][col] = FOOD;
		drawSquare(row,col, 3);
	}
}

//處理惡龍吃到食物邏輯
void dragonEatFood(int field[][GRID_SIDE], NodePointer dragon){
	//如果龍頭與食物位置重疊，就是吃到食物 
	if(field[dragon->row][dragon->col] == FOOD && field[dragon->row][dragon->col] != HOLE){
		field[dragon->row][dragon->col] = EMPTY; //將該食物清空 
		printf("The dragon has eaten food at row: %d, col: %d\n", dragon->row, dragon->col);
		addNode(dragon); //增加節點
		dragonLength++;
		createFood(field, dragon); //產生新的食物 
	}
}

//處理玩家吃到食物邏輯
void playerEatFood(int field[][GRID_SIDE], NodePointer dragon, NodePointer player){
	//如果龍頭與食物位置重疊，就是吃到食物
	if(field[player->row][player->col] == FOOD && field[player->row][player->col] != HOLE){
		field[player->row][player->col] = EMPTY; //將該食物清空 
		printf("The player has eaten food at row: %d, col: %d\n", player->row, player->col);
		scoreSum = scoreSum + scorePerFood; //紀錄分數 
		createFood(field, player); //產生新的食物 
	}
}

//處理player進入時空洞
void playerEnterHole(int field[][GRID_SIDE], NodePointer player){
	srand( time(NULL) );
	int target = -1;
	if(field[player->row][player->col] == HOLE){
		target = floor(rand()%holeCount);
		while(holeLocation[target][0] == player->row && holeLocation[target][1] == player->col){
			target = floor(rand()%holeCount);
		}
		teleportStepLoc(player, holeLocation[target][0], holeLocation[target][1], player->row, player->col);
	}
}

//設定空洞座標
void setHole(int field[][GRID_SIDE], int X, int Y){
	if(field[X][Y]!=1){
		holeLocation[holeCount][0]=X;
		holeLocation[holeCount][1]=Y;
		field[X][Y] = 3;
		printf("setHole :( %d, %d, %d )\n",holeCount,X,Y);
		holeCount++;
	}
}

//設定緩慢區範圍
void setCrowd(int field[][GRID_SIDE], int upBorder, int rightBorder, int bottomBorder, int leftBorder){
	int i,j;
	crowdLocation[0] = upBorder;
	crowdLocation[1] = rightBorder;
	crowdLocation[2] = bottomBorder;
	crowdLocation[3] = leftBorder;
	for( i=crowdLocation[0] ; i <= crowdLocation[2] ; i++){
		for( j=crowdLocation[3] ; j <= crowdLocation[1] ; j++){
			if(!IsAtWall(field, i, j))
				field[i][j]=4;
		}
	}
}

//取得瞬移座標
Location teleportStepLoc(NodePointer player, int X, int Y, int original_X, int original_Y){
	player->row = X;
	player->col = Y;
	drawSquare(original_X, original_Y, WHITE);
	printf("The player travel through the time tunnel to unknown.\n");
}

//進入緩速區
int crowdControl(int field[][GRID_SIDE], NodePointer player){
	int changeSpeed;
	if( field[player->row][player->col]==4 ){
		changeSpeed = CROWD_SPEED;
	}else{
		changeSpeed = INIT_SPEED;
	}
	return changeSpeed;
}

//增加惡龍身體節點
void addNode(NodePointer dragon){
	NodePointer tail = NULL;
	NodePointer newNode = (NodePointer) malloc(sizeof(Node)); //初始化一個新節點 
	//尋找龍的尾巴 
	while(dragon != NULL){
		tail = dragon;
		dragon = dragon -> next;
	}
	//將龍尾巴的方向屬性給新節點 
	newNode -> direct = tail -> direct;
	
	//決定新節點的位置，依據尾巴的移動方向來掛上新節點 
	switch(tail->direct){
		case RIGHT:
			newNode -> row = tail -> row;
			newNode -> col = tail -> col - 1;
			break;			
		case LEFT:
			newNode -> row = tail -> row;
			newNode -> col = tail -> col + 1;			
			break;
		case UP:
			newNode -> row = tail -> row + 1;
			newNode -> col = tail -> col;			
			break;
		case DOWN:
			newNode -> row = tail -> row - 1;
			newNode -> col = tail -> col;			
			break;
	}
	
	tail -> next = newNode; //將尾巴節點連接到新節點 
	newNode -> next = NULL;		
}

//龍的AI控制 
Direction dragonAI(int field[][GRID_SIDE], NodePointer dragon, NodePointer player) {
	Direction dragonDirect = dragon -> direct;
	Location start = {dragon -> row, dragon -> col};
	Location nearestFood = findNearestFood(field, dragon);
	if(nearestFood.row != -1 && nearestFood.col != -1){ 
		PathPointer path = findPath(field, start, nearestFood);
		if(path != NULL)
			dragonDirect = getDirectionByPath(dragon, path);
		else
			dragonDirect = safeDirection(field, dragon);
	}
	return dragonDirect;
}

//從路徑資料判斷下一步方向 
Direction getDirectionByPath(NodePointer head, PathPointer path){
	if(head != NULL && path != NULL){
		PathPointer nextPath = path->next;
		int horizontal = nextPath->loc.col - head->col;
		int vertical = nextPath->loc.row - head->row;
		if(horizontal == 1)
			return RIGHT;
		else if(horizontal == -1)
			return LEFT;
		
		if(vertical == 1)
			return DOWN;
		else if(vertical == -1)
			return UP;
	}
	//如果無法正常處理，繼續照原本方向前進 
	return 	head -> direct;		
}

//取得安全方向，只考慮會不會撞牆
Direction safeDirection(int field[][GRID_SIDE], NodePointer dragon){
	int i;
	int dirSize = 4;
	Location loc;
	
	loc = nextStepLoc(dragon, UP);
	if(!IsAtWall(field, loc.row, loc.col) && !IsAtHole(field, loc.row, loc.col))
		return UP;
	loc = nextStepLoc(dragon, DOWN);
	if(!IsAtWall(field, loc.row, loc.col) && !IsAtHole(field, loc.row, loc.col))
		return DOWN;
	loc = nextStepLoc(dragon, RIGHT);
	if(!IsAtWall(field, loc.row, loc.col) && !IsAtHole(field, loc.row, loc.col))
		return RIGHT;
	loc = nextStepLoc(dragon, LEFT);
	if(!IsAtWall(field, loc.row, loc.col) && !IsAtHole(field, loc.row, loc.col))
		return LEFT;						
	return dragon->direct;
}

//取得下一步座標 
Location nextStepLoc(NodePointer node, Direction direct){
	int currRow =  node -> row;
	int currCol = node -> col;
	int nextRow, nextCol;
	Location loc;
	switch(direct){
		case RIGHT:
			nextRow = currRow;
			nextCol = currCol + 1;
			break;	
		case LEFT:
			nextRow = currRow;
			nextCol = currCol - 1;
			break;
		case UP:
			nextRow = currRow - 1;
			nextCol = currCol;
			break;				
		case DOWN:
			nextRow = currRow + 1;
			nextCol = currCol;		
			break;	
	}
	loc.row = nextRow;
	loc.col = nextCol;
	return loc;
}

//尋找兩點之間可到達的最短路徑 
PathPointer findPath(int field[][GRID_SIDE], Location startLoc, Location goalLoc){
	resetPathQueue();
	int steps = calcSteps(startLoc, goalLoc);
	PathNode start = {0, steps, startLoc, NULL, NULL};  //距離原點步數、距離目標步數、parent、next
	addPathQueue(start);
	while(!isPathQueueEmpty()){
		sortPathQueue();
		PathPointer current = popPathQueue();
		if(current == NULL)
			return NULL;
		if(current->loc.row == goalLoc.row && current->loc.col == goalLoc.col)
			return buildPath(current);
		int dirSize = 4;
		int iDir[] = {1, 0, -1, 0};
		int jDir[] = {0, 1, 0, -1};
		int i,j;
		for(i=0, j=0; i<dirSize; i++, j++){
			Location neighborLoc = {current->loc.row + iDir[i], current->loc.col + jDir[j]};
			if(!visited(neighborLoc) && !IsAtWall(field, neighborLoc.row, neighborLoc.col) && !IsAtHole(field, neighborLoc.row, neighborLoc.col)){
				int steps = calcSteps(neighborLoc, goalLoc);
				int cost = 	current->cost + 1;
				PathNode neighbor = {cost, steps, neighborLoc, current, NULL};
				if(!IsInPathQueue(neighbor)){
					addPathQueue(neighbor);
				}				
			}
		}
	}
	return NULL;
}

//將之後要拜訪的節點放入佇列裡
void addPathQueue(PathNode pathNode){
	if(rear == MAX_QUEUE_SIZE - 1){
		printf("the queue is full");
		return;
	}
	rear += 1;
	pathQueue[rear]	= pathNode;
}

//傳回柱列中的元素，並將它從柱列中刪除
PathPointer popPathQueue(){
	if(front == rear){
		printf("the queue is empty");
		return NULL;
	}
	front ++;
	PathPointer node = (PathPointer)malloc(sizeof(PathNode));
	node->cost = pathQueue[front].cost;
	node->steps = pathQueue[front].steps;
	node->loc = pathQueue[front].loc;
	node->parent = pathQueue[front].parent;
	node->next = pathQueue[front].next;
	return node;
}

//判斷柱列是否為空
bool isPathQueueEmpty(){
	return front == rear;
}

//重設柱列 
void resetPathQueue(){
	front = -1;
	rear = -1;	
}

//對柱列中的元素進行排序 
void sortPathQueue(){
	if(front == rear)
		return;
	int i, j;
	int nowTotal, nextTotal;	
	for(i=front + 1; i<rear; i++){
		for(j=i+1; j<=rear; j++){

			nowTotal = pathQueue[i].cost + pathQueue[i].steps;
			nextTotal = pathQueue[j].cost + pathQueue[j].steps;

			if(nowTotal > nextTotal){
				PathNode temp =  pathQueue[i];
				pathQueue[i] = pathQueue[j];
				pathQueue[j] = temp;
			}
		}
	}		
}

//判斷該元素是否在柱列之中
bool IsInPathQueue(PathNode pathNode){
	int i;
	if(front == rear)
		return false;
	for(i=front;i<=rear;i++){
		if(pathQueue[i].loc.row == pathNode.loc.row && pathQueue[i].loc.col == pathNode.loc.col)
			return true;
	}
	return false;
}

//回傳到目標位置的路徑串列 
PathPointer buildPath(PathPointer goal){
	if(goal == NULL || goal->parent == NULL)
		return NULL;
	PathPointer head = goal;
	head->next = NULL;
	PathPointer temp = head;
	
	while(head->parent){
		head = head->parent; 
		head->next = temp;
		temp = head;
	}
	return head;
}

//計算兩點之間需要移動的步數 
int calcSteps(Location start, Location goal){
	int steps = abs(start.row - goal.row) + abs(start.col - goal.col);
	return steps;
}

//判斷是否該節點已經拜訪過 
bool visited(Location loc){
	int i;
	for(i=0;i<=front;i++){
		if(pathQueue[i].loc.row == loc.row && pathQueue[i].loc.col == loc.col)
			return true;
	}
	return false;
}

//尋找最接近食物的座標 
Location findNearestFood(int field[][GRID_SIDE], NodePointer me){
	int rowDis, colDis, row, col, nearest = 100000;
	Location nearestFood;
	for(row = 0; row < GRID_SIDE; row++){
		for(col = 0; col < GRID_SIDE; col++){
			if(field[row][col] == FOOD){
				rowDis = abs(row - me -> row);
				colDis = abs(col - me -> col);
				if(nearest > (rowDis + colDis)){
					nearest = (rowDis + colDis);
					nearestFood.row = row;
					nearestFood.col = col;
				}
			}
		}
	}
	return nearestFood;
}

//尋找兩點之間可到達的最短路徑_勇者
PathPointer findPath2(int field[][GRID_SIDE], Location startLoc, Location goalLoc){
	resetPathQueue();
	int steps = calcSteps(startLoc, goalLoc);
	PathNode start = {0, steps, startLoc, NULL, NULL};  //距離原點步數、距離目標步數、parent、next
	addPathQueue(start);
	while(!isPathQueueEmpty()){
		sortPathQueue();
		PathPointer current = popPathQueue();
		if(current == NULL)
			return NULL;
		if(current->loc.row == goalLoc.row && current->loc.col == goalLoc.col)
			return buildPath(current);
		int dirSize = 4;
		int iDir[] = {1, 0, -1, 0};
		int jDir[] = {0, 1, 0, -1};
		int i,j;
		for(i=0, j=0; i<dirSize; i++, j++){
			Location neighborLoc = {current->loc.row + iDir[i], current->loc.col + jDir[j]};
			if(!visited(neighborLoc) && !IsAtWall(field, neighborLoc.row, neighborLoc.col) && !IsAtHole(field, neighborLoc.row, neighborLoc.col && !IsbumpDragon(dragonField, neighborLoc.row, neighborLoc.col))){
				int steps = calcSteps(neighborLoc, goalLoc);
				int cost = 	current->cost + 1;
				PathNode neighbor = {cost, steps, neighborLoc, current, NULL};
				if(!IsInPathQueue(neighbor)){
					addPathQueue(neighbor);
				}
			}
		}
	}
	return NULL;
}

//尋找兩點之間可到達的最短路徑_勇者_判斷
int findPath3(int field[][GRID_SIDE], Location startLoc, Location goalLoc){
	resetPathQueue();
	int steps = calcSteps(startLoc, goalLoc);
	PathNode start = {0, steps, startLoc, NULL, NULL};  //距離原點步數、距離目標步數、parent、next
	addPathQueue(start);
	while(!isPathQueueEmpty()){
		sortPathQueue();
		PathPointer current = popPathQueue();
		if(current == NULL)
			return 10000;
		if(current->loc.row == goalLoc.row && current->loc.col == goalLoc.col)
			return buildPath2(current);
		int dirSize = 4;
		int iDir[] = {1, 0, -1, 0};
		int jDir[] = {0, 1, 0, -1};
		int i,j;
		for(i=0, j=0; i<dirSize; i++, j++){
			Location neighborLoc = {current->loc.row + iDir[i], current->loc.col + jDir[j]};
			if(!visited(neighborLoc) && !IsAtWall(field, neighborLoc.row, neighborLoc.col) && !IsAtHole(field, neighborLoc.row, neighborLoc.col && !IsbumpDragon(dragonField, neighborLoc.row, neighborLoc.col))){
				int steps = calcSteps(neighborLoc, goalLoc);
				int cost = 	current->cost + 1;
				PathNode neighbor = {cost, steps, neighborLoc, current, NULL};
				if(!IsInPathQueue(neighbor)){
					addPathQueue(neighbor);
				}
			}
		}
	}
	return 10000;
}

//回傳到目標位置的路徑串列所需步數
int buildPath2(PathPointer goal){
	int steps = 0;
	if(goal == NULL || goal->parent == NULL)
		return 10000;
	PathPointer head = goal;
	head->next = NULL;
	PathPointer temp = head;

	while(head->parent){
		head = head->parent;
		head->next = temp;
		temp = head;
		steps++;
	}
	return steps;
}

//尋找最接近食物的座標
Location findNearestFood2(int field[][GRID_SIDE], NodePointer me){
	int rowDis, colDis, row, col, nearest = 100000;
	int nearfood = 0;
	Location nearestFood;
	Location start = {me -> row, me -> col};
	Location goal;
	for(row = 0; row < GRID_SIDE; row++){
		for(col = 0; col < GRID_SIDE; col++){
			if(field[row][col] == FOOD){
				goal = {row,col};
				nearfood = findPath3(field, start,  goal);
				if(nearest > nearfood){
					nearest = nearfood;
					nearestFood.row = row;
					nearestFood.col = col;
				}
			}
		}
	}
	printf("( %d , %d , %d )\n",nearest , row, col);
	return nearestFood;
}

//請同學實作勇者的AI 
Direction playerAI(int field[][GRID_SIDE], NodePointer player, NodePointer dragon){
	Direction playerDirect = player -> direct;
	Location start = {player -> row, player -> col};
	Location nearestFood = findNearestFood2(field, player);
	if(nearestFood.row != -1 && nearestFood.col != -1){
		PathPointer path = findPath(field, start, nearestFood);
		playerDirect = getDirectionByPath(player, path);
	}
	
	return playerDirect;
}

//技能_時間暫停 
void skilTimeOut(){
	if( scoreSum >= 5 ){
		printf("The player used skills [時間暫停].\n");
		Sleep(2500);
		scoreSum -= 5;
	}
}

//技能_緩速
int skilSlow(){
	static int slowSpeed = 0;
	int changeSpeed;
	if(slowSpeed==0){
		scoreSum -= 3;
		printf("The player used skills [緩速].\n");
	}
	if(IFSlowSpeed){
		changeSpeed = SLOW_SPEED;
		slowSpeed++;
	}
	if(slowSpeed>=6){
		IFSlowSpeed = !IFSlowSpeed;
		changeSpeed = INIT_SPEED;
		slowSpeed = 0;
	}
	return changeSpeed;
} 

//技能_閃現
Location skilFlash(NodePointer player){
	if(scoreSum>=3){
		scoreSum -= 3;
		int nextRow, nextCol;
		switch(player->direct){
			case RIGHT:
				nextRow = player->row;
				nextCol = player->col + FLASH_STEP;
				break;	
			case LEFT:
				nextRow = player->row;
				nextCol = player->col - FLASH_STEP;
				break;
			case UP:
				nextRow = player->row - FLASH_STEP;
				nextCol = player->col;
				break;
			case DOWN:
				nextRow = player->row + FLASH_STEP;
				nextCol = player->col;	
				break;	
		}
		printf("The player used skills [閃現].\n");
		drawSquare(player->row, player->col, BLACK);
		player->row = nextRow;
		player->col = nextCol;
		drawSquare(nextRow, nextCol, BLUE);
	}
}

//技能_製造牆壁 
void skilMakeWall(int field[][GRID_SIDE], NodePointer player){
	if(scoreSum>=2){
		scoreSum -= 2;
		int setRow, setCol;
		switch(player->direct){
			case RIGHT:
				setRow = player->row;
				setCol = player->col -1;
				break;	
			case LEFT:
				setRow = player->row;
				setCol = player->col +1;
				break;
			case UP:
				setRow = player->row +1;
				setCol = player->col;
				break;
			case DOWN:
				setRow = player->row -1;
				setCol = player->col;	
				break;	
		}
		printf("The player used skills [造牆].\n");
		field[setRow][setCol] = 1;
		drawSquare(setRow, setCol, YELLOW);
	}
} 

//技能_飛彈 
NodePointer skilMissile(int field[][GRID_SIDE], NodePointer player, NodePointer dragon, NodePointer missile){
	if(scoreSum>=50){
		if(!IFIsmissileShot){
			scoreSum -= 50;
			missile->direct = player->direct;
			missile->row = player->row;
			missile->col = player->col;
			missileMove(field, player, dragon, missile);
			IFIsmissileShot = !IFIsmissileShot;
			printf("The player used skills [飛彈].\n");
			return missile;
		}
	}
} 

void missileMove(int field[][GRID_SIDE], NodePointer player, NodePointer dragon, NodePointer missile){
	int i,j;
	NodePointer current;
	int targetRow = missile->row;
	int targetCol = missile->col;
	if( missile->direct == RIGHT )
		targetCol = targetCol+1;
	else if( missile->direct == LEFT )
		targetCol = targetCol-1;
	else if( missile->direct == UP )
		targetRow = targetRow-1;
	else if( missile->direct == DOWN )
		targetRow = targetRow+1;
	if(IsAtWall(field, targetRow, targetCol) || IsAtDragon(dragon, targetRow, targetCol )){
		if(IsAtDragon(dragon, targetRow, targetCol)){
  			while(dragon->row != targetRow && dragon->col != targetCol){
				dragon = dragon->next;
			}
			dragon->next = NULL;
			drawGameField(field);
		}
		for( i = targetRow-MISSILE_RANGE ; i <= targetRow+MISSILE_RANGE ; i++){
			for( j = targetCol-MISSILE_RANGE ; j <= targetCol+MISSILE_RANGE ; j++){
				if( i > 0 && i < 39 && j>0 && j<39){
					if( i>=crowdLocation[0] && i<=crowdLocation[2] && j>=crowdLocation[3] && j<=crowdLocation[1] ){
						field[i][j] = 4;
						drawSquare2(i, j, 9);
					}else{
						field[i][j] = 0;
						drawSquare(i, j, BLACK);
					}
				}
			}
		}
		IFIsmissileShot = !IFIsmissileShot;
	}else{
		drawSquare(missile->row, missile->col, BLACK);
		drawSquare(targetRow, targetCol, 3);
		missile->row = targetRow;
		missile->col = targetCol;
	}
}
