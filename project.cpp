//This program is for a player-vs-AI dice rolling game.
//The user will enter how many rounds they want to play, and three dice will be rolled
//in order to determine the target number for the round. The user will then get to pick
//how many dice they want to roll in order to achieve the target number or get as close 
//as possible. The winner of each round gets a point and the overall winner will be
//whomever gets the most points at the end of the game. The user can then play again.  

#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cctype>
//this library is included so we can use usleep() to delay the output for the user
//just a user experience implementation
#include <unistd.h>

const int diceside = 6;
const int targetroll = 3;
int roundnum = 0;
const int X = 1000000;
const int Y = 2000000;


//This displays the welcome message as asks the user how many rounds they want to play
int welcome();
//This is the main body of the game, will return true if the player won, false if lost
bool playgame(int round);
//This function rolls the die
int rolldie(int numrolls);

int main()
{
    int wincount = 0;
    int aicount = 0;
    printf("\n");
    srand(time(NULL));
    roundnum = welcome();
    printf("Ok! You wanna play %d rounds? Let's get started!\n\n", roundnum);
    usleep(X);
    for (int x = 1; x <= roundnum; x++)
    {
        //This calls playgame and returns true if the player won or false if lost
        bool gameresult = playgame(x);
        //If the player won this will update their score
        if (gameresult == true)
        {
            printf("Congratulations! You won the round :)\n\n");
            usleep(X);
            wincount ++;
            printf("::::The current score is > Player: %d  AI: %d::::\n\n", wincount, aicount);
            usleep(X);
        //if the AI won this will update their score
        } else if (gameresult == false)
        {
            printf("The AI beat you! You lost the round :(\n\n");
            usleep(X);
            aicount ++;
            printf("::::The current score is > Player: %d  AI: %d::::\n\n", wincount, aicount);
            usleep(X);
        }
    }
    //USER WINS
    if (wincount > aicount)
    {
	    int YorN = 0;
	    printf("$ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $\n");
	    printf("\n");
	    printf("YOU BEAT THE AI!!! You must be really smart or somethin\n");
	    printf("\n");
	    printf("$ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $\n");
        printf("\n");
        usleep(X);
        printf("PLAY AGAIN? (ENTER '1' FOR YES OR '0' FOR NO)\n");
        scanf("%d", &YorN);
	    if (YorN == 1)
	    {   
	        printf("You wanna play again? Okay! Let's do this!\n");
	        usleep(Y);
	        main();
	    }
    //AI WINS
    } else if (wincount < aicount)
    {
	    int YorN1 = 0;
	    printf(":( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :(\n");
	    printf("\n");
	    printf("THE AI WON!!! Guess that spells the end of humanity.....\n");
	    printf("\n");
    	printf(":( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :( :(\n");
        printf("\n");
        usleep(X);
        printf("PLAY AGAIN? (ENTER '1' FOR YES OR '0' FOR NO)\n");
	    scanf("%d", &YorN1);
	    if (YorN1 == 1)
	    {
	        printf("You wanna play again? Okay! Let's do this!\n");
	        main();
        }
    }
    return 0;
}

bool playgame(int round)
{
    printf("ROUND %d!\n", round);
    printf("--------------------------------------------------------------------------\n");
    usleep(Y);
    printf("The target for this round will be...\n");
    usleep(X);
    //rolling for target value
    printf("*%d dice are rolled*\n\n", targetroll);
    usleep(X);
    int target = rolldie(targetroll);
    printf("[ %d ]\n", target);
    //prompt user to enter the amount of rolls they want
    printf("How many dice would you like to roll to reach the target of %d?\n", target);
    usleep(X);
    int userroll = 0;
    scanf("%d", &userroll);
    //rolls and computes the total based on how many rolls the user wanted
    int usertotal = rolldie(userroll);
    printf("You roll %d die for a total of %d\n\n", userroll, usertotal);
    usleep(X);
    //AI roll
    int airoll = target / 4; 
    int aitotal = rolldie(airoll);
    printf("The AI rolls %d die for a total of %d\n\n", airoll, aitotal);
    usleep(X);
    //THE PLAYERS GOT THE SAME VALUE
    if (aitotal == usertotal)
    {
        printf("Huh, you and the AI both got %d... lets try that again\n", aitotal);
        printf("Remember, we must have a champion!!!\n\n");
        usleep(X);
        //recursive playgame 
        playgame(round);
    }
    //THE USER GOT THE TARGET
    if (usertotal == target)
    {
	    return true;
    }
    //THE AI GOT THE TARGET
    if (aitotal == target)
    {
	    return false;
    }
    //BOTH PLAYERS GO OVER THE TARGET
    if ((usertotal > target) && (aitotal > target))
    {
	    printf("Huh, you and the AI both went over the target! Couple of over-achievers\n");
        printf("We'll have to try that round again.\n\n");
        usleep(X);
        //recursive playgame
	    playgame(round);
    }
    //USER GOES OVER
    if ((usertotal > target) && (aitotal <= target))
    {
	    return false;
    }
    //AI GOES OVER
    if ((aitotal > target) && (usertotal <= target))
    {
	    return true;
    }
    //USER IS CLOSER
    if ((target - aitotal) > (target - usertotal))
    {
        return true;
    } 
    //AI IS CLOSER
    if ((target - aitotal) < (target - usertotal))
    {
	    return false;
    }
    return false;
}

int rolldie(int numrolls)
{
    int total = 0; 
    for (int x = 1; x <= numrolls; x++)
    {
	    int dienum = (1 + rand() % diceside);
	    total = total + dienum;
    }
    return total;
}

//welcome message as well as gathering how many rounds we'll play
int welcome()
{
    //apologies if this looks messy, just really wanted to implement this
    printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("Can you beat the AI?\n\n");
    usleep(Y);
    printf("The object of the game is to beat the AI by rolling a number of dice\n");
    printf("determined by you, in order to get as close to the round target as possible\n");
    printf("without going over. The target will be determined each round with a\n");
    printf("%d dice roll, putting the target in the range 3-18\n\n", targetroll);
    usleep(Y);
    printf("Each round the winner will be awarded a point which will add\n");
    printf("up to a final score determining the overall winner! Goodluck!\n\n");
    printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    usleep(Y);
    //This is where the user enters the number of rounds they want to play
    printf("Firstly we need to pick the number of rounds you wish to play! Enter below:\n");
    printf("(psst... make sure it's odd, we must have a champion!!)\n");
    int round = 0;
    scanf("%d", &round);
    while ((round % 2) == 0) //they entered an even number of rounds
    {
        printf("Hey! That wasn't an odd number :( Remember, we must have a champion!!\n");
	    printf("I'll give you another chance... only because im such a nice videogame\n");
	    scanf("%d", &round);
    }
    return round;
}



