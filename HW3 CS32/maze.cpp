//Jonathan Goh
//CS32 HW3



bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    if(sr == er && sc == ec)
    {
        return true;
    }
    
    maze[sr][sc] = '$';
    
    //Direction north
    if(sr!=0 && maze[sr-1][sc]!='$' && maze[sr-1][sc]!='X')
    {
        if(pathExists(maze, sr-1, sc, er, ec))
        {
            return true;
        }
    }
    
    //Direction east
    if(sc!=9 && maze[sr][sc+1]!='$' && maze[sr][sc+1]!='X')
    {
        if(pathExists(maze, sr, sc+1, er, ec))
        {
            return true;
        }
    }
    
    //Direction south
    if(sr!=9 && maze[sr+1][sc]!='$' && maze[sr+1][sc]!='X')
    {
        if(pathExists(maze, sr+1, sc, er, ec))
        {
            return true;
        }
    }
    
    //Direction west
    if(sc!=0 && maze[sr][sc-1]!='$' && maze[sr][sc-1]!='X')
    {
        if(pathExists(maze, sr, sc-1, er, ec))
        {
            return true;
        }
    }
    
    return false;
}

