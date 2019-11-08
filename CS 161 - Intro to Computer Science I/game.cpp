#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int  main()
{
	int num, rnum;
	cout << "It's time for adventure. You are in a camp in the Amazon Rainforest." << endl;
	cout << "You look around and see a river and a bridge. Where do you want to go? (1 - river, 2 - bridge)" << endl;
	cin >> num;
	if(num == 1)
	{
		cout << "You are at a river." << endl;
		cout << "There's a jungle across the river and a swamp near by. Where do you want to go? (1 - jungle, 2 - swamp)" << endl;
		cin >> num;
		srand(time(NULL));
		rnum = rand()%2;
		if (num == 1)
		{
			if (rnum == 0)
			{
				cout << "You drowned trying to swim across the river." << endl;
			}
			else if (rnum == 1)
			{
				cout << "You made it across the river and see the jungle up ahead." << endl;
				cout << "From the jungle, you see a temple and a cave nearby. Where do you want to go? (1 - cave, 2 - temple)" << endl;
				cin >> num;
				if (num == 1)
				{
					cout << "You enter the cave and get eatten by a bear." << endl;
				}
				else if (num == 2)
				{	
					cout << "You enter the temple and see a chest full of a gold in the corner." << endl;
					cout << "You win." << endl;
				}
			}
		}
		else if (num == 2)
		{
			cout << "You are at a swamp." << endl;
			cout << "At the swamp, you see a forest and a jungle. Where do you want to go? (1 - forest, 2 - jungle)" << endl;
			cin >> num;
			if(num == 1)
			{
				cout << "You get lost in the forest and starve to death." << endl;
			}		
			else if (num == 2)
			{
				cout << "You enter the jungle." << endl;
				cout << "From the jungle, you see a temple and a cave nearby. Where do you want to go? (1 - cave, 2 - temple)" << endl;
				cin >> num;
				if (num == 1)
				{
					cout << "You enter the cave and get eatten by a bear." << endl;
				}
				else if (num == 2)
				{	
					cout << "You enter the temple and see a chest full of a gold in the corner." << endl;
					cout << "You win." << endl;
				}
			}
		}
	}
	else if(num == 2)
	{
		cout << "You are at a bridge." << endl;
			cout << "From the bridge you see a jungle and a ravine nearby. Where do you want to go (1 - jungle, 2 - ravine)" << endl;
		cin >> num;
		if (num == 1)
		{
			cout << "From the jungle, you see a temple and a cave nearby. Where do you want to go? (1 - cave, 2 - temple)" << endl;
			cin >> num;
			if (num == 1)
			{
				cout << "You enter the cave and get eatten by a bear." << endl;
			}
			else if (num == 2)
			{	
				cout << "You enter the temple and see a chest full of a gold in the corner." << endl;
				cout << "You win." << endl;
			}
		}
		else if (num == 2)
			cout << "You slip and fall into the ravine and die." << endl;
	}
	return 0;
}
