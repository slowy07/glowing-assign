local heap = require("ds.heap")
local median_heap = {}

function median_heap.less_than(a, b)
    return a < b
end

function median_heap.new(less_than)
    local self
	self = {
		less_than = less_than,
		lower_half = heap.new(function(a, b)
			return self.less_than(b, a)
		end),
		upper_half = heap.new(function(a, b)
			return self.less_than(a, b)
		end),
	}
	return self
end

function median_heap:empty()
    return self.lower_half:empty()
end

function median_heap:size()
    return #self.lower_half + #self.upper_half
end

function median_heap:top()
    return self.lower_half:top()
end

function median_heap:pop()
    local value = self.lower_half:pop()
    if #self.lower_half < #self.upper_half then
        self.lower_half:push(self.upper_half:pop())
    end
    return value
end

function median_heap:push(value)
    if self:empty() then
        self.lower_half:push(value)
    elseif self.less_than(value, self:top()) then
        self.lower_half:push(value)
        if #self.lower_half - #self.upper_half > 1 then
            self.upper_half:push(self.lower_half:pop())
        end
    else
        self.upper_half:push(value)
        if #self.lower_half < #self.upper_half then
            self.lower_half:push(self.upper_half:pop())
        end
    end
end

return require("class")(median_heap)
