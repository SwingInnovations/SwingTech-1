function update(self)
    local input = STGame:Get():getInput()
    local position = self:transform():getTranslate()
    local camForward = STGame:Get():getCamera():getForward()
    local oldX, oldZ = position:getX(), position:getZ()
    local fX, fZ = camForward:getX(), camForward:getZ()
    local delta = STGame:Get():getDelta()
    local speedFactor = self:getAttributef("speedFactor")

    if input:isKeyDown(KEY.KEY_L) then
        self:transform():setTranslateX(fX + oldX + (speedFactor * delta))
        self:transform():setTranslateZ(fZ + oldZ + (speedFactor * delta))
    elseif input:isKeyDown(KEY.KEY_J) then
        self:transform():setTranslateX(fX - oldX + (speedFactor * delta))
        self:transform():setTranslateZ(fZ - oldZ + (speedFactor * delta))
    elseif input:isKeyDown(KEY.KEY_I) then
        self:transform():setTranslateZ(oldZ + (speedFactor * delta))
    elseif input:isKeyDown(KEY.KEY_K) then
        self:transform():setTranslateZ(oldZ - (speedFactor * delta))
    end

end