#include "Files.h"
/*
the .sfg are just text files I have given a different extension so it looksa like they cannot be opened
with a text file however they are pre-loadded in the solution and can be edited using Notepad++
this is not recomended as it will lead to levels not being correct and therefore the game impossible
*/
CFiles* CFiles::file=NULL;

CFiles::CFiles(void)
{
}


CFiles::~CFiles(void)
{
}

CFiles* CFiles::Inst()
{
	if(file == NULL)
	{
		file = new CFiles;
	}
	return file;
}

//takes level as input from world model
void CFiles::load_level(int a)
{
    load_horis(a);
	load_verts(a);
	load_enemy(a);
}
//takes level as input from load_level()
void CFiles::load_horis(int a)
{
	std::string entry;
	switch (a)
	{
		case 1:entry="files/horizontal_1.sfg";break;
		case 2:entry="files/horizontal_2.sfg";break;
		case 3:entry="files/horizontal_3.sfg";break;
		case 4:entry="files/horizontal_4.sfg";break;
		case 5:entry="files/horizontal_5.sfg";break;
	}
	std::ifstream input(entry,std::ios::in);
    int count=0;
    while(!input.eof())
    {
        input>>hor_x[count]>>hor_y[count];
        count++;
    }
	input.clear();
    input.close();
}

//takes level as input from load_level()
void CFiles::load_verts(int a)
{
	std::string entry;
	switch (a)
	{
		case 1:entry="files/vertical_1.sfg";break;
		case 2:entry="files/vertical_2.sfg";break;
		case 3:entry="files/vertical_3.sfg";break;
		case 4:entry="files/vertical_4.sfg";break;
		case 5:entry="files/vertical_5.sfg";break;
	}
	std::ifstream input(entry,std::ios::in);
	int count=0;
	while(!input.eof())
	{
		input>>vert_x[count]>>vert_y[count];
		count++;
	}
	input.clear();
	input.close();
}

//takes level as input from load_level()
void CFiles::load_enemy(int a)
{	
	std::string entry;
	switch (a)
	{
		case 1:entry="files/enemy_1.sfg";break;
		case 2:entry="files/enemy_2.sfg";break;
		case 3:entry="files/enemy_3.sfg";break;
		case 4:entry="files/enemy_4.sfg";break;
		case 5:entry="files/enemy_5.sfg";break;
	}
	std::ifstream input(entry,std::ios::in);
	int count=0;
	while(!input.eof())
	{
		input>>enemy_x[count]>>enemy_y[count]>>enemy_id[count];
		count++;
	}
	input.close();
}


void CFiles::load_scores()
{
    std::ifstream input("files/scores.sfg",std::ios::in);
    int count=0;
    while(!input.eof())
    {
        input>>name[count]>>points[count];
        count++;
    }
    input.close();
}

//the get_hor functions are used at the same time to get a x and y value
const int CFiles::get_hor_x(int x)
{
    return (hor_x[x]*128);
}

const int CFiles::get_hor_y(int y)
{
    return 280-(hor_y[y]*85);
}

//the get_vert functions are used at the same time to get a x and y value
const int CFiles::get_vert_x(int x)
{
    return (vert_x[x]*128)-4;
}

const int CFiles::get_vert_y(int y)
{
    return 210-(vert_y[y]*85);
}

//the get_hor functions are used at the same time to get a x and y position as well as an id
const int CFiles::get_ene_x(int x)
{
    return (enemy_x[x]*128)+45;
}

const int CFiles::get_ene_y(int y)
{
    return 280-(enemy_y[y]*85)-62;
}

const int CFiles::get_ene_id(int z)
{
	return enemy_id[z];
}

//the get_name and get points functions are used at the same time to get them inline on the table
const std::string CFiles::get_name(int a)
{
	return name[a];
}

const int CFiles::get_points(int a)
{
	return points[a];
}

void CFiles::set_high_score(std::string n,int p)
{
	for(int a=0; a<10; a++)
	{
		if(p > points[a])
		{
			
			for( int j=8; j>a ;j--)
			{
				points[j+1]=points[j];
				name[j+1]=name[j];
			}
			points[a]=p;
			name[a]=n;
			break;
		}
	}
}

void CFiles::save_scores()
{
    std::ofstream output;

    output.open("files/scores.sfg",std::ios::trunc);

    output<<name[0]<<" "<< points[0] <<std::endl;
    output<<name[1]<<" "<< points[1] <<std::endl;
    output<<name[2]<<" "<< points[2] <<std::endl;
    output<<name[3]<<" "<< points[3] <<std::endl;
    output<<name[4]<<" "<< points[4] <<std::endl;
    output<<name[5]<<" "<< points[5] <<std::endl;
    output<<name[6]<<" "<< points[6] <<std::endl;
    output<<name[7]<<" "<< points[7] <<std::endl;
    output<<name[8]<<" "<< points[8] <<std::endl;
    output<<name[9]<<" "<< points[9] ;

    output.close();
}


