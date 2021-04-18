#include <iostream>
#include <string>
#include <ctype.h>
#include <cstdlib>

using namespace std;

/**
 * define the gobal variables used in file
 */
typedef struct CarDrive
{
    string password;        //The variable saves the user-entered password
    int gearChoice;          //The variable saves the user's choice on menu Gearbox
    int controlChoice;       //The variable saves the user's choice R or D on menu Gearbox
    int speed;                 //The variable saves current speed
    bool isDrive;              //The variable saves the state of the Gearbox is D (Drive) mode or not

};
CarDrive car;   //define alter name for CarDrive

/**
 * Forward declaration for functions used in file
 */
void displayNotification();
void gearBoxMenu();
void controlMenu();
void setSpeed();



/** Main Function */
int main()
{

    //declare default password
    string defaultPassword = "12345678";

    //Require user enter the password
    cout << "NHAP MA SO CA NHAN: ";
    cin >> car.password;

    //If user-entered not match with default password then must enter password again
    while(defaultPassword.compare(car.password) != 0)
    {
        system("cls");
        cout << "MA SO CA NHAN KHONG DUNG, VUI LONG NHAP LAI" << endl;
        cout << "NHAP MA SO CA NHAN: ";
        cin >> car.password;
    }

    //Clear screen
    system("cls");
    cout << "XIN CHAO " << car.password << endl;
    car.speed = 0;

    //Show Gearbox menu
    //Over and over again constantly until user choice POWER OFF
     do
    {
        gearBoxMenu();

        //The cases user was chose
        switch (car.gearChoice)
        {
        case 1:     //case 1: P (Park)
            //Clear screen
            system("cls");

            if (car.speed > 0)
            {
                cout << "HAY CHAC CHAN XE DA DUNG VA VAN TOC LA 0 KM/H \n" << endl;
                break;
            }
            else
            {
                cout << "DA VE SO P." << endl;
                cout << "CHU Y SU DUNG PHANH TAY DE DAM BAO AN TOAN \n" << endl;
            }
            break;

        case 2:   //case 2: R (Reverse)
            //Clear screen
            system("cls");
            //Over and over again constantly until user choice Back to Gearbox menu
            do
            {
                //Check the state of car is D (Drive) mode or not
                //if is D mode then show Warning message
                if(car.isDrive && car.speed > 0)
                {
                    //Clear screen
                    system("cls");
                    //show warning message
                    cout << "XE DANG CHAY TIEN TOI\n" << endl;
                }
                else    //If is not D mode then do code below
                {
                    //Check the car is changing gears between Reverse and Drive or not
                    //If the speed is 0 and dose not is speed up or brake then set speed to 7 Km/h
                    if (car.speed == 0 && car.controlChoice != 2 && car.controlChoice != 3)
                    {
                        car.speed = 7;
                        //set state D mode to false
                        car.isDrive = false;
                        cout << "----  TOC DO HIEN TAI LA: " << car.speed << " Km/h\n" << endl;
                    }
                    else        //car has not been stopped
                    {
                        //set state D mode to false
                        car.isDrive = false;
                        //show information about current speed
                        displayNotification();
                    }

                    //show Menu D or R mode
                    controlMenu();
                    //set speed for car
                    setSpeed();
                }
            }
            while (car.controlChoice != 4);
            break;

        case 3:   //case 3: N (Neutral)
            //Clear screen
            system("cls");

            //Check speed is 0 Km/h or not
            //if is not 0 Km/h then show warning
            if (car.speed > 0)
            {
                cout << "HAY CHAC CHAN XE DA DUNG VA VAN TOC LA 0 KM/H\n" << endl;
                break;
            }
            else    //case the speed is 0 Km/h
            {
                cout << "DA VE SO N.\n" << endl;
            }
            break;

        case 4:     //case 4: D (Drive)
            //Clear screen
            system("cls");

            //Over and over again constantly until user choice Back to Gearbox menu
            do
            {
                //Check the state of car is R (Reverse) mode or not
                //if is R mode then show Warning message
                if(!car.isDrive && car.speed > 0)
                {
                    //Clear screen
                    system("cls");
                    //show warning message
                    cout << "XE DANG CHAY LUI\n" << endl;
                }
                else    //If is not D mode then do code below
                {
                    //Check the car is changing gears between Reverse and Drive or not
                    //If the speed is 0 and dose not is speed up or brake then set speed to 7 Km/h
                    if (car.speed == 0 && car.controlChoice != 3 && car.controlChoice != 2)
                    {
                        car.speed = 7;
                        car.isDrive = true;
                        cout << "----  TOC DO HIEN TAI LA: " << car.speed << " Km/h\n" << endl;
                    }
                    else        //car has not been stopped
                    {
                        //set state D mode to false
                        car.isDrive = true;
                        //show information about current speed
                        displayNotification();
                    }

                    //show Menu D or R mode
                    controlMenu();
                    //set speed for car
                    setSpeed();
                }
            }
            while (car.controlChoice != 4);
            break;

        case 5:     //case 5: POWER OFF
            //Clear screen
            system("cls");
            break;

        default:    //Throw warning when user does not choice from 1 to 5
            //Clear screen
            system("cls");
            //show warning message
            cout << "VUI LONG CHON TU 1 DEN 5\n" << endl;
            break;
        }
    }
    while (car.gearChoice != 5);

    //show goodbye notice
    cout << "*---------------- POWER OFF ---------------*" << endl;
    cout << "*                                          *" << endl;
    cout << "*      CAM ON VI DA SU DUNG PHAN MEM       *" << endl;
    cout << "*                                          *" << endl;
    cout << "********************************************" << endl;

    return 0;
}



/** All Function used in this file */

/**
 * Function display the notification about speed to screen
 */
void displayNotification()
{
    //display for R (Reverse) mode
    if ( !car.isDrive )
    {
        //Warning when speed over 20 Km/h
        if (car.speed > 20)
        {
            cout << "----  TOC DO HIEN TAI LA: " << car.speed << " Km/n" << endl;
            cout << "TOC DO NGUY HIEM, BAN NEN GIAM TOC DO\n" << endl;
        }
        else    //Notify when speed not more than 20 Km/h
        {
            cout << " ----  TOC DO HIEN TAI LA: " << car.speed << " Km/h\n" << endl;
        }
    }
    else    //display for D (Drive) mode
    {
        //Warning when speed over 60 Km/h
        if (car.speed > 60)
        {
            cout << "----  TOC DO HIEN TAI LA: " << car.speed << " Km/n" << endl;
            cout << "TOC DO NGUY HIEM, BAN NEN GIAM TOC DO\n" << endl;
        }
        else    //Notify when speed not more than 60 Km/h
        {
            cout << " ----  TOC DO HIEN TAI LA: " << car.speed << " Km/h\n" << endl;
        }
    }
}

/**
 * Function display the Gearbox menu
 */
void gearBoxMenu()
{
    //The variable saves the state of Gearbox
    //is the first time show Gearbox Menu or not
    bool isFirstTime = true;

    //Show menu and require user enter the choice
    //If user-entered is not digit then do this again
    do
    {
        //if does not the first time show menu then clear screen
        if (!isFirstTime)
        {
            system("cls");
        }

        //The case user input not a digit
        if ( cin.fail() )
        {
            cout <<"VUI LONG CHI NHAP SO \n" << endl;
        }

        //If is the first time show menu then set variable to False
        isFirstTime = false;
        //Reset the failed state
        cin.clear();
        //Cleans cache when user press Enter or enough 256 characters
        cin.ignore(256, '\n');

        //Show menu and require user enter the choice
        cout << "XIN MOI LUA CHON: " << endl;
        cout << "1. P" << endl;
        cout << "2. R" << endl;
        cout << "3. N" << endl;
        cout << "4. D" << endl;
        cout << "5. POWER OFF" << endl;
        cout << ">> ";
        cin >> car.gearChoice;
    }
    while (cin.fail());
}

/**
 * Function display Control Menu when user choice D or R on the Gearbox menu
 */
void controlMenu()
{
    //Show menu and require user enter the choice
    //If user-entered is not digit then do this again
    do
    {
        //The case user input not a digit
        if ( cin.fail() )
        {
            system("cls");
            cout <<"VUI LONG CHI NHAP SO\n" << endl;
            displayNotification();
        }

        //Reset the failed state
        cin.clear();
        //Cleans cache when user press Enter or enough 256 characters
        cin.ignore(256, '\n');

        //Show menu and require user enter the choice
        cout <<"MOI LUA CHON: " << endl;
        cout << "1. TANG TOC" << endl;
        cout << "2. GIAM TOC" << endl;
        cout << "3. PHANH" << endl;
        cout << "4. TRO VE MENU" << endl;
        cout << ">> ";
        cin >> car.controlChoice;
    }
    while ( cin.fail());
}

/**
 * Function set the speed of the car follow the user's choice on Control Menu (R mode or D mode)
 */
void setSpeed()
{
    //the cases user was chose in Control Menu
    switch (car.controlChoice)
    {

    case 1:   //case 1 speed up

        //speed up to 5 Km/h
        car.speed += 5;
        //Clear screen
        system("cls");
        break;

    case 2:   //case 2: speed down

        //speed down to 5 Km/h and check the speed after speed down
        //If less than 0 Km/h, set speed to 0 Km/h
        //If greater than 0, do nothing
        (car.speed -= 5) < 0 ? car.speed = 0 : car.speed = car.speed;

        //Clear screen
        system("cls");
        break;

    case 3:   //case 3: Brake
        //set speed to 0 Km/h
        car.speed = 0;

        //Clear screen
        system("cls");
        break;

    case 4:     //case 4: Back to Gearbox menu
        //clear screen and do nothing
        system("cls");
        break;

    default:    //Throw warning when user does not choice from 1 to 4
        //Clear screen
        system("cls");

        cout << "VUI LONG CHON TU 1 DEN 4\n" << endl;
        break;
    }
}
