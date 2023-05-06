SELECT stock_name,
    SUM(CASE
            WHEN operation='Buy' THEN -price
            WHEN operation='Sell' THEN price
        End) AS capital_gain_loss
FROM Stocks
GROUP BY stock_name 
