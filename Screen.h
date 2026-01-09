#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <string.h>
#include <Windows.h>

#include "Utils.h"

#include "time.h"


#define N_LANDMINE 10
using namespace std;

class Screen
{
	char* lines;//지뢰, 깃발, 숫자 정보를 저장할 상태 배열
	char* answers;//화면 아래에 출력할 답안 배열, 지뢰의 위치 출력
	char* scene;//플레이어에게 보여줄 배열
	char* isVisted;//이미 체크한 위치인지를 저장하는 배열

	//int trapOffset;

	int countFlag = N_LANDMINE;//남은 깃발의 갯수
	int correctFlag = 0;//지뢰위치에 올바르게 꽂은 깃발
	int trapidx = 0;//지뢰의 위치 인덱스

public:
	int n_rows;
	int n_cols;
	Screen(int n_rows, int n_cols)
		: n_rows(n_rows), n_cols(n_cols),
		lines(new char[n_rows * (n_cols + 1)]),
		answers(new char[n_rows * (n_cols + 1)]),
		scene(new char[n_rows * (n_cols + 1)]),
		isVisted(new char[n_rows * (n_cols + 1)])
	{

		Borland::Initialize();
		clear();
	}

	virtual ~Screen()
	{
		delete[] lines;
		delete[] answers;
		delete[] scene;
		delete[] isVisted;

	}

	int pos2offset(int x, int y, int n_cols)
	{
		return y * (n_cols + 1) + x;
	}


	void clear()
	{
		memset(lines, 'X', n_rows * (n_cols + 1));
		memset(answers, 'X', n_rows * (n_cols + 1));
		memset(isVisted, 'N', n_rows * (n_cols + 1));

		for (int i = 0; i < n_rows; i++)
		{
			lines[i * (n_cols + 1) + n_cols] = '\n';
			answers[i * (n_cols + 1) + n_cols] = '\n';
			isVisted[i * (n_cols + 1) + n_cols] = '\n';

		}
		lines[n_rows * (n_cols + 1)] = '\0';
		answers[n_rows * (n_cols + 1)] = '\0';
		isVisted[n_rows * (n_cols + 1)] = '\0';


	}

	void clearscene()//게임 화면 초기화
	{
		memset(scene, 'X', n_rows * (n_cols + 1));
		for (int i = 0; i < n_rows; i++)
		{
			scene[i * (n_cols + 1) + n_cols] = '\n';
		}
		scene[n_rows * (n_cols + 1)] = '\0';
	}


	
	void draw(const Position& pos, char shape)
	{
		int offset = pos2offset(pos.x, pos.y, n_cols);

		scene[offset] = shape;
	}


	void setLandmine(char shape)//지뢰 설치 함수
	{
		for (int i = 0; i < N_LANDMINE; i++)
		{
			trapidx = createLandmine();
			
			if (answers[trapidx] == shape)
				--i;
			else
			{
				answers[trapidx] = shape;
			}

		}
	}
	int createLandmine()//랜덤으로 지뢰를 생성하는 함수
	{
		// 무한루프 뽑을 갯수를 변수로 두고, 제대로 뽑히면 +1, 동일한게 뽑히면 넘어가 위로
		srand(time(NULL));
		int x = rand() % n_rows;
		int y = rand() % n_cols;
		int trapOffset = pos2offset(x, y, n_cols);
		return trapOffset;//지뢰의 오프셋 위치값을 반환


	}
	int countTrap(int idx)//현재 위치 중심으로 주변 8칸의 지뢰 갯수를 세는 함수
	{
		int count = 0;

		for (int j = idx - 12; j < idx - 9; j++)//왼쪽 위부터 검사
		{
			if (j > -1 && answers[j] == '*')
			{
				count++;
			}
		}
		for (int j = idx - 1; j < idx + 2; j = j + 2)//가운데 줄
		{
			if (j > -1 && answers[j] == '*')
			{
				count++;
			}
		}
		for (int j = idx + 10; j < idx + 13; j++)//맨 아래줄
		{
			if (j > -1 && answers[j] == '*')
			{
				count++;
			}
		}
		return count;
	}
	void setNumber()//주변 지뢰의 갯수를 배열에 저장해놓는 함수
	{
		for (int i = 0; i < n_rows * (n_cols + 1); i++)
		{
			if (answers[i] == '*' || answers[i] == '\n')
				continue;
			else
			{
				int count = countTrap(i);
				answers[i] = count + '0';
			}
		}
		

	}
	

	void mapOpen(int idx)//맵을 여는 함수
	{

		if (isVisted[idx] == 'N' && isVisted[idx] != '\n')//이미 체크했는지 검사
		{
			isVisted[idx] = 'Y';
			if (answers[idx] == '0')//주변 지뢰 갯수를 저장하는 배열 answers의 해당 위치가 0이면
			{
				for (int j = idx - 12; j < idx - 9; j++)//왼쪽 위부터 주변 8자리를 검사
				{
					if (j > -1)//인덱스가 범위 안에 있는지 확인
					{
						mapOpen(j);//재귀형식으로 자기자신 호출
					}

				}
				for (int j = idx - 1; j < idx + 2; j = j + 2)//가운데 줄 양 옆 검사
				{
					if (j > -1)
					{
						mapOpen(j);
					}

				}
				for (int j = idx + 10; j < idx + 13; j++)//마지막줄 검사
				{
					if (j > -1)
					{
						mapOpen(j);
					}

				}
				lines[idx] = answers[idx];//자기 자신의 위치 복사
			}
			else//answers가 0이 아니면
			{
				if (answers[idx] != '*' && answers[idx] != '\n')//지뢰인지 줄바꿈문자인지 검사
				{
					lines[idx] = answers[idx];//answers가 0이 아니고 지뢰/줄바꿈 문자가 아니면 1이상의 숫자이므로
				}
			}
		}
	}
		void renderLines()//각각의 배열을 출력하기 위한 함수, 확인용
		{
			for (int i = 0; i < n_rows - 1; i++)
			{
				lines[i * (n_cols + 1) + n_cols] = '\n';
			}
			lines[(n_cols + 1) * n_rows] = '\0';

			Borland::GotoXY(0, 25);
			printf("%s", lines);
			printf("\n");
			printf("%s", isVisted);


		}
		void renderScene()//게임 화면 출력 함수
		{
			for (int i = 0; i < n_rows - 1; i++)
			{
				scene[i * (n_cols + 1) + n_cols] = '\n';
			}
			scene[(n_cols + 1) * n_rows] = '\0';

			Borland::GotoXY(0, 0);
			printf("%s", scene);
			printf("남은 깃발 갯수: %d  ", countFlag);
			printf("맵 오픈:m, 깃발:f");


		}


		void renderAnswer()//지뢰 위치와 주변 지뢰 갯수를 저장한 배열 출력하는 함수, 확인용
		{
			for (int i = 0; i < n_rows - 1; i++)
			{
				answers[i * (n_cols + 1) + n_cols] = '\n';
			}
			answers[(n_cols + 1) * n_rows] = '\0';
			Borland::GotoXY(0, 20);
			printf("%s", answers);
		}

	

		void gameOver()
		{
			Borland::GotoXY(0, 11);
			printf("GAME OVER");
			exit(0);
		}
		void gameClear()
		{
			Borland::GotoXY(15, 0);
			printf("GAME CLEAR");
		}
		void checkTrap(const Position & pos)//지뢰에서 맵을 오픈하면 게임 종료
		{
			if (answers[pos2offset(pos.x, pos.y, n_cols)] == '*')
			{
				gameOver();
			}
		}
		void setFlag(const Position & pos)//깃발 출력
		{
			bool isFlag = false;
			int idx = pos2offset(pos.x, pos.y, n_cols);
			lines[idx] = 'F';
			
		}
		void isFlag(const Position & pos)
		{
			bool isflag = false;
			int idx = 0;
			idx = pos2offset(pos.x, pos.y, n_cols);
			if (lines[idx] == 'F')//깃발이 있으면
			{
				countFlag++;

				lines[idx] = '0';//깃발 회수
			}
			else//깃발이 없으면
			{
				countFlag--;

				lines[idx] = 'F';//깃발 세움
				isflag = true;
			}
		}
		void checkFlag(const Position & pos)//깃발을 올바르게 세웠는지 검사
		{
			Borland::GotoXY(0, 10);
			int idx = 0;
			idx = pos2offset(pos.x, pos.y, n_cols);
			if (correctFlag == N_LANDMINE)
				gameClear();
			if (answers[idx] == '*')
			{
				correctFlag++;
			}

		}
		void screencopy()
		{
			strcpy(scene, lines);
		}


	};