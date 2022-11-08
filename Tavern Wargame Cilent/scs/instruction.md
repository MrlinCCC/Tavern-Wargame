# <center>`SCS 语法使用说明`</center>

- ## **基本描述**

  - ### 1、scs 的语法对括号的使用要求较为严格：每个语句外层都需增加一个括号；对于复合运算的语句一定需要使用括号，而基本类型一定不能随意增加括号。
  - ### 2、在解释器初始化时，支持的自定义基本类型有： int char float string function；可进行运算的类型有(int int) (float float) (char int)(string string);支持的运算有= == != < <= > >= + += - -= \* \*= / /= % %= & &= | |= _(但不是所有的类型都能进行上述所有运算，且使用的是波兰表达式)_

---

- ## **内部函数(func)**
  - ### ①、eval ：语句至左向右执行，并返回最右边表达式的求值结果
  - ### ②、length_of ：求 string 长度
  - ### ③、at ：获取 string 对应下标字符
  - ### ④、import ：导入外部文件
  - ### ⑤、read：控制台输入
  - ### ⑥、print：控制台输出
  - ### ⑦、apply：调用 function 类型的函数

---

- ## **关键字(keyword)**

  - ### 自定义函数(func)
    **语法标准：func 函数名 [函数参数] 执行体**<br>
    `注意`:<br>
    1、函数名不可与关键字重名<br>
    2、参数列表的格式为(变量类型一 &nbsp;&nbsp;形参变量名一)(变量类型二&nbsp;&nbsp; 形参变量名二)...若无参数直接省略，不要以（）代替<br>
    3、执行体的格式(执行语句一 &nbsp;&nbsp;执行语句二 ...)，且语句最终的求值结果即为函数的返回值<br>
    4、函数调用格式：函数名 实参一 实参二...<br>
    `例子`:<br>
    ```lisp
    (func fib (int x)
        (if (<= x 2)
            1
            (+ (fib (- x 1)) (fib (- x 2)))
        )
    )
    (var int a)
    (read a)
    (print (fib a))
    ```
  - ### 自定义变量(var)/自定义常量(const)

    **语法标准：var/const 变量/常量类型 变量/常量名 [初始值]**<br>
    `注意`:<br>
    1、变量/常量的类型必需已经注册
    2、变量/常量名可以同关键字相同，但不建议这么做
    3、变量/常量的初始值可以为空(int float 默认初值为 0)<br>
    `例子`:<br>

    ```lisp
    (var int a 1024)
    (var float b)
    (var char c 'A')
    (var string d "abc")
    (const int e 1024)
    (const float f 6.66)
    (print a '\n' b '\n' c '\n' d '\n' e '\n' f '\n')
    ```

  - ### 条件判断(if)

    **语法标准：if 判断条件 条件真执行体 [条件假执行体]**<br>
    `注意`:<br>
    1、判断条件的格式：int/(结果为 int 的表达式)<br>
    2、执行体的格式:(语句一 语句二...)<br>
    3、多条件判断可通过|、&运算实现<br>
    `例子`:<br>

    ```lisp
    (var int score)
    (read score)
    (if (>= score 90)
        (print "成绩优秀")
        (if (>= score 80)
            (print "成绩良好")
            (if (>= score 60)
                (print "成绩及格")
                (print "成绩不及格")
            )
        )
    )
    ```

  - ### 条件循环(for/while)

    **语法标准：for 初始化执行体 循环条件 结束执行体 循环主体内容**<br>
    **&emsp;&emsp;&emsp;&emsp;&emsp;while 循环条件 循环主体内容**<br>
    `注意`:<br>
    1、初始化/结束执行体的格式：(语句一 语句二 ...)<br>
    2、循环条件的格式：int/(结果为 int 的表达式)<br>
    3、循环主体的格式：(eval 语句一 语句二 ...)<br>
    4、循环可嵌套使用<br>
    `例子`:<br>

    ```lisp
    (for
      (var int i 1)
      (< i 10)
      (+= i 1)
      (eval
          (for
              (var int j 1)
              (< j 10)
              (+= j 1)
              (print i '*' j '=' (* i j) ' ')
          )
          (print '\n')
      )
    )
    ```

    ```lisp
    (var int i 1)
    (while
        (< i 10)
        (eval
            (var int j 1)
            (while
                (< j 10)
                (eval
                    (print i '*' j '=' (* i j) ' ')
                    (+= j 1)
                )
            )
            (print '\n')
            (+= i 1)
        )
    )
    ```
