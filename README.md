For details, read [my article](https://medium.com/mirkat-x-blog/implement-quine-mccluskey-algorithm-and-petricks-method-in-c-40168163474).

# Method

Two Steps:

step 1. Find out all the prime implicants of the boolean function (Quine-McCluskey Algorithm).

step 2. Determine all minimum sum-of-products solutions from prime implicant chart (Petrick's Method).

# Note on my Petrick's Method

There are three rules for simplifying Sum of Product (SOP):

1. X + X = X

2. XX = X

3. X + XY = X

For X + X = X, I checked this rule in Petrick_Method::Expension, and if I find that it has already appeared, I won't add it to the SOP.

For XX = X, I used the characteristics of the container set and use vector< set<string> > to store the SOP, which can be simply simplified.

For X + XY = X, I adopted a non-processing principle. The purpose of this code is to find the minimum cover of a boolean function by using its prime implicants, not the most condensed expression of a boolean function, so I did not do anything with this rule.

According to the above three rules and corresponding processing guidelines, in the final SOP formulas obtained, the product with the least number of clauses is the minimum cover.

---

詳細解說請見[我的網站](https://medium.com/mirkat-x-blog/implement-quine-mccluskey-algorithm-and-petricks-method-in-c-40168163474)

# Method

總共兩步驟：

1. 找出布林函數的所有 prime implicants（Quine-McCluskey Algorithm）。

2. 使用 prime implicants 來找出 minimum cover（Petrick’s Method）。

# Note

簡化 Sum of Product(SOP) 有三大規則：
1. X + X = X
2. XX = X
3. X + XY = X

對於 X + X = X，我在 Petrick_Method::Expension 中做檢查，如果發現已經出現過，便不會將其加入 SOP 中。

對於 XX = X，我則利用容器 set 的特性，使用 vector< set<string> > 來儲存 SOP，即可簡化。

對於 X + XY = X，我則採取不處理的原則。此份程式碼的目的是尋找布林函數使用 prime implicant 來表達的 minimum cover，並非布林函數的最精簡表示式，因此我並沒有對這個規則做任何處理。

依照上述三個規則以及對應的處理方針，在最終獲得的 SOP 式子中，擁有 clauses 數量最少的 product 即是 minimum cover。
