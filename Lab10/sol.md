## ex1.
> If you run ./hello a couple of times, you should see that the numbers are not always in numerical order and will most likely vary across runs. Think about the reason and explain to your TA.

由于并行化的特性，每次运行代码时，任务被分解为多个子任务，并分配给多个线程并行执行。由于每个线程的执行速度和完成时间都可能不同，线程的执行顺序和完成时间可能会因为多种因素而不同，例如 CPU 的负载、线程调度的优先级等等。

## ex2
> Describe the performance differences between the methods you implemented and try to analyze the reason(Run more times to find a common pattern instead of just running once).

```
PS C:\Users\ShengxinLi\Desktop\Codes\CA\Lab\Lab10> ./matmul.exe
Naive: 3.91600 seconds
Optimized (slices): 0.40300 seconds
Optimized (chunks): 0.40400 seconds
PS C:\Users\ShengxinLi\Desktop\Codes\CA\Lab\Lab10> ./matmul.exe
Naive: 3.92000 seconds
Optimized (slices): 0.40300 seconds
Optimized (chunks): 0.40100 seconds
```

力大砖飞，给他16个线程就好了。

> Explain why using OpenMP may not necessarily lead to optimal performance on a single compute node with multiple cores.

各个core之间的工作量分配不均衡、各个core的缓存之间的同步、读写内存的带宽的不足、部分程序可并行化的空间不高 等因素导致。

> Bonus: Implement an additional optimization and discuss its impact on performance.

感觉可以引入strassen分治算法，把复杂度从$O(n^3)$降到$O(n^{log_2^7})$，但我没精力写了。

## 后话
可能ex2不用手动设置16个线程。以及，可能需要把c清空，因为我们观测到，开2个线程比开16个还快。。。