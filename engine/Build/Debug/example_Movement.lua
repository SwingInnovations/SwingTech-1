-- This is an example script to demonstrate user-controlled movement.
function update(self)
    local input = STGame:Get():getInput();
    local position = self:transform():getTranslate();
    local oldX = position:getX();
    local oldZ = position:getZ();
    local delta = STGame:Get():getDelta();
    local speedFactor = 0.025;
    if input:isKeyDown(KEY.KEY_L) then
        self:transform():setTranslateX(oldX + (speedFactor * delta));
    elseif input:isKeyDown(KEY.KEY_J) then
        self:transform():setTranslateX(oldX - (speedFactor * delta));
    elseif input:isKeyDown(KEY.KEY_I) then
        self:transform():setTranslateZ(oldZ + (speedFactor * delta));
    elseif input:isKeyDown(KEY.KEY_K) then
        self:transform():setTranslateZ(oldZ - (speedFactor * delta));
    end

    if input:isKeyPressed(KEY.KEY_F) then
        Foo()
    end
end

function OnStrike(self, other)
    print("Striked!");
end