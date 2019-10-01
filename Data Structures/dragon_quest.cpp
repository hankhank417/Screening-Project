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

#define SCREEN_HEIGHT 500 //�]�w�C���������� 
#define SCREEN_WIDTH 500 //�]�w�C�������e��
#define GRID_SIDE 40 //�]�w�C����}�C���l�ƶq 
#define LEFT_MARGINE 30 //�]�w����� 
#define TOP_MARGINE 40 //�]�w�W��� 
#define FOOD_AMOUT 2 //�]�w�C�����ͭ����ƶq
#define MAX_QUEUE_SIZE 1600 //�]�w�W�C�j�p 
#define initializeScoreSum 1000 //�]�w��l����
#define INIT_SPEED  1 //�]�w��l���ʳt��
#define CROWD_SPEED  200 //�]�w�w�t�ϲ��ʳt��
#define SLOW_SPEED  600 //�]�w�w�t�ޯಾ�ʳt�� 
#define FLASH_STEP 3 //�]�w�{�{�Z������ 
#define MISSILE_RANGE 2 //�]�w���u�z���d�� ( �d�� = x*2+1 ) 
#define MODE 1 //�]�wPlayerAI���Ҧ� ( 0�쥻�B1 ROOM )

//�ŧi�e�i��V�C�|��� 
enum Direction {
	RIGHT, 
	LEFT, 
	UP, 
	DOWN 
};

//�ŧi�C�����X�{����C�|��� 
enum Object {
	EMPTY, //�ť� 
	WALL, //��λ�ê�� 
	FOOD, //���� 
	HOLE,
	crowd
};

//�ŧi�c�s����`�I���c 
struct Node {
	int row; //�`�I��b�ĴX�� 
	int col; //�`�I��b�ĴX�C 
	Direction direct; //�Ӹ`�I���e�i��V 
	struct Node *next;	//���V�U�@�Ӹ`�I 
}; 

//�w�q���V�`�I���c�������ܼ� 
typedef struct Node *NodePointer;

//�w�q�y�е��c 
struct Location {
	int row;
	int col;
};

typedef struct PathNode *PathPointer;

//�w�q���|�`�I���c�A�Ψӫإ߲��ʸ��| 
struct PathNode {
	int cost; //�Z�����I���B�� 
	int steps; //�Z���ؼЪ��B�� 
	Location loc;
	PathPointer parent;
	PathPointer next;
};

void openWindow(); //�}�Ҵ������� 
void closeGame(NodePointer dragon); //�B�z�C�������޿� 
int playGame(int field[][GRID_SIDE], NodePointer dragon, NodePointer player, NodePointer missile); //�C���i���޿�
bool IsGameOver(NodePointer dragon, NodePointer player, int field[][GRID_SIDE]); //�c�s�O�_���`(���`����G����M����ۤv����) 
int showGameOverMsg(); //�C�������T��
void showInfo(); //��ܹC��������T 
void drawGameField(int field[][GRID_SIDE]); //ø�s�C���ϰ� 
void drawSquare(int row, int col, int color); //ø�s��� _�� 
void drawSquare2(int row, int col, int color); //ø�s���_�׽u 
void drawSquare3(int field[][GRID_SIDE]); //ø�s���_�w�t�϶�� 
void controlDragonDirection(int field[][GRID_SIDE], NodePointer dragon, NodePointer player); //Ū��AI��J�A�ó]�w��Ҧ��c�s�`�I 
void controlPlayerDirection(int field[][GRID_SIDE], NodePointer player, NodePointer dragon); //Ū����L��V��J�A�Ϊ�AI��J 
void moveNext(int field[][GRID_SIDE], NodePointer dragon, NodePointer player, NodePointer missile); //ø�s�C�e�i�@�B���������
void createFood(int field[][GRID_SIDE], NodePointer dragon); //���ͭ��� 
bool IsAtWall(int field[][GRID_SIDE], int row, int col); //�P�_�O�_������ 
bool IsAtHole(int field[][GRID_SIDE], int row, int col); //�P�_�O�_�i�J�ɪŬ}
bool IsAtDragon(NodePointer dragon, int row, int col); //�P�_�O�_����c�s�ۤv������
void addPointTodragonField(int dragonField[][2],int row,int col); //�s�W�s�����d��
bool IsbumpDragon(int dragonField[][2], int row, int col); //�P�_�i�̬O�_�i�J�s�����
void dragonEatFood(int field[][GRID_SIDE], NodePointer dragon); //�B�z�c�s�Y�쭹���޿� 
void playerEatFood(int field[][GRID_SIDE], NodePointer dragon, NodePointer player); //�B�z���a�Y�쭹���޿�
void playerEnterHole(int field[][GRID_SIDE], NodePointer player); //�B�z���a�i�J�ɪŬ}�޿�
void setHole(int field[][GRID_SIDE], int X, int Y); //�]�w�ɪŬ}�y��
Location teleportStepLoc(NodePointer player, int X, int Y, int original_X, int original_Y); //�ɪŬ}�i�J&�ǰe�y��
void setCrowd(int field[][GRID_SIDE], int upBorder, int rightBorder, int bottomBorder, int leftBorder); //�]�w�w�C�Ͻd��
int crowdControl(int field[][GRID_SIDE], NodePointer player); //�i�J�w�C�� 
void addNode(NodePointer dragon); //�W�[�c�s����`�I
Location findNearestFood(int field[][GRID_SIDE], NodePointer dragon); //�M��̱��񭹪����y�� 
Location findNearestFood2(int field[][GRID_SIDE], NodePointer me); //�M��̱��񭹪����y��_�׶}�s�����
Direction safeDirection(int field[][GRID_SIDE], NodePointer dragon); //���o�w����V�A�u�Ҽ{�|���|���� 
Location nextStepLoc(NodePointer node, Direction direct); //���o�U�@�B�y�� 
PathPointer findPath(int field[][GRID_SIDE], Location startLoc, Location goalLoc); //�M����I�����i��F�����|
PathPointer findPath2(int field[][GRID_SIDE], Location startLoc, Location goalLoc); //�M����I�����i��F�����|_�׶}�s�����
int findPath3(int field[][GRID_SIDE], Location startLoc, Location goalLoc); //�M��i�̻P���������i��F���̵u�B�ƨæ^�ǨB��
void addPathQueue(PathNode pathNode); //�N����n���X���`�I��J��C�� 
PathPointer popPathQueue(); //�Ǧ^�W�C���������A�ñN���q�W�C���R�� 
bool isPathQueueEmpty(); //�P�_�W�C�O�_���� 
void resetPathQueue(); //���]�W�C 
void sortPathQueue(); //��W�C���������i��Ƨ� 
bool IsInPathQueue(PathNode pathNode); //�P�_�Ӥ����O�_�b�W�C���� 
PathPointer buildPath(PathPointer goal); //�^�Ǩ�ؼЦ�m�����|��C 
int buildPath2(PathPointer goal); //�^�Ǩ�ؼЦ�m�����|��C�һݨB��
int calcSteps(Location start, Location goal); //�p����I�����ݭn���ʪ��B�� 
bool visited(Location loc); //�P�_�O�_�Ӹ`�I�w�g���X�L 
Direction getDirectionByPath(NodePointer dragon, PathPointer path); //�q���|��ƧP�_�U�@�B��V 

Direction dragonAI(int field[][GRID_SIDE], NodePointer dragon, NodePointer player); //�c�sAI 
Direction playerAI(int field[][GRID_SIDE], NodePointer player, NodePointer dragon); //�i��AI 
NodePointer Mode_1(int field[][GRID_SIDE], NodePointer player, NodePointer dragon, Direction direct); //�i��AI Mode1
bool around(int field[][GRID_SIDE], NodePointer dragon ,NodePointer player);

void skilTimeOut(); //�ޯ�_�ɶ��Ȱ� 
int skilSlow(); //�ޯ�_�w�t 
Location skilFlash(NodePointer player); //�ޯ�_�{�{ 
void skilMakeWall(int field[][GRID_SIDE], NodePointer player); //�ޯ�_�y�� 
NodePointer skilMissile(int field[][GRID_SIDE], NodePointer player, NodePointer dragon, NodePointer missile); //�ޯ�_���u
void missileMove(int field[][GRID_SIDE], NodePointer player, NodePointer dragon, NodePointer missile); //���u�o�g��...

struct PathNode pathQueue[MAX_QUEUE_SIZE]; //�ŧi�N�n���X���`�I�W�C 
int front; //queue �Ĥ@�Ӥ������e�@�Ӧ�m 
int rear; //queue �̫�@�Ӥ�������m

int speed; //�C�����ʳt��
int scoreSum = initializeScoreSum; //�������� 
int totalTime = 0; //�����C���ɶ� 
int const scorePerFood = 1; //�C�@�������i�o���� 
int holeLocation[1600][2]; //��J�ɪŬ}�y��
int holeCount = 0; //�p��ɪŬ}�ƶq
int crowdLocation[4]; //�w�t�Ͻd�� ( �W, �k, �U, �� )
int dragonField[25000][2]; //��J�s�����y��
int dragonRoom = 0; //�p���s�����ƶq
int fieldCount = 0;
int dragonLength = 0;
bool meetSelfWillDie = false; //�M�w�c�s����ۤv����O�_�|����
bool IFPlayAI = false; //�O�_�}��AI�Ҧ� (*�D�ϥΪ̳]�w)
bool IFSlowSpeed = false; //�O�_�}�ҽw�t�ޯ� (*�D�ϥΪ̳]�w)
bool IFIsmissileShot = false; //�O�_���u�g�X (*�D�ϥΪ̳]�w)
bool IFDragonMore = false; //�s�O�_��S�w���� (*�D�ϥΪ̳]�w)
bool IFPlugins = true; //�O�_�}�ҥ~��
bool IFCrowdControl = false; //�O�_�}�ҽw�t��
bool IFHole = false; //�O�_�}�l�ɪŬ}

// �D�{��      
int main( ){  	
	openWindow();
	
	while(TRUE){
		Node headPlayer = {2, 6, RIGHT, NULL}; //�]�w�i�̪�l��m�M��V
		Node headDragon = {37, 3, RIGHT, NULL}; //�]�w�s�Y��l��m�M��V 
		Node headMissile; //�]�w���u
		NodePointer dragon = &headDragon;
		NodePointer player = &headPlayer;
		NodePointer missile = &headMissile;
		speed = INIT_SPEED;
		holeCount = 0;

		//�]�w�C�����M��ê��
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
			//�]�w�w�C�Ͻd��
			if(IFCrowdControl)
				setCrowd(field3, 14, 23, 22, 15);

	        //�]�w�ɪŬ}
	        if(IFHole){
	        	setHole(field3,4,4);
				setHole(field3,35,35);
				setHole(field3,4,35);
				setHole(field3,35,4);
			}
			 PlaySound(TEXT("D:\\Word\\University\\Sophomore-1\\Data structure\\finalProject\\KnightVSDragon\\music.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
			key = playGame(field3, dragon, player, missile); //�i��C��
		}else if(fieldCount%4==1){
			//�]�w�w�C�Ͻd��
			if(IFCrowdControl)
				setCrowd(field, 14, 23, 22, 15);

	        //�]�w�ɪŬ}
	        if(IFHole){
				setHole(field,4,35);
				setHole(field,35,4);
			}
			 PlaySound(TEXT("D:\\Word\\University\\Sophomore-1\\Data structure\\finalProject\\KnightVSDragon\\music.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
			key = playGame(field, dragon, player, missile); //�i��C��
		}else if(fieldCount%4==2){
			if(IFCrowdControl)
				setCrowd(field1, 14, 23, 22, 15);

	        //�]�w�ɪŬ}
	        if(IFHole){
	        	setHole(field1,4,6);
				setHole(field1,30,34);
				setHole(field1,6,33);
				setHole(field1,33,10);
			}
			PlaySound(TEXT("D:\\Word\\University\\Sophomore-1\\Data structure\\finalProject\\KnightVSDragon\\music.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
			key = playGame(field1, dragon, player, missile); //�i��C��
		}else if(fieldCount%4==3){
			if(IFCrowdControl)
				setCrowd(field2, 14, 23, 22, 15);

	        //�]�w�ɪŬ}
	        if(IFHole){
	        	setHole(field2,9,9);
				setHole(field2,34,30);
				setHole(field2,8,29);
				setHole(field2,30,9);
			}
			PlaySound(TEXT("D:\\Word\\University\\Sophomore-1\\Data structure\\finalProject\\KnightVSDragon\\music.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
			key = playGame(field2, dragon, player, missile); //�i��C��
		}
			
			
		
		
		if (key == 'q' || key == 'Q')
			closeGame(dragon); //�p�G���a��J'q'���}�C��	
		else if (key == 's' || key == 'S'){
			IFDragonMore = false;
			continue; //�p�G���a��J's' �~��C�� 	
		}else if(key == 'z' || key == 'Z'){ //�����a��
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

//�}�Ҵ�������
void openWindow(){
	initwindow(SCREEN_WIDTH*1.44 + LEFT_MARGINE * 3, SCREEN_HEIGHT + TOP_MARGINE * 3, "Hungry dragon Game");
}

//�B�z�C�������޿� 
void closeGame(NodePointer dragon){
	free(dragon);
	exit(0);
}

//�C���i���޿�
int playGame(int field[][GRID_SIDE], NodePointer dragon, NodePointer player, NodePointer missile) {
	
	drawGameField(field); //ø�s�C���ϰ� 
	createFood(field, dragon); //���ͲĤ@������ 
	
	while(true){
				
		int key = 0;
		if(IFCrowdControl)
			drawSquare3(field); //���sø�s�w�t��
		controlDragonDirection(field, dragon, player); 
		controlPlayerDirection(field, player, dragon);//Ū�����a��J��V��A�ñN�s��V�]�w��U�c�s�`�I 
		moveNext(field, dragon, player, missile); //�̾ڸ`�I����V�Aø�s�s���c�s��m
		dragonEatFood(field, dragon); //�P�_�c�s�O�_���Y�쭹���A�p�G���s�W�`�I�����
		playerEatFood(field, dragon, player); //�P�_���a�O�_���Y�쭹���A�p�G���W�[���� 
		if(IFHole)
			playerEnterHole(field, player); //�P�_�O�_�i�J�ɪŬ}
		if(IFCrowdControl)
			speed = crowdControl(field, player); //�P�_�O�_�i�J�w�C��
		
		if(IFSlowSpeed)	//�P�_�O�_�}�ҽw�t�ޯ� 
			speed = skilSlow();
			
		if(IFIsmissileShot)
			missileMove(field, player, dragon, missile);
		if(IFIsmissileShot)
			missileMove(field, player, dragon, missile);
		
		showInfo(); //��ܮɶ��M���Ƹ�T 

		if(dragonLength >= 320 && !IFDragonMore){
			printf(" You feel an evil presence watching you... ");
			PlaySound(TEXT("D:\\Word\\University\\Sophomore-1\\Data structure\\finalProject\\KnightVSDragon\\music2.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
			IFDragonMore = !IFDragonMore;
		}

		if(IsGameOver(dragon, player, field)){ //�P�_�O�_�ŦX�C����������A
			PlaySound(TEXT("D:\\Word\\University\\Sophomore-1\\Data structure\\finalProject\\KnightVSDragon\\GameOver.wav"),NULL,SND_FILENAME|SND_ASYNC);
			return showGameOverMsg(); //��ܹC�������T���A�õ��ݪ��a��J�ﶵ
		}

		
		//���F�Y�쭹���|���ͷs�����A�t�Τ]�H�����ͷs���� 
		srand((unsigned)time(NULL));
		if (rand() % 20 == 0)
			createFood(field, dragon);
			
		if(key != 0)
			return key;
		
		delay(speed); //�M�w���󲾰ʳt�סAspeed�V�p���ʶV�� 
		
		//Ū���D��V�䪺��L��L��J 
	   	if(kbhit()) {
	   		char key;
			key = getch();	
			
			//�u����J�j�p�g��a, q �M s�A�t�Τ~�������ñN��J���G�ߨ�~�h���ݳB�z 
			if (key == 'q' || key == 'Q' || key == 's' || key == 'S' || key == 'z' || key == 'Z' || key == 'x' || key == 'X' || key == 'c' || key == 'C')
				return key; 				
			else if (key == 'a' || key == 'A') //�M�w�O�_���ܼҦ� �A�D�n�����a�Ҧ��M�q���ޱ���AI�Ҧ� 
				IFPlayAI = !IFPlayAI;
			else if (key == 'v' || key == 'V')
				IFPlugins = !IFPlugins;
			else if (key == 't' || key == 'T') //�ϥμȰ��ޯ� 
				skilTimeOut();
			else if (key == 'e' || key == 'E'){ //�ϥνw�t�ޯ�
				if( !IFSlowSpeed && scoreSum>=3)
					IFSlowSpeed = !IFSlowSpeed;
			}
			else if (key == 'r' || key == 'R') //�ϥΰ{�{�ޯ� 
				skilFlash(player);
			else if (key == 'w' || key == 'W') //�ϥγy��ޯ� 
				skilMakeWall(field, player);
			else if (key == 'g' || key == 'G') //�ϥέ��u�ޯ� 
				if(!IFIsmissileShot)
					missile = skilMissile(field, player, dragon, missile);
		}
	}
}

//ø�s�C���ϰ�A�̾ڹC�����x�}�]�wø�s���� 
void drawGameField(int field[][GRID_SIDE]){
   	int row = 0, col = 0;
   	cleardevice(); //�M�z�ù��e�� 
	for(row = 0; row < GRID_SIDE; row ++){
   		for(col = 0; col <  GRID_SIDE; col++){
				switch(field[row][col])	{
					case 0: //�I��
						drawSquare(row, col, 0);
						break;
					case 1: //��b�x�}�����ȬO1 
						drawSquare(row, col, 14);
						break;
					case 2: //�����b�x�}�����ȬO2
						drawSquare(row, col, 3);
						break;
					case 3: //�ɪŬ}�b�x�}�����ȬO3
						if(IFHole)
							drawSquare(row, col, 1);
						break;
					case 4: //�w�t�Ϧb�x�}�����ȬO4 
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

//ø�s���_�� 
void drawSquare(int row, int col, int color){
	
	int squareHeight = SCREEN_HEIGHT / GRID_SIDE;
   	int SquareWidth = SCREEN_WIDTH / GRID_SIDE;
	int left = 0, right = 0, bottom = 0, top = 0;
	left = LEFT_MARGINE + col * SquareWidth + col;
   	top =  TOP_MARGINE + row * squareHeight + row;
	right = left + SquareWidth;
   	bottom = top + squareHeight;
   	 
	setfillstyle(SOLID_FILL,color); //�]�wø�s���󪺬���ߩM�C�� 
   	bar(left , top, right, bottom);	//�]�wø�s�������m 
}
//ø�s���_�׽u
void drawSquare2(int row, int col, int color){
	
	int squareHeight = SCREEN_HEIGHT / GRID_SIDE;
   	int SquareWidth = SCREEN_WIDTH / GRID_SIDE;
	int left = 0, right = 0, bottom = 0, top = 0;
	left = LEFT_MARGINE + col * SquareWidth + col;
   	top =  TOP_MARGINE + row * squareHeight + row;
	right = left + SquareWidth;
   	bottom = top + squareHeight;
   	 
	setfillstyle(SLASH_FILL ,color); //�]�wø�s���󪺬��׽u�M�C�� 
   	bar(left , top, right, bottom);	//�]�wø�s�������m 
}

////ø�s���_�w�t��(�ɪ�) 
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

//ø�s�C�e�i�@�B���������
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
		//�̾ڸ`�I����V�ݩʡA�]�w���ʤU�@�B����m	
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


//�s�W�s�����d��
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

//�P�_�i�̬O�_�i�J�s�����
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

//�c�s�O�_���`(���`����G����M����ۤv����) 
bool IsGameOver(NodePointer dragon, NodePointer player, int field[][GRID_SIDE]){
	NodePointer head = dragon;
	
	//�P�_�O�_������ 
	if (IsAtWall(field, head->row, head->col))
		return true;
	if (IsAtWall(field, player->row, player->col))
		return true;
	
	//�P�_�O�_����c�s�ۤv 
	if(meetSelfWillDie)
		return IsAtDragon(dragon->next, head->row, head->col);
	
	//�ˬd�O�_AI�����s 
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

//�P�_�O�_������
bool IsAtWall(int field[][GRID_SIDE], int row, int col){
		if (field[row][col] == 1 || field[row][col] == 5 ||field[row][col] == 6 || field[row][col] == 7 || field[row][col] == 8 || field[row][col] == 9)
			return true;
		return false;
}
//�P�_�O�_�i�J�ɪŬ} 
bool IsAtHole(int field[][GRID_SIDE], int row, int col){
		if (field[row][col] == HOLE)
			return true;
		return false;
}

//�P�_�O�_����c�s�ۤv������
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

//�C�������T��
int showGameOverMsg(){
   	//cleardevice(); //�M�z�Ҧ��ù���ơA�p�G�Ʊ�u��ܰT���ɡA�������� 

	int i = 0;
	char msg1[15] = "Game Over!!";
	char msg2[60] = "    press [q] to quit or [s] to restart!!          ";
	char msg3[60] = "   �U�жW�ӶW���A�굲�j�a���� !!!                  ";
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

//��ܹC��������T
void showInfo(){
	totalTime += speed;
	char skilTimeOut[20] = "�ɶ��Ȱ�(T) 5 cost";
	char skilSlow[20] = "�w�t(E) 3 cost";
	char skilFlash[20] = "�{�{(R) 3 cost";
	char skilMakeWall[20] = "�y��(W) 2 cost";
	char skilMissile[20] = "���u(G) 50 cost";
	char timeMsg[45] = " Time:";
	char scoreMsg[45] = "Score:";
	char modeMsg[20] = "";
	char optMsg1[50] = "press [q] to quit, [s] to restart or";
	char optMsg2[50] = "press [a] to change mode, [z] to change map.";
	char member0[40] = "B054020001 ���Χ�";
	char member1[40] = "B054020002 �J����";
	char member2[40] = "B054020003 ���v��";
	char member3[40] = "B054020007 ��  �f";
	char member4[40] = "B054020029 �x�l�a";
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
	
	setcolor(WHITE); //�]�w��r�C�� 
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1); //�]�w�r���A�����Ϋ����M�r���j�p 
   	outtextxy(0, 0, timeMsg); //�̾ڧ��п�X��r��ù�	
	
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

//Ū����L��V��J�A�ó]�w��Ҧ��c�s�`�I 
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


//Ū����L��V��J�A�ó]�w��Ҧ��c�s�`�I 
void controlDragonDirection(int field[][GRID_SIDE], NodePointer dragon, NodePointer player) {
		
	Direction dragonDirect = dragonAI(field, dragon, player);
	//���F�F�칳�s�@�˲��ʤ覡�A���s���ܤ�V�ɡA�ä��O��Ө���@�_���ܡA
	//�ӬO����ʦa�A�U�Ӹ`�I�v�@���ܡA��@�Ӹ`�I����s���e�i��V�ɡA
	//�|�N�ۤv�ثe����V�ǵ��U�@�ӡC 
	Direction temp;
	while(dragon != NULL){
		temp = dragon -> direct;
		dragon -> direct = dragonDirect;
		dragonDirect = temp;
		dragon = dragon -> next;
	}
}

//���ͭ���
void createFood(int field[][GRID_SIDE], NodePointer dragon){
	int row, col, i, foodAmount = FOOD_AMOUT;
	srand((unsigned)time(NULL)); //���ثe�t�ήɶ��@���üƺؤl 

	for(i=0; i< foodAmount; i++){
		//�p�G�üƲ��ͪ���m�O�b��M�s���魫�|�A�h���s���͡A����ŦX���󬰤� 
		do{
			row = rand() % GRID_SIDE;
			col = rand() % GRID_SIDE;	
		}while(IsAtWall(field, row, col) || IsAtDragon(dragon, row, col) || IsAtHole(field, row, col));
	
		field[row][col] = FOOD;
		drawSquare(row,col, 3);
	}
}

//�B�z�c�s�Y�쭹���޿�
void dragonEatFood(int field[][GRID_SIDE], NodePointer dragon){
	//�p�G�s�Y�P������m���|�A�N�O�Y�쭹�� 
	if(field[dragon->row][dragon->col] == FOOD && field[dragon->row][dragon->col] != HOLE){
		field[dragon->row][dragon->col] = EMPTY; //�N�ӭ����M�� 
		printf("The dragon has eaten food at row: %d, col: %d\n", dragon->row, dragon->col);
		addNode(dragon); //�W�[�`�I
		dragonLength++;
		createFood(field, dragon); //���ͷs������ 
	}
}

//�B�z���a�Y�쭹���޿�
void playerEatFood(int field[][GRID_SIDE], NodePointer dragon, NodePointer player){
	//�p�G�s�Y�P������m���|�A�N�O�Y�쭹��
	if(field[player->row][player->col] == FOOD && field[player->row][player->col] != HOLE){
		field[player->row][player->col] = EMPTY; //�N�ӭ����M�� 
		printf("The player has eaten food at row: %d, col: %d\n", player->row, player->col);
		scoreSum = scoreSum + scorePerFood; //�������� 
		createFood(field, player); //���ͷs������ 
	}
}

//�B�zplayer�i�J�ɪŬ}
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

//�]�w�Ŭ}�y��
void setHole(int field[][GRID_SIDE], int X, int Y){
	if(field[X][Y]!=1){
		holeLocation[holeCount][0]=X;
		holeLocation[holeCount][1]=Y;
		field[X][Y] = 3;
		printf("setHole :( %d, %d, %d )\n",holeCount,X,Y);
		holeCount++;
	}
}

//�]�w�w�C�Ͻd��
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

//���o�����y��
Location teleportStepLoc(NodePointer player, int X, int Y, int original_X, int original_Y){
	player->row = X;
	player->col = Y;
	drawSquare(original_X, original_Y, WHITE);
	printf("The player travel through the time tunnel to unknown.\n");
}

//�i�J�w�t��
int crowdControl(int field[][GRID_SIDE], NodePointer player){
	int changeSpeed;
	if( field[player->row][player->col]==4 ){
		changeSpeed = CROWD_SPEED;
	}else{
		changeSpeed = INIT_SPEED;
	}
	return changeSpeed;
}

//�W�[�c�s����`�I
void addNode(NodePointer dragon){
	NodePointer tail = NULL;
	NodePointer newNode = (NodePointer) malloc(sizeof(Node)); //��l�Ƥ@�ӷs�`�I 
	//�M���s������ 
	while(dragon != NULL){
		tail = dragon;
		dragon = dragon -> next;
	}
	//�N�s���ڪ���V�ݩʵ��s�`�I 
	newNode -> direct = tail -> direct;
	
	//�M�w�s�`�I����m�A�̾ڧ��ڪ����ʤ�V�ӱ��W�s�`�I 
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
	
	tail -> next = newNode; //�N���ڸ`�I�s����s�`�I 
	newNode -> next = NULL;		
}

//�s��AI���� 
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

//�q���|��ƧP�_�U�@�B��V 
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
	//�p�G�L�k���`�B�z�A�~��ӭ쥻��V�e�i 
	return 	head -> direct;		
}

//���o�w����V�A�u�Ҽ{�|���|����
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

//���o�U�@�B�y�� 
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

//�M����I�����i��F���̵u���| 
PathPointer findPath(int field[][GRID_SIDE], Location startLoc, Location goalLoc){
	resetPathQueue();
	int steps = calcSteps(startLoc, goalLoc);
	PathNode start = {0, steps, startLoc, NULL, NULL};  //�Z�����I�B�ơB�Z���ؼШB�ơBparent�Bnext
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

//�N����n���X���`�I��J��C��
void addPathQueue(PathNode pathNode){
	if(rear == MAX_QUEUE_SIZE - 1){
		printf("the queue is full");
		return;
	}
	rear += 1;
	pathQueue[rear]	= pathNode;
}

//�Ǧ^�W�C���������A�ñN���q�W�C���R��
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

//�P�_�W�C�O�_����
bool isPathQueueEmpty(){
	return front == rear;
}

//���]�W�C 
void resetPathQueue(){
	front = -1;
	rear = -1;	
}

//��W�C���������i��Ƨ� 
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

//�P�_�Ӥ����O�_�b�W�C����
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

//�^�Ǩ�ؼЦ�m�����|��C 
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

//�p����I�����ݭn���ʪ��B�� 
int calcSteps(Location start, Location goal){
	int steps = abs(start.row - goal.row) + abs(start.col - goal.col);
	return steps;
}

//�P�_�O�_�Ӹ`�I�w�g���X�L 
bool visited(Location loc){
	int i;
	for(i=0;i<=front;i++){
		if(pathQueue[i].loc.row == loc.row && pathQueue[i].loc.col == loc.col)
			return true;
	}
	return false;
}

//�M��̱��񭹪����y�� 
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

//�M����I�����i��F���̵u���|_�i��
PathPointer findPath2(int field[][GRID_SIDE], Location startLoc, Location goalLoc){
	resetPathQueue();
	int steps = calcSteps(startLoc, goalLoc);
	PathNode start = {0, steps, startLoc, NULL, NULL};  //�Z�����I�B�ơB�Z���ؼШB�ơBparent�Bnext
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

//�M����I�����i��F���̵u���|_�i��_�P�_
int findPath3(int field[][GRID_SIDE], Location startLoc, Location goalLoc){
	resetPathQueue();
	int steps = calcSteps(startLoc, goalLoc);
	PathNode start = {0, steps, startLoc, NULL, NULL};  //�Z�����I�B�ơB�Z���ؼШB�ơBparent�Bnext
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

//�^�Ǩ�ؼЦ�m�����|��C�һݨB��
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

//�M��̱��񭹪����y��
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

//�ЦP�ǹ�@�i�̪�AI 
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

//�ޯ�_�ɶ��Ȱ� 
void skilTimeOut(){
	if( scoreSum >= 5 ){
		printf("The player used skills [�ɶ��Ȱ�].\n");
		Sleep(2500);
		scoreSum -= 5;
	}
}

//�ޯ�_�w�t
int skilSlow(){
	static int slowSpeed = 0;
	int changeSpeed;
	if(slowSpeed==0){
		scoreSum -= 3;
		printf("The player used skills [�w�t].\n");
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

//�ޯ�_�{�{
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
		printf("The player used skills [�{�{].\n");
		drawSquare(player->row, player->col, BLACK);
		player->row = nextRow;
		player->col = nextCol;
		drawSquare(nextRow, nextCol, BLUE);
	}
}

//�ޯ�_�s�y��� 
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
		printf("The player used skills [�y��].\n");
		field[setRow][setCol] = 1;
		drawSquare(setRow, setCol, YELLOW);
	}
} 

//�ޯ�_���u 
NodePointer skilMissile(int field[][GRID_SIDE], NodePointer player, NodePointer dragon, NodePointer missile){
	if(scoreSum>=50){
		if(!IFIsmissileShot){
			scoreSum -= 50;
			missile->direct = player->direct;
			missile->row = player->row;
			missile->col = player->col;
			missileMove(field, player, dragon, missile);
			IFIsmissileShot = !IFIsmissileShot;
			printf("The player used skills [���u].\n");
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
