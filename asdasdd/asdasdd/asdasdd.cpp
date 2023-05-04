#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;

    vector<int> teheneszetek(N), choices(N, -1), caps(M), result(N);
    vector<vector<int>> prices(N, vector<int>(M));

    for (int i = 0; i < N; i++)
        cin >> teheneszetek[i];
    for (int i = 0; i < M; i++)
        cin >> caps[i];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> prices[i][j];

    int i = 0, min_price = INT_MAX;
    while (i >= 0)
    {
        if (i >= N)
        {
            // calc price
            int total = 0;
            for (int j = 0; j < N; j++)
                total += prices[j][choices[j]] * teheneszetek[j];

            if (total < min_price)
            {
                min_price = total;
                for (int j = 0; j < N; j++)
                    result[j] = choices[j] + 1;
            }

            i--;
            caps[choices[i]] += teheneszetek[i];
            choices[i] = -1;
            i--;
            caps[choices[i]] += teheneszetek[i];
            continue;
        }

        while (1)
        {
            choices[i]++;
            if (choices[i] >= M || caps[choices[i]] - teheneszetek[i] >= 0)
                break;
        }

        if (choices[i] < M)
        {
            caps[choices[i]] -= teheneszetek[i];
            i++;
        }
        else
        {
            choices[i] = -1;
            i--;
            if (i < 0) break;
            caps[choices[i]] += teheneszetek[i];
        }
    }

    std::cout << min_price << "\n";
    for (auto& e : result)
        std::cout << e << " ";
    std::cout << "\n";
}