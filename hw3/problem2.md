## Problem 2
```
void someclass::somefunc() {
  if (this->n == this->max) {
    bar();
    this->max *= 2;
  } else {
    foo();
  }
  (this->n)++;
}
```

Assume that when someclass is created, `n=0` and `max=10`.

### a. What is the worst-case runtime for somefunc, if bar takes Θ(n^2) time and foo takes Θ(log n) time?

	The worst case runtime for somefunc is Θ(n^2) because while n=0 and max=10 and foo() is called, 
	and in such case bar() will not be immediately called, if the function is called ten more times 
	then bar() is called instead of foo(). The idea of worst-case runtime analysis is to describe 
	the worst runtime possible for somefunc(), and in this case bar() causes the worst case.

### b. What is the amortized runtime for somefunc, if bar takes Θ(n^2) time and foo takes Θ(log n) time?

	To calculate the amortized runtime for somefunc, we will repeat somefunc n times. 
	Then divide the final runtime by n. Let's see what we know:

	* every time n == max, its runtime is n^2, and increments by 2^n. 
	Due to the nature of its incrementation, this instance occurs once every log(n) times, 
	which is applied to an increasing n^2 with n increasing 2^k. Thus the summation is:

		SUMMATION FROM k=1 TO log n OF ((10*(2^k)^2) + 10)
		= 100 * SUM k=1 TO log n OF (2^k^2) + 10 * n * log n
		= 100 * n^2 + 10 n * log n
		= Θ(n^2)

	* for all other cases, the runtime is log(n) whenever n != max
		SUMMATION FROM k=1 TO n OF log n
		= Θ(n log n)

	* the amortized runtime is the combination of (Θ(n^2) + Θ(n log n)) / n
		= Θ(n) + Θ(log n)
		= Θ(n)

### c. What is the amortized runtime for somefunc, if bar takes Θ(n^2) time and foo takes Θ(n log n) time?
	* when n == max, n^2 * nlog n, which we got from B
	* for all other cases
		SUM FROM k=1 TO n OF n log n
		= Θ(n^2 log n)
	* amortized runtime
		= (Θ(n^2) + Θ(n^2 log n)) / n
		= Θ(n) + Θ(n log n)
		= Θ(n log n)

### d. 

```
void someclass::anotherfunc() {
  if (this->n > 0) (this->n)--;
  if (this->n <= (this->max)/2) {
    bar();
    this->max /= 2;
  } else {
    foo();
  }
}
```

Assume that bar takes Θ(n^2) time and foo takes Θ(log n) time. 

**What is the worst-case sequence of calls to somefunc and anotherfunc?**

	Assume that x is a very large number:
```
this->n = x/2 + 1;
this->max = x;
while(true){
	anotherfunc() // runs bar(), max = x/2, n = x/2
	somefunc() // runs bar(), max = x, n = x/2 + 1
}
```
	Both anotherfunc() and somefunc() in this sequence will run bar(), which is n^2 time complexity.
	As soon as somefunc() is run, you will notice that max and n both reset to the original values.
	This means that this exact sequence can be run infinite amount of times and still run, 
	albeit it will never end (it is the worst-case sequence of calls.)

**What would be the amortized runtime per function call?**

	The amortized runtime per function call, if you call anotherfunc() then somefunc() in sequential order, 
	you will run bar() twice. Meaning you will have a time complexity of around 2*n^2. No matter how many times
	you call this sequence... sum from 1 to n of 2*n^2 / n = 2*n^2.
	
	The worst case amortized runtime represented in big O notation is Θ(n^2).
