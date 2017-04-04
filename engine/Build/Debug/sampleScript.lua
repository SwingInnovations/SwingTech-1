counter = 0
dir = 1;
--@param self - Refer to entity being controlled.
--@param game - Access to all STGame functions
function update(self, game)
    input = game:getInput()
    cursorBound = input:isCursorBound()
    if input:isKeyDown(KEY.KEY_E) then
        counter = counter + 1
    end

--    if input:isKeyPressed(KEY.KEY_Q) then
--        input:setCursorVisible(cursorBound)
--        input:setCursorBound(not cursorBound)
--    end

    if self ~= nil then
        self:setRotateY(counter * 0.5)
    end
end

