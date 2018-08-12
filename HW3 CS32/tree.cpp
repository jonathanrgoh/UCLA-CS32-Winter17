int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
    if (n2<=0)
    {
        return 1;
    }
    
    if (n2>0 && n1<=0)
    {
        return 0;
    }
    
    if (a1[n1-1]==a2[n2-1])
    {
        return countIncludes(a1, n1-1, a2, n2-1) + countIncludes(a1, n1-1, a2, n2);
    }
    
    else
    {
        return countIncludes(a1, n1-1, a2, n2);
    }
}


void exchange(double& x, double& y)
{
    double t;
    
    t = x;
    x = y;
    y = t;
}

void split(double a[], int n, double splitter, int& firstNotGreater, int& firstLess)
{
    int firstU = 0;
    firstLess = n;
    firstNotGreater = 0;
    
    
    if (n<0)
    {
        n=0;
    }
    
    while (firstU<firstLess)
    {
        if (a[firstU] < splitter)
        {
            firstLess--;
            exchange(a[firstU], a[firstLess]);
        }
        
        else
        {
            if (a[firstU] > splitter)
            {
                exchange(a[firstNotGreater], a[firstU]);
                firstNotGreater++;
            }
            
            firstU++;
        }
    }
}


void order(double a[], int n)
{
    if (n<=1)
    {
        return;
    }
    
    int f, fG;
    split(a, n, a[n / 2], f, fG);
    order(a, f);
    order(a + fG, n - fG);
}

