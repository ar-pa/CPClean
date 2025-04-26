const int MAX_MAT = 2;

struct Mat{
    int a[MAX_MAT][MAX_MAT];
    explicit Mat(bool emp = false){
        memset(a, 0, sizeof a);
        if(emp)
            for(int i = 0; i < MAX_MAT; i++)
                a[i][i] = 1;
    }
    const int* operator [](int i) const{
        return a[i];
    }
    int* operator [](int i){
        return a[i];
    }
    Mat operator +(const Mat &b){
        Mat ret;
        for(int i = 0; i < MAX_MAT; i++)
            for(int j = 0; j < MAX_MAT; j++)
                ret[i][j] = a[i][j] + b[i][j];
        return ret;
    }
    Mat operator *(const Mat &b){
        Mat ret;
        for(int k = 0; k < MAX_MAT; k++)
            for(int i = 0; i < MAX_MAT; i++)
                for(int j = 0; j < MAX_MAT; j++)
                    ret[i][j] += a[i][k] * b[k][j];
        return ret;
    }
    Mat operator ^(int b){
        Mat a = *this;
        Mat ret(true);
        for(; b; b >>= 1, a = a * a)
            if(b & 1)
                ret = ret * a;
        return ret;
    }
};
