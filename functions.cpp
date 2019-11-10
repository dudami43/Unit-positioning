#include <bits/stdc++.h>
#include "functions.h"

int coversPoint(int position, int destiny, int time, double speed, std::vector<std::vector<int>>& weight_matrix)
{
    if((weight_matrix[position][destiny]/speed) <= time)
        return 1;
    return 0;
}