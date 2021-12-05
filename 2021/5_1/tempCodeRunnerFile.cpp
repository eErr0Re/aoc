    else if (x1 != x2)
        {
            while (x_asc ? x1 <= x2 : x2 <= x1)
            {
                ++field[y1][x1];
                x_asc ? ++x1 : --x1;
            }
        }
        else
        {
            while (y_asc ? y1 <= y2 : y2 <= y1)
                ++field[y1][x1];
                y_asc ? ++y1 : --y1;
        }