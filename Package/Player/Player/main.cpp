#include "Player.h"
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
// main.cpp is the only file you will be submitting for the contest
// HINT: before submitting this file, make sure to test compiling on Release 
//       and deactivating Debug mode from the Match Maker
// HINT: read the complete rules for submitting this file on the contest website
int turn = 0;
Move rev[moveCount];
int my[] = {0, -1, 1,  0, 0 };
int mx[] = {0,  0, 0, -1, 1 };


#define SMAX 32

typedef struct {
	int info;
	int inDanger;
} Cell;

typedef struct {
	int x;
	int y;
} Coord;

FILE *out; 
int dimX, dimY;
Cell map[SMAX][SMAX];
queue <Coord>  bombs[7];
IGame *XGAME;


void PrintMap() {
	int i,j;

	fprintf(out, "Map ========= \n");

	for (i=0; i< dimX; i++)
	{
		for (j=0; j< dimY; j++)
			fprintf(out, "%d\t", map[i][j].info);

		fprintf(out, "\t\t\t\t");

		for (j=0; j< dimY; j++)
			fprintf(out, "%d\t", map[i][j].inDanger);

		fprintf(out, "\n");
	}

	fflush(out);
}


void SetDangerZones( int bombType, Coord bob, int dirx, int diry) {
	int x = bob.x + dirx;
	int y = bob.y + diry;
	Coord Point;
	while (x >= 0 && x < dimX && y >=0 && y < dimY) 
	{
		int info = map[x][y].info;

		if (info == -1 || info == 2)
			return;

		if (info == 0 )
		{
			if (map[x][y].inDanger)
			{
				if (bombType < map[x][y].inDanger)
					map[x][y].inDanger = bombType;
			}
			else
				map[x][y].inDanger = bombType;
		}

		if (info == 1 && map[x][y].inDanger != 1)
		{
			map[x][y].inDanger = bombType;
		}
		
		if (info == 4)
		{
			if (map[x][y].inDanger == bombType)
				return;
			map[x][y].inDanger = bombType;
			Point.x = x;
			Point.y = y;
			bombs[bombType].push(Point);
			return;
		}

		x = x + dirx;
		y = y + diry;
	}

}

void CreateDangerZones() 
{
	int i;
	for (i=1; i<=6; i++)
	{
		while (!bombs[i].empty()) 
		{
			Coord bob = bombs[i].front();
			bombs[i].pop();
			if (i == map[bob.x][bob.y].inDanger)
			{
				SetDangerZones(i, bob, 0 , 1);	
				SetDangerZones(i, bob, 0 , -1);	
				SetDangerZones(i, bob, 1 , 0);	
				SetDangerZones(i, bob, -1 , 0);	
			}
		}
	}
}

void GetChainMatrix() 
{
	int i, j, bob, wall;
	Coord Point;

	for (i=0; i< dimX; i++)
	{
		for (j=0; j< dimY; j++)
		{
			bob = XGAME->Bomb(i,j);
			wall = XGAME->Wall(i,j);

			map[i][j].info = wall;
			map[i][j].inDanger = bob;

			if (bob > 0)
			{
				map[i][j].info = 4;
				Point.x = i;
				Point.y = j;
				bombs[bob].push(Point);
			}

		}
	}
	CreateDangerZones();
	PrintMap();
}




void PlayerInit(int playerId, IGame* game)
{
	
    //TODO: add initialization code here
    //HINT: this function is called only once (before the game starts)
    //HINT: the time taken by this function is taken out of the time allocated for your first move

	rev[moveUp] = moveDown;
	rev[moveDown] = moveUp;
	rev[moveLeft] = moveRight;
	rev[moveRight] = moveLeft;
	rev[moveNone] = moveNone;

	out = fopen("map.txt","w");
	dimX = game->SizeX();
	dimY = game->SizeY();

}

//     fi
//    fxf
//     fi
float v[16][16][16];
char  v2[16][16][16];
float heatmap[16][16];
float inf = 1<<20;

typedef struct {
	int x, y;
	int dist;
	float heat;
} qe;


class Qecomp
{
public:
  bool operator() (const qe& x, const qe& y) const
  {
    float dif = x.heat - y.heat;
	if ( dif > -0.0001 && dif < 0.0001 )
		return x.dist > y.dist;
	return x.heat < y.heat;
  }
};



void generate_heat_map (IGame *game, int playerId)
{
	//queue < pair < int,  pair < int , int > > > q;
	queue <qe> q;
	//priority_queue<qe, vector<qe>, Qecomp> q;
	qe e;
	memset(heatmap, 0, sizeof(heatmap));
	for (int i = 0; i < game->PlayerCount(); ++i)
	{
			if( !game->PlayerAlive(i) )
				continue;

			vector < vector < bool > > viz (16, vector < bool > (16, 0));
			//q.push(make_pair(inf, make_pair(game->PlayerPosX(i), game->PlayerPosY(i))));
			e.dist = 0;
			e.x = game->PlayerPosX(i);
			e.y = game->PlayerPosY(i);
			e.heat = 100000000;
			q.push(e);

			while (!q.empty())
			{
					//qe t = q.top();
					qe t = q.front();
					q.pop();
					//int x = t.second.first;
					//int y = t.second.second;
					viz[t.x][t.y] = 1;
					heatmap[t.x][t.y] += t.heat;
					int kids = 0;
					for (int j = moveUp; j < moveCount; ++ j)
					{
						int x = t.x + mx[j];
						int y = t.y + my[j];
						/*if (x+mx[j] > -1 && y+my[j] > -1 && x+mx[j] <game->SizeX() && y+my[j] < game->SizeY() && 
							!viz[x+mx[j]][y+my[j]] && map[x+mx[j]][y+my[j]].info == 0)
						{
							if (map[x+mx[j]][y+my[j]].inDanger != t.dist + 1 &&
								map[x+mx[j]][y+my[j]].inDanger != t.dist + 2)
							++kids;
						}*/
						if (x > -1 && y > -1 && 
							x < game->SizeX() && y < game->SizeY() && 
							!viz[x][y] && map[x][y].info == 0)
						{
							if (map[x][y].inDanger != t.dist + 1 &&
								map[x][y].inDanger != t.dist + 2)
									++kids;
						}

					}
					if (!kids)
						continue;

					e.dist = t.dist + 1;
					if (i!=playerId)
					{
						if (kids == 1)
							e.heat = t.heat *2;
						else
							e.heat = t.heat / kids;
					}
					else
						e.heat = -(t.heat /kids);
					if (e.heat < 0.0001)
						continue;

					for (int j = moveUp; j < moveCount; ++ j)
					{
						int x = t.x + mx[j];
						int y = t.y + my[j];

						if (x > -1 && y > -1 && 
							x <game->SizeX() && y < game->SizeY() && 
							!viz[x][y] && map[x][y].info == 0)
						{
							if (map[x][y].inDanger != t.dist + 1 &&
								map[x][y].inDanger != t.dist + 2)
							{
								e.x = x;
								e.y = y;
								q.push(e);
								viz[x][y] = 1;
							}
						}
					}
			}
				
		}
}
float dfs (IGame *game, int playerId, int depth, int from)
{
	if (!game->PlayerAlive(playerId))
			return 0;
	
	

	if (depth == 0)
			return heatmap[game->PlayerPosX(playerId)][game->PlayerPosY(playerId)]+1;
	if (v2[game->PlayerPosX(playerId)][game->PlayerPosY(playerId)][depth])
		return v[game->PlayerPosX(playerId)][game->PlayerPosY(playerId)][depth];
	
	//generate_heat_map(game, playerId);
//	XGAME = game;
//	GetChainMatrix();
	float r = 0;
	for (Move i = moveFirst; i != moveCount; ++i)
	{
		int x = game->PlayerPosX(playerId)+my[i];
		int y = game->PlayerPosY(playerId)+mx[i];
		if (simulation->CanMove(game, playerId, i) || (x > -1 && y > -1 && 
							x <game->SizeX() && y < game->SizeY() &&  game->Bomb(x,y) == -1))
		{
			IGame *ngame = game->Clone();
			simulation->StoreMove(playerId, i, 0);
			simulation->BeginTurn(ngame);
			simulation->EndTurn(ngame);
			float k = dfs(ngame, playerId, depth-1, i);
			r +=k;
			delete ngame;
		}
	}
	if (!v2[game->PlayerPosX(playerId)][game->PlayerPosY(playerId)][depth])
	{
		v2[game->PlayerPosX(playerId)][game->PlayerPosY(playerId)][depth] = 1;
		v[game->PlayerPosX(playerId)][game->PlayerPosY(playerId)][depth] = r;
	}
	return r;
}

void PlayerMove(int playerId, IGame* game, Move& move, bool& bomb)
{
	XGAME = game;
	GetChainMatrix();
//	fprintf(out,"Turn: %d\n", turn );
//	fflush(out);
	//simulation->BeginTurn(game);
	++turn;
	
	move = moveNone;
	float m = -1000;
	int gata = 0;
	int killswitch = 0;
	vector < int > bmbs;
	memset(heatmap, 0, sizeof(heatmap));
	for (int i = 0; i < game->PlayerCount(); ++ i)
		if(game->PlayerAlive(i) && i!=playerId)
		{
			IGame * ngame = game->Clone();
			int &x = ngame->Bomb(ngame->PlayerPosX(i), ngame->PlayerPosY(i));
			x = 7;
			simulation->BeginTurn(ngame);
			simulation->EndTurn(ngame);
			memset(v2, 0, sizeof(v2));
			float f1 = dfs(ngame, i, 6, 0);
			delete ngame;


		/*	ngame = game->Clone();
			simulation->BeginTurn(ngame);
			simulation->EndTurn(ngame);
			memset(v2, 0, sizeof(v2));
			float f2 = dfs (ngame, i, 6, 0);*/
			if (!(f1 <= 0.001))
			{
				bmbs.push_back(i);
			}
			//delete ngame;

		}
	for (int we = 6; we >=0; we-=6)
	{

		for (int i = 0; i < bmbs.size(); ++ i)
		{
			int &x = game->Bomb(game->PlayerPosX(bmbs[i]), game->PlayerPosY(bmbs[i]));
			x = we;
		}
		generate_heat_map(game, playerId);
		for (int k = 1; k >= 0 && !gata; --k)
		for (Move i = moveUp; i <= moveCount; ++i)
		{
			if (k == 0 && m > 0)
			{
				gata = 1;
				break;
			}
			if (i == moveCount)
				i = moveNone;
			if (simulation->CanMove(game, playerId, i) || game->Bomb(game->PlayerPosX(playerId)+my[i],game->PlayerPosY(playerId)+mx[i]) == -1)
			{
				IGame * ngame = game->Clone();
				simulation->StoreMove(playerId, i, k);
				/*
				for (int h = 0; h < game->PlayerCount(); ++h)
					if (h!=playerId)
						simulation->StoreMove(h, moveNone, true);
						*/
				simulation->BeginTurn(ngame);
				simulation->EndTurn(ngame);
				if (ngame->PlayerAlive(playerId))
				{
					float o;
					memset(v2, 0, sizeof(v2));
					o = dfs(ngame, playerId, 8, i);
					if (o > m)
					{
						m = o;
						move = i;
						bomb = k;
					}
				}
				delete ngame;
				//delete ngame;
			}
			if (i == moveNone)
				break;


		}
		if (m <= 0.001) 
		{
			printf("I can't survive\n");
			
		}
		else
			break;
	}
	printf("Time left %d\n", GetTimeLeft());
    //TODO: add AI code here
    //TODO: assign values to move and bomb (which represent your move for this step)
    //HINT: this function is called once for every game step
    //HINT: you can use the simulation pointer to simulate game states
    //HINT: you can modify the contents of the game pointer
    //HINT: you can clone the game state to evolve different scenarios
    //HINT: this function must return before GetTimeLeft() returns 0
    //HINT: the game will evolve 1 step before your character starts moving, so it's useful to
    //      call simulation->BeginTurn(game) to get the state of the game at the time your player 
    //      will begin to move or place the bomb.
    
}
