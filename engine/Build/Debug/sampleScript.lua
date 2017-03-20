counter = 0
dir = 1;

--@param game - Access to all STGame functions
function update(self, game)
    input = game:getInput()
    cursorBound = input:isCursorBound()
    if input:isKeyPressed(KEY.KEY_E) then
        dir = dir * -1
    end

--    if input:isKeyPressed(KEY.KEY_Q) then
--        input:setCursorVisible(cursorBound)
--        input:setCursorBound(not cursorBound)
--    end

    if self ~= nil then
        self:setRotateY(counter * 0.5);
        counter = counter + 1 * dir
    end

    self:setShdrUniformi("counter", counter);

end

