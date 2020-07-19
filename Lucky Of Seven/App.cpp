#include <iostream>
#include <string>
#include <ctime>

struct vars { //creating a struct for the public variables to be used in all functions.
	double amountofmoney = 0, maxmoney = 0, beginmoney = 0;
	int rand1 = 0, rand2 = 0, randsum = 0, rn = 1, rndwin = 0, rndlose = 0;
	char cont = 'Y', exit = 'N';
};
//defining the functions to the compiler that those functions are exist.
void rndwin(double& beginmoney, double& maxmoney, int& rn, int& rndwin);
void rndcont(double& beginmoney, double& maxmoney, char& cont);
void rndlost(double& beginmoney, int& rn, int& rndlose);
void gamesummary(double& beginmoney, double& maxmoney, int& rn, int& rndwin);
void diceroll(int& rand1, int& rand2, int& randsum);
void deposit(double& beginmoney, double& amountofmoney, char& exit);


vars v;//defining the struct to be used in all the functions with the same name.

int main()
{
	srand(time(NULL));
	do {
		/*set all the variable to 0 if the player starts a new game!*/
		v.amountofmoney = 0, v.maxmoney = 0, v.beginmoney = 0;
		v.rand1 = 0, v.rand2 = 0, v.randsum = 0, v.rn = 1, v.rndwin = 0, v.rndlose = 0;
		/*------------------------------------------------------------------------------*/

		deposit(v.beginmoney, v.amountofmoney, v.exit);

		for (; v.beginmoney >= 1;) /*the game continues rolling dice until the player's money gets 0*/
		{
			diceroll(v.rand1, v.rand2, v.randsum);/*the game will again roll the dice. in case if the player wills to continue the game.*/
			if (v.cont == 'n' || v.cont == 'N') { break; } /*checking if the player still wants to play or not. if not the loop breaks and shows the summary.*/

			else //if the player wants to continue the game.
			{
				if (v.randsum == 7) //the player wins the round.
				{
					rndwin(v.beginmoney, v.maxmoney, v.rn, v.rndwin); //calling function.
					diceroll(v.rand1, v.rand2, v.randsum);/*the game will again roll the dice. in case if the player wills to continue the game.*/

					if (v.beginmoney > v.amountofmoney) /*checking if the player wins more money than the amount that the player deposited*/
					{
						rndcont(v.beginmoney, v.maxmoney, v.cont); //calling function.
						if (v.cont == 'n' || v.cont == 'N') { break; } /*checking if the player still wants to continue if not the loop breaks and shows the summary.*/
						else { rndlost(v.beginmoney, v.rn, v.rndlose); } /*if the player continue it will roll the dice and calls the lose function to do the actions.*/
					}
				}
				else //if the player doesn't get 7 in the addition of both dice dots.
				{
					rndlost(v.beginmoney, v.rn, v.rndlose); //calling function.
					if (v.beginmoney == 0) { break; }/*if the player has 0 money the game ends and shows the summary.*/
					else/*if the player has more than $1 the game continues.*/
					{
						diceroll(v.rand1, v.rand2, v.randsum);/*the game will again roll the dice. in case if the player wills to continue the game.*/

					}
				}
			}
		}
		gamesummary(v.beginmoney, v.maxmoney, v.rn, v.rndwin); //calling function.
		std::cout << std::endl << "if you want to start a new game type (D): "; /*if the player wants to start a new game*/
		std::cin >> v.exit;
		/*---------------------------------------------------------------------------------*/
	} while (v.exit == 'D' || v.exit == 'd'); //using abbreviation of deposit to start a new game.


}

void deposit(double& beginmoney, double& amountofmoney, char& exit)
{
	v.cont = 'Y';  //to reset the game to continue.
	v.exit = 'N'; //to start a new game.
	std::cout << "Deposit a desired amount of money you want to start the game. $";
	std::cin >> v.beginmoney; //deposit variable.
	v.amountofmoney = v.beginmoney; //deposit amount of money will be saved in the memory.	
}

void diceroll(int& rand1, int& rand2, int& randsum)
{
	/*this function is used to roll the dice randomly.*/
	do {
		v.rand1 = (rand() % 6) + 1;
		v.rand2 = (rand() % 6) + 1;
		v.randsum = v.rand1 + v.rand2;

	} while (v.randsum > 12);
}

void rndwin(double& beginmoney, double& maxmoney, int& rn, int& rndwin)
{
	/*this function is used if the player wins the round.*/
	std::cout << "\n------------------------\n" << "Roll Number: " << v.rn << "\nYou've won $4.";
	v.beginmoney += 4;
	v.maxmoney += 4;
	v.rndwin++;
	v.rn++;
	std::cout << "\nMaximum money you won: $" << v.maxmoney << " And it tooks " << v.rn - 1 << " Rolls to win that amount of money." << "\nRemaining Balance: $" << v.beginmoney;
}

void rndcont(double& beginmoney, double& maxmoney, char& cont) {
	/*this function is used if the player wants to continue the match.*/

	std::cout << "\n------------------------\n" << "DO YOU WANT TO CONTINUE?\n" << R"(Amount of money you won: $)" << v.maxmoney << std::endl << R"(Deposit Amount: $)" << v.amountofmoney << std::endl << R"(Current Balanace: $)" << v.beginmoney << std::endl << R"(Do you want to continue? type Y for yes, N for No. )";
	std::cin >> v.cont;

}

void rndlost(double& beginmoney, int& rn, int& rndlose)
{
	/*this function is used if the player loses the round.*/

	std::cout << "\n------------------------\n" << "Number of Rolls: " << v.rn << "\nYou've lost $1.";
	v.beginmoney -= 1;
	v.rn++;
	v.rndlose++;
	std::cout << "\nRemaining Balance: $" << v.beginmoney;
}

void gamesummary(double& beginmoney, double& maxmoney, int& rn, int& rndwin) {
	/*this function is used if the player ends the match. and shows a summary of the matches the player played.*/

	std::cout << "\n--------------------------------\n"
		<< "\nTHE GAME ENDED." << "\nHere is summary of your Game: " << "\n--------------------------------\n" << "Current Balance: $" << v.beginmoney << "\nDeposit Amount: $" << v.amountofmoney << "\nMaximum money you won: $" << v.maxmoney << "\nNumber of Rolls you played: " << v.rn - 1 << "\nNumber of Rolls you won: " << v.rndwin << "\nNumber of Rolls you lost: " << v.rndlose << std::endl;
	system("pause"); //to stop the console and let the player sees their status about the matches the player played.
}