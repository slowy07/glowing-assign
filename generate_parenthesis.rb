def generate_parenthesis(n)
    parenthesis = []
    backtrack(parenthesis, '', 0, 0, n)
    parenthesis
end

def backtrack(parenthesis, curr, open, close, max)
    if curr.length == max * 2
        parenthesis.push(curr)
        return
    end

    backtrack(parenthesis, curr + '(', open + 1, close, max) if open < max
    backtrack(parenthesis, curr + ')', open, close + 1, max) if close < open
end

n = 3
print(generate_parenthesis(n))
n = 1
print(generate_parenthesis(n))
