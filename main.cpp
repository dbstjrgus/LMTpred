
#include <chrono>
#include <thread>
#include "apiaccess.h"
#include "circularDeque.h"

/**
 * The project uses alphavantage stock api, with time series of 5 minutes.
 * The premises is built around that so lets not change it advocating for too much flexibilities
 * Thanks
 */


// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    std::string exampleTime = "2025-05-09 12:05:00";
    std::string exampleSection = "3. low";

    circularDeque<int> deque(6);
    deque.insertBack(5);
    deque.insertFront(4);

    deque.print();


/**
    while (true) {
        printRawJson(target);
        retrievePrice(exampleTime, exampleSection);
        return 0;
    }
    */

}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.