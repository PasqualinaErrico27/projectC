/*                  Esercizio 1: Robot

    Questo programma simula un robot in una stanza, circondato di mura con un'uscita.
    Il punto fondamentale è quello di far uscire il robot dalla stanza attraverso le mosse casuali e quelle "conosciute".
    In ogni caso il robot non farà mai un passo retrocedendo nella posizione precedente
*/




#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAP_W 16
#define MAP_H 16
#define MAP_FREE ' '
#define MAP_MURO '#'
#define MAP_BOT  'X'
#define BOT_LEFT 0
#define BOT_RIGHT 1
#define BOT_TOP 2
#define BOT_DOWN 3
#define BOT_RANDOM 0
#define BOT_CHOSEN 1

char map[MAP_H][MAP_W] = {{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
			              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
			              {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
						  {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
						  {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
						  {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
						  {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
						  {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
						  {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
						  {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
						  {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
						  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
						  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
						  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
						  {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
						  {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}};

int mossa;
int direction;


void initrandom()
{
	srand(time(NULL));   ///facendo così questa funzione genera il seme per la rand.
}

int casuale_bot(int max)
{
    max = 1 + rand()%15;
    return max;
}



int casuale(int max)
{
    max = rand()%99 + 1;   ///facendo così posso ottenere il valore per poter definire se la mossa è casuale o scelta.
	return max;
}

///movimento
void movimento_robot(int direzione, int* robot_y, int* robot_x)
{
	switch (direzione)
	{
		default: case BOT_LEFT:
			--(*robot_x);
		break;

		case BOT_RIGHT:
			++(*robot_x);
		break;

		case BOT_TOP:
			--(*robot_y);
		break;

		case BOT_DOWN:
			++(*robot_y);
		break;
	}
}

int bot_canwalk(int direzione, int robot_y, int robot_x)
{
	switch (direzione)
	{
		default: case BOT_LEFT:
			if ( robot_x == 0 ) return 0;
		return ( map[robot_y][robot_x-1] == MAP_FREE ) ? 1 : 0;

		case BOT_RIGHT:
			if ( robot_x == MAP_W  - 1 ) return 0;
		return ( map[robot_y][robot_x+1] == MAP_FREE ) ? 1 : 0;

		case BOT_TOP:
			if ( robot_y == 0 ) return 0;
		return ( map[robot_y - 1][robot_x] == MAP_FREE ) ? 1 : 0;

		case BOT_DOWN:
			if ( robot_y == MAP_H - 1 ) return 0;
		return ( map[robot_y + 1][robot_x] == MAP_FREE ) ? 1 : 0;
	}
	return 0;
}

int bot_maxwalk(int direzione, int robot_y, int robot_x) ///mi permette di seguire la strada più lunga
{
	int max = 0;

	switch (direzione)
	{
		default: case BOT_LEFT:
			for ( --robot_x ; robot_x >= 0 && map[robot_y][robot_x] == MAP_FREE; ++max, --robot_x);
		return max;

		case BOT_RIGHT:
			for ( ++robot_x ; robot_x < MAP_W && map[robot_y][robot_x] == MAP_FREE; ++max, ++robot_x);
		return max;

		case BOT_TOP:
			for ( --robot_y ; robot_y >= 0 && map[robot_y][robot_x] != MAP_MURO; ++max, --robot_y);
		return max;

		case BOT_DOWN:
			for ( ++robot_y ; robot_y < MAP_H && map[robot_y][robot_x] != MAP_MURO ; ++max, ++robot_y);
		return max;
	}

	return 0;
}

int bot_chosen(int robot_y, int robot_x) ///fa muovere il robot nel caso in cui ci sia la "scelta"
{
	int i;
	int candidate[4];
	int ncandy = 0;
	int ret;
	int max = 0;

	for ( i = 0; i < 4; ++i )
	{
		ret = bot_maxwalk(i,robot_y,robot_x);
		if ( ret > max )
		{
			candidate[0] = i;
			ncandy = 1;
			max = ret;
		}
		else if ( ret == max )
		{
			candidate[ncandy++] = i ;
		}
	}

	return ( ncandy > 1 ) ? candidate[casuale(ncandy-1)] : candidate[0];
}

int bot_diceluck() ///mi fa capire se devo attivare la funzione BOT_RANDOM o CHOSEN
{
	return ( casuale(100) > 30 ) ? BOT_RANDOM : BOT_CHOSEN;
}

void bot_move(int* robot_y, int* robot_x) ///movimento del robot, indica se uscirà un casuale o uno "visto"
{
	static int oldx = 0;
	static int oldy = 0;

	int dl;
	int direzione;
	int ty,tx;

	do
	{
		mossa = dl =  bot_diceluck();
		switch ( dl )
		{
			default: case BOT_CHOSEN:
				direzione = bot_chosen(*robot_y,*robot_x);
			break;

			case BOT_RANDOM:
				direzione = casuale(3);
			break;
		}

		tx = *robot_x;
		ty = *robot_y;
		if ( !bot_canwalk(direzione,ty,tx) ) continue;
		movimento_robot(direzione,&ty,&tx);
	}while(tx == oldx && ty == oldy  );

	direction = direzione;

	oldx = *robot_x;
	oldy = *robot_y;
	*robot_x = tx;
	*robot_y = ty;
}

int bot_winner(int robot_y, int robot_x) ///visualizza se il robot ha vinto o meno
{
	return ( !robot_y || !robot_x || robot_y == MAP_H -1 || robot_x == MAP_W -1 ) ? 1 : 0;
}

void map_draw(int robot_y, int robot_x) ///disegna sia la mappa che il robot
{
	system("CLS");
	int y,x;
	for ( y = 0; y < MAP_H; ++y )
	{
		for ( x = 0; x < MAP_W; ++x )
		{
			if ( y == robot_y && x == robot_x )
				putchar(MAP_BOT);

                else
				putchar(map[y][x]);
		}
		printf("\n");
	}
	printf("%s\n",(mossa == BOT_CHOSEN ) ? "random" : "chosen" );
}

int main()
{
	int robot_y;
	int robot_x;
	int murocasuale = 0;
	int i,j;

	initrandom();

	for (i = 1; i < 15; i++)
    {
        for (j=1; j<15; j++)
        {
            murocasuale = rand()%11;

            if (murocasuale < 1)
            {
                map[i][j] = MAP_MURO;
            }
        }
    }

	do ///il do mi permette di non sbagliare mai lo spawn del robot
	{
		robot_y = casuale_bot(15);
		robot_x = casuale_bot(15);
		if (map[robot_y][robot_x]== MAP_MURO)
        {
            robot_y = casuale_bot(15);
            robot_x = casuale_bot(15);

        }
	}while ( map[robot_y][robot_x] != MAP_FREE);


    map_draw(robot_y,robot_x);
	system("pause");
	sleep(1);

	while ( !bot_winner(robot_y,robot_x) ) ///fin quando il robot non si trova nella zona di "vittoria" fallo muovere
	{
		bot_move(&robot_y,&robot_x);
		map_draw(robot_y,robot_x);
		system("pause");
		sleep(1);
	}

	printf("\n\nGood Bot\n\n");

    system("pause");

	return 0;
}
