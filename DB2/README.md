# DB2
软件学院最具历史性的课程，可以与考古学院联动的那种。

包含两门课，其一为《企业级数据库性能调优》，其二为《数据库应用程序开发》。

据说这两门课之前是与IBM合作的产物，过了可以拿到一个证书，但是后来就没有证书了，不过课程还是保留下来了。

**该课程需要使用Windows XP虚拟机。** 为方便各位同学，猫娘整理了一些XP时代能使用的软件，以简化各项操作。详见后文。

## 相关资源
### 课程讲义、文档类
- 两门课程的PPT、相关课程资料等【其实直接在学习通下载更方便】[百度网盘](https://pan.baidu.com/s/1mfmzdJUvqVDRD4pbWSiXWw?pwd=9cqt) [蓝奏云](https://wwarm.lanzouv.com/b0o0315od
)【密码:2295】
- 课程要求编辑的单个文件代码，可能需要您在压缩包`cg113labfiles.zip`中的`CG113`目录下自行寻找。受限于<u>8.3文件名格式</u>（详见文末附录），部分代码的文件名变为类似于`LABUPD~1.JAV`的形式，需要您自行修改文件名。
- 如需配置DB2服务器，使用现代Java连接，可参考`db2连接指南.pdf`

### 旧版软件类
- XP SP3系统镜像【因蓝奏云100MB限制，只有百度网盘链接】【**仅当虚拟机系统无法正常使用时才需要重新安装**】[百度网盘链接](https://pan.baidu.com/s/18IMyug6fsDPk6tyybQ2-tw?pwd=189b)
- 一张当年番茄花园的系统盘，但是里面的XP是SP2版本，只使用里面附带的常用软件就好了 [番茄花园下载链接](https://pan.baidu.com/s/1p7d4bg9h9dT0Zn5idGPyjQ?pwd=e5m9)
- [知乎专栏：WinXP开发宝典](https://zhuanlan.zhihu.com/p/718030085)
- 以上软件资源，建议安装一个Notepad++和一个PDF阅读器即可。

### 代码
- 详见【代码】目录
- 管理系统所需依赖库在网盘的`数据库应用程序开发/lib.zip`，解压至【员工管理系统】即可
- 需要您自行修改`ManagerMain.java`中的数据库配置

## 企业级数据库性能调优
选修课-任选课，1.5学分（含1.5实践学分），推荐指数3.5颗星。

- 该课程没有任何技术难度，所有操作步骤均在PPT或者指导书上有提示。
- 甚至不需要你自己写代码，复制粘贴即可。但是可能由于这门课的东西太老，AI似乎并不能提供有效帮助。
- 每次课都有位置签到。
- 给分很高，而且算实践学分，但鉴于实验步骤比较繁琐，过于考古，且每次课都有签到，综合给到3.5分。

### 考核
- 平时成绩50分。实验报告1-5占40分，实验报告6占5分，国产数据库小论文占5分。
- 期末成绩50分。最后一次课上需要完成一个大作业（实际上就是5个简答题），PPT上都有，可以直接抄。如果没时间去还可以补考。
- 期末大作业限时90分钟。

### 真题1：2024.10.22
1. 实验中创建artists表的时候，为什么把常规数据指定存储在DMS01表空间，索引指定存储在DMS02表空间，大对象则只能存储在DMS03表空间？这样做的好处是什么？
2. 为表空间A在物理磁盘C上映射了5个containers，表空间B在物理磁盘D、E、F上分别映射了1个container，请问哪个表空间读写性能更好，为什么？
3. 在import实验过程中，向artists表中导入数据时，应该成功导入79行，但有些同学只导入了36行，请分析有可能存在的问题。
4. 日志有几种工作方式？你在进行数据库备份和恢复的实验时，分别对日志进行了怎样的设置？复原和前滚分别对应日志的哪种工作方式？
5. 在实验中曾经编写下列语句：
    ```sql
    create trigger recorder
    after update
    of qty on stock
    referencing new as n
    for each row mode db2sql
    when (n.qty <= 5)
    insert into recorder values (n.itemno, current timestamp)
    ```
    请解释该语句所实现的具体功能。分析该触发器能否阻止同一件商品背重复插入reorder表中？如果不能，请给出修改方案。

### 真题2：2024.10.24
1. 实验中创建musicdb数据库时，指定的Page大小为4K，但在创建DMS01表空间时，指定extent size的大小为4Page，请问DMS01表空间分配存储空间的单位是多少K？不同表空间的extent size的大小可以不同吗？
2. 为表空间A在物理磁盘C上映射了5个container，表空间B在物理磁盘D、E、F、G、H上分别映射了1个container，请问哪个表空间的读写性能更好？为什么？
3. 在load实验过程中，为什么以repalce方式向artists表装载了78行之后，使得albums表和stock表不可用？如何解决这种Pending问题？
4. 日志有几种工作方式？你在进行数据库备份和恢复的实验时，分别对日志进行了怎样的设置？复原和前滚分别对应日志的哪种工作方式？
5. 请创建一个reorder触发器，该触发器在stock表的qty列上有修改，满足`qty<=5`时触发，该触发器为后触发器，出发点动作是`insert into reorder values(n.itemno, current timestamp)`，要求当多次满足条件时，只触发一次。

## 数据库系统应用程序开发
必修课，1.5学分，计入保研绩点。

依旧联动考古学院。
- **你需要使用Java5**
- 虚拟机同上门课程，如果你选了上面那门课，可以直接沿用。
- 为什么不能用新版本的Java，首先是因为这玩意需要用XP虚拟机，要在那个虚拟机上面跑你的Java代码，里面只有Java5。你可能会想在自己物理机上面把虚拟机当数据库服务器连接，但是很遗憾，连接这个数据库会遇到各种问题，猫娘甚至专门在学习通讨论区发了个帖子描述了解决办法。
- 如果您确定要使用现代Java（猫娘也是这样做的），可参考猫娘给出的文档。
- 课程要求没有明确指出需要做出一个完整的管理系统，但鉴于该课程很多任务都要求做出一个GUI界面，且根据最终成绩来看，做出完整管理系统的同学得分较高，因此建议您做一个完整的管理系统，实现需要GUI实现的实验任务。

### 考核
- 实验报告50分。实验报告包括一些对课程文档中提供的Java代码进行修改的任务，其他则是编写GUI程序进行CRUD操作的任务。除展示代码效果外，还需要提供对出现的问题进行修复的过程。
- 考试50分。与《企业级数据库性能调优》不同的是，该课程是必修课，因此是正规的期末考试。

### 真题：2024.12.29

#### 一、给出代码片段（5\*15=75）

1.向一个表插入10万行，每500行提交一次

2.查询员工信息表，然后将奖金为0的员工绩效考核设置为不合格 `提示：for update 与 where current of`

3.键盘读入员工信息并插入，包含两个空列 `使用setNull()`

4.异常处理，给出两个`SQLState`代码，捕获异常并输出错误信息

5.数据库插入`BLOB`对象的照片

#### 二、设计题（25）

1.12306如何实现查火车票不用登陆，买票需要登录`考点：事务隔离性级别`

2.实现一个12306火车信息查询，然后根据发时、票价等排序，根据席别等因素筛选

*最终得分98分，课程的内容还是比较简单的，只要实验是自己做的，90+没问题。*

> 试植梓为期 掔发为纾
>
> ——《韶华未既》
---

### 知识点总结

> 注意：以下内容较长

##### 1.导入所需的包

```java
import java.sql.*;
import java.io.*;
import java.lang.*;
```

---

##### 2.加载JDBC驱动

```java
// MyJDBC.java
public class MyJDBC {
    static { //内部静态类
        try {
            Class.forName("COM.ibm.db2.jdbc.app.DB2Driver");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

---

##### 3.实例化`Connection`对象

- 无用户名密码（本地账户登录）

```java
try {
    String url = "jdbc:db2:sample";
    Connection conn = DriverManager.getConnection(url);
} catch (Exception e) {
    throw new Exception("\nUsage: java MyJDBC [,uanme,passwd]");
}
```

- 有用户名密码（远程登陆）

```java
try {
    String url = "jdbc:db2:sample";
    String userid = "JLU";
    String passwd = "826132";
    Connection conn = DriverManager.getConnection(url, userid, passwd);
} catch (Exception e) {
    throw new Exception("\nUsage: java MyJDBC [,uanme,passwd]");
}
```

---

##### 4.查询操作：`Statement`,`ResultSet`（注意同样要用`try-catch`包围，这里为了方便演示就省略了）

```java
String sql = "SELECT EMPNO, LASTNAME FROM TEMPL WHERE SALARY > 40000";
Statement stmt = conn.createStatement();
ResultSet rs = stmt.executeQuery(sql);
while (rs.next) {
    System.out.println("empno = " + rs.getString(1) + "lastname = " + rs.getString(2));
}
rs.close();
stmt.close();
conn.close();
```

---

##### 5.更新操作：`Statement` VS `PreparedStatement`（注意同样要用`try-catch`包围，这里为了方便演示就省略了）

- `Statement`

```java
Statement stmt = conn.createStatement();
String sql = "UPDATE TEMPL SET LASTNAME = 'Stohl' WHERE EMPNO = '000110'";
int numRows = stmt.exectueUpdate();
System.out.println("Number of rows updated" + numRows);
```

- `PreparedStatement`

```java
String sql = "UPDATE TEMPL SET SALARY = ? WHERE EMPNO = ?";
PreparedStatement pstmt = conn.prepareStatement(sql);
pstmt.setString(1, argv[1]);
pstmt.setString(2, argv[2]);
int numRows = pstmt.exectueUpdate();
System.out.println("Number of rows updated" + numRows);
```

---

##### 6.关闭自动提交

```java
sample.setAutoCommit(false);
```

---

##### 7.最基本的GUI交互（GUI不作为考试重点）

- 输入对话框

```java
String empno = JOptionPane.showInputDialog(null, "请输入员工工号");
```

- 消息对话框

```java
JOptionPane.showMessageDialog(null, "插入成功！");
```

---

##### 8.主变量与列变量

简单理解：主变量就是你编程用的语言定义的变量，列变量就是数据库里面的变量。

DB2工具`DCLGEN`：帮助找到列变量和主变量的对应关系。

```batch
db2dclgn -D sample -T employee -L Java
```

意为找到`sample`数据库中`employee`表的各列在Java中的对应主变量类型。

---

##### 9.空值处理

如果使用下列代码判断是否为空值：

```java
String empno = rs.getString(1);
if (empno == null) {
    //...
}
```

当对应列变量为空值时，JDBC会根据变量类型为主变量赋予默认值，对于字符串类型，该值为空格。因此，空值处理的语句始终不会被执行。

JDBC提供`wasNull()`方法：

```java
String empno = rs.getString(1);
if (rs.wasNull() {
    //...
}
```

当读取的列变量为空值，该方法返回`true`。

同样，如果我们需要给列变量赋空值，直接使用`null`将会给字符串赋值为`'null'`。JDBC提供`setNull()`方法：

```java
pstmt.setNull(1, java.sql.Type.CHAR);
pstmt.setNull(2, java.sql.Type.SMALLINT);
pstmt.setNull(3, java.sql.Type.INTEGER);
```

通过该方法即可设置空值。

---

##### 10.异常处理（不必背诵错误代码，考试会给）

SQLCA：SQL通信区。高级语言调用SQL语句后，数据库引擎访问数据库后，用特殊代码向SQLCA返回访问状况。

数据库访问发生异常时，抛出`SQLException`异常。

`SQLCode`：错误代码集。在DB2中，<0代表SQL语句有错误，>0且!=100为警告信息，=0为返回0行（行不存在）。`SQLCode`依赖于具体数据库产品，由厂商自行定义，包含更加详细的错误信息。

`SQLState`：错误代码集。国际标准，所有数据库产品中多数代码是统一的。

例如：

```java
try {
    String sql = "DELETE FROM TEMPL WHERE EMPNO = 999";
    pstmt = con.prepareStatement(sql);
    deleteCount = pstmt.executeUpdate();
    if ((SQLWarn = pstmt.getWarnings()) != null) {
        System.out.println("\nWarning received on a DELETE \n");
    }
} catch (SQLException e) {
    if (e.getSQLState().equals("42818")) {
        // 处理类型不兼容的异常
        System.out.println("\n Operand data tyoes not Compatible \n");
    } else {
        System.out.println("\n Error deleting from TEMPL \n");
        System.out.println("\n Value of SQLCode is: \n");
        String SQLCode = e.getErrorCode(); //注意此处方法名是ErrorCode，而不是SQLCode
        System.out.println(SQLCode);
    }
}
```

常见错误代码示例（转载自[吉林大学数据库应用程序开发知识点总结-CSDN博客](https://blog.csdn.net/It_Ray/article/details/135437808)）：

```java
switch(SQLCODE) {
            case 802:
                //数据溢出
                JOptionPane.showMessageDialog( null , "数据溢出" ,"SQL错误" , JOptionPane.ERROR_MESSAGE) ;
                break;
            case -007:
                //SQL语句中有非法字符
                JOptionPane.showMessageDialog( null , "SQL语句中有非法字符" ,"SQL信息" , JOptionPane.ERROR_MESSAGE) ;
                break;
            case -010:
                //丢失引号
                JOptionPane.showMessageDialog( null , "SQL语句丢失引号" ,"SQL信息" , JOptionPane.ERROR_MESSAGE) ;
                break;
            case -060:
                //某特定数据类型的长度或者标量规范无效
                JOptionPane.showMessageDialog( null , "某特定数据类型的长度或者标量规范无效" ,"SQL信息" , JOptionPane.ERROR_MESSAGE) ;
                break;
            case -102:
                //字符串常量太长
                JOptionPane.showMessageDialog( null , "字符串常量太长" ,"SQL信息" , JOptionPane.ERROR_MESSAGE) ;
                break;
            case -104:
                //SQL语句中遇到非法符号
                JOptionPane.showMessageDialog( null , "SQL语句中遇到非法符号" ,"SQL信息" , JOptionPane.ERROR_MESSAGE) ;
                break;
            case -433:
                //指定的值太长
                JOptionPane.showMessageDialog( null , "指定的值太长" ,"SQL信息" , JOptionPane.ERROR_MESSAGE) ;
                break;
            case -405:
                //数值文字超出了范围
                JOptionPane.showMessageDialog( null , "数值文字超出了范围" ,"SQL信息" , JOptionPane.ERROR_MESSAGE) ;
                break;
}


```

---

##### 11.结果集游标

```java
PreparedStatement pstmt = conn.prepareStatement(sql, rs.TYPE_FORWARD_ONLY, rs.CONCUR_READ_ONKY);
```

第二个参数含义是只允许前向滚动，也就是说游标只能往前走，不能倒退，这是默认值。如果希望游标是可滚动的，可以改为`rs.TYPE_SCROLL_INSENSITIVE`（允许倒退，数据库变化时结果集不变）或者`rs.TYPE_SCROLL_SENSITIVE`（允许倒退，数据库变化时结果集同步）。

第三个参数限制了结果集的用途，意为只允许并发读取（只在读取的时候可以并发）。改为`CONCUR_UPDATABLE`则允许并发修改，但是本课程中DB2的驱动程序不支持。

对于`Statement`也同样适用，只需要把默认的无参方法改成重载的两个参数的方法即可。

```java
Statement pstmt = conn.createStatement(rs.TYPE_FORWARD_ONLY, rs.CONCUR_READ_ONKY);
```

物化：结果集暂存于磁盘。例如，需要对结果集排序时，内存中不足以保存排序结果，需要为结果集临时分配磁盘空间。

```java
String mySelect = "SELECT LASTNAME, FIRSTNME FROM EMP FOR UPDATE";
String myUpdate = "UPDATE EMP SET FIRSTNAME = ? WHERE CURRENT OF ";
```

这二者都不是标准的SQL语句。`FOR UPDATE`指示数据库引擎该语句将被用于修改，第二个字符串含有问号，含有参数标记，`WHERE CURRENT OF`后面等待游标名称，组合起来就是一个完整的SQL语句了。

```java
String cursorName = null;
Statement stmt = conn.createStatement();
ResultSet rs = stmt.executeQuery(mySelect);
cursorName = rs.getCursorName();
PreparedStatement ps = conn.prepareStatement(myUpdate + cursorName);
```

注意此处执行的是`select`语句，也就是查询。因此，`cursorName`返回的，也就是查询后得到的结果集的游标名。更新语句与这个游标相拼接，条件就是游标指向当前行的值。有没有发现这两条语句都是针对同一个表的？也就是说，查询结果集的游标定位到某行的时候，更新语句就直接可以用这个游标的指向来执行更新操作了。

```java
while (rs.next) {
    String lastname = rs.getString(1);
    String firstnme = rs.getString(2);

    if (lastname.equals("SMITH")) {
        String newFirstnme = "George";
        ps.setString(1, newFirstnme);
        ps.executeUpdate();
    }
}
rs.close();
ps.close();
stmt.close();
conn.close();
```

这里随着`select`语句结果集游标的移动，逐个检查数据集中的姓氏是否为SMITH。当检查到姓SMITH的人时，`update`语句就可以直接通过游标定位要修改的行了。先查询——获取结果集——获取的结果集上进行修改。

```java
rs.afterLast(); // 将结果集游标移动到最后一行之后
rs.prevoius(); // 游标前移一行
rs.absolute(1); // 移动到第一行
rs.absolute(-1); // 移动到最后一行
rs.first(); // 移动到第一行
rs.last(); // 移动到最后一行
rs.relative(2); // 前移两行
rs.relative(-2); //回退2行
```

---

##### 12.元数据接口

`getColumnCount()`结果集列数

`getColumnLabel()`结果集列的名称

```java
DatabaseMetaData dbmd = sample.getMetaData();
ResultSet rs = dbmd.getSchemas();
```

获取数据库的模式元数据

```java
String[] tableTypes = {"TABLE", "VIEW"};
ResultSet rs = dbmd.getTables(null, "JLU", "%", tableTypes);
```

获取模式为JLU的表信息

---

##### 13.批处理

当执行了一行所有列的`setString()`后：

```java
ps.addBatch();
```

向批处理添加一行。

```java
int[] rowCounts = ps.executeBatch();
```

执行批处理，返回每个语句影响的行数。

---

##### 14.大对象

`BLOB`：二进制大对象

`CLOB`：字符型大对象

SQL函数`POSSTR(RESUME, 'Personal')`：获取`'Personal'`字符串在`RESUME`列中第一次出现的位置。

SQL函数`SUBSTR(RESUME, 1, 999)`：截取`RESUME`列中从1开始，读取999个字符。注意SQL的下标是1开始的。

SQL函数`SUBSTR(RESUME, 114514)`：截取RESUME列中从下标为114514的字符开始，直到末尾的子串。

SQL `select`语句中，`||` 不是逻辑运算符。它代表将前后两个字符串拼接起来。

读取`CLOB`时，要注意：`select`字句中截取后，还是`CLOB`；Java程序中要用`Clob resumelob = rs.getClob()`读取。

如何将`Clob`转化为我们常见的字符串呢？

```java
while (rs.next()) {
    empno = rs.getString(1);
    resumefmt = rs.getString(2);
    resumelob = rs.getClob(3);
    long len = resumelob.length();
    int len1 = (int)len;
    String resumeout = resumelob.getSubString(1, len1);
}
```

首先用`resumelob.length()`获取大对象的整体长度，强制转换为32位整型后，读取从第1位到结尾的字串，其实就是整个字符串，这样我们就得到了所需要的简历字符串。注意从结果集中读取`CLOB`时，不能使用`String`类型，也不能使用`getString`方法，要使用对应的`Clob`版本。

读取和插入`BLOB`，则需要使用Java流。

- 写入

```java
File file = new File("C:/a.jpg");
java.io.BufferedInputStream imageInput = new java.io.BufferedInputStream(new java.io.FileInputStream(file));
pstmt.setBinaryStream(1, imageInput, (int)file.length());
pstmt.executeUpdate();
```

首先获取文件对象，指定要写入的文件；然后使用该文件对象定义输入流；最后，将输入流写入数据库。

- 读取

读取同理，获得BLOB对象后，转换为流，定义文件对象，最后写入文件。

```java
Blob blob = (Blob)rs.getBlob(1);
java.io.InputStream inputStream = blob.getBinaryStream();
File file = new File("C:/backa.jpg");
FileOutputStream fos = new FIleOutputStream(file);

int c;
while((c = inputStream.read()) != -1) {
    fos.write(c);
}
```

#### 整体评价

跟往年的题不完全一样，还是要以PPT为主，学习通视频好好看看。


## 附录：关于8.3文件名（千问AI生成）
8.3文件名格式是一种早期的文件命名规范，主要应用于DOS和早期的Windows操作系统中。

**“8.3”这个名字的含义：**
*   **8**：代表文件名的主体部分（主名）最多只能有 **8个字符**。
*   **3**：代表文件的扩展名最多只能有 **3个字符**。
*   两者之间用一个点（`.`）隔开，例如 `G9401.DBF`。

**为什么会有8.3格式？**
这主要是为了兼容早期的DOS和FAT文件系统。随着Windows系统的发展，开始支持包含空格和特殊字符的长文件名。但为了保证旧版软件和系统的兼容性，Windows会自动为长文件名生成一个符合8.3规则的“短文件名”作为别名。

**短文件名的生成规则：**
当长文件名超过限制时，系统会按照以下规则自动生成短文件名：
1. 取长文件名的前 **6个有效字符**（去除空格和特殊字符，并转换为大写）。
2. 后面加上波浪号 **`~`**。
3. 最后加上一个 **数字**（从1开始，用于避免文件名冲突）。

**常见示例：**
*   `Program Files` 的短文件名通常是 `PROGRA~1`。
*   `Program Files (x86)` 的短文件名通常是 `PROGRA~2`。
*   `My Long File Name.txt` 可能会变成 `MYLONG~1.TXT`。

在现代的Windows系统（如Windows 10/11）中，8.3格式已经不再是默认的命名方式，大家日常使用的都是长文件名。不过，系统底层依然保留了对它的支持，以确保某些老旧软件或特定脚本能够正常运行。