# SORT_AND_SEARCH_STRING
📄 문자열에 대한 동작할당과 입력 방법 및 이차원 포인터에 대한 함수의 인자 전달 방식에 대하여

[![Build Status](https://travis-ci.org/sokhyg9016/SORT_AND_SEARCH_STRING.svg?branch=master)](https://travis-ci.org/sokhyg9016/SORT_AND_SEARCH_STRING)

| **작성일**       | **키워드**           | 
| ------------- |:-------------:| 
| 2019.07.29     | `함수 매개변수` `배열` `이중 포인터` `문자열` | 

<hr>

## ✔ About Function Argument 

> K. N. KING - C PROGRAMMING A MODERN APPROACH (p. 265 ~ 266)

<p>
    
    "When passed to a function, an array name is always treated as a pointer."
        
</p>
<p>Consider the following function, which returns the largest element in an array of integers:</p>

```c
int find_largest(int a[], int n)
{
  int i, max;

  max = a[0];
  for(i = 1; i < n; i++)
    if(a[i] > max)
      max = a[i];
  return max;
}
```

<p>Suppose that we call <em><b>find_largest</b></em> as follows:</p>

```c
#include <stdio.h>
#define N 10

int main()
{
  int largest;
  int b[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  largest = find_largest(b, N);
  return 0;
}
```
<p>
  This call causes a pointer to the first element of <em><b>b</b></em> to be assigned to <em><b>b</b></em>; the array itself isn't copied.<br>
The fact that an array argument is treated as a pointer has some important con-sequences:
</p>


> 📑 When an ordinary variable is passed to a function, its value is copied; any changes to the corresponding parameter don't affect the variable. In contrast, an array used as argument isn't protected against change, since no copy is made of the array itself.|

> 📑 An array parameter can be declared as a pointer if desired. For example, <em>find_largest</em> could be defined as follows:

```c
int find_largest(int *a, int n)
{
 ...
}
```

> Declaring **__a__** to be a pointer is equivalent to declaring it to be an array; the compiler treats the declarations as though they were identical.


