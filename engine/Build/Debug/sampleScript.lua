counter = 0
dir = 1;
--@param game - Access to all STGame functions
function update(game)
    input = game:getInput()
    if input:isKeyPressed(0x08) then
        dir = dir * -1
    end

    if self ~= nil then
        self:getTransform():setRotateY(counter * 0.5);
        counter = counter + 1 * dir
    end
end

