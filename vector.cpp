template<class > class Array{
  nint * ptr;
  int maxSize;
  int nowSize;
public:
  Array(int _size=0){
    maxSize = _size>0 ? _size: 256;
    nowSize = 0;
    ptr = new nint[maxSize];
  }
  ~Array(){delete [] ptr;}
  int size(){return nowSize;}
  int back(){return ptr[nowSize-1];}
  Array(Array & b){
    maxSize = b.maxSize;
    nowSize = b.nowSize;
    //delete [] ptr;
    ptr = new nint[maxSize];
    for(int i=0; i<nowSize; i++)
      ptr[i]=b[i];
  }
  void pb(nint x){
    if(nowSize==maxSize){
      nint * oldptr = ptr;
      ptr = new nint[maxSize<<=1];
      memcpy(ptr,oldptr,nowSize*sizeof(nint));
      //for(int i=0; i<nowSize; i++)ptr[i]=oldptr[i];
      //delete [] oldptr;
    }
    ptr[nowSize++]=x;
  }
  void pop(){
    if(nowSize<maxSize>>2){
      nint * oldptr = ptr;
      ptr = new nint[maxSize>>=1];
      for(int i=0; i<nowSize; i++)
	ptr[i]=oldptr[i];
      //delete [] oldptr;
    }
    nowSize--;
  }
  nint & operator[](int i){
    if(i>=nowSize)
      printf("Out Of Range\n"),exit(-1);
    else
      return ptr[i];
  }
  Array operator=(Array & b){
    maxSize = b.maxSize;
    nowSize = b.nowSize;
    //delete [] ptr;
    ptr = new nint[maxSize];
    for(int i=0; i<nowSize; i++)
      ptr[i]=b[i];
    return b;
  }
};
