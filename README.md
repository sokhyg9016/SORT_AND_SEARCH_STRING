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

> This call causes a pointer to the first element of ```b``` to be assigned to ```a```; the array itself isn't copied.
<p>
    
    이 호출으로 인해 'b' 의 첫 번째 요소인 'a' 에 b의 첫 번재 요소의 주소가 저장되고, 배열 자체가 복사되지 않는다.
   
</p>


<br>

> When an ordinary variable is passed to a function, its value is copied; any changes to the corresponding parameter don't affect the variable. In contrast, an array used as argument isn't protected against change, since no copy is made of the array itself.
<p>
    
    일반 변수가 함수에 전달되면 그 값이 복사된다. 해당 매개변수의 변경은 변수에 영향을 미치지 않는다. 
    이와는 대조적으로, 인수로 사용되는 배열은 배열 자체의 복사본이 만들어지지 않기 때문에 변경으로부터 보호되지 않는다.
   
</p>

> An array parameter can be declared as a pointer if desired. For example, ```find_largest``` could be defined as follows:

```c
int find_largest(int *a, int n)
{
 ...
}
```

> Declaring **__a__** to be a pointer is equivalent to declaring it to be an array; the compiler treats the declarations as though they were identical.
<p>
    
    (함수의 매개변수 선언시)'a' 를 포인터로 선언하는 것은 이를 배열로 선언하는 것과 같다. 
    컴파일러는 선언문을 동일하다고 취급한다.
   
</p>

> 이러한 원리는 main 함수에서도 볼 수 있다. 즉 무슨말인가 하면,

```c
int main(int argc, char* argv[]) { ... }
```
보통 이러한 형태로 사용도 하고,
```c
int main(int argc, char** argv) {...}
```
이러한 형태로도 사용하는데, 사실 두 경우 모두 ```argv```에 차이는 없고, 다만 컴파일러가 ```argv[]```를 포인터로 처리해 줄 수 있다는 것이다.

<br>
<br>

## ✔ [참고]The C Programming Language - Ritchie & Kernighan

> ```P. 99```

> There is one difference between an ```array name``` and a ```pointer``` that must be kept in mind. **```A pointer is a variable```**, so ```pa=a``` and ```pa++``` are legal. But an **```array name is not a variable```**; constructions like ```a=pa``` and ```a++``` are illegal. When an ```array name``` is passed to a function, what is passed is the location of the initial element. Within the called function, this argument is a local variable, and so an **__array name parameter is a pointer__**, that is, a variable containing an address.
<p>

	배열 이름과 포인터 사이에는 명심해야 할 차이점이 하나 있다. 
	포인터는 변수이기 때문에 `pa=a` 와 `pa++` 와 같은 문법을 쓸 수 있다. *그러나 배열 이름은 변수가 아니다. 	   
	`a=pa` 와 `a++` 와 같은 구조는 불법이다. 

	배열 이름이 함수에 전달될 때 전달되는 것은 1번째 요소의 위치다. 
	호출된 함수 내에서 이 인수는 지역 변수이기 때문에 배열 이름 매개 변수는 포인터, 즉 주소를 포함하는 변수다.
	
	
</p>


<br>


## 📑 코드 살피기

> ```binary_search_string.c```

```c
...

dec = (char**)malloc(sizeof(char*) * N);

//Allocate space to store string and store string.
for (i = 0; i < N; i++)
{
        dec[i] = (char*)malloc(sizeof(char*) * MAX_SIZE);
        read_line(str, MAX_SIZE);
        strcpy_s(dec[i], MAX_SIZE, str);
}

...
```
여기서 주목할 것은 동적할당 받은 ```char*``` 타입의 ```dec[i]``` 이다.
이 코드에서 배열을  ```read_line()```을 이용해 입력받고 입력받은 배열을 저장한 ```str```변수에 저장된 문자열을 다시 ```strcpy_s```를 이용하여 ```dec[i]```에 저장하였다. 

그렇다면 굳이 왜 이렇게 번거롭게 해야 하는 건가?
그냥 ```dec[i] = "Hello World!"```이렇게 하면 안되는 건가?

먼저 ```dec[i]```의 구조를 살펴보자.

<hr>
<br>

| 여기서는 MAX_SIZE를 5라고 가정 |
| --- |
```c
dec[i] = (char*)malloc(sizeof(char*) * MAX_SIZE);
```

```dec[i] (uninitialized memory, heap, 0x00591068)``` 

| cd | cd | cd | cd | cd |
| ------------- |:-------------:|:-------------:| :-------------:| :-------------:| 


<br>
<br>

```c
dec[i] = "testingonly";
```

```(uninitialized memory, heap, 0x00591068)```

| cd | cd | cd | cd | cd |
| ------------- |:-------------:|:-------------:| :-------------:| :-------------:| 

```dec[i] = "testingonly"``` 

| t | e | s | t | i | n | g | o | n | l | y | \0 |
| - |:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:| 

<br>

> 즉, 만약 ```dec[i] = "testingonly"```를 한다면 기존에 가지고 있던 ```0x00591068``` 라는 heap에 할당받은 메모리의 첫번째 주소값을 잃게 되고 새로운 주소를 가리키게 된다. 그렇다면 이 상태에서 메모리를 해제하면 어떻게 될까?

```c
free(test); // error, because test is no longer pointing to allocated space.
```
> 기존에 할당받은 위치가 아닌 문자열이 저장되어 있는 공간의 첫번째 주소를 가리키고 있으므로 에러가 발생한다.
따라서 기존에 할당받은 위치에다 값을 대입하려면 ```strcpy```를 사용해야 한다.

<br>
<br>

### 📄 코드 - ```int read_line(char* str, int n)```

> K. N. KING - C PROGRAMMING [p. 287]


```c
char str[15];
scanf("%s", str);
```

> There's no need to put the ```&``` operator in front of ```str``` in the call of ```scanf```; like any array name, ```str```
is treated as a pointer when passed to a function. When ```scanf``` is called, it skips white space, then reads characters and stores them in "str" until it encounters a white-space character.
<p>

	scanf함수 호출시 str앞에 &연산자를 붙일 필요가 없다. 다른 배열 이름들처럼, str은 함수에 전달될 때 포인터로 처리된다.
	scanf 함수가 호출되면, 공백은 건너 뛰고, 공백 문자(스펭스 또는 텝)와 마주칠 때까지 문자를 읽고 'str'에 저장한다.
</p>

> A string read using scanf will never contain white space, Consequently, scanf won't usually read a full line of input;
<p>

	scanf를 사용하여 읽은 문자열에는 공백이 전혀 없으므로, 따라서 scanf는 일반적으로 입력의 전체 줄을 읽지 않는다.

</p>

나의 경우, 일반적으로 문자열을 받을 때 ```fgets```를 많이 쓰는 편이다. 이번에 String 쪽을 공부하다가 괜찮은 입력 함수가 있어서 사용해 보았다.
아래는 해당 입력함수의 내용이다.

```c

int read_line(char* str, int n)
{
	char ch;
	int i;

	i = 0;

	fputs("INPUT: ", stdout); 
	while ((ch = getchar()) != '\n')
	{
		if (i < n)
		{
			str[i++] = ch;
		}
	}
	str[i] = '\0';

	return i;
}

```

