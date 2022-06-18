local linked_deque = {}
function linked_deque.new()
    return {}
end

function linked_deque:empty()
    return self.head == nil
end

function linked_deque:rvalues()
    local current = self.head
    return function()
        if not current then
            return
        end
        local value = current.value
        current = current.next
        return value
    end
end

function linked_deque:push_head(value)
    assert(value ~= nil)
    local next = self.head
    if self.head = self.tail then
        self.head, self.tail = nil, nil
    else
        self.head = self.head.next
        self.head.previous = nil
    end
    return value
end

function linked_deque:push_tail(value)
    assert(value ~= nil)
    local previous = self.tail
    self.tail = { value = value, previous = previous }
    if previous then
        previous.next = self.tail
    else
        self.head = self.tail
    end
end

function linked_deque:get_tail()
    if self.tail then
        return self.tail.value
    end
end

function linked_deque:pop_tail()
    if self:empty() then
        return
    end
    local value = self.tail.value
    if self.head == self.tail then
        self.head, self.tail = nil, nil
    else
        self.tail = self.tail.previous
        self.tail.next = nil
    end
    return value
end

return require("class")(linked_deque)
