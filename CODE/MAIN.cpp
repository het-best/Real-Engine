


// ENGINE FILES
#include "MAIN_CYCLE.cpp"

int main()
{
    /*
        101 - WAS CLOSED BY CLOSE BUTTON
        102 - WAS CLOSED BY ESCAPE KEY
    */

    #ifdef DEBUGGING
        std::thread debugging_thread{ ENGINE_DEBUGGING::run };
    #endif

    int exit_code = ENGINE_MAIN_CYCLE::MAIN_CYCLE();

    #ifdef DEBUGGING
        debugging_thread.join();
    #endif

    cout << "EXIT CODE: " << exit_code << endl;
    cout << "EXIT INFORMATION: " << endl;

    ifstream file("exit.log");
    string exit_line;
    while (getline(file, exit_line)) {
        cout << exit_line << endl;
    }
    file.close();
    
    cout << endl;
}
