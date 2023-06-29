# Chapter3

3.1 查询1991年出生的读者姓名、工作单位和身份证号。
```SQL
SELECT readerName, workUnit, identitycard
FROM Reader
```

3.2 查询图书名含有“数据库”的图书的详细信息。
```SQL
SELECT *
FROM Book
WHERE bookName LIKE '%数据库%'
```

3.8 查询每种类别图书的分类号、分类名称、最高价格和平均价格，并按最高价格的升序输出。
```SQL
SELECT classNo, className, MAX(price) AS highestPrice, AVG(price) AS avgPrice
FROM BookClass, Book
WHERE BookClass.classNo = Book.classNo
GROUP BY classNo
ORDER BY highestPrice
```

3.11 查询在借图书的总价不低于200元的读者编号、读者姓名和在借图书总价
```SQL
SELECT readerNo, readerName, SUM(price) AS sum_price
FROM Borrow, Reader, Book
WHERE Borrow.readerNo = Reader.readerNo AND Book.bookNo = Reader.Borrow.bookNo AND returnDate IS NULL
GROUP BY readerNo
HAVING SUM(price) >= 200
```

3.14 查询既借阅过“政治经济学”图书又借阅过“数据库系统概念”图书的读者编号、读者姓名以及这两种图书的图书名称、借书日期和归还日期。
```SQL
SELECT readerNo, readerName, bookName, borrowDate, returnDate
FROM Borrow, Reader, Book
WHERE Borrow.readerNo = Reader.No AND Borrow.bookNo = Book.bookNo 
AND (bookName = '政治经济学' OR bookName = '数据库系统概念') 
AND Reader.readerNo IN(
    SELECT readerNo
    FROM Borrow, Book
    WHERE Borrow.bookNo = Book.bookNo AND bookName = '政治经济学'
) AND Reader.readerNo IN(
    SELECT readerNo
    FROM Borrow, Book
    WHERE Borrow.bookNo = Book.bookNo AND bookName = '概率论系统概念'
)
```