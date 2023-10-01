SELECT U.name AS `name` , SUM(T.amount) AS `balance`
FROM `Users` AS `U`
    JOIN `Transactions` AS `T` ON U.account = T.account
GROUP BY T.account
HAVING `balance` > 10000
