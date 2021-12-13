if (dir == 'x')
        {
            int new_size = max(x_size - val - 1, val);
            vector<vector<bool>> temp(y_size, vector<bool>(new_size, 0));
            if (val < x_size / 2)
            {
                for (int i = 0; i < y_size; ++i)
                    for (int j = 0, k = x_size - 1; k > val; --k, ++j)
                    {
                        if (k >= paper[i].size())
                            continue;
                        temp[i][j] = paper[i][k];
                    }

                for (int i = 0; i < y_size; ++i)
                    for (int j = new_size - val, k = 0; k < paper[i].size(); ++j, ++k)
                        temp[i][j] = temp[i][j] | paper[i][k];
            }
            else
            {
                for (int i = 0; i < y_size; ++i)
                    for (int j = 0; j < val && j < paper[i].size(); ++j)
                        temp[i][j] = paper[i][j];

                for (int i = 0; i < y_size; ++i)
                    for (int j = new_size - 1, k = val + 1; k < paper[i].size(); --j, ++k)
                        temp[i][j] = temp[i][j] | paper[i][k];
            }
            x_size = new_size;
            paper = temp;
        }