先是用散列函数来检查重复,若冲突,则再用KMP算法来验证祖先,
散列函数是用字母与其连续出现次数决定的素数和相邻不同字母决定的素数之积模大素数得到,
最坏情况下是O(n * m ^ 2)的复杂度,但几乎不可能出现,一般情况下能够符合题目要求.
