/*Time solution Project by UziBytes*/
/*This code is designed only for windows machine*/

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include<conio.h>
#include<windows.h>

using namespace std;

void liveClock()
{
restart_clock:
    int sec_prev = 0;
    cout << "\033[2J\033[1;1H";     //Clears the Screen
    cout << "\n\nPress any key to start the Live Clock : ";
    getch();
    fflush(stdin);
    while (!kbhit())    //Runs the code till keyboard press is detected
    {
        int seconds, minutes, hours;
        string mer;
        time_t total_seconds = time(0);
        struct tm *ct = localtime(&total_seconds);
        seconds = ct->tm_sec;
        minutes = ct->tm_min;
        hours = ct->tm_hour;
        if (hours >= 12)
            mer = "PM";
        else
            mer = "AM";
        hours = hours > 12 ? hours - 12 : hours;
        if (seconds == sec_prev + 1 || (sec_prev == 59 && seconds == 0))
        {
            cout << "\033[2J\033[1;1H";
            cout << "\n"
                 << (hours < 10 ? "0" : "") << hours << ":" << (minutes < 10 ? "0" : "") << minutes << ":" << (seconds < 10 ? "0" : "") << seconds << " " << mer << "\n";
            cout << "Press any key to end clock\n";
        }
        sec_prev = seconds;
    }
    getch();
    cout << "\033[2J\033[1;1H";
    char key;
    cout << "\n Press '1' to restart the clock : \n";
    cout << " Press any key to return to main menu : \n";
    key = getch();
    if (key == '1')
        goto restart_clock;
}

void timer()
{
reset_timer:
    cout << "\033[2J\033[1;1H";
    int hh, mm, ss;
    char xd;
    cout << "**SET TIMER**\n\n";
    cout << "Enter hours, minutes and seconds as asked below : ";
    cout << "\nHH: ";
    cin >> hh;
    if (hh > 5)
    {
        cout << "Timer cannot be set for more than 5 hours\n";
        cout << "Press any key to reset the Timer : ";
        fflush(stdin);
        xd = getch();
        goto reset_timer;
    }
    cout << "\nMM: ";
    cin >> mm;
    if (mm >= 60)
    {
        cout << "INVALID Minutes, must be less than 60\n";
        cout << "Press any key to reset the Timer : ";
        fflush(stdin);
        xd = getch();
        goto reset_timer;
    }
    cout << "\nSS: ";
    cin >> ss;
    if (ss >= 60)
    {
        cout << "INVALID Seconds, must be less than 60\n";
        cout << "Press any key to reset the Timer : ";
        fflush(stdin);
        xd = getch();
        goto reset_timer;
    }
    cout << "\033[2J\033[1;1H";
    while (hh-- >= 0)
    {
        while (mm-- >= 0)
        {
            while (ss-- >= 0)
            {
                cout << "______________\n";
                if (hh + 1 < 10 && mm + 1 < 10 && ss + 1 < 10)
                    cout << " 0" << hh + 1 << " : 0" << mm + 1 << " : 0" << ss + 1 << " ";
                else if (hh + 1 < 10 && mm + 1 >= 10 && ss + 1 < 10)
                    cout << " 0" << hh + 1 << " : " << mm + 1 << " : 0" << ss + 1 << " ";
                else if (hh + 1 < 10 && mm + 1 < 10 && ss + 1 >= 10)
                    cout << " 0" << hh + 1 << " : 0" << mm + 1 << " : " << ss + 1 << " ";
                else if (hh + 1 < 10 && mm + 1 >= 10 && ss + 1 >= 10)
                    cout << " 0" << hh + 1 << " : " << mm + 1 << " : " << ss + 1 << " ";
                else
                    cout << " " << hh + 1 << " : " << mm + 1 << " : " << ss + 1 << " ";
                cout << "\n--------------\n";
                sleep(1);   //Sleeps for 1 second
                cout << "\033[2J\033[1;1H";
            }
            ss = 59;    //Reset seconds
        }
        mm = 59;    //Reset minutes
    }
    cout << "**TIMEOUT**\n";
    cout << "\nPress '1' to restart TIMER : ";
    cout << "\nPress any key to return to main menu : ";
    char key;
    fflush(stdin);
    key = getch();
    if (key == '1')
        goto reset_timer;
}

void stopwatch()
{
reset_stopwatch:
    int m = 0, s = 0, h = 0, x = 0;
    cout << "\033[2J\033[1;1H";
    cout << "\n\t Press any key to start the Stopwatch.\n";
    cout << "\n\t  **STOP-WATCH** \n";
    cout << "\n\t\t  HH : MM : SS";

    cout << "\n\t\t  " << h << " : " << m << " : " << s;
    getch();
    fflush(stdin);
    while (!kbhit())
    {
        sleep(1);
        s++;
        if (s > 59)
        {
            m++;
            s = 0;
        }
        if (m > 59)
        {
            h++;
            m = 0;
            s = 0;
        }
        cout << "\033[2J\033[1;1H";
        cout << "\n\t\t - STOP-WATCH\n";
        cout << "\n\t\t Press any key to stop\n\n";
        cout << "\n\t\t HH: MM: SS";
        cout << "\n\t\t " << h << " : " << m << " : " << s;
        cout << "\n";
    }
    getch();
    cout << "\n\t\t Elapsed Time : ";
    cout << "\n\t\t " << h << " : " << m << " : " << s;
    cout << "\nPress '1' to restart STOPWATCH : ";
    cout << "\nPress any key to return to main menu : ";
    char key;
    fflush(stdin);
    key = getch();
    if (key == '1')
        goto reset_stopwatch;
}

void worldclock()
{
    // reset_wc:
    cout << "\033[2J\033[1;1H";
    cout << "Coming soon...\nPress any key to return to main menu : ";
    getch();
}

int main()
{
mainmenu:
    cout << "\033[2J\033[1;1H";
    cout << "** Welcome to <Uzi> Time Management Solutions **\t\t\t" << __DATE__ << "\n\n\n";
    cout << "Press '1' to view live Digital Clock\n";
    cout << "Press '2' to set Timer\n";
    cout << "Press '3' to use Stopwatch\n";
    cout << "Press '4' to view World Clock\n\n";
    int x = -1;
    char ch;
    fflush(stdin);
    cout << "Please Enter your Choice : ";
    ch = getch();
    switch (ch)
    {
    case '1':
        liveClock();
        goto mainmenu;
        break;
    case '2':
        timer();
        goto mainmenu;
        break;
    case '3':
        stopwatch();
        goto mainmenu;
        break;
    case '4':
        worldclock();
        goto mainmenu;
        break;
    default:
        cout << "\033[2J\033[1;1H";
        cout << "\n\n\n\t\t!! INVALID CHOICE !!";
        cout << "\n\nPress any key to return to main menu : ";
        char sd = getch();
        goto mainmenu;
        break;
    }
    return 0;
}

//End of Code