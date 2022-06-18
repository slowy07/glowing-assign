describe("Median heap", function()
    local median_heap = require("ds.median_heap")
    local heap = median_heap.new()
    for i = 1, 100 do
        heap:push(i)
    end
    assert.equal(50, heap:top())
end)
