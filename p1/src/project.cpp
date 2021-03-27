#include <iostream>
#include <chrono>

using namespace std;

int main()
{

    // Get starting timepoint
    auto start = std::chrono::high_resolution_clock::now();

    // algorithm begin
    // algorithm finish

    // Get ending timepoint
    auto stop = std::chrono::high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get durarion. To cast it to proper unit
    // use duration cast method
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    cout << duration.count() << endl;

    return 0;
}
