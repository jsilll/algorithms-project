#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
    int n, k;

    scanf("%d %d", &n, &k);

    vector<vector<int>> cpu_costs(2, vector<int>(n, 0));
    vector<vector<int>> com_costs(n, vector<int>(n, 0));

    // filling cpu processing costs matrix
    int cpu0_cost, cpu1_cost;
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &cpu0_cost, &cpu1_cost);
        cpu_costs[0][i] = cpu0_cost;
        cpu_costs[1][i] = cpu1_cost;
    }

    // filling communications costs matrix
    int id1, id2, com_cost;
    for (int i = 0; i < k; i++)
    {
        scanf("%d %d %d", &id1, &id2, &com_cost);
        com_costs[id1 - 1][id2 - 1] = com_cost;
        com_costs[id2 - 1][id1 - 1] = com_cost;
    }

    return 0;
}
