# Chapter7
## 7.2
(1)
```SQL
UPDATE Book
SET price = price * 1.1
WHERE classNo in (
    SELECT classNo
    FROM BoookClass
    WHERE className = '经济类'
)
```

(2)
```SQL
UPDATE Book
SET price = price * 0.95
WHERE shopNum = (
    SELECT MAX(shopNum)
    FROM Book
)
```

(3)
```SQL
DELETE FROM Borrow
WHERE readerNo IN(
    SELECT readerNo
    FROM Reader
    WHERE readerName = '张小娟'
)
```

(4)
```SQL
CREATE VIEW BookView
AS
    SELECT Reader.readerNo, readerName, SUM(price) AS '总价'
    WHERE Reader.readerNo = Borrow.readerNo 
        AND Book.bookNo = Borrow.bookNo
    GROUP BY Reader.readerNo,readerName
    HAVING SUM(price) > 60
```

(5)
```SQL
CREATE VIEW
AS
    SELECT Reader.readerNo, readerName,    
        SUBSTRING(identifycard, 7, 14) AS birthday,  
        workUnit, bookName, borrowDate
    FROM Reader, Borrow, Book
    WHERE Reader.readerNo = Borrow.readerNo AND 
        Borrow.bookNo = Book.bookNo AND 
        YEAR(GETDATE()) - 
        CONVERT(INT, 
        SUBSTRING(identifycard, 7, 14)) BETWEEN 25 AND 35
```

## 7.3
(1)
```SQL
CREATE PROCEDURE pro1(@cNo, char(4))
AS
    SELECT COUNT(*) AS sNum, AVG(score) AS avg_score
    FROM Score
    WHERE courseNo = @cNo
```

(2)
```SQL
CREATE PROCEDURE pro2
AS
    SELECT studentNo, courseNo, MAX(score) AS max_score
    FROM Score
    GROUP BY studentNo, courseNo
```

## 7.4
(1)
```SQL
CREATE TRIGGER refuseBorrowing
ON Borrow FOR INSERT AS
BEGIN
    IF(
        SELECT COUNT(*)
        FROM inserted
        GROUP BY readerNo
    ) >= 10
    -- 假定最大借书数量是10 --
        ROLLBACK
END
```
