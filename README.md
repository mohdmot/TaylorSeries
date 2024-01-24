<h1 align="center">Taylor Series in 10 Billion Iterations</h1>
<p align="center">
        <img src="https://github.com/mohdmot/TaylorSeries/blob/main/figure/formula.png?raw=true">
</p>
In this test, I implemented the Taylor series with 10 billion iterations.

Naturally, this huge number of mathematical operations requires a very strong and fast programming language, so the choice fell on the **C language**

In the beginning, I created ( [main.c](https://github.com/mohdmot/TaylorSeries/blob/main/main.c) ). In short , it is a C code that performs this operation while recording the output to a CSV file ( [taylor.csv](https://github.com/mohdmot/TaylorSeries/blob/main/taylor.csv) ). To avoid the large volume of data that will be dealt with, the data range chosen for writing was limited, meaning:
* Record all iterations with their pi value from 1 to 1 million.
* Not all numbers larger than a million will be recorded, only those that are divisible by a million.

So :
```
iter 	   pi
1          4
2          2.666667
3          3.466667
4          2.895238
5          3.339683
...        ...
1000000    3.141592
2000000    3.141592
3000000    3.141592
4000000    3.141592
```
To run main.c you can simply compile the file:
```
gcc main.c -o main
```
We can run it with the command ( `main.exe` ) for Windows or ( `./main.out` ) for Linux, It will work this way, just wait until it finishes.
```
Claculating Pi With Taylor Series
        Iteration = 4000000000 , pi = 3.1415926533
Program Stoped in 4000000000 Iteration
```

In the beginning, you may encounter some bugs in writing or dealing with a similar program. These are the problems that I encountered:
- When you allow the program to continue to infinity, you may encounter problems with variables, so you must set a limit such as 10 billion.
- Simple datatypes such as `int`, `float` will not work, because they will not handle a large number of iterations, so I used `long long` .

I think everything is clear now regarding the C code, now we move on to analyze the results we obtained.

## Analysis The Results
If we display all the data at once, we will find that there is oscillation in the results at the beginning over a slightly wide range from approximately 2.7 to 4, and then stability in the value until the end. Of course, with simple mathematical knowledge, we will know that the values is not steady, we just cannot see the progression that happens and heading to the value of pi, because of the large number of iterations. We are talking about 10 billion iterations represented by us in the x-axis.

We used this code to download the file, read it, and prepare some of the functions we will need:
```py
import matplotlib.pyplot as plt
import pandas as pd
import matplotlib.pyplot as plt

# Read file from github
csv = pd.read_csv('https://github.com/mohdmot/TaylorSeries/raw/main/taylor.csv')
csv.columns = ['iter','value']

# get a part of data
def get_part (s,e):
  start = list(csv['iter']).index(s)
  end   = list(csv['iter']).index(e)
  return pd.DataFrame({"iter" : csv['iter'].iloc[start:end] , "value" : csv['value'].iloc[start:end]})
```
And this is to plot all the data:
```py
plt.plot(csv['iter'], csv['value'],label='Series Result')
plt.legend(loc='best')
plt.title('Iterations (1-10,000,000,000)')
plt.show()
```
![](https://github.com/mohdmot/TaylorSeries/blob/main/figure/full.png?raw=true)

Let's take a look at the behavior of the oscillation at the beginning to see where it starts and where it starts to get smaller.
```py
# First 20 Iterations
d = get_part(1,20)
plt.plot([1,20],[3.14159265359,3.14159265359], 'r', label='Actual Pi')
plt.plot(d['iter'] , d['value'],label='Series Result')
plt.legend(loc='best')
plt.title('Iterations (1 - 20)')
plt.show()
```
![](https://github.com/mohdmot/TaylorSeries/blob/main/figure/1_20.png?raw=true)

We see in the previous figure that the value of pi was large and began to pivot and decrease after the second iteration little by little, until the range of oscillation became in 3.0 - 3.2 at approximately the 17th iteration.

We can notice the same things when we move a little further away, the oscillation is regular and goes right towards the value of pi.
```py
# First 100 Iterations
d = get_part(1,100)
plt.plot([1,100],[3.14159265359,3.14159265359], 'r', label='Actual Pi')
plt.plot(d['iter'] , d['value'],label='Series Result')
plt.legend(loc='best')
plt.title('Iterations (1 - 100)')
plt.show()
```
![](https://github.com/mohdmot/TaylorSeries/blob/main/figure/1_100.png?raw=true)

We mentioned previously that we recorded all occurrences from 1 to a million, and then all numbers divisible by a million after that, to reduce the size of our results.

We'll go over some samples of the results, let's start with ( `800,000,000` to `1,200,000,000` ) :
```py
iter = 1200000000
d = get_part(800000000,iter)
plt.plot([800000000,1200000000],[3.14159265359,3.14159265359], 'r', label='Actual Pi')
plt.plot(d['iter'] , d['value'],label='Series Result')
plt.legend(loc='best')
plt.title('Iterations (800,000,000 - 1,200,000,000)')
plt.gca().get_yaxis().get_major_formatter().set_useOffset(False)
plt.show()
```
![](https://github.com/mohdmot/TaylorSeries/blob/main/figure/800_1200.png?raw=true)

We will notice that the value of the difference between iteration `1,200,000,000` and the value of pi is `0.0000000008`. Let's come to the next one, which is ( `1,200,000,000` to `3,200,000,000` )
```py
iter = 3200000000
d = get_part(1200000000,iter)
plt.plot([1200000000,3200000000],[3.14159265359,3.14159265359], 'r', label='Actual Pi')
plt.plot(d['iter'] , d['value'],label='Series Result')
plt.legend(loc='best')
plt.title('Iterations (1,200,000,000 - 3,200,000,000)')
plt.gca().get_yaxis().get_major_formatter().set_useOffset(False)
plt.show()
```
![](https://github.com/mohdmot/TaylorSeries/blob/main/figure/1200_3200.png?raw=true)

We notice that the difference is reduced to `0.0000000003`, of course it is known that the deeper we go into the series, the more the change gradually becomes very, very small over time.

Let's go further, to the end of our data ( `8,200,000,000` to `9,200,000,000` ).
```py
d = get_part(8200000000,9200000000)
plt.plot([8200000000,9200000000],[3.14159265359,3.14159265359], 'r', label='Actual Pi')
plt.plot(d['iter'] , d['value'],label='Series Result')
plt.legend(loc='best')
plt.title('Iterations (8,200,000,000 - 9,200,000,000)')
plt.gca().get_yaxis().get_major_formatter().set_useOffset(False)
plt.show()
```
![](https://github.com/mohdmot/TaylorSeries/blob/main/figure/8200_9200.png?raw=true)

We notice something different here, the data is constant, and the difference is now `0.00000000008` meaning that it is `3.75` times smaller than the previous graph.

**Note:** Pay attention, there is an extra zero in the difference. The zeros before the comma have become 10, they were 9.

## Conclusion
We also noticed that the values were fixed at the end, so we will do a simple search in the data to find the first time that pi was calculated as `3.1415926535`, in other words, the last repetition before our values were stop changing.
```py
first_found_idx = list(csv['value']).index(3.1415926535)
print('We got the right first 11 digits of pi in the', csv['iter'][first_found_idx], 'iteration')
```
We got:
```
We got the right first 11 digits of pi in the 7235000000 iteration
```
Thus, we calculated the first 11 (the first 10 after the dot) as digits of pi in the Taylor series, and we were able to do this with 7235000000 iterations.
